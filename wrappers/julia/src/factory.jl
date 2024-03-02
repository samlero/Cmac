#!/usr/bin/julia

export CreateCmac
"""
Create a raw and untrained Cmac.

## Arguments
- `numQ::Int64`: Number of quantizations.
- `numLayers::Int64`: Number of layers (which would indicate number of active weights).
- `maxmem::Int64`: Maximum potential memory index or memory size.
- `numOut::Int64`: Number of outputs.
- `upper::Vector{Float64}`: Upper limits of the Predict method inputs.
- `lower::Vector{Float64}`: Lower limits of the Predict method inputs.
- `beta::Float64`: Learning rate.
- `nu::Float64`: Damping coefficient.

## Returns
The pointer to the cmac instance.
"""
function CreateCmac(numQ::Int64, numLayers::Int64, maxmem::Int64, numOut::Int64,
        upper::Vector{Float64}, lower::Vector{Float64}, beta::Float64,
        nu::Float64)::Ptr{ICmac}
    return ccall((:CCmacLibCreateCmac, cmaclib_core),
        Ptr{ICmac}, (Cuint, Cuint, Cuint, Cuint, Ptr{Cdouble}, Culong,
        Ptr{Cdouble}, Culong, Cdouble, Cdouble),
        Cuint(numQ), Cuint(numLayers), Cuint(maxmem), Cuint(numOut),
        pointer(upper), length(upper), pointer(lower), length(lower),
        Cdouble(beta), Cdouble(nu))
end

export CreateDefaultCmac
"""
Create a Cmac with default values.

## Returns
The pointer to the cmac instance.
"""
function CreateDefaultCmac()::Ptr{ICmac}
    return ccall((:CCmacLibCreateDefaultCmac, cmaclib_core),
        Ptr{ICmac}, ())
end

export CreateMarshaller
"""
Creates an instance of IMarshaller.

## Returns
The pointer to the newly created marshaller instance.
"""
function CreateMarshaller()::Ptr{IMarshaller}
    return ccall((:CCmacLibCreateMarshaller, cmaclib_core),
        Ptr{IMarshaller}, ())
end