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

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.