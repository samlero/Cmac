#include "Result.h"
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







