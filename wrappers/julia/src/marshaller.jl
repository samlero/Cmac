#!/usr/bin/julia

export IMarshaller
"""
Save and load serializable objects.
"""
struct IMarshaller end

export IMarshallerSave
"""
Save the serializable object.

## Arguments
- `pInst::Ptr{IMarshaller}`: The pointer to the marshaller instance.
- `pSerializable::Ptr{ISerializable}`: Object to save.
- `directory::Cstring`: Folder to save the serializable object in.
- `filename::Cstring`: Name of the object to save.

## Returns
Indicates if the save operation was successful or not.
"""
function IMarshallerSave(pInst::Ptr{IMarshaller},
        pSerializable::Ptr{ISerializable}, directory::String,
        filename::String)::Ptr{IResult}
    return ccall((:CCmacLibIMarshallerSave, cmaclib_core),
        Ptr{IResult}, (Ptr{IMarshaller}, Ptr{ISerializable}, Cstring, Cstring),
        pInst, pSerializable, directory, filename)
end

export IMarshallerLoad
"""
Fills the contents of the serialzable object.

## Arguments
- `pInst::Ptr{IMarshaller}`: The pointer to the marshaller instance.
- `pSerializable::Ptr{ISerializable}`: Object to fill.
- `filepath::Cstring`: Location of the file that contains the serializable
object's contents.

## Returns
Indicates if the save operation was successful or not.
"""
function IMarshallerLoad(pInst::Ptr{IMarshaller},
        pSerializable::Ptr{ISerializable}, filepath::String)::Ptr{IResult}
    return ccall((:CCmacLibIMarshallerLoad, cmaclib_core),
        Ptr{IResult}, (Ptr{IMarshaller}, Ptr{ISerializable}, Cstring),
        pInst, pSerializable, filepath)
end

export IMarshallerDestroy
"""
Destructor.

## Arguments
- `pInst`: The pointer to the marshaller instance.
"""
function IMarshallerDestroy(pInst::Ptr{IMarshaller})::Nothing
    ccall((:CCmacLibIMarshallerDestroy, cmaclib_core),
        Cvoid, (Ptr{IMarshaller}, ), pInst)
end