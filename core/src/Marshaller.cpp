#include "Marshaller.h"

using namespace CmacLib;

bool CmacLib::Marshaller::Save(ISerializable *serializable, std::string directory, std::string filename)
{
    // call the serialize method of the serializable object to get a string representation

    // save the string to a file

    return false;
}

bool CmacLib::Marshaller::Load(ISerializable *serializable, std::string filepath)
{
    // load the contents of the file

    // call the deserialize method

    return false;
}
