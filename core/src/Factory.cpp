#include "Factory.h"
#include "Cmac.h"
#include "Marshaller.h"

#include <stdexcept>
#include <utility>

using namespace CmacLib;

std::unique_ptr<ICmac> Factory::CreateCmac(unsigned int numQ, unsigned int numLayers
    , unsigned int maxmem, unsigned int numOut, std::vector<double>&& upper
    , std::vector<double>&& lower, double beta, double nu)
{
    return std::make_unique<Cmac>(numQ, numLayers
        , maxmem, numOut, ::std::move(upper), ::std::move(lower), beta, nu);
}

std::unique_ptr<ICmac> CmacLib::Factory::CreateDefaultCmac()
{
    return std::make_unique<Cmac>(1, 1, 10, 1
        , std::vector<double>(1, 1.0), std::vector<double>(1, -1.0)
        , 0.0, 0.0);
}

std::unique_ptr<IMarshaller> CmacLib::Factory::CreateMarshaller()
{
    return std::make_unique<Marshaller>();
}
