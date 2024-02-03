#include "mex.hpp"
#include "mexAdapter.hpp"
#include "CmacLib.h"
#include <iostream>
#include <utility>
#include <iterator>

using namespace CmacLib;

class InputIndex
{
    public:
    const static unsigned int METHOD = 0;
    const static unsigned int POINTER = 1;
    const static unsigned int CREATE_CMAC_NUM_Q = 2;
    const static unsigned int CREATE_CMAC_NUM_LAYERS = 3;
    const static unsigned int CREATE_CMAC_MAX_MEMORY = 4;
    const static unsigned int CREATE_CMAC_NUM_OUTPUT = 5;
    const static unsigned int CREATE_CMAC_UPPER_LIMITS = 6;
    const static unsigned int CREATE_CMAC_LOWER_LIMITS = 7;
    const static unsigned int CREATE_CMAC_BETA = 8;
    const static unsigned int CREATE_CMAC_NU = 9;
};

class InputSize
{
    public:
    const static unsigned int NEW = 1;
    const static unsigned int DELETE = 2;
    const static unsigned int CREATE_CMAC = 10;
    const static unsigned int CREATE_MARSHALLER = 2;
    const static unsigned int CREATE_DEFAULT_CMAC = 2;
};

class Method
{
    public:
    const static unsigned int NEW = 0;
    const static unsigned int DELETE = 1;
    const static unsigned int CREATE_CMAC = 100;
    const static unsigned int CREATE_MARSHALLER = 101;
    const static unsigned int CREATE_DEFAULT_CMAC = 102;
};

class MexFunction : public matlab::mex::Function {
    matlab::data::ArrayFactory factory;

