#ifndef IADJUSTMENT_H
#define IADJUSTMENT_H

#include <cmaclib/defines.h>
#include <cmaclib/IResult.h>

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
double** CMACLIB_SHARED_SYMBOL CCmacLibIAdjustmentGetWeightChanges(
	CCmacLibIAdjustment* pAdjustment
);

/// @brief Indicates if an operation was successful.
/// @param pAdjustment The pointer to the adjustment instance.
/// @return Success.
cmaclib_bool_t CMACLIB_SHARED_SYMBOL CCmacLibIAdjustmentIsSuccessful(
	CCmacLibIAdjustment* pAdjustment
);

/// @brief If not successful, a failure message is provided.
/// @param pAdjustment The pointer to the adjustment instance.
const char* CMACLIB_SHARED_SYMBOL CCmacLibIAdjustmentGetMessage(
	CCmacLibIAdjustment* pAdjustment
);

/// @brief Destructor.
/// @param ppAdjustment The pointer to the pointer to the adjustment instance.
void CMACLIB_SHARED_SYMBOL CCmacLibIAdjustmentDestroy(
	CCmacLibIAdjustment** ppAdjustment
);

#if defined(__cplusplus)
}
#endif
// END C Wrappers.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.