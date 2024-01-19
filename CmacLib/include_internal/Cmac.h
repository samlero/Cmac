#ifndef CMAC_H
#define CMAC_H

#include <memory>
#include <vector>
#include "IPrediction.h"
#include "IAdjustment.h"
#include "ICmac.h"

class Cmac: public ICmac {
private:
	unsigned int numQ, numLayers, maxMem, maxHashValue, numOutput, numInput;
	std::vector<double> upper, lower;
	double beta, nu;

	// contains all weights (output by weight)
	std::vector<std::vector<double>> memory;
	// contains indices to the weights
	std::vector<size_t> hashtable;
	// contains normalizing denominator for the inputs
	std::vector<double> denominator;
	// offset in each layer
	std::vector<std::vector<double>> offsets;

private: // methods
	/// <summary>
	/// Normalizes the input.
	/// </summary>
	/// <param name="raw"></param>
	/// <returns></returns>
	std::vector<double> Normalize(std::vector<double>& raw);

public:
	Cmac(unsigned int numQ
		, unsigned int numLayers
		, unsigned int maxmem
		, unsigned int numOut
		, std::vector<double> upper
		, std::vector<double> lower
		, double beta
		, double nu);

	/** Include this once we have saving and loading ready.
	Cmac(unsigned int numQ
		, unsigned int numLayers
		, unsigned int maxHash
		, std::vector<double> upper
		, std::vector<double> lower
		, double beta
		, double nu
		, std::vector<std::vector<double>>& memory
		, std::vector<unsigned int>& hashtable);
		**/
	~Cmac();

	std::unique_ptr<IPrediction> Predict(std::vector<double>& input) override;
	std::unique_ptr<IAdjustment> Adjust(std::vector<double>& correction
		, const IPrediction* prediction
		, double damping) override;
};

#endif