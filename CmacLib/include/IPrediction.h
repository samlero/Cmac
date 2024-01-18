#ifndef IPREDICTION_H
#define IPREDICTION_H

#include <vector>
#include "IResult.h"

class IPrediction {
public:
	/// <summary>
	/// Get the main output of the prediction.
	/// </summary>
	/// <returns></returns>
	virtual const std::vector<double>& GetValues() = 0;
	/// <summary>
	/// Get the indices of the active weights.
	/// </summary>
	/// <returns></returns>
	virtual const std::vector<std::vector<unsigned int>>& GetActiveWeightIndices() = 0;
	/// <summary>
	/// Get the values of the active weights in each layer and output.
	/// </summary>
	/// <returns></returns>
	virtual const std::vector<std::vector<double>>& GetActiveWeights() = 0;
	/// <summary>
	/// Indicates if the prediction was successful or not, and provides a reason as to why the prediction failed.
	/// </summary>
	/// <returns></returns>
	virtual const IResult& GetResult() = 0;
};

#endif