#!/usr/bin/python

import os
import pytest
import cmaclib

@pytest.fixture(scope="function")
def setup_teardown() -> None:
    """Setup teardown fixture for each test case.
    """

    # Delete .cmac serialization files.
    cmac_files = [file for file in os.listdir() if file.endswith(".cmac")]
    for file in cmac_files:
        os.remove(file)

    yield
    # This block will execute after the test.

    # Delete .cmac serialization files.
    cmac_files = [file for file in os.listdir() if file.endswith(".cmac")]
    for file in cmac_files:
        os.remove(file)

def test_object_member_existence(setup_teardown) -> None:
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

    # Create serialization to check its members.
    serialization = cmac.Serialize()

    assert hasattr(serialization.GetString, "__call__")
    # Remember how ISerialization also inherits from IResult.
    assert hasattr(serialization.IsSuccessful, "__call__")
    assert hasattr(serialization.GetMessage, "__call__")

def test_serialize_deserialize_cmac(setup_teardown) -> None:
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

    serialization = cmac.Serialize()

    assert serialization.IsSuccessful()
    assert len(serialization.GetString()) > 0
    assert len(serialization.GetMessage()) == 0

    def_cmac = factory.CreateDefaultCmac()
    deserialization = def_cmac.Deserialize(serialization.GetString())

    assert deserialization.IsSuccessful()
    assert len(deserialization.GetMessage()) == 0

    marshaller = factory.CreateMarshaller()
    marshaller.Save(cmac, os.getcwd(), "expected")

    another_serialization = def_cmac.Serialize()

    assert another_serialization.IsSuccessful()
    assert len(another_serialization.GetString()) > 0
    assert len(another_serialization.GetMessage()) == 0
    
    assert len(serialization.GetString()) == len(another_serialization.GetString())