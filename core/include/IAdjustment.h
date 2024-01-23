#ifndef IADJUSTMENT_H
#define IADJUSTMENT_H

#include <vector>
#include "IResult.h"

namespace CmacLib
{
	/// @brief Contains weight adjustment data.
	class IAdjustment {
	public:

		/// @brief Get the amount the each active weight changed.
		/// @return Weight change dW.
		virtual const std::vector<std::vector<double>>& GetWeightChanges() = 0;

		/// @brief Get the result (if not successful, a message of the failure is provided).
		/// @return Operation result.
		virtual IResult* const GetResult() = 0;
		
		/// @brief Destructor
		virtual ~IAdjustment(){};
	};
}

#endif