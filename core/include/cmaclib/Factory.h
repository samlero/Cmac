#ifndef FACTORY_H
#define FACTORY_H

#include <cmaclib/defines.h>
#include <cmaclib/ICmac.h>
#include <cmaclib/IMarshaller.h>

// Begin C++ Only Region.
#if defined(__cplusplus)
#include <memory>
#include <string>

namespace CmacLib
{
	/// @brief Creates Cmac objects.
	class CMACLIB_SHARED_SYMBOL Factory {
	public:
		/// @brief Create a raw and untrained Cmac.
		/// @param numQ Number of quantizations.
		/// @param numLayers Number of layers (which would indicate number of active weights)
		/// @param maxmem Maximum potential memory index or memory size.
		/// @param numOut Number of outputs.
		/// @param upper Upper limits of the Predict method inputs.
		/// @param lower Lower limits of the Predict method inputs.
		/// @param beta Learning rate.
		/// @param nu Damping coefficient.
		/// @return ICmac.
		std::unique_ptr<ICmac> CreateCmac(unsigned int numQ
			, unsigned int numLayers
			, unsigned int maxmem
			, unsigned int numOut
			, std::vector<double>&& upper
			, std::vector<double>&& lower
			, double beta
			, double nu);

		/// @brief Create a Cmac with default values.
		/// @return ICmac
		std::unique_ptr<ICmac> CreateDefaultCmac();

		/// @brief Creates an instance of IMarshaller.
		/// @return IMarshaller object
		std::unique_ptr<IMarshaller> CreateMarshaller();

		Factory();
		~Factory();
	};
}
#endif
// End C++ Only Region.

// C Wrappers.
#if defined(__cplusplus)
extern "C" {
#endif

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
CMACLIB_SHARED_SYMBOL CCmacLibICmac* CCmacLibCreateCmac(
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
);

/// @brief Create a Cmac with default values.
/// @return The pointer to the cmac instance.
CMACLIB_SHARED_SYMBOL CCmacLibICmac* CCmacLibCreateDefaultCmac();

/// @brief Creates an instance of IMarshaller.
/// @return The pointer to the newly created marshaller instance.
CMACLIB_SHARED_SYMBOL CCmacLibIMarshaller* CCmacLibCreateMarshaller();

#if defined(__cplusplus)
}
#endif
// END C Wrappers.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.