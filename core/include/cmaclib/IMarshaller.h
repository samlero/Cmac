#ifndef IMARSHALLER_H
#define IMARSHALLER_H

#include <cmaclib/defines.h>
#include <cmaclib/ISerializable.h>
#include <cmaclib/IResult.h>

// Begin C++ Only Region.
#if defined(__cplusplus)
#include <memory>

namespace CmacLib
{
    /// @brief Save and load serializable objects
    class CMACLIB_SHARED_SYMBOL IMarshaller
    {
    public:
        virtual ~IMarshaller(){}

        /// @brief Save the serializable object. 
        /// @param serializable Object to save.
        /// @param directory Folder to save the serializable object in.
        /// @param filename Name of the object to save.
        /// @return Indicates if the save operation was successful or not.
        virtual std::unique_ptr<IResult> Save(ISerializable* serializable,
            const std::string& directory, const std::string& filename) = 0;
        
        /// @brief Fills the contents of the serialzable object.
        /// @param serializable Object to fill.
        /// @param filepath Location of the file that contains the serializable object's contents.
        /// @return 
        virtual std::unique_ptr<IResult> Load(ISerializable* serializable, const std::string& filepath) = 0;
    };
}
#endif
// End C++ Only Region.

// CCmacLibIMarshaller Definition.
#if defined(__cplusplus)
typedef CmacLib::IMarshaller CCmacLibIMarshaller;
#else
typedef struct CCmacLibIMarshaller CCmacLibIMarshaller;
#endif
// END CCmacLibIMarshaller Definition.

// C Wrappers.
#if defined(__cplusplus)
extern "C" {
#endif

/// @brief Save the serializable object.
/// @param pMarshaller The pointer to the marshaller instance.
/// @param serializable Object to save.
/// @param directory Folder to save the serializable object in.
/// @param filename Name of the object to save.
/// @return Indicates if the save operation was successful or not.
CCmacLibIResult* CMACLIB_SHARED_SYMBOL CCmacLibIMarshallerSave(
    CCmacLibIMarshaller* pMarshaller, CCmacLibISerializable* pSerializable,
    const char* directory, const char* filename
);

/// @brief Fills the contents of the serialzable object.
/// @param pMarshaller The pointer to the marshaller instance.
/// @param serializable Object to fill.
/// @param filepath Location of the file that contains the serializable object's contents.
CCmacLibIResult* CMACLIB_SHARED_SYMBOL CCmacLibIMarshallerLoad(
    CCmacLibIMarshaller* pMarshaller, CCmacLibISerializable* pSerializable,
    const char* filepath
);

/// @brief Destructor.
/// @param pMarshaller The pointer to the marshaller instance.
void CMACLIB_SHARED_SYMBOL CCmacLibIMarshallerDestroy(
    CCmacLibIMarshaller* pMarshaller
);

#if defined(__cplusplus)
}
#endif
// END C Wrappers.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.