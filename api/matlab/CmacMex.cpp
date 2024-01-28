#include "mex.hpp"
#include "mexAdapter.hpp"
#include "CmacLib.h"

using namespace CmacLib;

class MexFunction : public matlab::mex::Function {
    matlab::data::ArrayFactory factory;
public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs){
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();

        if(inputs.size() == 2 // destructor
                || inputs.size() == 3 // predict
                || inputs.size() == 5) // adjust
        {
            // First input should be a method name
            if(inputs[0].getType() != matlab::data::ArrayType::CHAR)
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("First input must be of type char array.")}));
                return;
            }
            std::cout<<"Cmac:Extract method name"<<std::endl;
            // extract the method name
            matlab::data::CharArray inChar(inputs[0]);
            std::string method = inChar.toAscii();

            // second input should be a pointer
            if(inputs[1].getType() != matlab::data::ArrayType::UINT64)
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("Second input must be of type uint64.")}));
                return;
            }
            std::cout<<"Cmac:Extract Cmac pointer"<<std::endl;
            // get Cmac pointer
            matlab::data::TypedArray<uint64_t> dataArray = std::move(inputs[1]);
            auto dataPtr = dataArray.release();
            uint64_t* dataRaw = dataPtr.get();
            ICmac* cmac = (ICmac*)(*dataRaw);

            // make sure method name is CreateCmac
            if(method == "Predict")
            {
                std::cout<<"Cmac:Predict"<<std::endl;
                // check if third input is double
                if(inputs[2].getType() != matlab::data::ArrayType::DOUBLE)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Third input should be of type double.") }));
                    return;
                }
                std::cout<<"Cmac:Predict: Extract inputs"<<std::endl;
                matlab::data::TypedArray<double> pInputs = std::move(inputs[2]);
                std::vector<double> predictInputs(pInputs.begin(), pInputs.end());

                std::cout<<"Cmac:Predict: Call library predict method."<<std::endl;
                std::unique_ptr<IPrediction> prediction 
                    = cmac->Predict(predictInputs);

                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)prediction.release());
            }
            else if(method == "Adjust")
            {
                std::cout<<"Cmac:Adjust"<<std::endl;
                // check if third input is double
                if(inputs[2].getType() != matlab::data::ArrayType::DOUBLE)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Third input should be of type double.") }));
                    return;
                }
                std::cout<<"Cmac:Adjust: Extract corrections"<<std::endl;
                matlab::data::TypedArray<double> pCorrections = std::move(inputs[2]);
                std::vector<double> corrections(pCorrections.begin(), pCorrections.end());

                // fourth input is a prediction pointer
                if(inputs[3].getType() != matlab::data::ArrayType::UINT64)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Fourth input should be of type uint64.") }));
                    return;
                }
                std::cout<<"Cmac:Adjust: Extract prediction"<<std::endl;
                // get prediction pointer
                matlab::data::TypedArray<uint64_t> dataArray = std::move(inputs[3]);
                auto dataPtr = dataArray.release();
                uint64_t* dataRaw = dataPtr.get();
                IPrediction* prediction = (IPrediction*)(*dataRaw);
                
                // fifth input is a double
                if(inputs[4].getType() != matlab::data::ArrayType::DOUBLE)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Fifth input should be of type double.") }));
                    return;
                }
                std::cout<<"Cmac:Adjust: Extract damping"<<std::endl;
                matlab::data::TypedArray<double> pDamping = std::move(inputs[4]);

                std::cout<<"Cmac:Adjust: Call adjust method"<<std::endl;
                // call the Adjust method
                std::unique_ptr<IAdjustment> adjustment = cmac->Adjust(corrections
                                                                       , prediction
                                                                       , pDamping[0]);
                
                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)adjustment.release());
            }
            else if(method == "Delete")
            {
                std::cout<<"Cmac:Delete"<<std::endl;
                delete cmac;
            }
            else
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("Not a supported method name.") }));
                return;
            }        
        }
        else
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("Not a supported method.")}));
        }
    }
};