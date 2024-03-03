#ifndef ISERIALIZATION_H
#define ISERIALIZATION_H

#include <cmaclib/defines.h>
#include <cmaclib/IResult.h>

// Begin C++ Only Region.
#if defined(__cplusplus)
namespace CmacLib
{
    /// @brief The serialization output.
    class CMACLIB_SHARED_SYMBOL ISerialization : public virtual IResult
    {
    public:
        virtual ~ISerialization(){};

        /// @brief The string from the resulting serialization process.
        /// @return serialized string
        virtual std::string GetString() = 0;
    };
}
#endif
// End C++ Only Region.

// CCmacLibISerialization Definition.
#if defined(__cplusplus)
/// @brief The serialization output.
typedef CmacLib::ISerialization CCmacLibISerialization;
#else
/// @brief The serialization output.
typedef struct CCmacLibISerialization CCmacLibISerialization;
#endif
// END CCmacLibISerialization Definition.

// C Wrappers.
#if defined(__cplusplus)
extern "C" {
#endif

/// @brief The string from the resulting serialization process.
/// @param pSerialization The pointer to the serialization instance.
/// @return serialized string
CMACLIB_SHARED_SYMBOL const char* CCmacLibISerializationGetString(
    CCmacLibISerialization* pSerialization
);

/// @brief Indicates if an operation was successful.
/// @param pSerialization The pointer to the serialization instance.
/// @return Success.
CMACLIB_SHARED_SYMBOL cmaclib_bool_t CCmacLibISerializationIsSuccessful(
    CCmacLibISerialization* pSerialization
);

/// @brief If not successful, a failure message is provided.
/// @param pSerialization The pointer to the serialization instance.
CMACLIB_SHARED_SYMBOL const char* CCmacLibISerializationGetMessage(
    CCmacLibISerialization* pSerialization
);

/// @brief Destructor.
/// @param pSerialization The pointer to the serialization instance.
CMACLIB_SHARED_SYMBOL void CCmacLibISerializationDestroy(
    CCmacLibISerialization* pSerialization
);

#if defined(__cplusplus)
}
#endif
// END C Wrappers.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.