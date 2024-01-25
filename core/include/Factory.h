#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include <string>
#include "ICmac.h"
#include "IMarshaller.h"

namespace CmacLib
{
	/// @brief Creates Cmac objects.
	class Factory {
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
	};
}

#endif