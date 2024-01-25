#ifndef MARSHALLER_H
#define MARSHALLER_H

#include "IMarshaller.h"

namespace CmacLib
{
    class Marshaller : public IMarshaller
    {
    public:
        Marshaller(){}
        ~Marshaller(){}
    
    public: // overrides
        bool Save(ISerializable* serializable, std::string directory, std::string filename) override;
        bool Load(ISerializable* serializable, std::string filepath) override;
    };
}

#endif