#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#pragma warning( disable : 4250) // disable dominance warning

#include <string>
#include "ISerialization.h"
#include "Result.h"

namespace CmacLib
{
    class Serialization : public Result, public virtual ISerialization
    {
    private:
        std::string serialized;

    public:
        Serialization(std::string data);
        ~Serialization();

    public: // ISerialization override
        std::string GetString() override;
    };
}

#endif