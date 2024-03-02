#!/usr/bin/julia

@testset "test_serialize_deserialize_cmac" begin
    upper::Vector{Float64} = [10.0, 10.0]
    lower::Vector{Float64} = [-10.0, -10.0]

    pCmac::Ptr{ICmac} = CreateCmac(
        10, 100, 10^5, 2,
        upper, lower, 0.001, 0.00001
    )

    @assert isa(pCmac, Ptr{ICmac})
    @assert pCmac != C_NULL

    pSerialization::Ptr{ISerialization} = ICmacSerialize(pCmac)

    @assert ISerializationIsSuccessful(pSerialization)

    pDefaultCmac::Ptr{ICmac} = CreateDefaultCmac()
    pDeserialization::Ptr{IResult} = ICmacDeserialize(
        pDefaultCmac, ISerializationGetString(pSerialization))

    @assert IResultIsSuccessful(pDeserialization)

    pMarshaller::Ptr{IMarshaller} = CreateMarshaller()

    # Manually destroy pointers.
    IMarshallerDestroy(pMarshaller)
    IResultDestory(pDeserialization)
    ISerializationDestroy(pSerialization)
    ICmacDestroy(pCmac)
    ICmacDestroy(pDefaultCmac)
end