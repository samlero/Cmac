#include "Prediction.h"
#include "Result.h"
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

void Prediction::SetResult(IResult* result)
{
	this->result.reset(result);
}

Prediction::Prediction()
	: values(std::vector<double>())
	, activeWeightIndices(std::vector<unsigned int>())
	, activeWeights(std::vector<std::vector<double>>())
	, basisValues(std::vector<double>())
	, result(std::make_unique<Result>()){}

Prediction::~Prediction()
{
	this->result.reset();
}

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

IResult* const Prediction::GetResult()
{
	return this->result.get();
}
