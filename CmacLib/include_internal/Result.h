#ifndef RESULT_H
#define RESULT_H

#include <string>
#include "IResult.h"

class Result : public IResult{
private:
	bool successful;
	std::string message;

public:
	Result(bool success, std::string msg);
	~Result();

public: // overrides
	bool IsSuccessful() override;
	std::string GetMessage() override;
};

#endif