#!/usr/bin/julia

# Serializable type declaration.
export ISerializable
"""
Serializes and deserializes.
"""
struct ISerializable end

export ISerializableSerialize
"""
Serializes the object in its own unique format.

## Arguments
- `pInst::Ptr{ISerializable}`: The pointer to the serializable instance.

## Returns
Serialized string.
"""
function ISerializableSerialize(pInst::Ptr{ISerializable})::Ptr{ISerialization}
    return ccall((:CCmacLibISerializableSerialize, cmaclib_core),
        Ptr{ISerialization}, (Ptr{ISerializable}, ), pInst)
end

export ISerializableDeserialize
"""
Deserializes the content into its member variables.

## Arguments
- `pInst::Ptr{ISerializable}`: The pointer to the serializable instance.
- `content::Cstring`: Valid deserializable content.

## Returns
The result of the operation.
"""
function ISerializableDeserialize(pInst::Ptr{ISerializable},
        content::Cstring)::Ptr{IResult}
    return ccall((:CCmacLibISerializableDeserialize, cmaclib_core),
        Ptr{IResult}, (Ptr{ISerializable}, Cstring), pInst, content)
end

export ISerializableGetExtension
"""

## Arguments
- `pInst::Ptr{ISerializable}`: The pointer to the serializable instance.

## Returns
The extension of the serializable object.
"""
function ISerializableGetExtension(pInst::Ptr{ISerializable})::Cstring
    return ccall((:CCmacLibISerializableGetExtension, cmaclib_core),
        Cstring, (Ptr{ISerializable}, ), pInst)
end

export ISerializableDestroy
"""
Destructor.

## Arguments
- `pInst::Ptr{ISerializable}`: The pointer to the serializable instance.
"""
function ISerializableDestroy(pInst::Ptr{ISerializable})::Nothing
    ccall((:CCmacLibISerializableDestroy, cmaclib_core),
        Cvoid, (Ptr{ISerializable}, ), pInst)
end