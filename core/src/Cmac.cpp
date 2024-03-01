#include "cmaclib/Cmac.h"

#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <utility>
#include <ios>
#include "cmaclib/Result.h"
#include "cmaclib/Prediction.h"
#include "cmaclib/Adjustment.h"
#include "cmaclib/CmacTagger.h"
#include "cmaclib/Serialization.h"

using namespace CmacLib;

std::vector<double> Cmac::Normalize(const std::vector<double>& raw)
{
	std::vector<double> result;
    result.reserve(raw.size());

    for (size_t i = 0; i < raw.size(); i++) {
        double value = (raw[i] - lower[i]) / denominator[i];
        value = std::max(0.0, std::min(value, 1.0));
        result.emplace_back(value);
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

std::unique_ptr<IPrediction> Cmac::Predict(const std::vector<double>& input)
{
	std::unique_ptr<Prediction> prediction = ::std::make_unique<Prediction>();

	try
	{	
		if (input.size() != this->upper.size())
		{
			prediction->SetIsSuccessful(false);
			prediction->SetMessage("Incorrect input size.");
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
					prediction->SetIsSuccessful(false);
					prediction->SetMessage("Hash location/index is greater than the size of the hashtable.");
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
		prediction->SetActiveWeightIndices(::std::move(indices));
		prediction->SetActiveWeights(::std::move(weights));
		prediction->SetBasisValues(::std::move(gammas));
		prediction->SetValues(::std::move(values));
		prediction->SetIsSuccessful(true);
	}
	catch (const std::exception& ex) 
	{
		prediction->SetIsSuccessful(false);
		prediction->SetMessage("An exception occured at Predict. " + std::string(ex.what()));
	}

	return prediction;
}

std::unique_ptr<IAdjustment> Cmac::Adjust(const std::vector<double>& correction, IPrediction* const prediction, double damping)
{
	std::unique_ptr<Adjustment> adjustment = ::std::make_unique<Adjustment>();
	try
	{
		// check output and correction are the same size
		if (correction.size() != this->numOutput)
		{
			adjustment->SetIsSuccessful(false);
			adjustment->SetMessage("Correction should be the same size as the number of outputs.");
			return adjustment;
		}

		// extract prediction variables
		std::vector<double> gammas = prediction->GetBasisValues();
		std::vector<std::vector<double>> weights = prediction->GetActiveWeights();
		std::vector<unsigned int> indices = prediction->GetActiveWeightIndices();

		// check weight indices same as the number of layers
		if (indices.size() != this->numLayers)
		{
			adjustment->SetIsSuccessful(false);
			adjustment->SetMessage("Size of active weight indices do not match the number of layers.");
			return adjustment;
		}

		// check basis values
		if (gammas.size() != this->numLayers)
		{
			adjustment->SetIsSuccessful(false);
			adjustment->SetMessage("Size of basis values do not match the number of layers.");
			return adjustment;
		}

		// check output size of the active weights matrix
		if (weights.size() != this->numOutput)
		{
			adjustment->SetIsSuccessful(false);
			adjustment->SetMessage("First size of the active weights matrix does not match the number of outputs.");
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
				adjustment->SetIsSuccessful(false);
				adjustment->SetMessage("Sub-array of the active weights do not match the number of layers.");
				return adjustment;
			}

			for (size_t layer = 0; layer < this->numLayers; layer++)
			{
				dw[out][layer] = (this->beta) * (gammas[layer]*correction[out] - (this->nu)*damping* weights[out][layer]);
				this->memory[out][indices[layer]] += dw[out][layer];
			}
		}

		// collect all the results
		adjustment->SetWeightChanges(::std::move(dw));
		adjustment->SetIsSuccessful(true);
	}
	catch (const std::exception& ex)
	{
		adjustment->SetIsSuccessful(false);
		adjustment->SetMessage("An exception occured at Predict. " + std::string(ex.what()));
	}
	return adjustment;
}

std::unique_ptr<IResult> Cmac::Zeroize()
{
	std::unique_ptr<Result> result(std::make_unique<Result>());
	try
	{
		for(size_t i = 0; i < this->memory.size(); i++)
		{
			for(size_t j = 0; j < this->memory[i].size(); j++)
			{
				this->memory[i][j] = 0.0;
			}
		}
		result->SetIsSuccessful(true);
	}	
	catch(const std::exception& ex)
	{
		result->SetIsSuccessful(false);
		result->SetMessage(ex.what());
	}
	return result;
}

std::unique_ptr<ISerialization> Cmac::Serialize()
{
	std::unique_ptr<Serialization> serialization(std::make_unique<Serialization>());
	try
	{		
		// create tagger
		std::unique_ptr<CmacTagger> tagger(std::make_unique<CmacTagger>());
		std::string result;
		// integer types
		result += tagger->Entry(std::to_string(this->numQ), CmacTagger::NUM_Q);
		result += tagger->Entry(std::to_string(this->numLayers), CmacTagger::NUM_LAYERS);
		result += tagger->Entry(std::to_string(this->maxMem), CmacTagger::MAX_MEMORY);
		result += tagger->Entry(std::to_string(this->maxHashValue), CmacTagger::MAX_HASH_VALUE);
		result += tagger->Entry(std::to_string(this->numOutput), CmacTagger::NUM_OUTPUTS);
		result += tagger->Entry(std::to_string(this->numInput), CmacTagger::NUM_INPUTS);
		// double types
		result += tagger->Entry(tagger->ToString(this->beta), CmacTagger::BETA);
		result += tagger->Entry(tagger->ToString(this->nu), CmacTagger::NU);
		// hashtable
		result += tagger->Entry(tagger->ToString(this->hashtable), CmacTagger::HASHTABLE);
		// vector doubles
		result += tagger->Entry(tagger->ToString(this->upper), CmacTagger::UPPER_LIMITS);
		result += tagger->Entry(tagger->ToString(this->lower), CmacTagger::LOWER_LIMITS);
		result += tagger->Entry(tagger->ToString(this->denominator), CmacTagger::DENOMINATOR);
		// memory
		result += tagger->Entry(tagger->ToString(this->memory), CmacTagger::MEMORY);
		// offsets
		result += tagger->Entry(tagger->ToString(this->offsets), CmacTagger::OFFSETS);
		// wrap the entire content inside the root
		result = tagger->StartTag(CmacTagger::ROOT) 
			+ "\n" + result + tagger->EndTag(CmacTagger::ROOT);

		serialization->SetString(std::move(result));
		serialization->SetIsSuccessful(true);
	}
	catch(const std::exception& ex)
	{
		serialization->SetIsSuccessful(false);
		serialization->SetMessage(ex.what());
	}
	return serialization;
}

std::unique_ptr<IResult> Cmac::Deserialize(std::string&& content)
{
	std::unique_ptr<Result> result(std::make_unique<Result>());
	try
	{
		result->SetIsSuccessful(false);

		// create helper
		std::unique_ptr<CmacTagger> tagger(std::make_unique<CmacTagger>());
		
		// unsigned ints
		this->numQ = tagger->GetUnsignedInt(content, CmacTagger::NUM_Q);
		this->numLayers = tagger->GetUnsignedInt(content, CmacTagger::NUM_LAYERS);
		this->maxMem = tagger->GetUnsignedInt(content, CmacTagger::MAX_MEMORY);
		this->maxHashValue = tagger->GetUnsignedInt(content, CmacTagger::MAX_HASH_VALUE);
		this->numOutput = tagger->GetUnsignedInt(content, CmacTagger::NUM_OUTPUTS);
		this->numInput = tagger->GetUnsignedInt(content, CmacTagger::NUM_INPUTS);
		// doubles
		this->beta = tagger->GetDouble(content, CmacTagger::BETA);
		this->nu = tagger->GetDouble(content, CmacTagger::NU);
		// array unsigned ints
		this->hashtable = tagger->GetUnsignedInts(content, CmacTagger::HASHTABLE);
		// array doubles
		this->denominator = tagger->GetDoubles(content, CmacTagger::DENOMINATOR);
		this->upper = tagger->GetDoubles(content, CmacTagger::UPPER_LIMITS);
		this->lower = tagger->GetDoubles(content, CmacTagger::LOWER_LIMITS);
		// matrix doubles
		this->offsets = tagger->GetMatrixDoubles(content, CmacTagger::OFFSETS);
		this->memory = tagger->GetMatrixDoubles(content, CmacTagger::MEMORY);
		
		result->SetIsSuccessful(true);
	}
	catch(const std::exception& ex)
	{
		result->SetMessage(ex.what());
	}
	return result;
}

std::string Cmac::GetExtension()
{
    return "cmac";
}

/// @brief Acquires active weights and associated basis values,
/// then multiply and sum to produce an output.
/// @param pCmac The pointer to the cmac instance.
/// @param inputData States. (array pointer)
/// @param inputSize States. (array size)
/// @return Prediction result.
CCmacLibIPrediction* CCmacLibICmacPredict(
	CCmacLibICmac* pCmac, double* inputData, unsigned long inputSize
) {
	return pCmac->Predict(
		::std::vector<double>(inputData, inputData + inputSize)
	).release();
}

/// @brief Train the weights of the Cmac.
/// @param pCmac The pointer to the cmac instance.
/// @param correctionData Error of the prediction. (array pointer)
/// @param correctionSize Error of the prediction. (array size)
/// @param pPrediction Contains indices of weights and basis values.
/// @param damping Additional damping to further reduce chances of overfitting.
/// @return Adjustment result.
CCmacLibIAdjustment* CCmacLibICmacAdjust(
	CCmacLibICmac* pCmac, double* correctionData, unsigned long correctionSize,
	CCmacLibIPrediction* pPrediction, double damping
) {
	return pCmac->Adjust(
		::std::vector<double>(correctionData, correctionData + correctionSize),
		pPrediction, damping
	).release();
}

/// @brief Sets all the weights in memory to zero, untraining the Cmac.
/// @param pCmac The pointer to the cmac instance.
/// @return Result of the operation.
CCmacLibIResult* CCmacLibICmacZeroize(
	CCmacLibICmac* pCmac
) {
	return pCmac->Zeroize().release();
}

/// @brief Serializes the object in its own unique format.
/// @param pCmac The pointer to the cmac instance.
/// @return Serialized string.
CCmacLibISerialization* CCmacLibICmacSerialize(
	CCmacLibICmac* pCmac
) {
	return pCmac->Serialize().release();
}

/// @brief Deserializes the content into its member variables.
/// @param pCmac The pointer to the cmac instance.
/// @param content Valid deserializable content.
CCmacLibIResult* CCmacLibICmacDeserialize(
	CCmacLibICmac* pCmac, const char* content
) {
	return pCmac->Deserialize(content).release();
}

/// @param pCmac The pointer to the cmac instance.
/// @return The extension of the serializable object
const char* CCmacLibICmacGetExtension(
	CCmacLibICmac* pCmac
) {
	return pCmac->GetExtension().c_str();
}

/// @brief Destructor.
/// @param pCmac The pointer to the cmac instance.
void CCmacLibICmacDestroy(
	CCmacLibICmac* pCmac
) {
	if (pCmac) delete pCmac;
}