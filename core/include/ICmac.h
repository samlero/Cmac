#ifndef ICMAC_H
#define ICMAC_H

#include <memory>
#include "IPrediction.h"
#include "IAdjustment.h"
#include "IResult.h"

namespace CmacLib
{
	/// @brief Cerebellar Model Articulation Controller (CMAC)
	class ICmac {
	public:

		/// @brief Acquires active weights and associated basis values, then multiply and sum to produce an output.
		/// @param input States.
		/// @return Prediction result.
		virtual std::unique_ptr<IPrediction> Predict(std::vector<double>& input) = 0;

		/// @brief Train the weights of the Cmac.
		/// @param correction Error of the prediction.
		/// @param prediction Contains indices of weights and basis values.
		/// @param damping Additional damping to further reduce chances of overfitting.
		/// @return Adjustment result.
		virtual std::unique_ptr<IAdjustment> Adjust(std::vector<double>& correction
			, IPrediction* const prediction
			, double damping) = 0;

		/// @brief Save the contents and weights of the Cmac instance.
		/// @param directory Location to save the Cmac object.
		/// @param filename Name of the saved file.
		/// @return Save result.
		virtual std::unique_ptr<IResult> Save(std::string directory, std::string filename) = 0;

		/// @brief Destructor
		virtual ~ICmac(){};
	};
}

#endif