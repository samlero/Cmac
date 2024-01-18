#include "Adjustment.h"

Adjustment::Adjustment(std::vector<std::vector<double>>& dw
	, IResult* result)
	: weightChanges(weightChanges)
{
	this->result.reset(result);
}

Adjustment::~Adjustment()
{
	this->result.reset();
}

const std::vector<std::vector<double>>& Adjustment::GetWeightChanges()
{
	return this->weightChanges;
}

const IResult& Adjustment::GetResult()
{
	return *(this->result);
}


