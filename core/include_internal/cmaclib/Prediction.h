#ifndef PREDICTION_H
#define PREDICTION_H

#pragma warning( disable : 4250) // disable dominance warning

#include <memory>
#include <vector>
#include <cmaclib/IPrediction.h>
#include <cmaclib/Result.h>

namespace CmacLib
{
	class Prediction : public Result, public virtual IPrediction {
	private:
		std::vector<double> values;
		std::vector<unsigned int> activeWeightIndices;
		std::vector<std::vector<double>> activeWeights;
		std::vector<double> basisValues;

	public: // setters
		void SetValues(std::vector<double>&& values);
		void SetActiveWeightIndices(std::vector<unsigned int>&& activeWeightIndices);
		void SetActiveWeights(std::vector<std::vector<double>>&& weights);
		void SetBasisValues(std::vector<double>&& basis);

	public: // constructor
		Prediction();
		~Prediction();

	public: // override getters
		const std::vector<double>& GetValues() override;
		const std::vector<unsigned int>& GetActiveWeightIndices() override;
		const std::vector<std::vector<double>>& GetActiveWeights() override;
		const std::vector<double>& GetBasisValues() override;
	};
}

#endif