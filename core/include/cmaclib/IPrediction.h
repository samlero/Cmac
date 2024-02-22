#ifndef IPREDICTION_H
#define IPREDICTION_H

#include <cmaclib/defines.h>
#include <cmaclib/IResult.h>

// Begin C++ Only Region.
#if defined(__cplusplus)
#include <vector>

namespace CmacLib
{
	/// @brief Prediction output.
	class CMACLIB_SHARED_SYMBOL IPrediction : public virtual IResult {
	public:
		/// @brief Get the calculated multiplication and accumulation of basis and active weights.
		/// @return Cmac output.
		virtual const std::vector<double>& GetValues() = 0;

		/// @brief Get the indices of the active weights.
		/// @return Active weight indices.
		virtual const std::vector<unsigned int>& GetActiveWeightIndices() = 0;

		/// @brief Get the values of the active weights.
		/// @return Active weight values.
		virtual const std::vector<std::vector<double>>& GetActiveWeights() = 0;

		/// @brief Get the basis function values.
		/// @return Basis function values.
		virtual const std::vector<double>& GetBasisValues() = 0;

		/// @brief Destructor.
		virtual ~IPrediction(){};
	};
}
#endif
// End C++ Only Region.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.