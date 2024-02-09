#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#pragma warning( disable : 4250) // disable dominance warning

#include <string>
#include <cmaclib/ISerialization.h>
#include "Result.h"

namespace CmacLib
{
    class Serialization : public Result, public virtual ISerialization
    {
    private:
        std::string serialized;

    public:
        Serialization();
        ~Serialization();

        void SetString(const std::string& str);
        void SetString(std::string&& str);

    public: // ISerialization override
        std::string GetString() override;
    };
}

#endif