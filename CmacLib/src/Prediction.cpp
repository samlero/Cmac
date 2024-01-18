#include "Prediction.h"

Prediction::Prediction(std::vector<double>& values
	, std::vector<std::vector<unsigned int>>& weightIndices
	, std::vector<std::vector<double>>& weightValues
	, std::vector<double>& basis
	, IResult* result)
	: values(values)
	, activeWeightIndices(weightIndices)
	, activeWeights(weightValues) 
	, basisValues(basis)
{
	this->result.reset(result);
}

Prediction::~Prediction()
{
	this->result.reset();
}

const std::vector<double>& Prediction::GetValues()
{
	return this->values;
}

const std::vector<std::vector<unsigned int>>& Prediction::GetActiveWeightIndices()
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

const IResult& Prediction::GetResult()
{
	return *(this->result);
}
