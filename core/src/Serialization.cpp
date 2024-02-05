#include "Serialization.h"

#include <utility>

using namespace CmacLib;

Serialization::Serialization() {}

Serialization::~Serialization(){}

void CmacLib::Serialization::SetString(const std::string& str) {
    serialized = str;
}

void CmacLib::Serialization::SetString(std::string&& str)
{
    this->serialized = std::move(str);
}

std::string CmacLib::Serialization::GetString()
{
    return this->serialized;
}
