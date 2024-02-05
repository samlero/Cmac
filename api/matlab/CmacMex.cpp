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
    const static unsigned int PREDICT_INPUT = 2;
    const static unsigned int ADJUST_CORRECTION = 2;
    const static unsigned int ADJUST_PREDICTION = 3;
    const static unsigned int ADJUST_DAMPING = 4;
    const static unsigned int DESERIALIZE_CONTENT = 2;
};

class InputSize
{
public:
    const static unsigned int DELETE = 2;
    const static unsigned int PREDICT = 3;
    const static unsigned int ADJUST = 5;
    const static unsigned int ZEROIZE = 2;
    const static unsigned int SERIALIZE = 2;
    const static unsigned int DESERIALIZE = 3;
};

class Method
{
public:
    const static unsigned int DELETE = 0;
    const static unsigned int PREDICT = 100;
    const static unsigned int ADJUST = 101;
    const static unsigned int ZEROIZE = 102;

    const static unsigned int SERIALIZE = 200;
    const static unsigned int DESERIALIZE = 201;
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

            #if Debug
            std::cout<<"Cmac:Extract Cmac pointer"<<std::endl;
            #endif
            // get Cmac pointer
            matlab::data::TypedArray<uint64_t> dataArray
                = std::move(inputs[InputIndex::POINTER]);
            auto dataPtr = dataArray.release();
            uint64_t* dataRaw = dataPtr.get();
            ICmac* cmac = (ICmac*)(*dataRaw);

            if(method == Method::PREDICT
               && inputs.size() == InputSize::PREDICT)
            {
                // check if third input is double
                if(inputs[InputIndex::PREDICT_INPUT].getType() != matlab::data::ArrayType::DOUBLE)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Third input should be of type double.") }));
                }
                matlab::data::TypedArray<double> pInputs = std::move(inputs[InputIndex::PREDICT_INPUT]);
                std::vector<double> predictInputs(pInputs.begin(), pInputs.end());
                std::unique_ptr<IPrediction> prediction
                    = cmac->Predict(predictInputs);

                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)prediction.release());

                #if Debug
                std::cout<<"Cmac: Predict method"<<std::endl;
                #endif
            }
            else if(method == Method::ADJUST
                    && inputs.size() == InputSize::ADJUST)
            {
                // check if third input is double
                if(inputs[InputIndex::ADJUST_CORRECTION].getType() != matlab::data::ArrayType::DOUBLE)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Third input should be of type double.") }));
                }
                matlab::data::TypedArray<double> pCorrections = std::move(inputs[InputIndex::ADJUST_CORRECTION]);
                std::vector<double> corrections(pCorrections.begin(), pCorrections.end());

                // fourth input is a prediction pointer
                if(inputs[InputIndex::ADJUST_PREDICTION].getType() != matlab::data::ArrayType::UINT64)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Fourth input should be of type uint64.") }));
                }
                // get prediction pointer
                matlab::data::TypedArray<uint64_t> dataArray = std::move(inputs[InputIndex::ADJUST_PREDICTION]);
                auto dataPtr = dataArray.release();
                uint64_t* dataRaw = dataPtr.get();
                IPrediction* prediction = (IPrediction*)(*dataRaw);

                // fifth input is a double
                if(inputs[InputIndex::ADJUST_DAMPING].getType() != matlab::data::ArrayType::DOUBLE)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Fifth input should be of type double.") }));
                }
                matlab::data::TypedArray<double> pDamping = std::move(inputs[InputIndex::ADJUST_DAMPING]);

                // call the Adjust method
                std::unique_ptr<IAdjustment> adjustment = cmac->Adjust(corrections
                                                                       , prediction
                                                                       , pDamping[0]);

                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)adjustment.release());

                #if Debug
                std::cout<<"Cmac: Adjust method"<<std::endl;
                #endif
            }
            else if(method == Method::ZEROIZE
                    && inputs.size() == InputSize::ZEROIZE)
            {
                std::unique_ptr<IResult> result = cmac->Zeroize();
                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)result.release());
                #if Debug
                std::cout<<"Cmac: Zeroize method"<<std::endl;
                #endif
            }
            else if(method == Method::SERIALIZE
                   && inputs.size() == InputSize::SERIALIZE)
            {
                std::unique_ptr<ISerialization> serialization = cmac->Serialize();
                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)serialization.release());
                #if Debug
                std::cout<<"Cmac: Serialize method"<<std::endl;
                #endif
            }
            else if(method == Method::DESERIALIZE
                    && inputs.size() == InputSize::DESERIALIZE)
            {
                if(inputs[InputIndex::DESERIALIZE_CONTENT].getType() != matlab::data::ArrayType::CHAR)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Third input expected to be char.")}));
                }
                matlab::data::CharArray charArr(inputs[InputIndex::DESERIALIZE_CONTENT]);
                std::string content(charArr.toAscii());
                std::unique_ptr<IResult> result = cmac->Deserialize(std::move(content));
                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)result.release());
                #if Debug
                std::cout<<"Cmac: Deserialize method"<<std::endl;
                #endif
            }
            else if(method == Method::DELETE 
                    && inputs.size() == InputSize::DELETE)
            {
                delete cmac;
                #if Debug
                std::cout<<"Cmac: Delete method"<<std::endl;
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