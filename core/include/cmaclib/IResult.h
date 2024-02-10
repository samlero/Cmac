#ifndef IRESULT_H
#define IRESULT_H

#include <string>
#include <cmaclib/defines.h>

namespace CmacLib
{
	/// @brief Result.
	class CMACLIB_SHARED_SYMBOL IResult {
	public:

		/// @brief Indicates if an operation was successful.
		/// @return Success.
		virtual bool IsSuccessful() = 0;

		/// @brief If not successful, a failure message is provided.
		/// @return 
		virtual std::string GetMessage() = 0;

		/// @brief Destructor
		virtual ~IResult(){};
	};
}

#endif