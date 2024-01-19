#include "Cmac.h"
#include <stdexcept>
#include <cstdlib>

#include "Result.h"
#include "Prediction.h"


std::vector<double> Cmac::Normalize(std::vector<double>& raw)
{
	std::vector<double> result(raw.size(), 0.0);
	for (size_t i = 0; i < raw.size(); i++) 
	{
		result[i] = (raw[i] - this->lower[i]) / this->denominator[i];
	}
	return result;
}

Cmac::Cmac(unsigned int numQ
	, unsigned int numLayers
	, unsigned int maxmem
	, unsigned int numOut
	, std::vector<double> upper
	, std::vector<double> lower
	, double beta, double nu)
	: numQ(numQ), numLayers(numLayers)
	, maxMem(maxmem)
	, numOutput(numOut)
	, numInput(upper.size())
	, upper(upper), lower(lower)
	, beta(beta), nu(nu)
{
	// check limit sizes are the same
	if (upper.size() != lower.size()) 
	{
		throw std::invalid_argument("Upper and lower limits must be of the same size.");
	}

	// check each element of the limits to see if the upper is higher than the lower
	// And might as well initialize the denominator
	this->denominator = std::vector<double>(upper.size());
	for (size_t i = 0; i < upper.size(); i++) 
	{
		if (upper[i] < lower[i]) 
		{
			throw std::invalid_argument("Ensure that the each upper limit element is larger than the lower limit element.");
		}

		this->denominator[i] = upper[i] - lower[i];
	}

	// create hashtable
	unsigned int hashsize = upper.size() * numLayers * numQ + numQ * numLayers + numQ;
	this->hashtable = std::vector<size_t>(hashsize);
	this->maxHashValue = 0;
	for (unsigned int i = 0; i < hashsize; i++) 
	{
		size_t index = std::rand() % maxmem;
		this->hashtable[i] = index;
		if (this->maxHashValue < index)
		{
			this->maxHashValue = index;
		}
	}

	// instantiate memory
	this->memory = std::vector<std::vector<double>>(numOut
		, std::vector<double>(maxHashValue, 0.0));

	// create offsets
	this->offsets = std::vector<std::vector<double>>(numLayers
		, std::vector<double>(upper.size(), 0.0));
	for (size_t layer = 0; layer < numLayers; layer++) 
	{
		for (size_t input = 0; input < upper.size(); input++)
		{
			this->offsets[layer][input] = ((double)rand()) / ((double)RAND_MAX);
		}
	}
}

Cmac::~Cmac(){}

std::unique_ptr<IPrediction> Cmac::Predict(std::vector<double>& input)
{
	std::unique_ptr<Prediction> prediction(new Prediction());

	try
	{	
		if (input.size() != this->upper.size())
		{
			std::unique_ptr<Result> result = std::make_unique<Result>();
			result->SetIsSuccessful(false);
			result->SetMessage("Incorrect input size.");
			prediction->SetResult(result.release());
			return prediction;
		}

		std::vector<double> normalized = Normalize(input);

		// get basis and hash indices
		std::vector<double> gammas(this->numLayers, 0.0);
		std::vector<size_t> indices(this->numLayers, 0);
		for (size_t i = 0; i < gammas.size(); i++)
		{
			double location = 0.0;
			for (size_t j = 0; j < normalized.size(); j++)
			{
				double place = normalized[j] * (((double)(this->numQ)) 
					- 1.0) + (this->offsets[i][j]);
				size_t cell = (size_t)place;
				double h = place - (double)cell;

				// calculate basis function value
				double fspline = 16.0 * (h*h - 2.0 * h*h*h + h*h*h*h);
				gammas[i] += (fspline/((double)input.size()));

				// calculate hash 
				size_t loc = cell + this->numQ * i + this->numQ * this->numLayers * j;
				location += (double)(this->hashtable[loc]);
			}
			indices[i] = (size_t)(fmod(location, (double)(this->maxHashValue)));
		}

		// get weights and add up for the output values
		std::vector<std::vector<double>> weights(this->numOutput
			, std::vector<double>(this->numLayers, 0.0));
		std::vector<double> values(this->numOutput, 0.0);
		for (size_t output = 0; output < this->numOutput; output++)
		{
			for (size_t layer = 0; layer < this->numLayers; layer++)
			{
				weights[output][layer] = this->memory[output][indices[layer]];

				values[output] += weights[output][layer] * gammas[layer];
			}
		}

		// fill in prediction/results
		prediction->SetActiveWeightIndices(indices);
		prediction->SetActiveWeights(weights);
		prediction->SetBasisValues(gammas);
		prediction->SetValues(values);
		std::unique_ptr<Result> result = std::make_unique<Result>();
		result->SetIsSuccessful(true);
		prediction->SetResult(result.release());
	}
	catch (std::exception ex) 
	{
		std::unique_ptr<Result> result = std::make_unique<Result>();
		result->SetIsSuccessful(false);
		result->SetMessage("An exception occured at Predict. " + std::string(ex.what()));
		prediction->SetResult(result.release());
	}

	return prediction;
}




