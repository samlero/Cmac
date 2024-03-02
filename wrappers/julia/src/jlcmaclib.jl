#!/usr/bin/julia

module jlcmaclib

include("core.jl")
include("collections.jl")
include("result.jl")
include("prediction.jl")
include("adjustment.jl")
include("serialization.jl")
include("serializable.jl")
include("marshaller.jl")
include("cmac.jl")
include("factory.jl")

end
__precompile__()