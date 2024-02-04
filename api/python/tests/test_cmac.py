#!/usr/bin/python

import cmaclib

def test_object_member_existence() -> None:
    factory: cmaclib.Factory = cmaclib.Factory()

    assert hasattr(factory.CreateCmac, "__call__")
    assert hasattr(factory.CreateDefaultCmac, "__call__")
    assert hasattr(factory.CreateMarshaller, "__call__")

    # Create cmac to check its members.
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

    assert hasattr(cmac.Predict, "__call__")
    assert hasattr(cmac.Adjust, "__call__")
    assert hasattr(cmac.Zeroize, "__call__")
    # Remember how ICmac also inherits from ISerializable.
    assert hasattr(cmac.Serialize, "__call__")
    assert hasattr(cmac.Deserialize, "__call__")
    assert hasattr(cmac.GetExtension, "__call__")

    # Create IResult object to check its members.
    result = cmac.Zeroize()

    assert hasattr(result.IsSuccessful, "__call__")
    assert hasattr(result.GetMessage, "__call__")

    # Create prediction to check its members.
    input: list[float] = [0.0, 0.0]
    prediction = cmac.Predict(input)

    assert hasattr(prediction.GetValues, "__call__")
    assert hasattr(prediction.GetActiveWeightIndices, "__call__")
    assert hasattr(prediction.GetActiveWeights, "__call__")
    assert hasattr(prediction.GetBasisValues, "__call__")
    # Remember how IPrediction also inherits from IResult.
    assert hasattr(prediction.IsSuccessful, "__call__")
    assert hasattr(prediction.GetMessage, "__call__")

    # Create adjustment to check its members.
    correction: list[float] = [0.001, 0.001]
    adjustment = cmac.Adjust(correction, prediction, 0.00001)

    assert hasattr(adjustment.GetWeightChanges, "__call__")
    # Remember how IAdjustment also inherits from IResult.
    assert hasattr(adjustment.IsSuccessful, "__call__")
    assert hasattr(adjustment.GetMessage, "__call__")

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