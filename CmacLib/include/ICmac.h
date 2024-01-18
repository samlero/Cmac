#ifndef ICMAC_H
#define ICMAC_H

#include <memory>
#include "IPrediction.h"
#include "IAdjustment.h"
#include "IResult.h"

class ICmac {
public:
	/// <summary>
	/// Calculate a prediction.
	/// </summary>
	/// <param name="input"></param>
	/// <returns></returns>
	virtual std::unique_ptr<IPrediction> Predict(std::vector<double>& input) = 0;
	/// <summary>
	/// Adjust the weights.
	/// </summary>
	/// <param name="correction">Errors to correct the weights by.</param>
	/// <param name="indices">Indices of the weights to adjust.</param>
	/// <param name="damping">Additional damping value to avoid overfitting.</param>
	/// <returns></returns>
	virtual std::unique_ptr<IAdjustment> Adjust(std::vector<double>& correction
		, std::vector<std::vector<unsigned int>>& indices
		, double damping) = 0;
};

#endif