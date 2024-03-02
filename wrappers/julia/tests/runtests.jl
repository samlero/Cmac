#!/usr/bin/julia

using Test

include("jlcmaclib.jl")
using .jlcmaclib

include("test_cmac.jl")
include("test_serialization.jl")