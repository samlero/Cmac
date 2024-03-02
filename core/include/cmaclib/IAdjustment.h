#ifndef IADJUSTMENT_H
#define IADJUSTMENT_H

#include <cmaclib/defines.h>
#include <cmaclib/IResult.h>
#include <cmaclib/collections.h>

// Begin C++ Only Region.
#if defined(__cplusplus)
#include <vector>

namespace CmacLib
{
	/// @brief Contains weight adjustment data.
	class CMACLIB_SHARED_SYMBOL IAdjustment : public virtual IResult {
	public:

		/// @brief Get the amount the each active weight changed.
		/// @return Weight change dW.
		virtual const std::vector<std::vector<double>>& GetWeightChanges() = 0;
		
		/// @brief Destructor
		virtual ~IAdjustment(){};
	};
}
#endif
// End C++ Only Region.

// CCmacLibIAdjustment Definition.
#if defined(__cplusplus)
typedef CmacLib::IAdjustment CCmacLibIAdjustment;
#else
typedef struct CCmacLibIAdjustment CCmacLibIAdjustment;
#endif
// END CCmacLibIAdjustment Definition.

// C Wrappers.
#if defined(__cplusplus)
extern "C" {
#endif

/// @brief Get the amount the each active weight changed.
/// @param pAdjustment The pointer to the adjustment instance.
/// @return Weight change dW.
/// (Remember to delete the CDoubleArray data pointer.)
CDoubleArrayArray CCmacLibIAdjustmentGetWeightChanges(
	CCmacLibIAdjustment* pAdjustment
);

/// @brief Indicates if an operation was successful.
/// @param pAdjustment The pointer to the adjustment instance.
/// @return Success.
cmaclib_bool_t CCmacLibIAdjustmentIsSuccessful(
	CCmacLibIAdjustment* pAdjustment
);

/// @brief If not successful, a failure message is provided.
/// @param pAdjustment The pointer to the adjustment instance.
const char* CCmacLibIAdjustmentGetMessage(
	CCmacLibIAdjustment* pAdjustment
);

/// @brief Destructor.
/// @param pAdjustment The pointer to the adjustment instance.
void CCmacLibIAdjustmentDestroy(
	CCmacLibIAdjustment* pAdjustment
);

#if defined(__cplusplus)
}
#endif
// END C Wrappers.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.