#ifndef IRESULT_H
#define IRESULT_H

#include <cmaclib/defines.h>

// Begin C++ Only Region.
#if defined(__cplusplus)
#include <string>

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
// End C++ Only Region.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.