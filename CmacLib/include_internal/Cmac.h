#ifndef CMAC_H
#define CMAC_H

#include <memory>
#include <vector>
#include "IPrediction.h"
#include "IAdjustment.h"
#include "ICmac.h"

class Cmac: public ICmac {
private:
	unsigned int numQ, numLayers, maxHash, numOutput, numInput;
	std::vector<double> upper, lower;
	double beta, nu;

	std::vector<std::vector<double>> memory;
	std::vector<unsigned int> hashtable;

public:
	Cmac(unsigned int numQ
		, unsigned int numLayers
		, unsigned int maxHash
		, std::vector<double> upper
		, std::vector<double> lower
		, double beta
		, double nu);

	Cmac(unsigned int numQ
		, unsigned int numLayers
		, unsigned int maxHash
		, std::vector<double> upper
		, std::vector<double> lower
		, double beta
		, double nu
		, std::vector<std::vector<double>>& memory
		, std::vector<unsigned int>& hashtable);
	~Cmac();

	std::unique_ptr<IPrediction> Predict(std::vector<double>& input) override;
	std::unique_ptr<IAdjustment> Adjust(std::vector<double>& correction
		, std::vector<std::vector<unsigned int>>& indices
		, double damping) override;
};

#endif