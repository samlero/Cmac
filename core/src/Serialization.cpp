#include "cmaclib/Serialization.h"

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

/// @brief The string from the resulting serialization process.
/// @return serialized string
const char* CCmacLibISerializationGetString(CCmacLibISerialization* pSerialization) {
    return pSerialization->GetString().c_str();
}

/// @brief Indicates if an operation was successful.
/// @return Success.
cmaclib_bool_t CCmacLibISerializationIsSuccessful(
    CCmacLibISerialization* pSerialization
) {
    return pSerialization->IsSuccessful();
}

/// @brief If not successful, a failure message is provided.
const char* CCmacLibISerializationGetMessage(
    CCmacLibISerialization* pSerialization
) {
    return pSerialization->GetMessage().c_str();
}

/// @brief Destructor.
void CCmacLibISerializationDestroy(CCmacLibISerialization** ppSerialization) {
    if (*ppSerialization) {
        delete *ppSerialization;
        *ppSerialization = nullptr;
    }
}