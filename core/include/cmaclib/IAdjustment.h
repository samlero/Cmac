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

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.