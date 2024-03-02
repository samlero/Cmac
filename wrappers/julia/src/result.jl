#!/usr/bin/julia

export IResult
"""
Result.
"""
struct IResult end

export IResultIsSuccessful
"""
Indicates if an operation was successful.

## Arguments
- `pInst`: The pointer to the result instance.

## Returns
Success.
"""
function IResultIsSuccessful(pInst::Ptr{IResult})::Bool
    return ccall((:CCmacLibIResultIsSuccessful, cmaclib_core),
        Bool, (Ptr{IResult}, ), pInst)
end

export IResultGetMessage
"""
If not successful, a failure message is provided.

## Arguments
- `pInst`: The pointer to the result instance.
"""
function IResultGetMessage(pInst::Ptr{IResult})::Cstring
    return ccall((:CCmacLibIResultGetMessage, cmaclib_core),
        Cstring, (Ptr{IResult}, ), pInst)
end

export IResultDestory
"""
Destructor.

## Arguments
- `pInst`: The pointer to the result instance.
"""
function IResultDestory(pInst::Ptr{IResult})::Cvoid
    return ccall((:CCmacLibIResultDestory, cmaclib_core),
        Cvoid, (Ptr{IResult}, ), pInst)
end