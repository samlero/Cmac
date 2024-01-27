#!/usr/bin/python

import cmaclib

def test_predict_success() -> None:
    factory: cmaclib.Factory = cmaclib.Factory()

    upper: list[float] = [10.0, 10.0]
    lower: list[float] = [-10.0, -10.0]
    cmac: cmaclib.ICmac = factory.CreateCmac(10 \
        , 100 \
		, int(1e5) \
		, 2 \
		, upper \
		, lower \
		, 0.001 \
		, 0.00001)

    input: list[float] = [0.0, 0.0]
    prediction = cmac.Predict(input)

	# verify prediction properties
    assert prediction is not None
    assert len(prediction.GetValues()) == 2
    assert prediction.IsSuccessful()
    assert len(prediction.GetBasisValues()) == 100

	# check each basis value is between 0 and 1
    for gamma in prediction.GetBasisValues():
        assert gamma <= 1.0 and gamma >= 0.0

    assert len(prediction.GetActiveWeights()) == 2
    for weight_col in prediction.GetActiveWeights():
        assert len(weight_col) == 100

    assert len(prediction.GetActiveWeightIndices()) == 100

def test_predict_fail() -> None:
    factory: cmaclib.Factory = cmaclib.Factory()

    upper: list[float] = [10.0, 10.0]
    lower: list[float] = [-10.0, -10.0]
    cmac: cmaclib.ICmac = factory.CreateCmac(10 \
        , 100 \
		, int(1e5) \
		, 2 \
		, upper \
		, lower \
		, 0.001 \
		, 0.00001)

    input: list[float] = [0.0]
    prediction = cmac.Predict(input)

    assert prediction is not None

    # verify prediction properties
    assert len(prediction.GetValues()) == 0
    assert not prediction.IsSuccessful()
    assert len(prediction.GetBasisValues()) == 0
    assert len(prediction.GetActiveWeights()) == 0
    assert len(prediction.GetActiveWeightIndices()) == 0

def test_adjust_success() -> None:
    factory: cmaclib.Factory = cmaclib.Factory()

    upper: list[float] = [10.0, 10.0]
    lower: list[float] = [-10.0, -10.0]
    cmac: cmaclib.ICmac = factory.CreateCmac(10 \
        , 100 \
		, int(1e5) \
		, 2 \
		, upper \
		, lower \
		, 0.001 \
		, 0.00001)

    input: list[float] = [0.0, 0.0]
    prediction = cmac.Predict(input)

    assert prediction is not None

    correction: list[float] = [0.001, 0.001]
    adjustment = cmac.Adjust(correction, prediction, 0.00001)

    assert adjustment is not None
    assert adjustment.IsSuccessful()
    assert len(adjustment.GetWeightChanges()) == 2

    for weight_change_col in adjustment.GetWeightChanges():
        assert len(weight_change_col) == 100

def test_adjust_fail() -> None:
    factory: cmaclib.Factory = cmaclib.Factory()

    upper: list[float] = [10.0, 10.0]
    lower: list[float] = [-10.0, -10.0]
    cmac: cmaclib.ICmac = factory.CreateCmac(10 \
        , 100 \
		, int(1e5) \
		, 2 \
		, upper \
		, lower \
		, 0.001 \
		, 0.00001)

    input: list[float] = [0.0, 0.0]
    prediction = cmac.Predict(input)

    assert prediction is not None

    correction: list[float] = [0.001]
    adjustment = cmac.Adjust(correction, prediction, 0.00001)

    assert adjustment is not None
    assert not adjustment.IsSuccessful()
    assert len(adjustment.GetWeightChanges()) == 0