    private:
    Factory* GetPointer(matlab::mex::ArgumentList inputs
                        , std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr)
    {
        if(inputs[InputIndex::POINTER].getType() != matlab::data::ArrayType::UINT64)
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("Expected uint64 for pointer value.")}));
        }

        matlab::data::TypedArray<uint64_t> dataArray = std::move(inputs[InputIndex::POINTER]);
        auto dataPtr = dataArray.release();
        uint64_t* dataRaw = dataPtr.get();
        Factory* cmacFactory = (Factory*)(*dataRaw);
        return cmacFactory;
    }

    public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs){
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();

        if(inputs.size() > 0)
        {
            // extract method type
            if(inputs[InputIndex::METHOD].getType() != matlab::data::ArrayType::UINT32)
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("FactoryMex: Expected uint32 for the method type.")}));
            }
            matlab::data::TypedArray<uint32_t> methodData
                = std::move(inputs[InputIndex::METHOD]);
            auto methodPtr = methodData.release();
            uint32_t* methodRaw = methodPtr.get();
            uint32_t method = *methodRaw;

            if(method == Method::NEW
               && inputs.size() == InputSize::NEW)
            {
                std::unique_ptr<Factory> cmacFactory = std::make_unique<Factory>();
                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)cmacFactory.release());

                #if Debug
                std::cout << "FactoryMex: Successful construction." << std::endl;
                #endif
            }
            else if(method == Method::DELETE
                    && inputs.size() == InputSize::DELETE)
            {
                Factory* ptr = this->GetPointer(inputs, matlabPtr);
                delete ptr;

                #if Debug
                std::cout << "FactoryMex: Successful deletion." << std::endl;
                #endif
            }
            else if(method == Method::CREATE_CMAC
                    && inputs.size() == InputSize::CREATE_CMAC)
            {
                Factory* ptr = this->GetPointer(inputs, matlabPtr);
                // check third-sixth inputs
                if(inputs[InputIndex::CREATE_CMAC_NUM_Q].getType() != matlab::data::ArrayType::UINT32
                   || inputs[InputIndex::CREATE_CMAC_NUM_LAYERS].getType() != matlab::data::ArrayType::UINT32
                   || inputs[InputIndex::CREATE_CMAC_MAX_MEMORY].getType() != matlab::data::ArrayType::UINT32
                   || inputs[InputIndex::CREATE_CMAC_NUM_OUTPUT].getType() != matlab::data::ArrayType::UINT32)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Inputs three to six should be unsigned int (32bit).")}));
                }
                std::cout<<"Factory:CreateCmac: Extract first set of arguments"<<std::endl;
                matlab::data::TypedArray<uint32_t> pNumQ = std::move(inputs[InputIndex::CREATE_CMAC_NUM_Q]);
                matlab::data::TypedArray<uint32_t> pNumLayers = std::move(inputs[InputIndex::CREATE_CMAC_NUM_LAYERS]);
                matlab::data::TypedArray<uint32_t> pMaxMem = std::move(inputs[InputIndex::CREATE_CMAC_MAX_MEMORY]);
                matlab::data::TypedArray<uint32_t> pNumOut = std::move(inputs[InputIndex::CREATE_CMAC_NUM_OUTPUT]);

                // check seventh and eight inputs
                if(inputs[InputIndex::CREATE_CMAC_UPPER_LIMITS].getType() != matlab::data::ArrayType::DOUBLE
                   || inputs[InputIndex::CREATE_CMAC_LOWER_LIMITS].getType() != matlab::data::ArrayType::DOUBLE)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Inputs seven and eight should be double.")}));
                }
                matlab::data::TypedArray<double> pUpper = std::move(inputs[InputIndex::CREATE_CMAC_UPPER_LIMITS]);
                matlab::data::TypedArray<double> pLower = std::move(inputs[InputIndex::CREATE_CMAC_LOWER_LIMITS]);
                // put them in a vector
                std::vector<double> upper(
                    ::std::make_move_iterator(pUpper.begin()),
                    ::std::make_move_iterator(pUpper.end())
                );
                std::vector<double> lower(
                    ::std::make_move_iterator(pLower.begin()),
                    ::std::make_move_iterator(pLower.end())
                );

                // check ninth and tenth inputs
                if(inputs[InputIndex::CREATE_CMAC_BETA].getType() != matlab::data::ArrayType::DOUBLE
                   || inputs[InputIndex::CREATE_CMAC_NU].getType() != matlab::data::ArrayType::DOUBLE)
                {
                    matlabPtr->feval(u"error", 0,
                                     std::vector<matlab::data::Array>({ factory.createScalar("Inputs nine and ten should be double.")}));
                }
                matlab::data::TypedArray<double> pBeta = std::move(inputs[InputIndex::CREATE_CMAC_BETA]);
                matlab::data::TypedArray<double> pNu = std::move(inputs[InputIndex::CREATE_CMAC_NU]);

                // checklist and extraction complete, call the method
                std::unique_ptr<ICmac> cmac = ptr->CreateCmac(pNumQ[0]
                                                              , pNumLayers[0]
                                                              , pMaxMem[0]
                                                              , pNumOut[0]
                                                              , ::std::move(upper)
                                                              , ::std::move(lower)
                                                              , pBeta[0]
                                                              , pNu[0]);

                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)cmac.release());
                #if Debug
                std::cout << "FactoryMex: CreateCmac." << std::endl;
                #endif
            }
            else if(method == Method::CREATE_MARSHALLER
                    && inputs.size() == InputSize::CREATE_MARSHALLER)
            {
                Factory* ptr = this->GetPointer(inputs, matlabPtr);
                std::unique_ptr<IMarshaller> marshaller
                    = ptr->CreateMarshaller();
                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)marshaller.release());
                #if Debug
                std::cout << "FactoryMex: CreateMarshaller." << std::endl;
                #endif
            }
            else if(method == Method::CREATE_DEFAULT_CMAC
                    && inputs.size() == InputSize::CREATE_DEFAULT_CMAC)
            {
                Factory* ptr = this->GetPointer(inputs, matlabPtr);
                std::unique_ptr<ICmac> cmac = ptr->CreateDefaultCmac();
                outputs[0] = factory.createScalar<uint64_t>((uint64_t)(void*)cmac.release());
                #if Debug
                std::cout << "FactoryMex: CreateDefaultCmac." << std::endl;
                #endif
            }
            else
            {
                matlabPtr->feval(u"error", 0,
                                 std::vector<matlab::data::Array>({ factory.createScalar("FactoryMex: Not a supported method or invalid input size.")}));
            }
        }
        else
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>({ factory.createScalar("FactoryMex: Must have at least one input.") }));
        }
    }
};