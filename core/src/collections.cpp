#include "cmaclib/collections.h"

/// @brief Properly destroy the CDoubleArrayArray instance.
/// @param arr The instance to be destroyed.
void CDoubleArrayArrayDestroy(CDoubleArrayArray arr) {
    delete[] arr.data;
}