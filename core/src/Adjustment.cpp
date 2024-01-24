#include "Adjustment.h"
#include "Result.h"
#include <utility>

using namespace CmacLib;

void Adjustment::SetWeightChanges(std::vector<std::vector<double>>&& dw)
{
	this->weightChanges = ::std::move(dw);
}

void Adjustment::SetResult(IResult* result)
{
	this->result.reset(result);
}

Adjustment::Adjustment()
	: weightChanges(std::vector<std::vector<double>>())
	, result(std::make_unique<Result>()){}

Adjustment::~Adjustment()
{
	this->result.reset();
}

const std::vector<std::vector<double>>& Adjustment::GetWeightChanges()
{
	return this->weightChanges;
}

IResult* const Adjustment::GetResult()
{
	return this->result.get();
}