#include "mex.hpp"
#include "mexAdapter.hpp"
#include "IAdjustment.h"
#include "IResult.h"

using namespace CmacLib;

class MexFunction : public matlab::mex::Function {
    matlab::data::ArrayFactory factory;
public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs){
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();

        if(inputs.size() != 2)
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("Input must contain only two arguments.")}));
            return;
        }

        // first argument must be the name of the method in question
        if(inputs[0].getType() != matlab::data::ArrayType::CHAR)
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("First input must be of type string.")}));
            return;
        }
        std::cout<<"Adjustment:Extract method name"<<std::endl;
        // extract the method name
        matlab::data::CharArray inChar(inputs[0]);
        std::string method = inChar.toAscii();


        if(inputs[1].getType() != matlab::data::ArrayType::UINT64)
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("Second input must be of type uint64.")}));
            return;
        }

        std::cout<<"Adjustment:Extract Adjustment pointer"<<std::endl;
        // extract the handle
        matlab::data::TypedArray<uint64_t> dataArray = std::move(inputs[1]);
        auto dataPtr = dataArray.release();
        uint64_t* dataRaw = dataPtr.get();
        IAdjustment* adjustment = (IAdjustment*)(*dataRaw);

        if(method == "GetWeightChanges")
        {
            std::cout<<"Adjustment:GetWeightChanges"<<std::endl;
            std::vector<std::vector<double>> matrix = adjustment->GetWeightChanges();
            std::vector<double> array;
            unsigned int ncols = 0;
            for(size_t i = 0; i < matrix.size(); i++){
                ncols = matrix[i].size();
                for(size_t j = 0; j < matrix[i].size(); j++){
                    array.push_back(matrix[i][j]);
                }
            }
            // active weights as an array
            outputs[0] = factory
                .createArray<double>({1, array.size()}
                                     , array.data()
                                     , array.data() + array.size());
            // number of rows
            outputs[1] = factory
                .createScalar<uint32_t>((unsigned int)matrix.size());
            // number of columns
            outputs[2] = factory
                .createScalar<uint32_t>(ncols);
        }
        else if(method == "Delete")
        {
            std::cout<<"Adjustment:Delete"<<std::endl;
            delete adjustment;
        }
        else if(method == "IsSuccessful"){
            bool success = adjustment->IsSuccessful();
            std::cout << "IsSuccessful: " << success << std::endl;
            outputs[0] = factory.createScalar<bool>(success);
        }
        else if(method == "GetMessage"){
            std::string msg = adjustment->GetMessage();
            outputs[0] = factory.createCharArray(msg);
        }
        else
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("Not a supported method.")}));
        }
    }
};