#ifndef IADJUSTMENT_H
#define IADJUSTMENT_H

#include <vector>
#include "IResult.h"

class IAdjustment {
public:
	/// <summary>
	/// Gets the amount each weight changed in each output level. 
	/// </summary>
	/// <returns></returns>
	virtual const std::vector<std::vector<double>>& GetWeightChanges() = 0;
	/// <summary>
	/// Indicates if the adjustment was successful or not and provides some reason as to why it failed.
	/// </summary>
	/// <returns></returns>
	virtual const IResult& GetResult() = 0;
};

#endif