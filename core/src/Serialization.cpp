#include "Serialization.h"

using namespace CmacLib;

Serialization::Serialization(std::string data) : serialized(data){}

Serialization::~Serialization(){}

std::string CmacLib::Serialization::GetString()
{
    return this->serialized;
}
