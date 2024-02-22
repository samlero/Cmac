#include "cmaclib/Prediction.h"

#include <cmaclib/Result.h>
#include <utility>

using namespace CmacLib;

void Prediction::SetValues(std::vector<double>&& values)
{
	this->values = ::std::move(values);
}

void Prediction::SetActiveWeightIndices(std::vector<unsigned int>&& activeWeightIndices)
{
	this->activeWeightIndices = ::std::move(activeWeightIndices);
}

void Prediction::SetActiveWeights(std::vector<std::vector<double>>&& weights)
{
	this->activeWeights = ::std::move(weights);
}

void Prediction::SetBasisValues(std::vector<double>&& basis)
{
	this->basisValues = ::std::move(basis);
}

Prediction::Prediction()
	: values(std::vector<double>())
	, activeWeightIndices(std::vector<unsigned int>())
	, activeWeights(std::vector<std::vector<double>>())
	, basisValues(std::vector<double>()){}

Prediction::~Prediction(){}

const std::vector<double>& Prediction::GetValues()
{
	return this->values;
}

const std::vector<unsigned int>& Prediction::GetActiveWeightIndices()
{
	return this->activeWeightIndices;
}

const std::vector<std::vector<double>>& Prediction::GetActiveWeights()
{
	return this->activeWeights;
}

const std::vector<double>& Prediction::GetBasisValues()
{
	return this->basisValues;
}

/// @brief Get the calculated multiplication and accumulation
/// of basis and active weights.
/// @param pPrediction The pointer to the prediction instance.
/// @return Cmac output.
const double* CCmacLibIPredictionGetValues(
	CCmacLibIPrediction* pPrediction
) {
	return pPrediction->GetValues().data();
}

/// @brief Get the indices of the active weights.
/// @param pPrediction The pointer to the prediction instance.
/// @return Active weight indices.
const unsigned int* CCmacLibIPredictionGetActiveWeightIndices(
	CCmacLibIPrediction* pPrediction
) {
	return pPrediction->GetActiveWeightIndices().data();
}

/// @brief Get the values of the active weights.
/// (DO NOT FORGET TO DELETE THE RETURNED POINTER AFTER USAGE.)
/// @param pPrediction The pointer to the prediction instance.
/// @return Active weight values.
double** CCmacLibIPredictionGetActiveWeights(
	CCmacLibIPrediction* pPrediction
) {
	/// @brief The container for the active weights 2-D array.
	double** matrix = new double*[pPrediction->GetActiveWeights().size()];

	for (unsigned int i = 0; i < pPrediction->GetActiveWeights().size(); i++) {
		matrix[i] = (double*) pPrediction->GetActiveWeights().data()->data();
	}

	return matrix;
}

/// @brief Get the basis function values.
/// @param pPrediction The pointer to the prediction instance.
/// @return Basis function values.
const double* CCmacLibIPredictionGetBasisValues(
	CCmacLibIPrediction* pPrediction
) {
	return pPrediction->GetBasisValues().data();
}

/// @brief Indicates if an operation was successful.
/// @param pPrediction The pointer to the prediction instance.
/// @return Success.
cmaclib_bool_t CCmacLibIPredictionIsSuccessful(
	CCmacLibIPrediction* pPrediction
) {
	return pPrediction->IsSuccessful();
}

/// @brief If not successful, a failure message is provided.
/// @param pPrediction The pointer to the prediction instance.
const char* CCmacLibIPredictionGetMessage(
	CCmacLibIPrediction* pPrediction
) {
	return pPrediction->GetMessage().c_str();
}

/// @brief Destructor.
/// @param ppPrediction The pointer to the pointer to the prediction instance.
void CCmacLibIPredictionDestroy(
	CCmacLibIPrediction** ppPrediction
) {
	if (*ppPrediction) {
		delete *ppPrediction;
		*ppPrediction = nullptr;
	}
}