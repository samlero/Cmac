#include "mex.hpp"
#include "mexAdapter.hpp"
#include "IAdjustment.h"
#include "IResult.h"

using namespace CmacLib;

class InputIndex
{
public:
    const static unsigned int METHOD = 1;
    const static unsigned int POINTER = 2;
};

class Method
{
public:
    const static unsigned int DELETE = 0;
    const static unsigned int GET_WEIGHT_CHANGES = 100;
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
        matlab::data::TypedArray<uint32_t> methodData = std::move(inputs[InputIndex::METHOD]);
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
        IAdjustment* adjustment = (IAdjustment*)(*dataRaw);

        #if Debug
        std::cout<<"AdjustmentMex: Pointer: "<< *dataRaw <<std::endl;
        #endif

        if(method == Method::GET_WEIGHT_CHANGES)
        {
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
            #if Debug
            std::cout << "AdjustmentMex: GetWeightChanges method." << std::endl;
            #endif
        }
        else if(method == Method::DELETE)
        {
            delete adjustment;
            #if Debug
            std::cout << "AdjustmentMex: Delete method." << std::endl;
            #endif
        }
        else if(method == Method::IS_SUCCESSFUL)
        {
            bool success = adjustment->IsSuccessful();
            outputs[0] = factory.createScalar<bool>(success);
            #if Debug
            std::cout << "AdjustmentMex: IsSuccessful method." << std::endl;
            #endif
        }
        else if(method == Method::GET_MESSAGE)
        {
            std::string msg = adjustment->GetMessage();
            outputs[0] = factory.createCharArray(msg);
            #if Debug
            std::cout << "AdjustmentMex: GetMessage method." << std::endl;
            #endif
        }
        else
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("Not a supported method.")}));
        }
    }
};