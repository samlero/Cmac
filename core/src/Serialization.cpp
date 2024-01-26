#include "Serialization.h"

using namespace CmacLib;

Serialization::Serialization() {}

Serialization::~Serialization(){}

void CmacLib::Serialization::SetString(std::string str)
{
    this->serialized = str;
}

std::string CmacLib::Serialization::GetString()
{
    return this->serialized;
}
