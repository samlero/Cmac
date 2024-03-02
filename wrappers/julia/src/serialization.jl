#!/usr/bin/julia

export ISerialization
"""
Serialization result data.
"""
struct ISerialization end

export ISerializationGetString
"""
The string from the resulting serialization process.

## Arguments
- `pInst::Ptr{ISerialization}`: The pointer to the serialization instance.

## Returns
serialized string
"""
function ISerializationGetString(pInst::Ptr{ISerialization})::Cstring
    return ccall((:CCmacLibISerializationGetString, cmaclib_core),
        Cstring, (Ptr{ISerialization}, ), pInst)
end

export ISerializationIsSuccessful
"""
Indicates if an operation was successful.

## Arguments
- `pInst::Ptr{ISerialization}`: The pointer to the serialization instance.

## Returns
Success.
"""
function ISerializationIsSuccessful(pInst::Ptr{ISerialization})::Bool
    return ccall((:CCmacLibISerializationIsSuccessful, cmaclib_core),
        Bool, (Ptr{ISerialization}, ), pInst)
end

export ISerializationGetMessage
"""
If not successful, a failure message is provided.

## Arguments
- `pInst::Ptr{ISerialization}`: The pointer to the serialization instance.

## Returns
The failure message.
"""
function ISerializationGetMessage(pInst::Ptr{ISerialization})::Cstring
    return ccall((:CCmacLibISerializationGetMessage, cmaclib_core),
        Cstring, (Ptr{ISerialization}, ), pInst)
end

export ISerializationDestroy
"""
Destructor.

## Arguments
- `pInst::Ptr{ISerialization}`: The pointer to the serialization instance.
"""
function ISerializationDestroy(pInst::Ptr{ISerialization})::Nothing
    ccall((:CCmacLibISerializationDestroy, cmaclib_core),
        Cvoid, (Ptr{ISerialization}, ), pInst)
end