#ifndef IRESULT_H
#define IRESULT_H

#include <string>

namespace CmacLib
{
	class IResult {
	public:
		/// <summary>
		/// Indicates if an action was successful or not.
		/// </summary>
		/// <returns></returns>
		virtual bool IsSuccessful() = 0;
		/// <summary>
		///  If unsuccessful, a message is provided for the cause.
		/// </summary>
		/// <returns></returns>
		virtual std::string GetMessage() = 0;

		virtual ~IResult(){};
	};
}

#endif