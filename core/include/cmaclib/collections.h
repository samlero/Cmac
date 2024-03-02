#if !defined(CMACLIB_COLLECTIONS_HEADER_FILE)
#define CMACLIB_COLLECTIONS_HEADER_FILE

#include <cmaclib/defines.h>
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

/// @brief An array of doubles with fixed array size.
typedef struct CDoubleArray {
    /// @brief The pointer to the first element in the array.
    double* data;
    /// @brief The size of the array.
    size_t size;
} CDoubleArray;

/// @brief An array of CDoubleArray with fixed array size.
typedef struct CDoubleArrayArray {
    /// @brief The pointer to the first element in the array.
    CDoubleArray* data;
    /// @brief The size of the array.
    size_t size;
} CDoubleArrayArray;

/// @brief Properly destroy the CDoubleArrayArray instance.
/// @param arr The instance to be destroyed.
CMACLIB_SHARED_SYMBOL void CDoubleArrayArrayDestroy(CDoubleArrayArray arr);

/// @brief An array of unsigned ints with fixed array size.
typedef struct CUintArray {
    /// @brief The pointer to the first element in the array.
    unsigned int* data;
    /// @brief The size of the array.
    size_t size;
} CUintArray;

#if defined(__cplusplus)
}
#endif

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.