#if !defined(CMACLIB_DEFINES_HEADER_FILE)
#define CMACLIB_DEFINES_HEADER_FILE

/*
    This header file contains preprocessor definitions
    used by the CmacLib library.
*/

// CMACLIB_SHARED_SYMBOL Definition.
#if !defined(CMACLIB_SHARED_SYMBOL)
// Dynamic libraries.
#if defined(CMACLIB_SHARED_LIBRARY)

// MSVC Compilers.
#if defined(_MSC_VER)
// Building.
#if defined(CMACLIB_BUILD_SHARED_LIB)
/// @brief Shared library export symbol.
#define CMACLIB_SHARED_SYMBOL __declspec(dllexport)
// Importing.
#else
/// @brief Shared library export symbol.
#define CMACLIB_SHARED_SYMBOL __declspec(dllimport)
#endif
// End MSVC.

// Begin gcc or clang compilers.
#elif defined(__GNUC__) || defined(__clang__)
/// @brief Shared library export symbol.
#define CMACLIB_SHARED_SYMBOL __attribute__((visibility("default")))
// END gcc or clang compilers.

#else
#error "Compiler currently unsupported."
#endif

// Static libraries.
#else
/// @brief Shared library export symbol.
#define CMACLIB_SHARED_SYMBOL
#endif
#endif
// CMACLIB_SHARED_SYMBOL Definition END.

// Boolean type definition.
#if defined(__cplusplus)
typedef bool cmaclib_bool_t;
#else
typedef char cmaclib_bool_t;
#endif
// END Boolean type definition.

// Boolean True Definition.
#if !defined(CMACLIB_BOOLEAN_TRUE)
#if defined(__cplusplus)
#define CMACLIB_BOOLEAN_TRUE true
#else
#define CMACLIB_BOOLEAN_TRUE 0x01
#endif
#endif
// END Boolean True Definition.

// Boolean False Definition.
#if !defined(CMACLIB_BOOLEAN_FALSE)
#if defined(__cplusplus)
#define CMACLIB_BOOLEAN_FALSE false
#else
#define CMACLIB_BOOLEAN_FALSE 0x00
#endif
#endif
// END Boolean False Definition.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.