#ifndef RESULT_H
#define RESULT_H

#include <string>
#include <cmaclib/IResult.h>

namespace CmacLib
{
	class Result : public virtual IResult {
	private:
		bool successful;
		std::string message;

	public: // setters
		void SetIsSuccessful(bool success);
		void SetMessage(std::string&& msg);

	public:
		Result();
		~Result();

	public: // overrides
		bool IsSuccessful() override;
		std::string GetMessage() override;
	};
}

#endif