#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <string>

namespace CmacLib
{
    /// @brief Serializes and deserializes
    class ISerializable{
    public:
        /// @brief Serializes the object in its own unique format.
        /// @return Serialized string.
        virtual std::string Serialize() = 0;

        /// @brief Deserializes the content into its member variables.
        /// @param content Valid deserializable content.
        virtual void Deserialize(std::string&& content) = 0;
    };
}

#endif