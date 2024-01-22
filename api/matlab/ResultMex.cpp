#include "mex.hpp"
#include "mexAdapter.hpp"
#include "IResult.h"
#include <string>

using namespace CmacLib;

class MexFunction : public matlab::mex::Function {
    matlab::data::ArrayFactory factory;
public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs){
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();

        // input size is always two (handle and method name)
        if(inputs.size() != 2)
        {
            matlabPtr->feval(u"error", 0, 
                std::vector<matlab::data::Array>({ factory.createScalar("Input must contain only two arguments.")}));
            return;
        }

        // first argument must be an IResult* pointer
        if(inputs[0].getType() != matlab::data::ArrayType::UINT64)
        {
            matlabPtr->feval(u"error", 0, 
                std::vector<matlab::data::Array>({ factory.createScalar("First input must be of type uint64.")}));
            return;
        }
        // extract the handle
        matlab::data::TypedArray<uint64_t> dataArray = std::move(inputs[0]);
        auto dataPtr = dataArray.release();
        uint64_t* dataRaw = dataPtr.get();
        IResult* result = (IResult*)(*dataRaw);

        // second argument must be the name of the method in question
        if(inputs[1].getType() != matlab::data::ArrayType::CHAR)
        {
            matlabPtr->feval(u"error", 0, 
                std::vector<matlab::data::Array>({ factory.createScalar("Second input must be of type string.")}));
            return;
        }
        // extract the method name
        matlab::data::CharArray inChar(inputs[1]);
        std::string method = inChar.toAscii();

        if(method == "IsSuccessful"){
            bool success = result->IsSuccessful();
            outputs[0] = factory.createScalar<bool>(success);
        }
        else if(method == "GetMessage"){
            std::string msg = result->GetMessage();
            outputs[0] = factory.createCharArray(msg);
        }
        else{
           matlabPtr->feval(u"error", 0, 
                std::vector<matlab::data::Array>({ factory.createScalar("Not a supported method.")}));
        }
    }
};
