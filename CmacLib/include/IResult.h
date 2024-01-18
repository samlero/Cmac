#ifndef IRESULT_H
#define IRESULT_H

#include <string>

class IResult {
public:
	virtual bool IsSuccessful() = 0;
	virtual std::string GetMessage() = 0;
};

#endif