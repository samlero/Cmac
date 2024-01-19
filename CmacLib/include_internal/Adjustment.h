#ifndef ADJUSTMENT_H
#define ADJUSTMENT_H

#include <vector>
#include <memory>
#include "IResult.h"
#include "IAdjustment.h"

namespace CmacLib
{
	class Adjustment : public IAdjustment {
	private:
		std::vector<std::vector<double>> weightChanges;
		std::unique_ptr<IResult> result;

	public: // setters
		void SetWeightChanges(std::vector<std::vector<double>>& dw);
		void SetResult(IResult* result);

	public:
		Adjustment();
		~Adjustment();

	public: // overrides
		const std::vector<std::vector<double>>& GetWeightChanges() override;
		const IResult& GetResult() override;
	};
}

#endif