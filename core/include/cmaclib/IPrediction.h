#ifndef IPREDICTION_H
#define IPREDICTION_H

#include <cmaclib/defines.h>
#include <cmaclib/IResult.h>
#include <cmaclib/collections.h>

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

// CCmacLibIPrediction Definition.
#if defined(__cplusplus)
typedef CmacLib::IPrediction CCmacLibIPrediction;
#else
typedef struct CCmacLibIPrediction CCmacLibIPrediction;
#endif
// END CCmacLibIPrediction Definition.

// C Wrappers.
#if defined(__cplusplus)
extern "C" {
#endif

/// @brief Get the calculated multiplication and accumulation
/// of basis and active weights.
/// @param pPrediction The pointer to the prediction instance.
/// @return Cmac output.
CDoubleArray CCmacLibIPredictionGetValues(
	CCmacLibIPrediction* pPrediction
);

/// @brief Get the indices of the active weights.
/// @param pPrediction The pointer to the prediction instance.
/// @return Active weight indices.
CUintArray CCmacLibIPredictionGetActiveWeightIndices(
	CCmacLibIPrediction* pPrediction
);

/// @brief Get the values of the active weights.
/// @param pPrediction The pointer to the prediction instance.
/// @return Active weight values.
/// (Remember to delete the CDoubleArray data pointer.)
CDoubleArrayArray CCmacLibIPredictionGetActiveWeights(
	CCmacLibIPrediction* pPrediction
);

/// @brief Get the basis function values.
/// @param pPrediction The pointer to the prediction instance.
/// @return Basis function values.
CDoubleArray CCmacLibIPredictionGetBasisValues(
	CCmacLibIPrediction* pPrediction
);

/// @brief Indicates if an operation was successful.
/// @param pPrediction The pointer to the prediction instance.
/// @return Success.
cmaclib_bool_t CCmacLibIPredictionIsSuccessful(
	CCmacLibIPrediction* pPrediction
);

/// @brief If not successful, a failure message is provided.
/// @param pPrediction The pointer to the prediction instance.
const char* CCmacLibIPredictionGetMessage(
	CCmacLibIPrediction* pPrediction
);

/// @brief Destructor.
/// @param pPrediction The pointer to the prediction instance.
void CCmacLibIPredictionDestroy(
	CCmacLibIPrediction* pPrediction
);

#if defined(__cplusplus)
}
#endif
// END C Wrappers.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.