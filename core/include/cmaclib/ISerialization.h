#ifndef ISERIALIZATION_H
#define ISERIALIZATION_H

#include <cmaclib/defines.h>
#include <cmaclib/IResult.h>

// Begin C++ Only Region.
#if defined(__cplusplus)
namespace CmacLib
{
    class CMACLIB_SHARED_SYMBOL ISerialization : public virtual IResult
    {
    public:
        virtual ~ISerialization(){};

        /// @brief The string from the resulting serialization process.
        /// @return serialized string
        virtual std::string GetString() = 0;
    };
}
#endif
// End C++ Only Region.

#endif
// End of file.
// DO NOT WRITE BEYOND HERE.