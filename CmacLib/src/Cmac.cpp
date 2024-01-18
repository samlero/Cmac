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
	size_t maxHashValue = 0;
	for (unsigned int i = 0; i < hashsize; i++) 
	{
		size_t index = std::rand() % maxmem;
		this->hashtable[i] = index;
		if (maxHashValue < index) 
		{
			maxHashValue = index;
		}
	}

	// instantiate memory
	this->memory = std::vector<std::vector<double>>(numOut
		, std::vector<double>(maxHashValue, 0.0));
}

Cmac::~Cmac(){}

std::unique_ptr<IPrediction> Cmac::Predict(std::vector<double>& input)
{
	std::unique_ptr<IPrediction> prediction;

	try
	{
		std::vector<double> normalized = Normalize(input);


	}
	catch (std::exception ex) 
	{
		std::unique_ptr<Result> result = std::make_unique<Result>();
		result->SetIsSuccessful(false);
		result->SetMessage("An exception occured at Predict. " + std::string(ex.what()));
		prediction = std::make_unique<Prediction>(result.release());
	}

	return prediction;
}




