#ifndef PREDICTION_H
#define PREDICTION_H

#include <memory>
#include <vector>
#include "IPrediction.h"

namespace CmacLib
{
	class Prediction : public IPrediction {
	private:
		std::vector<double> values;
		std::vector<size_t> activeWeightIndices;
		std::vector<std::vector<double>> activeWeights;
		std::vector<double> basisValues;
		std::unique_ptr<IResult> result;

	public: // setters
		void SetValues(std::vector<double>& values);
		void SetActiveWeightIndices(std::vector<size_t>& activeWeightIndices);
		void SetActiveWeights(std::vector<std::vector<double>>& weights);
		void SetBasisValues(std::vector<double>& basis);
		void SetResult(IResult* result);

	public: // constructor
		Prediction();
		~Prediction();

	public: // override getters
		const std::vector<double>& GetValues() override;
		const std::vector<size_t>& GetActiveWeightIndices() override;
		const std::vector<std::vector<double>>& GetActiveWeights() override;
		const std::vector<double>& GetBasisValues() override;
		const IResult& GetResult() override;
	};
}

#endif