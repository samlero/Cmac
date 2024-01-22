#include "mex.hpp"
#include "mexAdapter.hpp"
#include "IPrediction.h"
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
                std::vector<matlab::data::Array>({ factory.createScalar("First input must be of type uint32.")}));
            return;
        }
        // extract the handle
        matlab::data::TypedArray<uint64_t> dataArray = std::move(inputs[0]);
        auto dataPtr = dataArray.release();
        uint64_t* dataRaw = dataPtr.get();
        IPrediction* prediction = (IPrediction*)(*dataRaw);

        // second argument must be the name of the method in question
        if(inputs[0].getType() != matlab::data::ArrayType::MATLAB_STRING)
        {
            matlabPtr->feval(u"error", 0, 
                std::vector<matlab::data::Array>({ factory.createScalar("Second input must be of type string.")}));
            return;
        }
        // extract the method name
        matlab::data::CharArray inChar = inputs[1];
        std::string method = inChar.toAscii();

        // output must only contain one output
        if(outputs.size() != 1){
            matlabPtr->feval(u"error", 0, 
                std::vector<matlab::data::Array>({ factory.createScalar("One output required.")}));
            return;
        }

        if(method == "GetValues"){
            std::vector<double> values = prediction->GetValues();
            outputs[0] = factory
                .createArray<double>({1, values.size()}
                                     , values.data()
                                     , values.data() + values.size());
        }
        else if(method == "GetActiveWeightIndices"){
            std::vector<unsigned int> values = prediction->GetActiveWeightIndices();
            outputs[0] = factory
                .createArray<uint32_t>({1, values.size()}
                                     , values.data()
                                     , values.data() + values.size());
        }
        else if(method == "GetActiveWeights"){
            std::vector<std::vector<double>> matrix = prediction->GetActiveWeights();
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
        else if(method == "GetBasisValues"){
            std::vector<double> values = prediction->GetBasisValues();
            outputs[0] = factory
                .createArray<double>({1, values.size()}
                                     , values.data()
                                     , values.data() + values.size());
        }
        else if(method == "GetResult"){
            IResult* result = prediction->GetResult();
            outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)result);
        }
        else if(method == "Delete"){
            delete prediction;
        }
        else{
           matlabPtr->feval(u"error", 0, 
                std::vector<matlab::data::Array>({ factory.createScalar("Not a supported method.")}));
        }
    }
};
