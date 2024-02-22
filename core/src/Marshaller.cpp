#include "cmaclib/Marshaller.h"

#include <cmaclib/Result.h>
#include <iostream>
#include <fstream>

using namespace CmacLib;

std::unique_ptr<IResult> Marshaller::Save(ISerializable *serializable,
    const std::string& directory, const std::string& filename)
{
    std::unique_ptr<Result> result(std::make_unique<Result>());
    try
    {
        result->SetIsSuccessful(false);

        // call the serialize method of the serializable object to get a string representation
        std::unique_ptr<ISerialization> serialization = serializable->Serialize();

        if(!serialization->IsSuccessful())
        {
            result->SetMessage("Serialization failed.");
            return result;
        }
    
        // concatenate filepath
        std::string filepath = directory + "/" + filename + "." + serializable->GetExtension();

        // save
        std::ofstream file;
        file.open (filepath, std::ios_base::binary);
        file << serialization->GetString();
        file.close();

        // set result to successful
        result->SetIsSuccessful(true);
    }
    catch(const std::exception& ex)
    {
        result->SetMessage(ex.what());
    }
    return result;
}

std::unique_ptr<IResult> Marshaller::Load(ISerializable *serializable, const std::string& filepath)
{
    std::unique_ptr<Result> result(std::make_unique<Result>());
    try
    {
        result->SetIsSuccessful(false);

        // check if the filepath has the serializable's extension
        std::string extension = filepath.substr(filepath.length() - serializable->GetExtension().size(), filepath.length());
        if(extension != serializable->GetExtension())
        {
            result->SetMessage("Filepath does not contain the correct extension.");
            return result;
        }

        // load the content
        std::ifstream file(filepath);
        std::string content = "";
        std::string line;
        while(std::getline(file, line))
        {
            content += line;
            content.push_back('\n');
        }
        content.pop_back();

        // deserialize
        std::unique_ptr<IResult> deserialization = serializable->Deserialize(std::move(content));

        if(!deserialization->IsSuccessful())
        {
            result->SetMessage("Deserialization failed.");
            return result;
        }

        // successful operation
        result->SetIsSuccessful(true);
    } 
    catch(const std::exception& ex)
    {
        result->SetMessage(ex.what());
    }
    return result;
}

/// @brief Save the serializable object.
/// @param pMarshaller The pointer to the marshaller instance.
/// @param serializable Object to save.
/// @param directory Folder to save the serializable object in.
/// @param filename Name of the object to save.
/// @return Indicates if the save operation was successful or not.
CCmacLibIResult* CCmacLibIMarshallerSave(
    CCmacLibIMarshaller* pMarshaller, CCmacLibISerializable* pSerializable,
    const char* directory, const char* filename
) {
    return pMarshaller->Save(pSerializable, directory, filename).release();
}

/// @brief Fills the contents of the serialzable object.
/// @param pMarshaller The pointer to the marshaller instance.
/// @param serializable Object to fill.
/// @param filepath Location of the file that contains the serializable object's contents.
CCmacLibIResult* CCmacLibIMarshallerLoad(
    CCmacLibIMarshaller* pMarshaller, CCmacLibISerializable* pSerializable,
    const char* filepath
) {
    return pMarshaller->Load(pSerializable, filepath).release();
}

/// @brief Destructor.
/// @param ppMarshaller The pointer to the pointer to the marshaller instance.
void CCmacLibIMarshallerDestroy(
    CCmacLibIMarshaller** ppMarshaller
) {
    if (*ppMarshaller) {
        delete *ppMarshaller;
        *ppMarshaller = nullptr;
    }
}