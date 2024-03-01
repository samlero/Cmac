#ifndef ISERIALIZATION_H
#define ISERIALIZATION_H

#include <cmaclib/defines.h>
#include <cmaclib/IResult.h>

// Begin C++ Only Region.
#if defined(__cplusplus)
namespace CmacLib
{
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
typedef CmacLib::ISerialization CCmacLibISerialization;
#else
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
const char* CMACLIB_SHARED_SYMBOL CCmacLibISerializationGetString(
    CCmacLibISerialization* pSerialization
);

/// @brief Indicates if an operation was successful.
/// @param pSerialization The pointer to the serialization instance.
/// @return Success.
cmaclib_bool_t CMACLIB_SHARED_SYMBOL CCmacLibISerializationIsSuccessful(
    CCmacLibISerialization* pSerialization
);

/// @brief If not successful, a failure message is provided.
/// @param pSerialization The pointer to the serialization instance.
const char* CMACLIB_SHARED_SYMBOL CCmacLibISerializationGetMessage(
    CCmacLibISerialization* pSerialization
);

/// @brief Destructor.
/// @param pSerialization The pointer to the serialization instance.
void CMACLIB_SHARED_SYMBOL CCmacLibISerializationDestroy(
    CCmacLibISerialization* pSerialization
);

#if defined(__cplusplus)
}
#endif
// END C Wrappers.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.