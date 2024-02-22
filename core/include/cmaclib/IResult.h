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

// CCmacLibIResult Definition.
#if defined(__cplusplus)
typedef CmacLib::IResult CCmacLibIResult;
#else
typedef struct CCmacLibIResult CCmacLibIResult;
#endif
// END CCmacLibIResult Definition.

// C Wrappers.
#if defined(__cplusplus)
extern "C" {
#endif

/// @brief Indicates if an operation was successful.
/// @param pResult The pointer to the result instance.
/// @return Success.
cmaclib_bool_t CMACLIB_SHARED_SYMBOL CCmacLibIResultIsSuccessful(
	CCmacLibIResult* pResult
);

/// @brief If not successful, a failure message is provided.
/// @param pResult The pointer to the result instance.
const char* CMACLIB_SHARED_SYMBOL CCmacLibIResultGetMessage(
	CCmacLibIResult* pResult
);

/// @brief Destructor.
/// @param ppResult The pointer to the pointer to the result instance.
void CMACLIB_SHARED_SYMBOL CCmacLibIResultDestory(
	CCmacLibIResult** ppResult
);

#if defined(__cplusplus)
}
#endif
// END C Wrappers.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.