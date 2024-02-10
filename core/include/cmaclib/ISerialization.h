#ifndef ISERIALIZATION_H
#define ISERIALIZATION_H

#include <cmaclib/defines.h>
#include <cmaclib/IResult.h>

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