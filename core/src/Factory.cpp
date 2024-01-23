#include "Factory.h"
#include "Cmac.h"

using namespace CmacLib;

std::unique_ptr<ICmac> Factory::CreateCmac(unsigned int numQ, unsigned int numLayers
    , unsigned int maxmem, unsigned int numOut, std::vector<double> upper
    , std::vector<double> lower, double beta, double nu)
{
    return std::make_unique<Cmac>(numQ, numLayers
        , maxmem, numOut, upper, lower, beta, nu);
}

std::unique_ptr<ICmac> LoadCmac(std::string pathfile)
{

    // Need to update Cmac.h constructor to include all the member variables.
    // Either make a separate constructor or add missing ones to the currently existing constructor
    // and let them be empty by default.
    throw std::exception("LoadCmac NOT IMPLEMENTED.");
}
