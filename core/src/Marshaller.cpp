#include "Marshaller.h"
#include "Result.h"
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
        file.open (filepath);
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
        serializable->Deserialize(std::move(content));

        // successful operation
        result->SetIsSuccessful(true);
    } 
    catch(const std::exception& ex)
    {
        result->SetMessage(ex.what());
    }
    return result;
}
