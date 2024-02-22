#include "cmaclib/Adjustment.h"

#include <cmaclib/Result.h>
#include <utility>

using namespace CmacLib;

void Adjustment::SetWeightChanges(std::vector<std::vector<double>>&& dw)
{
	this->weightChanges = ::std::move(dw);
}

Adjustment::Adjustment()
	: weightChanges(std::vector<std::vector<double>>()){}

Adjustment::~Adjustment(){}

const std::vector<std::vector<double>>& Adjustment::GetWeightChanges()
{
	return this->weightChanges;
}

/// @brief Get the amount the each active weight changed.
/// (DO NOT FORGET TO DELETE THE RETURNED POINTER AFTER USAGE.)
/// @param pAdjustment The pointer to the adjustment instance.
/// @return Weight change dW.
double** CCmacLibIAdjustmentGetWeightChanges(
	CCmacLibIAdjustment* pAdjustment
) {
	/// @brief The container for the active weights 2-D array.
	double** matrix = new double*[pAdjustment->GetWeightChanges().size()];

	for (unsigned int i = 0; i < pAdjustment->GetWeightChanges().size(); i++) {
		matrix[i] = (double*) pAdjustment->GetWeightChanges().data()->data();
	}

	return matrix;
}

/// @brief Indicates if an operation was successful.
/// @param pAdjustment The pointer to the adjustment instance.
/// @return Success.
cmaclib_bool_t CCmacLibIAdjustmentIsSuccessful(
	CCmacLibIAdjustment* pAdjustment
) {
	return pAdjustment->IsSuccessful();
}

/// @brief If not successful, a failure message is provided.
/// @param pAdjustment The pointer to the adjustment instance.
const char* CCmacLibIAdjustmentGetMessage(
	CCmacLibIAdjustment* pAdjustment
) {
	return pAdjustment->GetMessage().c_str();
}

/// @brief Destructor.
/// @param ppAdjustment The pointer to the pointer to the adjustment instance.
void CCmacLibIAdjustmentDestroy(
	CCmacLibIAdjustment** ppAdjustment
) {
	if (*ppAdjustment) {
		delete *ppAdjustment;
		*ppAdjustment = nullptr;
	}
}