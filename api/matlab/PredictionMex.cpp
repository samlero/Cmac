#include "mex.hpp"
#include "mexAdapter.hpp"
#include "IPrediction.h"
#include "IResult.h"
#include <string>
#include <iostream>

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

        // first argument must be the name of the method in question
        if(inputs[0].getType() != matlab::data::ArrayType::CHAR)
        {
            matlabPtr->feval(u"error", 0, 
                std::vector<matlab::data::Array>({ factory.createScalar("First input must be of type string.")}));
            return;
        }
        std::cout<<"Prediction:Extract method name"<<std::endl;
        // extract the method name
        matlab::data::CharArray inChar(inputs[0]);
        std::string method = inChar.toAscii();

        // second argument must be an IPrediction* pointer
        if(inputs[1].getType() != matlab::data::ArrayType::UINT64)
        {
            matlabPtr->feval(u"error", 0, 
                std::vector<matlab::data::Array>({ factory.createScalar("Second input must be of type uint64.")}));
            return;
        }
        std::cout<<"Prediction:Extract IPrediction pointer"<<std::endl;
        // extract the handle
        matlab::data::TypedArray<uint64_t> dataArray = std::move(inputs[1]);
        auto dataPtr = dataArray.release();
        uint64_t* dataRaw = dataPtr.get();
        IPrediction* prediction = (IPrediction*)(*dataRaw);


        if(method == "GetValues")
        {
            std::cout<<"Prediction:GetValues"<<std::endl;
            std::vector<double> values = prediction->GetValues();
            outputs[0] = factory
                .createArray<double>({1, values.size()}
                                     , values.data()
                                     , values.data() + values.size());
        }
        else if(method == "GetActiveWeightIndices")
        {
            std::cout<<"Prediction:GetActiveWeightIndices"<<std::endl;
            std::vector<unsigned int> values = prediction->GetActiveWeightIndices();
            outputs[0] = factory
                .createArray<uint32_t>({1, values.size()}
                                     , values.data()
                                     , values.data() + values.size());
        }
        else if(method == "GetActiveWeights")
        {
            std::cout<<"Prediction:GetActiveWeights"<<std::endl;
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
        else if(method == "GetBasisValues")
        {
            std::cout<<"Prediction:GetBasisValues"<<std::endl;
            std::vector<double> values = prediction->GetBasisValues();
            outputs[0] = factory
                .createArray<double>({1, values.size()}
                                     , values.data()
                                     , values.data() + values.size());
        }
        else if(method == "Delete")
        {
            std::cout<<"Prediction:Delete"<<std::endl;
            delete prediction;
        }
        else
        {
           matlabPtr->feval(u"error", 0, 
                std::vector<matlab::data::Array>({ factory.createScalar("Not a supported method.")}));
        }
    }
};
