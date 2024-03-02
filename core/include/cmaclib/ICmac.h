#ifndef ICMAC_H
#define ICMAC_H

#include <cmaclib/defines.h>
#include <cmaclib/IPrediction.h>
#include <cmaclib/IAdjustment.h>
#include <cmaclib/IResult.h>
#include <cmaclib/ISerializable.h>

// Begin C++ Only Region.
#if defined(__cplusplus)
#include <memory>

namespace CmacLib
{
	/// @brief Cerebellar Model Articulation Controller (CMAC)
	class CMACLIB_SHARED_SYMBOL ICmac : public virtual ISerializable{
	public:

		/// @brief Acquires active weights and associated basis values, then multiply and sum to produce an output.
		/// @param input States.
		/// @return Prediction result.
		virtual std::unique_ptr<IPrediction> Predict(const std::vector<double>& input) = 0;

		/// @brief Train the weights of the Cmac.
		/// @param correction Error of the prediction.
		/// @param prediction Contains indices of weights and basis values.
		/// @param damping Additional damping to further reduce chances of overfitting.
		/// @return Adjustment result.
		virtual std::unique_ptr<IAdjustment> Adjust(const std::vector<double>& correction
			, IPrediction* const prediction
			, double damping) = 0;

		/// @brief Sets all the weights in memory to zero, untraining the Cmac.
		/// @return Result of the operation.
		virtual std::unique_ptr<IResult> Zeroize() = 0;

		/// @brief Destructor
		virtual ~ICmac(){};
	};
}
#endif
// End C++ Only Region.

// CCmacLibICmac definition.
#if defined(__cplusplus)
typedef CmacLib::ICmac CCmacLibICmac;
#else
typedef struct CCmacLibICmac CCmacLibICmac;
#endif
// END CCmacLibICmac definition.

// C Wrappers.
#if defined(__cplusplus)
extern "C" {
#endif

/// @brief Acquires active weights and associated basis values,
/// then multiply and sum to produce an output.
/// @param pCmac The pointer to the cmac instance.
/// @param inputData States. (array pointer)
/// @param inputSize States. (array size)
/// @return Prediction result.
CMACLIB_SHARED_SYMBOL CCmacLibIPrediction* CCmacLibICmacPredict(
	CCmacLibICmac* pCmac, double* inputData, unsigned long inputSize
);

/// @brief Train the weights of the Cmac.
/// @param pCmac The pointer to the cmac instance.
/// @param correctionData Error of the prediction. (array pointer)
/// @param correctionSize Error of the prediction. (array size)
/// @param pPrediction Contains indices of weights and basis values.
/// @param damping Additional damping to further reduce chances of overfitting.
/// @return Adjustment result.
CMACLIB_SHARED_SYMBOL CCmacLibIAdjustment* CCmacLibICmacAdjust(
	CCmacLibICmac* pCmac, double* correctionData, unsigned long correctionSize,
	CCmacLibIPrediction* pPrediction, double damping
);

/// @brief Sets all the weights in memory to zero, untraining the Cmac.
/// @param pCmac The pointer to the cmac instance.
/// @return Result of the operation.
CMACLIB_SHARED_SYMBOL CCmacLibIResult* CCmacLibICmacZeroize(
	CCmacLibICmac* pCmac
);

/// @brief Serializes the object in its own unique format.
/// @param pCmac The pointer to the cmac instance.
/// @return Serialized string.
CMACLIB_SHARED_SYMBOL CCmacLibISerialization* CCmacLibICmacSerialize(
	CCmacLibICmac* pCmac
);

/// @brief Deserializes the content into its member variables.
/// @param pCmac The pointer to the cmac instance.
/// @param content Valid deserializable content.
CMACLIB_SHARED_SYMBOL CCmacLibIResult* CCmacLibICmacDeserialize(
	CCmacLibICmac* pCmac, const char* content
);

/// @param pCmac The pointer to the cmac instance.
/// @return The extension of the serializable object
CMACLIB_SHARED_SYMBOL const char* CCmacLibICmacGetExtension(
	CCmacLibICmac* pCmac
);

/// @brief Destructor.
/// @param pCmac The pointer to the cmac instance.
CMACLIB_SHARED_SYMBOL void CCmacLibICmacDestroy(
	CCmacLibICmac* pCmac
);

#if defined(__cplusplus)
}
#endif
// END C Wrappers.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.