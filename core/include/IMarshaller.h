#ifndef IMARSHALLER_H
#define IMARSHALLER_H

#include "ISerializable.h"
#include "IResult.h"
#include <memory>

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
        /// @return Indicates if the save operation was successful or not.
        virtual std::unique_ptr<IResult> Save(ISerializable* serializable, std::string directory, std::string filename) = 0;
        
        /// @brief Fills the contents of the serialzable object.
        /// @param serializable Object to fill.
        /// @param filepath Location of the file that contains the serializable object's contents.
        /// @return 
        virtual std::unique_ptr<IResult> Load(ISerializable* serializable, const std::string& filepath) = 0;
    };
}

#endif