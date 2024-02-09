#ifndef IADJUSTMENT_H
#define IADJUSTMENT_H

#include <vector>
#include <cmaclib/IResult.h>

namespace CmacLib
{
	/// @brief Contains weight adjustment data.
	class IAdjustment : public virtual IResult {
	public:

		/// @brief Get the amount the each active weight changed.
		/// @return Weight change dW.
		virtual const std::vector<std::vector<double>>& GetWeightChanges() = 0;
		
		/// @brief Destructor
		virtual ~IAdjustment(){};
	};
}

#endif