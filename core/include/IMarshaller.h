#ifndef IMARSHALLER_H
#define IMARSHALLER_H

#include "ISerializable.h"

namespace CmacLib
{
    /// @brief Save and load serializable objects
    class IMarshaller
    {
    public:
        virtual ~IMarshaller(){}

        /// @brief Save the serializable object. 
        /// @param serializable Object to save.
        /// @param directory Folder to save the serializable object in.
        /// @param filename Name of the object to save.
        /// @return 
        virtual bool Save(ISerializable* serializable, std::string directory, std::string filename) = 0;
        
        /// @brief Fills the contents of the serialzable object.
        /// @param serializable Object to fill.
        /// @param filepath Location of the file that contains the serializable object's contents.
        /// @return 
        virtual bool Load(ISerializable* serializable, std::string filepath) = 0;
    };
}

#endif