#include "mex.hpp"
#include "mexAdapter.hpp"
#include "CmacLib.h"
#include <string>

using namespace CmacLib;

class InputIndex
{
    public:
    const static unsigned int METHOD = 0;
    const static unsigned int POINTER = 1;
    const static unsigned int SAVE_SERIALIZABLE = 2;
    const static unsigned int SAVE_DIRECTORY = 3;
    const static unsigned int SAVE_FILENAME = 4;
    const static unsigned int LOAD_SERIALIZABLE = 2;
    const static unsigned int LOAD_FILEPATH = 3;
};

class InputSize
{
    public:
    const static unsigned int DELETE = 2;
    const static unsigned int SAVE = 5;
    const static unsigned int LOAD = 4;
};

class Method
{
    public:
    const static unsigned int DELETE = 0;
    const static unsigned int SAVE = 100;
    const static unsigned int LOAD = 101;
};

class MexFunction : public matlab::mex::Function {
    matlab::data::ArrayFactory factory;
    const static unsigned int MIN_INPUT_SIZE = 2;
    public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs){
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();


        if(inputs.size() >= MIN_INPUT_SIZE)
        {
            // get method
            if(inputs[InputIndex::METHOD].getType() != matlab::data::ArrayType::UINT32)
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("First input must be of type uint32.")}));
            }
            // extract the method type
            matlab::data::TypedArray<uint32_t> methodData = std::move(inputs[InputIndex::METHOD]);
            auto methodPtr = methodData.release();
            uint32_t* methodRaw = methodPtr.get();
            uint32_t method = *methodRaw;

            // get pointer
            if(inputs[InputIndex::POINTER].getType() != matlab::data::ArrayType::UINT64)
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("Second input must be of type uint64.")}));
                return;
            }
            std::cout<<"MarshallerMex : Extract Marshaller pointer"<<std::endl;
            // get Marshaller pointer
            matlab::data::TypedArray<uint64_t> dataArray
                = std::move(inputs[InputIndex::POINTER]);
            auto dataPtr = dataArray.release();
            uint64_t* dataRaw = dataPtr.get();
            IMarshaller* marshaller = (IMarshaller*)(*dataRaw);

            if(method == Method::SAVE
               && inputs.size() == InputSize::SAVE)
            {
                // check if third input is double
                if(inputs[InputIndex::SAVE_SERIALIZABLE].getType() != matlab::data::ArrayType::UINT64)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Third input should be of type uint64.") }));
                }
                matlab::data::TypedArray<uint64_t> dataArray
                    = std::move(inputs[InputIndex::SAVE_SERIALIZABLE]);
                auto dataPtr = dataArray.release();
                uint64_t* dataRaw = dataPtr.get();
                ISerializable* serializable = (ISerializable*)(*dataRaw);

                if(inputs[InputIndex::SAVE_DIRECTORY].getType() != matlab::data::ArrayType::CHAR)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Fourth input should be of type char.") }));
                }
                matlab::data::CharArray dirArr(inputs[InputIndex::SAVE_DIRECTORY]);
                std::string directory(dirArr.toAscii());

                if(inputs[InputIndex::SAVE_FILENAME].getType() != matlab::data::ArrayType::CHAR)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Fifth input should be of type char.") }));
                }
                matlab::data::CharArray filenameArr(inputs[InputIndex::SAVE_FILENAME]);
                std::string filename(filenameArr.toAscii());

                std::unique_ptr<IResult> result 
                    = marshaller->Save(serializable
                                       , directory, filename);

                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)result.release());

                #if Debug
                std::cout<<"MarshallerMex: Save method"<<std::endl;
                #endif
            }
            if(method == Method::LOAD
               && inputs.size() == InputSize::LOAD)
            {
                // check if third input is double
                if(inputs[InputIndex::LOAD_SERIALIZABLE].getType() != matlab::data::ArrayType::UINT64)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Third input should be of type uint64.") }));
                }
                matlab::data::TypedArray<uint64_t> dataArray
                    = std::move(inputs[InputIndex::LOAD_SERIALIZABLE]);
                auto dataPtr = dataArray.release();
                uint64_t* dataRaw = dataPtr.get();
                ISerializable* serializable = (ISerializable*)(*dataRaw);

                if(inputs[InputIndex::LOAD_FILEPATH].getType() != matlab::data::ArrayType::CHAR)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Fourth input should be of type char.") }));
                }
                matlab::data::CharArray filepathArr(inputs[InputIndex::LOAD_FILEPATH]);
                std::string filepath(filepathArr.toAscii());

                std::unique_ptr<IResult> result 
                    = marshaller->Load(serializable, filepath);

                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)result.release());

                #if Debug
                std::cout<<"MarshallerMex: Load method"<<std::endl;
                #endif
            }
            else if(method == Method::DELETE
                    && inputs.size() == InputSize::DELETE)
            {
                delete marshaller;
                #if Debug
                std::cout<<"MarshallerMex: Delete method"<<std::endl;
                #endif
            }
            else
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("Not a supported method.")}));
            }

        }
        else
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("Requires at least 2 inputs.")}));
        }
    }
};