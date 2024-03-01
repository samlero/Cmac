#include "cmaclib/Result.h"

#include <utility>

using namespace CmacLib;

void Result::SetIsSuccessful(bool success)
{
	this->successful = success;
}

void Result::SetMessage(std::string&& msg)
{
	this->message = ::std::move(msg);
}

Result::Result(): successful(false), message(""){}

Result::~Result(){}

bool Result::IsSuccessful()
{
	return this->successful;
}

std::string Result::GetMessage()
{
	return this->message;
}

/// @brief Indicates if an operation was successful.
/// @param pResult The pointer to the result instance.
/// @return Success.
cmaclib_bool_t CCmacLibIResultIsSuccessful(CCmacLibIResult* pResult) {
	return pResult->IsSuccessful();
}

/// @brief If not successful, a failure message is provided.
/// @param pResult The pointer to the result instance.
const char* CCmacLibIResultGetMessage(CCmacLibIResult* pResult) {
	return pResult->GetMessage().c_str();
}

/// @brief Destructor.
/// @param pResult The pointer to the result instance.
void CCmacLibIResultDestory(CCmacLibIResult* pResult) {
	if (pResult) delete pResult;
}