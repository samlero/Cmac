#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <memory>
#include <string>
#include "ISerialization.h"

namespace CmacLib
{
    /// @brief Serializes and deserializes
    class ISerializable{
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
    };
}

#endif