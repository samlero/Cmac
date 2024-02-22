#include "cmaclib/Factory.h"

#include <cmaclib/Cmac.h>
#include <cmaclib/Marshaller.h>
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

Factory::Factory(){}

Factory::~Factory(){}

/// @brief The default factory instance.
static Factory default_factory;

/// @brief Create a raw and untrained Cmac.
/// @param numQ Number of quantizations.
/// @param numLayers Number of layers (which would indicate number of active weights)
/// @param maxmem Maximum potential memory index or memory size.
/// @param numOut Number of outputs.
/// @param upperData Upper limits of the Predict method inputs. (array pointer)
/// @param upperSize Upper limits of the Predict method inputs. (array size)
/// @param lowerData Lower limits of the Predict method inputs. (array pointer)
/// @param lowerSize Lower limits of the Predict method inputs. (array size)
/// @param beta Learning rate.
/// @param nu Damping coefficient.
/// @return The pointer to the cmac instance.
CCmacLibICmac* CCmacLibCreateCmac(
	unsigned int numQ,
	unsigned int numLayers,
	unsigned int maxmem,
	unsigned int numOut,
	double* upperData,
	unsigned long upperSize,
	double* lowerData,
	unsigned long lowerSize,
	double beta,
	double nu
) {
    return default_factory.CreateCmac(
        numQ, numLayers, maxmem, numOut,
        ::std::vector<double>(upperData, upperData + upperSize),
        ::std::vector<double>(lowerData, lowerData + lowerSize),
        beta, nu
    ).release();
}

/// @brief Create a Cmac with default values.
/// @return The pointer to the cmac instance.
CCmacLibICmac* CCmacLibCreateDefaultCmac() {
    return default_factory.CreateDefaultCmac().release();
}

/// @brief Creates an instance of IMarshaller.
/// @return The pointer to the newly created marshaller instance.
CCmacLibIMarshaller* CCmacLibCreateMarshaller() {
    return default_factory.CreateMarshaller().release();
}