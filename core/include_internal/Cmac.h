#ifndef CMAC_H
#define CMAC_H

#include <memory>
#include <vector>
#include "IPrediction.h"
#include "IAdjustment.h"
#include "ICmac.h"

namespace CmacLib
{
	class Cmac : public ICmac {
	private:
		unsigned int numQ, numLayers, maxMem, maxHashValue, numOutput, numInput;
		std::vector<double> upper, lower;
		double beta, nu;

		// contains all weights (output by weight)
		std::vector<std::vector<double>> memory;
		// contains indices to the weights
		std::vector<unsigned int> hashtable;
		// contains normalizing denominator for the inputs
		std::vector<double> denominator;
		// offset in each layer
		std::vector<std::vector<double>> offsets;

	private:
		/// @brief Normalize the raw data.
		/// @param raw The vec of data to be normalized.
		void Normalize(std::vector<double>& raw);
		/// @brief Initialize the instance.
		void Init();

	public:
		Cmac(unsigned int numQ
			, unsigned int numLayers
			, unsigned int maxmem
			, unsigned int numOut
			, std::vector<double>&& upper
			, std::vector<double>&& lower
			, double beta
			, double nu);

		~Cmac();

		std::unique_ptr<IPrediction> Predict(std::vector<double>& input) override;
		std::unique_ptr<IAdjustment> Adjust(std::vector<double>& correction
			, IPrediction* const prediction
			, double damping) override;
		std::unique_ptr<IResult> Save(
			const std::string& directory, const std::string& filename
		) override;
	};
}

#endif