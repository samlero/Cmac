#include "mex.hpp"
#include "mexAdapter.hpp"
#include "CmacLib.h"
#include <string>
#include <typeinfo>

using namespace CmacLib;

class SerializableType
{
    public:
    const static unsigned int CMAC = 1000;
};

class InputIndex
{
    public:
    const static unsigned int METHOD = 0;
    const static unsigned int POINTER = 1;
    const static unsigned int SAVE_SERIALIZABLE = 2;
    const static unsigned int SAVE_DIRECTORY = 3;
    const static unsigned int SAVE_FILENAME = 4;
    const static unsigned int SAVE_SERIALIZABLE_TYPE = 5;
    const static unsigned int LOAD_SERIALIZABLE = 2;
    const static unsigned int LOAD_FILEPATH = 3;
    const static unsigned int LOAD_SERIALIZABLE_TYPE = 4;
};

class InputSize
{
    public:
    const static unsigned int DELETE = 2;
    const static unsigned int SAVE = 6;
    const static unsigned int LOAD = 5;
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
            #if Debug
            std::cout<<"MarshallerMex : Input size "<< inputs.size() <<std::endl;
            #endif
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
            #if Debug
            std::cout<<"MarshallerMex : Method "<< method <<std::endl;
            #endif

            // get pointer
            if(inputs[InputIndex::POINTER].getType() != matlab::data::ArrayType::UINT64)
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("Second input must be of type uint64.")}));
                return;
            }
            #if Debug
            std::cout<<"MarshallerMex : Extract Marshaller pointer"<<std::endl;
            #endif
            // get Marshaller pointer
            matlab::data::TypedArray<uint64_t> dataArray
                = std::move(inputs[InputIndex::POINTER]);
            auto dataPtr = dataArray.release();
            uint64_t* dataRaw = dataPtr.get();
            IMarshaller* marshaller = (IMarshaller*)(*dataRaw);

            if(method == Method::SAVE
               && inputs.size() == InputSize::SAVE)
            {
                if(inputs[InputIndex::SAVE_SERIALIZABLE_TYPE].getType() != matlab::data::ArrayType::UINT32)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Sixth input should be of type uint32.") }));
                }
                matlab::data::TypedArray<uint32_t> serTypeArr
                    = std::move(inputs[InputIndex::SAVE_SERIALIZABLE_TYPE]);
                auto serTypePtr = serTypeArr.release();
                uint32_t* serTypeRaw = serTypePtr.get();
                uint32_t serType = *serTypeRaw;

                // check if third input is pointer
                if(inputs[InputIndex::SAVE_SERIALIZABLE].getType() != matlab::data::ArrayType::UINT64)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Third input should be of type uint64.") }));
                }
                matlab::data::TypedArray<uint64_t> dataArray
                    = std::move(inputs[InputIndex::SAVE_SERIALIZABLE]);
                auto dataPtr = dataArray.release();
                uint64_t* dataRaw = dataPtr.get();

                ISerializable* serializable = nullptr; 
                if(serType == SerializableType::CMAC)
                {
                    serializable = static_cast<ICmac*>((void*)*dataRaw);
                }
                else
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Casting type not supported.") }));
                }
                
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

                #if Debug
                std::cout<<"MarshallerMex : Directory: "
                    << directory << ", Filename: "<< filename <<std::endl;
                #endif

                std::unique_ptr<IResult> result 
                    = marshaller->Save(serializable
                                       , directory, filename);

                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)result.release());

                #if Debug
                std::cout<<"MarshallerMex : Save method"<<std::endl;
                #endif
            }
            else if(method == Method::LOAD
               && inputs.size() == InputSize::LOAD)
            {
                if(inputs[InputIndex::LOAD_SERIALIZABLE_TYPE].getType() != matlab::data::ArrayType::UINT32)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Sixth input should be of type uint32.") }));
                }
                matlab::data::TypedArray<uint32_t> serTypeArr
                    = std::move(inputs[InputIndex::LOAD_SERIALIZABLE_TYPE]);
                auto serTypePtr = serTypeArr.release();
                uint32_t* serTypeRaw = serTypePtr.get();
                uint32_t serType = *serTypeRaw;

                // check if third input is pointer
                if(inputs[InputIndex::LOAD_SERIALIZABLE].getType() != matlab::data::ArrayType::UINT64)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Third input should be of type uint64.") }));
                }
                matlab::data::TypedArray<uint64_t> dataArray
                    = std::move(inputs[InputIndex::LOAD_SERIALIZABLE]);
                auto dataPtr = dataArray.release();
                uint64_t* dataRaw = dataPtr.get();
                ISerializable* serializable = nullptr;
                if(serType == SerializableType::CMAC)
                {
                    serializable = static_cast<ICmac*>((void*)*dataRaw);
                }
                else
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Casting type not supported.") }));
                }

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
                std::cout<<"MarshallerMex : Load method"<<std::endl;
                #endif
            }
            else if(method == Method::DELETE
                    && inputs.size() == InputSize::DELETE)
            {
                delete marshaller;
                #if Debug
                std::cout<<"MarshallerMex : Delete method"<<std::endl;
                #endif
            }
            else
            {
                #if Debug
                std::cout<<"MarshallerMex : Method: "<< method 
                    << ", Input Size: " << inputs.size() <<std::endl;
                #endif
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