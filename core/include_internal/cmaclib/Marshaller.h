#ifndef MARSHALLER_H
#define MARSHALLER_H

#include <cmaclib/IMarshaller.h>

namespace CmacLib
{
    class Marshaller : public IMarshaller
    {
    public:
        Marshaller(){}
        ~Marshaller(){}
    
    public: // overrides
        std::unique_ptr<IResult> Save(ISerializable* serializable,
            const std::string& directory, const std::string& filename) override;
        std::unique_ptr<IResult> Load(ISerializable* serializable, const std::string& filepath) override;
    };
}

#endif