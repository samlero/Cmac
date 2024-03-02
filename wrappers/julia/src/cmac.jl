#!/usr/bin/julia

export ICmac
"""
Cerebellar Model Articulation Controller (CMAC)
"""
struct ICmac end

export ICmacPredict
"""
Acquires active weights and associated basis values,
then multiply and sum to produce an output.

## Arguments
- `pInst::Ptr{ICmac}`: The pointer to the pointer to the cmac instance.
- `input::Vector{Float64}`: States.
## Returns
The pointer to the prediction result.
"""
function ICmacPredict(pInst::Ptr{ICmac}, input::Vector{Float64})::Ptr{IPrediction}
    return ccall((:CCmacLibICmacPredict, cmaclib_core),
        Ptr{IPrediction}, (Ptr{ICmac}, Ptr{Cdouble}, Culong),
        pInst, pointer(input), length(input))
end

export ICmacAdjust
"""
Train the weights of the Cmac.

## Arguments
- `pInst::Ptr{ICmac}`: The pointer to the pointer to the cmac instance.
- `correction::Vector{Float64}`: Error of the prediction.
- `pPrediction::Ptr{IAdjustment}`: The pointer to the prediction result.
- `damping::Cdouble`: Additional damping to further reduce chances of overfitting.
## Returns
The pointer to the adjustment result.
"""
function ICmacAdjust(pInst::Ptr{ICmac}, correction::Vector{Float64},
        pPrediction::Ptr{IPrediction}, damping::Cdouble)::Ptr{IAdjustment}
    return ccall((:CCmacLibICmacAdjust, cmaclib_core),
        Ptr{IAdjustment}, (Ptr{ICmac}, Ptr{Cdouble}, Culong, Ptr{IPrediction}, Cdouble),
        pInst, pointer(correction), length(correction), pPrediction, damping)
end

export ICmacZeroize
"""
Sets all the weights in memory to zero, untraining the Cmac.

## Arguments
- `pInst::Ptr{ICmac}`: The pointer to the cmac instance.
## Returns
The result of the operation.
"""
function ICmacZeroize(pInst::Ptr{ICmac})::Ptr{IResult}
    return ccall((:CCmacLibICmacZeroize, cmaclib_core),
        Ptr{IResult}, (Ptr{ICmac}, ), pInst)
end

export ICmacSerialize
"""
Serializes the object in its own unique format.

## Arguments
- `pInst::Ptr{ICmac}`: The pointer to the cmac instance.
## Returns
The result of the operation.
"""
function ICmacSerialize(pInst::Ptr{ICmac})::Ptr{ISerialization}
    return ccall((:CCmacLibICmacSerialize, cmaclib_core),
        Ptr{ISerialization}, (Ptr{ICmac}, ), pInst)
end

export ICmacDeserialize
"""
Deserializes the content into its member variables.

## Arguments
- `pInst::Ptr{ICmac}`: The pointer to the cmac instance.
- `content::Cstring`: Valid deserializable content.
## Returns
The result of the operation.
"""
function ICmacDeserialize(pInst::Ptr{ICmac}, content::Cstring)::Ptr{IResult}
    return ccall((:CCmacLibICmacDeserialize, cmaclib_core),
        Ptr{IResult}, (Ptr{ICmac}, Cstring), pInst, content)
end

export ICmacGetExtension
"""
## Arguments
- `pInst::Ptr{ICmac}`: The pointer to the cmac instance.
## Returns
The extension of the serializable object
"""
function ICmacGetExtension(pInst::Ptr{ICmac})::Ptr{ISerialization}
    return ccall((:CCmacLibICmacGetExtension, cmaclib_core),
        Ptr{ISerialization}, (Ptr{ICmac}, ), pInst)
end

export ICmacDestroy
"""
Destructor.

## Arguments
- `pInst::Ptr{ICmac}`: The pointer to the cmac instance.
"""
function ICmacDestroy(pInst::Ptr{ICmac})::Cvoid
    return ccall((:CCmacLibICmacDestroy, cmaclib_core),
        Cvoid, (Ptr{ICmac}, ), pInst)
end