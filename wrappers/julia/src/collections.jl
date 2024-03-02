#!/usr/bin/julia

export CDoubleArray
"""
An array of doubles with fixed array size.

## Fields
- `data::Ptr{Cdouble}`: The pointer to the first element in the array.
- `size::Culong`: The size of the array.
"""
struct CDoubleArray
    data::Ptr{Cdouble}
    size::Culong
end

export CDoubleArrayArray
"""
An array of CDoubleArray with fixed array size.

## Fields
- `data::Ptr{CDoubleArray}`: The pointer to the first element in the array.
- `size::Culong`: The size of the array.
"""
struct CDoubleArrayArray
    data::Ptr{CDoubleArray}
    size::Culong
end

export CDoubleArrayArrayDestroy
"""
Properly destroy the CDoubleArrayArray instance.

## Arguments
- `arr::CDoubleArrayArray`: The instance to be destroyed.
"""
function CDoubleArrayArrayDestroy(arr::CDoubleArrayArray)::Nothing
    ccall((:CDoubleArrayArrayDestroy, cmaclib_core),
        Cvoid, (CDoubleArrayArray, ), arr)
end

export CUintArray
"""
An array of unsigned ints with fixed array size.

## Fields
- `data::Ptr{Cuint}`: The pointer to the first element in the array.
- `size::Culong`: The size of the array.
"""
struct CUintArray
    data::Ptr{Cuint}
    size::Culong
end