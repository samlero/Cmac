/*
    This file contains the python macros that exports C++ classes to
    something that the python interpreter can read.
*/

#include "CmacLib.h"

// Implementation header files.
#include "Result.h"
#include "Serialization.h"
#include "Prediction.h"
#include "Adjustment.h"
#include "Marshaller.h"
#include "Cmac.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace CmacLib;

PYBIND11_MODULE(cmaclib, m) {
    pybind11::class_<IResult, Result>(m, "IResult")
        .def("IsSuccessful", &IResult::IsSuccessful)
        .def("GetMessage", &IResult::GetMessage);

    pybind11::class_<ISerialization, Serialization, IResult>(m, "ISerialization")
        .def("GetString", &ISerialization::GetString);

    pybind11::class_<IPrediction, Prediction, IResult>(m, "IPrediction")
        .def("GetValues", &IPrediction::GetValues)
        .def("GetActiveWeightIndices", &IPrediction::GetActiveWeightIndices)
        .def("GetActiveWeights", &IPrediction::GetActiveWeights)
        .def("GetBasisValues", &IPrediction::GetBasisValues);

    pybind11::class_<IAdjustment, Adjustment, IResult>(m, "IAdjustment")
        .def("GetWeightChanges", &IAdjustment::GetWeightChanges);

    pybind11::class_<IMarshaller, Marshaller>(m, "IMarshaller")
        .def("Save", &IMarshaller::Save)
        .def("Load", &IMarshaller::Load);

    pybind11::class_<ISerializable, Cmac>(m, "ISerializable")
        .def("Serialize", &ISerializable::Serialize)
        .def("Deserialize", &ISerializable::Deserialize);

    pybind11::class_<ICmac, Cmac>(m, "ICmac")
        .def("Predict", &ICmac::Predict)
        .def("Adjust", &ICmac::Adjust);

    pybind11::class_<Factory>(m, "Factory")
        .def(pybind11::init<>())
        .def("CreateCmac", &Factory::CreateCmac)
        .def("CreateDefaultCmac", &Factory::CreateDefaultCmac)
        .def("CreateMarshaller", &Factory::CreateMarshaller);
}