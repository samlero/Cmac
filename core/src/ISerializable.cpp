#include "cmaclib/ISerializable.h"

/// @brief Serializes the object in its own unique format.
/// @param pSerializable The pointer to the serializable instance.
/// @return Serialized string.
CCmacLibISerialization* CCmacLibISerializableSerialize(
    CCmacLibISerializable* pSerializable
) {
    return pSerializable->Serialize().release();
}

/// @brief Deserializes the content into its member variables.
/// @param pSerializable The pointer to the serializable instance.
/// @param content Valid deserializable content.
CCmacLibIResult* CCmacLibISerializableDeserialize(
    CCmacLibISerializable* pSerializable, const char* content
) {
    return pSerializable->Deserialize(content).release();
}

/// @param pSerializable The pointer to the serializable instance.
/// @return The extension of the serializable object
const char* CCmacLibISerializableGetExtension(
    CCmacLibISerializable* pSerializable
) {
    return pSerializable->GetExtension().c_str();
}

/// @brief Destructor.
/// @param pSerializable The pointer to the serializable instance.
void CCmacLibISerializableDestroy(
    CCmacLibISerializable* pSerializable
) {
    if (pSerializable) delete pSerializable;
}