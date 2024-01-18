#ifndef CMAC_H
#define CMAC_H

#include <memory>
#include <vector>
#include "IPrediction.h"
#include "IAdjustment.h"

class Cmac {
private:
	class CmacImpl;
	std::unique_ptr<CmacImpl> pImpl;
public:

	Cmac(unsigned int numQ
		, unsigned int numLayers
		, unsigned int maxHash
		, std::vector<double> upper
		, std::vector<double> lower
		, double beta
		, double nu);

	// TODO: Cmac(std::string filepath)

	~Cmac();

	/// <summary>
	/// Calculate a prediction.
	/// </summary>
	/// <param name="input"></param>
	/// <returns></returns>
	std::unique_ptr<IPrediction> Predict(std::vector<double>& input);
	/// <summary>
	/// Adjust the weights.
	/// </summary>
	/// <param name="correction">Errors to correct the weights by.</param>
	/// <param name="indices">Indices of the weights to adjust.</param>
	/// <param name="damping">Additional damping value to avoid overfitting.</param>
	/// <returns></returns>
	std::unique_ptr<IAdjustment> Adjust(std::vector<double>& correction, std::vector<std::vector<unsigned int>> indices, double damping);
};

#endif