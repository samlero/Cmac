#include "mex.hpp"
#include "mexAdapter.hpp"
#include <IResult.h>
#include <string>

using namespace CmacLib;

class MexFunction : public matlab::mex::Function {
    matlab::data::ArrayFactory factory;
public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs){
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();

        if(inputs.size() == 2){
            // first argument must be an IResult* pointer
            // TODO: check type
            matlab::data::TypedArray<uint32_t> dataArray = std::move(inputs[0]);
            auto dataPtr = dataArray.release();
            uint32_t* dataRaw = dataPtr.get();
            IResult* result = (IResult*)dataRaw;

            // second argument must be the name of the method in question
            // TODO: check type
            matlab::data::CharArray inChar = inputs[1];
            std::string method = inChar.toAscii();

            // output must only contain one output
            if(outputs.size() != 1){
                matlabPtr->feval(u"error", 0, 
                    std::vector<matlab::data::Array>({ factory.createScalar("One output required.")}));
                return;
            }

            if(method == "IsSuccessful"){
                bool success = result->IsSuccessful();
                outputs[0] = factory.createScalar<bool>(success);
            }
            else if(method == "GetMessage"){
                std::string msg = result->GetMessage();
                outputs[0] = factory.createCharArray(msg);
            }
            else{
                // throw error here
            }
        }
        else{
            // throw error here
        }
    }
};
