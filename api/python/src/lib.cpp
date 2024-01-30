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
    pybind11::class_<IResult>(m, "IResult")
        .def("IsSuccessful", &IResult::IsSuccessful, pybind11::return_value_policy::take_ownership)
        .def("GetMessage", &IResult::GetMessage, pybind11::return_value_policy::take_ownership);
    pybind11::class_<Result, IResult>(m, "Result");

    pybind11::class_<ISerialization, IResult>(m, "ISerialization")
        .def("GetString", &ISerialization::GetString, pybind11::return_value_policy::take_ownership);
    pybind11::class_<Serialization, ISerialization, Result>(m, "Serialization");

    pybind11::class_<IPrediction, IResult>(m, "IPrediction")
        .def("GetValues", &IPrediction::GetValues, pybind11::return_value_policy::reference_internal)
        .def("GetActiveWeightIndices", &IPrediction::GetActiveWeightIndices, pybind11::return_value_policy::reference_internal)
        .def("GetActiveWeights", &IPrediction::GetActiveWeights, pybind11::return_value_policy::reference_internal)
        .def("GetBasisValues", &IPrediction::GetBasisValues, pybind11::return_value_policy::reference_internal);
    pybind11::class_<Prediction, IPrediction, Result>(m, "Prediction");

    pybind11::class_<IAdjustment, IResult>(m, "IAdjustment")
        .def("GetWeightChanges", &IAdjustment::GetWeightChanges, pybind11::return_value_policy::reference_internal);
    pybind11::class_<Adjustment, IAdjustment, Result>(m, "Adjustment");

    pybind11::class_<IMarshaller>(m, "IMarshaller")
        .def("Save", &IMarshaller::Save, pybind11::return_value_policy::take_ownership)
        .def("Load", &IMarshaller::Load, pybind11::return_value_policy::take_ownership);
    pybind11::class_<Marshaller, IMarshaller>(m, "Marshaller");

    pybind11::class_<ISerializable>(m, "ISerializable")
        .def("Serialize", &ISerializable::Serialize, pybind11::return_value_policy::take_ownership)
        .def("Deserialize", &ISerializable::Deserialize, pybind11::return_value_policy::take_ownership);

    pybind11::class_<ICmac, ISerializable>(m, "ICmac")
        .def("Predict", &ICmac::Predict, pybind11::return_value_policy::take_ownership)
        .def("Adjust", &ICmac::Adjust, pybind11::return_value_policy::take_ownership);

    pybind11::class_<Cmac, ICmac>(m, "Cmac");

    pybind11::class_<Factory>(m, "Factory")
        .def(pybind11::init<>())
        .def("CreateCmac", &Factory::CreateCmac, pybind11::return_value_policy::take_ownership)
        .def("CreateDefaultCmac", &Factory::CreateDefaultCmac, pybind11::return_value_policy::take_ownership)
        .def("CreateMarshaller", &Factory::CreateMarshaller, pybind11::return_value_policy::take_ownership);
}