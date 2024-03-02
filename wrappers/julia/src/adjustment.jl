#!/usr/bin/julia

export IAdjustment
"""
Contains weight adjustment data.
"""
struct IAdjustment end

export IAdjustmentGetWeightChanges
"""
Get the amount the each active weight changed.
## Arguments
- `pInst::Ptr{IAdjustment}`: The pointer to the adjustment instance.
## Returns
Weight change dW.
"""
function IAdjustmentGetWeightChanges(pInst::Ptr{IAdjustment})::Vector{Vector{Cdouble}}
    c_data = ccall((:CCmacLibIAdjustmentGetWeightChanges, cmaclib_core),
        CDoubleArrayArray, (Ptr{IPrediction}, ), pInst)

    # The container for the active weights to be returned.
    matrix::Vector{Vector{Cdouble}} = []
    c_matrix::Vector{CDoubleArray} = unsafe_wrap(Vector{CDoubleArray},
        c_data.data, c_data.size)

    for col_vec_wrapped::CDoubleArray in c_matrix
        col_vec::Vector{Cdouble} = unsafe_wrap(
            Vector{Cdouble}, col_vec_wrapped.data, col_vec_wrapped.size
        )
        push!(matrix, col_vec)
    end

    # Properly Dispose c_data.
    ccall((:CDoubleArrayArrayDestroy, cmaclib_core),
        Cvoid, (CDoubleArrayArray, ), c_data)

    return matrix
end

export IAdjustmentIsSuccessful
"""
Indicates if an operation was successful.
## Arguments
- `pInst::Ptr{IAdjustment}`: The pointer to the adjustment instance.
## Returns
Success
"""
function IAdjustmentIsSuccessful(pInst::Ptr{IAdjustment})::Bool
    return ccall((:CCmacLibIAdjustmentIsSuccessful, cmaclib_core),
        Bool, (Ptr{IAdjustment}, ), pInst)
end

export IAdjustmentGetMessage
"""
If not successful, a failure message is provided.
## Arguments
- `pInst::Ptr{IAdjustment}`: The pointer to the adjustment instance.
## Returns
The failure message in C string.
"""
function IAdjustmentGetMessage(pInst::Ptr{IAdjustment})::Cstring
    return ccall((:CCmacLibIAdjustmentGetMessage, cmaclib_core),
        Cstring, (Ptr{IAdjustment}, ), pInst)
end

export IAdjustmentDestroy
"""
Destructor.

## Arguments
- `pInst::Ptr{IAdjustment}`: The pointer to the adjustment instance.
"""
function IAdjustmentDestroy(pInst::Ptr{IAdjustment})::Nothing
    ccall((:CCmacLibIAdjustmentDestroy, cmaclib_core),
        Cvoid, (Ptr{IAdjustment}, ), pInst)
end