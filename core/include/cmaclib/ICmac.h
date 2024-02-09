#ifndef ICMAC_H
#define ICMAC_H

#include <memory>
#include <cmaclib/IPrediction.h>
#include <cmaclib/IAdjustment.h>
#include <cmaclib/IResult.h>
#include <cmaclib/ISerializable.h>

namespace CmacLib
{
	/// @brief Cerebellar Model Articulation Controller (CMAC)
	class ICmac : public virtual ISerializable{
	public:

		/// @brief Acquires active weights and associated basis values, then multiply and sum to produce an output.
		/// @param input States.
		/// @return Prediction result.
		virtual std::unique_ptr<IPrediction> Predict(const std::vector<double>& input) = 0;

		/// @brief Train the weights of the Cmac.
		/// @param correction Error of the prediction.
		/// @param prediction Contains indices of weights and basis values.
		/// @param damping Additional damping to further reduce chances of overfitting.
		/// @return Adjustment result.
		virtual std::unique_ptr<IAdjustment> Adjust(const std::vector<double>& correction
			, IPrediction* const prediction
			, double damping) = 0;

		/// @brief Sets all the weights in memory to zero, untraining the Cmac.
		/// @return Result of the operation.
		virtual std::unique_ptr<IResult> Zeroize() = 0;

		/// @brief Destructor
		virtual ~ICmac(){};
	};
}

#endif