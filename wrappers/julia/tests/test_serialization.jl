#!/usr/bin/julia

"""
Deletes all the .cmac files within the current directory.
"""
function delete_cmac_files()::Nothing
    # Get the list of files in the current working directory
    files = readdir()
    # Filter out only the .cmac files
    cmac_files = filter(x -> endswith(x, ".cmac"), files)
    # Delete each .cmac file
    for file in cmac_files
        full_path = joinpath(pwd(), file)
        rm(full_path)
    end
end

@testset "test_serialize_deserialize_cmac" begin
    delete_cmac_files()

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
    IMarshallerSave(pMarshaller, Ptr{ISerializable}(pCmac), pwd(), "expected")

    pAnotherSerialization::Ptr{ISerialization} = ICmacSerialize(pDefaultCmac)
    @assert ISerializationIsSuccessful(pAnotherSerialization)

    # Manually destroy pointers.
    IMarshallerDestroy(pMarshaller)
    ISerializationDestroy(pAnotherSerialization)
    IResultDestory(pDeserialization)
    ISerializationDestroy(pSerialization)
    ICmacDestroy(pCmac)
    ICmacDestroy(pDefaultCmac)

    delete_cmac_files()
end