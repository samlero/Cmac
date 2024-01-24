#include "Cmac.h"
#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <utility>

#include "Result.h"
#include "Prediction.h"
#include "Adjustment.h"

using namespace CmacLib;

std::vector<double> Cmac::Normalize(std::vector<double>& raw)
{
	std::vector<double> result(raw.size(), 0.0);
	for (size_t i = 0; i < raw.size(); i++) 
	{
		result[i] = (raw[i] - this->lower[i]) / this->denominator[i];
		if(result[i] > 1.0) 
		{
			result[i] = 1.0;
		}
		if(result[i] < 0.0)
		{
			result[i] = 0.0;
		}
	}
	return result;
}

/// @brief Initialize the cmac instance.
void Cmac::Init() {
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
	unsigned int hashsize = ((unsigned int)upper.size()) * numLayers * numQ + numQ * numLayers + numQ;
	this->hashtable = std::vector<unsigned int>(hashsize);
	this->maxHashValue = 0;
	for (unsigned int i = 0; i < hashsize; i++) 
	{
		unsigned int index = std::rand() % maxMem;
		this->hashtable[i] = index;
		if (this->maxHashValue < index)
		{
			this->maxHashValue = index;
		}
	}

	// instantiate memory
	this->memory = std::vector<std::vector<double>>(numOutput
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

Cmac::Cmac(unsigned int numQ
	, unsigned int numLayers
	, unsigned int maxmem
	, unsigned int numOut
	, std::vector<double>&& upper
	, std::vector<double>&& lower
	, double beta, double nu)
	: numQ(numQ), numLayers(numLayers)
	, maxMem(maxmem)
	, numOutput(numOut)
	, numInput((unsigned int)upper.size())
	, upper(::std::move(upper)), lower(::std::move(lower))
	, beta(beta), nu(nu)
{
	Init();
}

Cmac::~Cmac(){}

std::unique_ptr<IPrediction> Cmac::Predict(std::vector<double>& input)
{
	std::unique_ptr<Prediction> prediction = ::std::make_unique<Prediction>();

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
		std::vector<unsigned int> indices(this->numLayers, 0);
		// get weights and add up for the output values
		std::vector<std::vector<double>> weights(this->numOutput
			, std::vector<double>(this->numLayers, 0.0));
		std::vector<double> values(this->numOutput, 0.0);
		for (size_t i = 0; i < gammas.size(); i++)
		{
			// acquire the location and find gamma
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
				if (loc > this->hashtable.size())
				{
					std::unique_ptr<Result> result = std::make_unique<Result>();
					result->SetIsSuccessful(false);
					result->SetMessage("Hash location/index is greater than the size of the hashtable.");
					prediction->SetResult(result.release());
				}
				location += (double)(this->hashtable[loc]);
			}
			indices[i] = (unsigned int)(std::fmod(location, (double)(this->maxHashValue)));

			// update the output
			for (size_t out = 0; out < this->numOutput; out++)
			{
				weights[out][i] = this->memory[out][indices[i]];
				values[out] += weights[out][i] * gammas[i];
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

std::unique_ptr<IAdjustment> Cmac::Adjust(std::vector<double>& correction, IPrediction* const prediction, double damping)
{
	std::unique_ptr<Adjustment> adjustment = ::std::make_unique<Adjustment>();
	try
	{
		// check output and correction are the same size
		if (correction.size() != this->numOutput)
		{
			std::unique_ptr<Result> result = std::make_unique<Result>();
			result->SetIsSuccessful(false);
			result->SetMessage("Correction should be the same size as the number of outputs.");
			adjustment->SetResult(result.release());
			return adjustment;
		}

		// extract prediction variables
		std::vector<double> gammas = prediction->GetBasisValues();
		std::vector<std::vector<double>> weights = prediction->GetActiveWeights();
		std::vector<unsigned int> indices = prediction->GetActiveWeightIndices();

		// check weight indices same as the number of layers
		if (indices.size() != this->numLayers)
		{
			std::unique_ptr<Result> result = std::make_unique<Result>();
			result->SetIsSuccessful(false);
			result->SetMessage("Size of active weight indices do not match the number of layers.");
			adjustment->SetResult(result.release());
			return adjustment;
		}

		// check basis values
		if (gammas.size() != this->numLayers)
		{
			std::unique_ptr<Result> result = std::make_unique<Result>();
			result->SetIsSuccessful(false);
			result->SetMessage("Size of basis values do not match the number of layers.");
			adjustment->SetResult(result.release());
			return adjustment;
		}

		// check output size of the active weights matrix
		if (weights.size() != this->numOutput)
		{
			std::unique_ptr<Result> result = std::make_unique<Result>();
			result->SetIsSuccessful(false);
			result->SetMessage("First size of the active weights matrix does not match the number of outputs.");
			adjustment->SetResult(result.release());
			return adjustment;
		}

		std::vector<std::vector<double>> dw(this->numOutput
			, std::vector<double>(this->numLayers, 0.0));
		// loop through and check the size of each sub-array of active weights matrix
		for (size_t out = 0; out < this->numOutput; out++)
		{
			// check sub-array if correct size
			if (weights[out].size() != this->numLayers)
			{
				std::unique_ptr<Result> result = std::make_unique<Result>();
				result->SetIsSuccessful(false);
				result->SetMessage("Sub-array of the active weights do not match the number of layers.");
				adjustment->SetResult(result.release());
				return adjustment;
			}

			for (size_t layer = 0; layer < this->numLayers; layer++)
			{
				dw[out][layer] = (this->beta) * (gammas[layer]*correction[out] - (this->nu)*damping* weights[out][layer]);
				this->memory[out][indices[layer]] += dw[out][layer];
			}
		}

		// collect all the results
		adjustment->SetWeightChanges(dw);
		std::unique_ptr<Result> result = std::make_unique<Result>();
		result->SetIsSuccessful(true);
		adjustment->SetResult(result.release());
	}
	catch (std::exception ex)
	{
		std::unique_ptr<Result> result = std::make_unique<Result>();
		result->SetIsSuccessful(false);
		result->SetMessage("An exception occured at Predict. " + std::string(ex.what()));
		adjustment->SetResult(result.release());
	}
	return adjustment;
}

std::unique_ptr<IResult> CmacLib::Cmac::Save(
	const std::string& directory, const std::string& filename
) {
	// Each member variable is its own Xml field.
	// Keep in mind that some vector member variables are 2D.
    throw std::runtime_error("Save NOT IMPLEMENTED.");
}