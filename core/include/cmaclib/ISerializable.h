#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <cmaclib/defines.h>
#include <cmaclib/ISerialization.h>

// Begin C++ Only Region.
#if defined(__cplusplus)
#include <memory>
#include <string>

namespace CmacLib
{
    /// @brief Serializes and deserializes
    class CMACLIB_SHARED_SYMBOL ISerializable{
    public:
        /// @brief Serializes the object in its own unique format.
        /// @return Serialized string.
        virtual std::unique_ptr<ISerialization> Serialize() = 0;

        /// @brief Deserializes the content into its member variables.
        /// @param content Valid deserializable content.
        virtual std::unique_ptr<IResult> Deserialize(std::string&& content) = 0;

        /// @brief Extension of the serializable object
        /// @return 
        virtual std::string GetExtension() = 0;

        virtual ~ISerializable(){}
    };
}
#endif
// End C++ Only Region.

// CCmacLibISerializable Definition.
#if defined(__cplusplus)
/// @brief Serializes and deserializes.
typedef CmacLib::ISerializable CCmacLibISerializable;
#else
/// @brief Serializes and deserializes.
typedef struct CCmacLibISerializable CCmacLibISerializable;
#endif
// END CCmacLibISerializable Definition.

// C Wrappers.
#if defined(__cplusplus)
extern "C" {
#endif

/// @brief Serializes the object in its own unique format.
/// @param pSerializable The pointer to the serializable instance.
/// @return Serialized string.
CMACLIB_SHARED_SYMBOL CCmacLibISerialization* CCmacLibISerializableSerialize(
    CCmacLibISerializable* pSerializable
);

/// @brief Deserializes the content into its member variables.
/// @param pSerializable The pointer to the serializable instance.
/// @param content Valid deserializable content.
CMACLIB_SHARED_SYMBOL CCmacLibIResult* CCmacLibISerializableDeserialize(
    CCmacLibISerializable* pSerializable, const char* content
);

/// @return The extension of the serializable object
/// @param pSerializable The pointer to the serializable instance.
CMACLIB_SHARED_SYMBOL const char* CCmacLibISerializableGetExtension(
    CCmacLibISerializable* pSerializable
);

/// @brief Destructor.
/// @param pSerializable The pointer to the serializable instance.
CMACLIB_SHARED_SYMBOL void CCmacLibISerializableDestroy(
    CCmacLibISerializable* pSerializable
);

#if defined(__cplusplus)
}
#endif
// END C Wrappers.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.