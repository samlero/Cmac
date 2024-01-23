#include "mex.hpp"
#include "mexAdapter.hpp"
#include "ICmac.h"
#include "Factory.h"
#include <iostream>

using namespace CmacLib;

class MexFunction : public matlab::mex::Function {
    matlab::data::ArrayFactory factory;
public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs){
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();

        if(inputs.size() == 10)
        {
            std::cout<<"Factory:CreateCmac"<<std::endl;
            // check first input
            if(inputs[0].getType() != matlab::data::ArrayType::UINT64)
            {
                matlabPtr->feval(u"error", 0,
                    std::vector<matlab::data::Array>({ factory.createScalar("First input must be of type uint64.") }));
                return;
            }
            std::cout<<"Factory:CreateCmac: Extract factory pointer"<<std::endl;
            // get Factory pointer
            matlab::data::TypedArray<uint64_t> dataArray = std::move(inputs[0]);
            auto dataPtr = dataArray.release();
            uint64_t* dataRaw = dataPtr.get();
            Factory* cmacFactory = (Factory*)(*dataRaw);

            // check second input
            if(inputs[1].getType() != matlab::data::ArrayType::CHAR)
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("Second input must be of type string.")}));
                return;
            }
            std::cout<<"Factory:CreateCmac: Extract method name"<<std::endl;
            // extract the method name
            matlab::data::CharArray inChar(inputs[1]);
            std::string method = inChar.toAscii();
            // make sure method name is CreateCmac
            if(method != "CreateCmac")
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("The only supported method (for now) is CreateCmac.")}));
                return;
            }

            // check third-sixth inputs 
            if(inputs[2].getType() != matlab::data::ArrayType::UINT32
               || inputs[3].getType() != matlab::data::ArrayType::UINT32
               || inputs[4].getType() != matlab::data::ArrayType::UINT32
               || inputs[5].getType() != matlab::data::ArrayType::UINT32)
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("Inputs three to six should be unsigned int (32bit).")}));
                return;
            }
            std::cout<<"Factory:CreateCmac: Extract first set of arguments"<<std::endl;
            matlab::data::TypedArray<uint32_t> pNumQ = std::move(inputs[2]);
            matlab::data::TypedArray<uint32_t> pNumLayers = std::move(inputs[3]);
            matlab::data::TypedArray<uint32_t> pMaxMem = std::move(inputs[4]);
            matlab::data::TypedArray<uint32_t> pNumOut = std::move(inputs[5]);

            // check seventh and eight inputs
            if(inputs[6].getType() != matlab::data::ArrayType::DOUBLE
               || inputs[7].getType() != matlab::data::ArrayType::DOUBLE)
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("Inputs seven and eight should be double.")}));
                return;
            }
            std::cout<<"Factory:CreateCmac: Extract second set of arguments"<<std::endl;
            matlab::data::TypedArray<double> pUpper = std::move(inputs[6]);
            matlab::data::TypedArray<double> pLower = std::move(inputs[7]);
            // put them in a vector
            std::vector<double> upper(pUpper.begin(), pUpper.end());
            std::vector<double> lower(pLower.begin(), pLower.end());

            // check ninth and tenth inputs
            if(inputs[8].getType() != matlab::data::ArrayType::DOUBLE
               || inputs[9].getType() != matlab::data::ArrayType::DOUBLE)
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("Inputs nine and ten should be double.")}));
                return;
            }
            std::cout<<"Factory:CreateCmac: Extract third set of arguments"<<std::endl;
            matlab::data::TypedArray<double> pBeta = std::move(inputs[8]);
            matlab::data::TypedArray<double> pNu = std::move(inputs[9]);

            // checklist and extraction complete, call the method
            std::cout<<"Factory:CreateCmac: Call library method"<<std::endl;
            std::unique_ptr<ICmac> cmac = cmacFactory->CreateCmac(pNumQ[0]
                                                         , pNumLayers[0]
                                                         , pMaxMem[0]
                                                         , pNumOut[0]
                                                         , upper
                                                         , lower
                                                         , pBeta[0]
                                                         , pNu[0]);

            outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)cmac.release());
        }
        else if(inputs.size() == 1) // constructor
        {
            std::cout<< "Factory:Constructor" << std::endl;
            if(inputs[0].getType() != matlab::data::ArrayType::CHAR)
            {
                matlabPtr->feval(u"error", 0,
                    std::vector<matlab::data::Array>({ factory.createScalar("First input must be of a char array.") }));
                return;
            }

            // extract the method name
            std::cout<< "Factory:Constructor: Get method name" << std::endl;
            matlab::data::CharArray inChar(inputs[0]);
            std::cout<< "Factory:Constructor: Get method name 3" << std::endl;
            std::string method = inChar.toAscii();
            // make sure method name is CreateCmac
            if(method != "New")
            {
                matlabPtr->feval(u"error", 0,
                    std::vector<matlab::data::Array>({ factory.createScalar("Method name should be New.") }));
                return;
            }

            std::cout<< "Factory:Constructor: Create factory" << std::endl;
            Factory* cmacFactory = new Factory();
            outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)cmacFactory);
        }
        else if(inputs.size() == 2) // destructor
        {
            std::cout<< "Factory:Delete" << std::endl;
            // first input should be a pointer
            if(inputs[0].getType() != matlab::data::ArrayType::UINT64)
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("First input must be of type uint64.")}));
                return;
            }
            std::cout<< "Factory:Delete: Get pointer" << std::endl;
            // get Factory pointer
            matlab::data::TypedArray<uint64_t> dataArray = std::move(inputs[0]);
            auto dataPtr = dataArray.release();
            uint64_t* dataRaw = dataPtr.get();
            Factory* cmacFactory = (Factory*)(*dataRaw);

            // second input should be a method name
            if(inputs[1].getType() != matlab::data::ArrayType::CHAR)
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("Second input must be of type char array.")}));
                return;
            }
            std::cout<< "Factory:Delete: Get method name" << std::endl;
            // extract the method name
            matlab::data::CharArray inChar(inputs[1]);
            std::string method = inChar.toAscii();
            // make sure method name is CreateCmac
            if(method != "Delete")
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("The method call should be Delete.")}));
                return;
            }

            std::cout<< "Factory:Delete: call delete" << std::endl;
            delete cmacFactory;
        }
        else
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("Number of inputs should be either 1, 2 or 10.")}));
            return;
        }
    }
};