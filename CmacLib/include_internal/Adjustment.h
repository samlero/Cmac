#ifndef ADJUSTMENT_H
#define ADJUSTMENT_H

#include <vector>
#include <memory>
#include "IResult.h"
#include "IAdjustment.h"

class Adjustment : public IAdjustment {
private:
	std::vector<std::vector<double>> weightChanges;
	std::unique_ptr<IResult> result;

public:
	Adjustment(std::vector<std::vector<double>>& dw, IResult* result);
	~Adjustment();

public: // overrides
	const std::vector<std::vector<double>>& GetWeightChanges() override;
	const IResult& GetResult() override;
};

#endif