#include "cmaclib/Adjustment.h"

#include <cmaclib/Result.h>
#include <utility>

using namespace CmacLib;

void Adjustment::SetWeightChanges(std::vector<std::vector<double>>&& dw)
{
	this->weightChanges = ::std::move(dw);
}

Adjustment::Adjustment()
	: weightChanges(std::vector<std::vector<double>>()){}

Adjustment::~Adjustment(){}

const std::vector<std::vector<double>>& Adjustment::GetWeightChanges()
{
	return this->weightChanges;
}