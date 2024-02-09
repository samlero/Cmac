#ifndef ADJUSTMENT_H
#define ADJUSTMENT_H

#pragma warning( disable : 4250) // disable dominance warning

#include <vector>
#include <memory>
#include <cmaclib/IResult.h>
#include <cmaclib/IAdjustment.h>
#include <cmaclib/Result.h>

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