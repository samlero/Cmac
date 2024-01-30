#include "mex.hpp"
#include "mexAdapter.hpp"
#include "ISerialization.h"
#include "IResult.h"

using namespace CmacLib;

class InputIndex
{
public:
    const static unsigned int METHOD = 0;
    const static unsigned int POINTER = 1;
};

class Method
{
public:
    const static unsigned int DELETE = 0;
    const static unsigned int GET_STRING = 100;
    const static unsigned int IS_SUCCESSFUL = 101;
    const static unsigned int GET_MESSAGE = 102;
};

class MexFunction : public matlab::mex::Function {
    matlab::data::ArrayFactory factory;
    const static unsigned int INPUT_SIZE = 2;
public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs){
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();

        if(inputs.size() != INPUT_SIZE)
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("Input must contain only two arguments.")}));
        }

        // first argument must be the name of the method in question
        if(inputs[InputIndex::METHOD].getType() != matlab::data::ArrayType::UINT32)
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("First input must be of type uint32.")}));
        }
        // extract the method type
        matlab::data::TypedArray<uint32_t> methodData 
            = std::move(inputs[InputIndex::METHOD]);
        auto methodPtr = methodData.release();
        uint32_t* methodRaw = methodPtr.get();
        uint32_t method = *methodRaw;

        if(inputs[InputIndex::POINTER].getType() != matlab::data::ArrayType::UINT64)
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("Second input must be of type uint64.")}));
        }
        // extract the handle
        matlab::data::TypedArray<uint64_t> dataArray 
            = std::move(inputs[InputIndex::POINTER]);
        auto dataPtr = dataArray.release();
        uint64_t* dataRaw = dataPtr.get();
        ISerialization* serialization = (ISerialization*)(*dataRaw);

        #if Debug
        std::cout<<"SerializationMex: Pointer: "<< *dataRaw <<std::endl;
        #endif

        if(method == Method::GET_STRING)
        {
            std::string msg = serialization->GetString();
            outputs[0] = factory.createCharArray(msg);
            #if Debug
            std::cout << "SerializationMex: GetString method." << std::endl;
            #endif
        }
        else if(method == Method::DELETE)
        {
            delete serialization;
            #if Debug
            std::cout << "SerializationMex: Delete method." << std::endl;
            #endif
        }
        else if(method == Method::IS_SUCCESSFUL)
        {
            bool success = serialization->IsSuccessful();
            outputs[0] = factory.createScalar<bool>(success);
            #if Debug
            std::cout << "SerializationMex: IsSuccessful method." << std::endl;
            #endif
        }
        else if(method == Method::GET_MESSAGE)
        {
            std::string msg = serialization->GetMessage();
            outputs[0] = factory.createCharArray(msg);
            #if Debug
            std::cout << "SerializationMex: GetMessage method." << std::endl;
            #endif
        }
        else
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("Not a supported method.")}));
        }
    }
};