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
/// @param pAdjustment The pointer to the adjustment instance.
/// @return Weight change dW.
/// (Remember to delete the CDoubleArray data pointer.)
CDoubleArrayArray CCmacLibIAdjustmentGetWeightChanges(
	CCmacLibIAdjustment* pAdjustment
) {
	/// @brief The container for the active weights 2-D array.
	CDoubleArrayArray matrix;
	matrix.size = pAdjustment->GetWeightChanges().size();
	matrix.data = new CDoubleArray[matrix.size];

	for (unsigned long i = 0; i < matrix.size; i++) {
		matrix.data[i].data = (double*) pAdjustment->GetWeightChanges().data()->data();
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
/// @param pAdjustment The pointer to the adjustment instance.
void CCmacLibIAdjustmentDestroy(
	CCmacLibIAdjustment* pAdjustment
) {
	if (pAdjustment) delete pAdjustment;
}