#!/usr/bin/julia

# Prediction type declaration.
export IPrediction
"""
Prediction output.
"""
struct IPrediction end

export IPredictionGetValues
"""
Get the calculated multiplication and accumulation
of basis and active weights.

## Arguments
- `pInst::Ptr{IPrediction}`: The pointer to the prediction instance.
## Returns
Cmac output.
"""
function IPredictionGetValues(pInst::Ptr{IPrediction})::Vector{Cdouble}
    c_data::CDoubleArray = ccall(
        (:CCmacLibIPredictionGetValues, cmaclib_core),
        CDoubleArray, (Ptr{IPrediction}, ), pInst)
    return unsafe_wrap(Vector{Cdouble}, c_data.data, c_data.size)
end

export IPredictionGetActiveWeightIndices
"""
Get the indices of the active weights.

## Arguments
- `pInst::Ptr{IPrediction}`: The pointer to the prediction instance.
## Returns
Active weight indices.
"""
function IPredictionGetActiveWeightIndices(pInst::Ptr{IPrediction})::Vector{Cuint}
    c_data::CUintArray = ccall(
        (:CCmacLibIPredictionGetActiveWeightIndices, cmaclib_core),
        CUintArray, (Ptr{IPrediction}, ), pInst)
    return unsafe_wrap(Vector{Cuint}, c_data.data, c_data.size)
end

export IPredictionGetActiveWeights
"""
Get the values of the active weights.

## Arguments
- `pInst::Ptr{IPrediction}`: The pointer to the prediction instance.
## Returns
Active weight values.
"""
function IPredictionGetActiveWeights(pInst::Ptr{IPrediction})::Vector{Vector{Cdouble}}
    c_data = ccall((:CCmacLibIPredictionGetActiveWeights, cmaclib_core),
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

export IPredictionGetBasisValues
"""
Get the basis function values.

## Arguments
- `pInst::Ptr{IPrediction}`: The pointer to the prediction instance.
## Returns
Basis function values.
"""
function IPredictionGetBasisValues(pInst::Ptr{IPrediction})::Vector{Cdouble}
    c_data::CDoubleArray = ccall((:CCmacLibIPredictionGetBasisValues, cmaclib_core),
        CDoubleArray, (Ptr{IPrediction}, ), pInst)
    return unsafe_wrap(Vector{Cdouble}, c_data.data, c_data.size)
end

export IPredictionIsSuccessful
"""
Indicates if an operation was successful.

## Arguments
- `pInst::Ptr{IPrediction}`: The pointer to the prediction instance.
## Returns
Success.
"""
function IPredictionIsSuccessful(pInst::Ptr{IPrediction})::Bool
    return ccall((:CCmacLibIPredictionIsSuccessful, cmaclib_core),
        Bool, (Ptr{IPrediction}, ), pInst)
end

export IPredictionGetMessage
"""
If not successful, a failure message is provided.

## Arguments
- `pInst::Ptr{IPrediction}`: The pointer to the prediction instance.
## Returns
The failure message.
"""
function IPredictionGetMessage(pInst::Ptr{IPrediction})::Cstring
    return ccall((:CCmacLibIPredictionGetMessage, cmaclib_core),
        Cstring, (Ptr{IPrediction}, ), pInst)
end

export IPredictionDestroy
"""
Destructor.

## Arguments
- `pInst::Ptr{IPrediction}`: The pointer to the prediction instance.
"""
function IPredictionDestroy(pInst::Ptr{IPrediction})::Nothing
    ccall((:CCmacLibIPredictionDestroy, cmaclib_core),
        Cvoid, (Ptr{IPrediction}, ), pInst)
end