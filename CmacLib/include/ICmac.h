#ifndef ICMAC_H
#define ICMAC_H

#include <memory>
#include "IPrediction.h"
#include "IAdjustment.h"
#include "IResult.h"

namespace CmacLib
{
	class ICmac {
	public:
		/// <summary>
		/// Calculate a prediction.
		/// </summary>
		/// <param name="input"></param>
		/// <returns></returns>
		virtual std::unique_ptr<IPrediction> Predict(std::vector<double>& input) = 0;
		/// <summary>
		/// Adjust the weights using an array of corrections and only the weights from a prediction.
		/// </summary>
		/// <param name="correction">Error values</param>
		/// <param name="prediction">Prediction to correct.</param>
		/// <param name="damping">Additional parameter to avoid overfitting</param>
		/// <returns></returns>
		virtual std::unique_ptr<IAdjustment> Adjust(std::vector<double>& correction
			, IPrediction* const prediction
			, double damping) = 0;
	};
}

#endif