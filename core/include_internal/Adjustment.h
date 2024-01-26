#ifndef ADJUSTMENT_H
#define ADJUSTMENT_H

#include <vector>
#include <memory>
#include "IResult.h"
#include "IAdjustment.h"
#include "Result.h"

namespace CmacLib
{
	class Adjustment : public Result, public virtual IAdjustment {
	private:
		std::vector<std::vector<double>> weightChanges;

	public: // setters
		void SetWeightChanges(std::vector<std::vector<double>>&& dw);

	public:
		Adjustment();
		~Adjustment();

	public: // overrides
		const std::vector<std::vector<double>>& GetWeightChanges() override;
	};
}

#endif