#!/usr/bin/julia

@testset "test_predict_success" begin
    upper::Vector{Float64} = [10.0, 10.0]
    lower::Vector{Float64} = [-10.0, -10.0]

    pCmac::Ptr{ICmac} = CreateCmac(
        10, 100, 10^5, 2,
        upper, lower, 0.001, 0.00001
    )

    @assert isa(pCmac, Ptr{ICmac})
    @assert pCmac != C_NULL

    input::Vector{Float64} = [0.0, 0.0]
    pPrediction::Ptr{IPrediction} = ICmacPredict(pCmac, input)

    @assert isa(pPrediction, Ptr{IPrediction})
    @assert pPrediction != C_NULL

    @assert length(IPredictionGetValues(pPrediction)) == 2
    @assert IPredictionIsSuccessful(pPrediction)
    @assert length(IPredictionGetBasisValues(pPrediction)) == 100

    for gamma::Cdouble in IPredictionGetBasisValues(pPrediction)
        @assert gamma <= 1.0 and gamma >= 0.0
    end

    active_weights::Vector{Vector{Cdouble}} = IPredictionGetActiveWeights(pPrediction)

    @assert length(active_weights) == 2
    for weight_col::Vector{Cdouble} in active_weights
        @assert length(weight_col) == 100
    end

    @assert length(IPredictionGetActiveWeightIndices(pPrediction)) == 100

    # Manually destroy pointers.
    IPredictionDestroy(pPrediction)
    ICmacDestroy(pCmac)
end

@testset "test_predict_fail" begin
    upper::Vector{Float64} = [10.0, 10.0]
    lower::Vector{Float64} = [-10.0, -10.0]

    pCmac::Ptr{ICmac} = CreateCmac(
        10, 100, 10^5, 2,
        upper, lower, 0.001, 0.00001
    )

    @assert isa(pCmac, Ptr{ICmac})
    @assert pCmac != C_NULL

    input::Vector{Float64} = [0.0]

    pPrediction::Ptr{IPrediction} = ICmacPredict(pCmac, input)

    @assert isa(pPrediction, Ptr{IPrediction})
    @assert pPrediction != C_NULL

    # verify prediction properties
    @assert length(IPredictionGetValues(pPrediction)) == 0
    @assert ~IPredictionIsSuccessful(pPrediction)
    @assert length(IPredictionGetBasisValues(pPrediction)) == 0
    @assert length(IPredictionGetActiveWeights(pPrediction)) == 0
    @assert length(IPredictionGetActiveWeightIndices(pPrediction)) == 0

    # Manually destroy pointers.
    IPredictionDestroy(pPrediction)
    ICmacDestroy(pCmac)
end

@testset "test_adjust_success" begin
    upper::Vector{Float64} = [10.0, 10.0]
    lower::Vector{Float64} = [-10.0, -10.0]

    pCmac::Ptr{ICmac} = CreateCmac(
        10, 100, 10^5, 2,
        upper, lower, 0.001, 0.00001
    )

    @assert isa(pCmac, Ptr{ICmac})
    @assert pCmac != C_NULL

    input::Vector{Float64} = [0.0, 0.0]
    pPrediction::Ptr{IPrediction} = ICmacPredict(pCmac, input)

    @assert isa(pPrediction, Ptr{IPrediction})
    @assert pPrediction != C_NULL

    correction::Vector{Float64} = [0.001, 0.001]
    pAdjustment::Ptr{IAdjustment} = ICmacAdjust(pCmac, correction, pPrediction, 0.00001)

    @assert isa(pAdjustment, Ptr{IAdjustment})
    @assert pAdjustment != C_NULL

    @assert IAdjustmentIsSuccessful(pAdjustment)

    weight_changes::Vector{Vector{Cdouble}} = IAdjustmentGetWeightChanges(pAdjustment)
    @assert length(weight_changes) == 2

    for weight_change_col::Vector{Cdouble} in weight_changes
        @assert length(weight_change_col) == 100
    end

    # Manually destroy pointers.
    IAdjustmentDestroy(pAdjustment)
    IPredictionDestroy(pPrediction)
    ICmacDestroy(pCmac)
end

@testset "test_adjust_fail" begin
    upper::Vector{Float64} = [10.0, 10.0]
    lower::Vector{Float64} = [-10.0, -10.0]

    pCmac::Ptr{ICmac} = CreateCmac(
        10, 100, 10^5, 2,
        upper, lower, 0.001, 0.00001
    )

    @assert isa(pCmac, Ptr{ICmac})
    @assert pCmac != C_NULL

    input::Vector{Float64} = [0.0, 0.0]
    pPrediction::Ptr{IPrediction} = ICmacPredict(pCmac, input)

    @assert isa(pPrediction, Ptr{IPrediction})
    @assert pPrediction != C_NULL

    correction::Vector{Float64} = [0.001]
    pAdjustment::Ptr{IAdjustment} = ICmacAdjust(pCmac, correction, pPrediction, 0.00001)

    @assert isa(pAdjustment, Ptr{IAdjustment})
    @assert pAdjustment != C_NULL

    @assert ~IAdjustmentIsSuccessful(pAdjustment)
    @assert length(IAdjustmentGetWeightChanges(pAdjustment)) == 0

    # Manually destroy pointers.
    IAdjustmentDestroy(pAdjustment)
    IPredictionDestroy(pPrediction)
    ICmacDestroy(pCmac)
end