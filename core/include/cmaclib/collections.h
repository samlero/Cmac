#if !defined(CMACLIB_COLLECTIONS_HEADER_FILE)
#define CMACLIB_COLLECTIONS_HEADER_FILE

#include <cmaclib/defines.h>

#if defined(__cplusplus)
extern "C" {
#endif

/// @brief An array of doubles with fixed array size.
typedef struct CMACLIB_SHARED_SYMBOL CDoubleArray {
    /// @brief The pointer to the first element in the array.
    double* data;
    /// @brief The size of the array.
    unsigned long size;
} CDoubleArray;

/// @brief An array of CDoubleArray with fixed array size.
typedef struct CMACLIB_SHARED_SYMBOL CDoubleArrayArray {
    /// @brief The pointer to the first element in the array.
    CDoubleArray* data;
    /// @brief The size of the array.
    unsigned long size;
} CDoubleArrayArray;

/// @brief Properly destroy the CDoubleArrayArray instance.
/// @param arr The instance to be destroyed.
void CMACLIB_SHARED_SYMBOL CDoubleArrayArrayDestroy(CDoubleArrayArray arr);

/// @brief An array of unsigned ints with fixed array size.
typedef struct CMACLIB_SHARED_SYMBOL CUintArray {
    /// @brief The pointer to the first element in the array.
    unsigned int* data;
    /// @brief The size of the array.
    unsigned long size;
} CUintArray;

#if defined(__cplusplus)
}
#endif

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.