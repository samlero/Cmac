#ifndef PREDICTION_H
#define PREDICTION_H

#include <memory>
#include <vector>
#include "IPrediction.h"

class Prediction : public IPrediction{
private:
	std::vector<double> values;
	std::vector<std::vector<unsigned int>> activeWeightIndices;
	std::vector<std::vector<double>> activeWeights;
	std::vector<double> basisValues;
	std::unique_ptr<IResult> result;

public: // constructor
	Prediction(std::vector<double>& values
	, std::vector<std::vector<unsigned int>>& weightIndices
	, std::vector<std::vector<double>>& weightValues
	, std::vector<double>& basis
	, IResult* result);
	Prediction(IResult* result);
	~Prediction();

public: // override getters
	const std::vector<double>& GetValues() override;
	const std::vector<std::vector<unsigned int>>& GetActiveWeightIndices() override;
	const std::vector<std::vector<double>>& GetActiveWeights() override;
	const std::vector<double>& GetBasisValues() override;
	const IResult& GetResult() override;
};

#endif