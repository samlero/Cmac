/*
    This file contains the python macros that exports C++ classes to
    something that the python interpreter can read.
*/

#include "CmacLib.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace CmacLib;

PYBIND11_MODULE(pycmaclib, m) {
    pybind11::class_<IResult>(m, "IResult",
        pybind11::multiple_inheritance())
        .def("IsSuccessful", &IResult::IsSuccessful,
            "Indicates if an operation was successful.",
            pybind11::return_value_policy::take_ownership)
        .def("GetMessage", &IResult::GetMessage,
            "If not successful, a failure message is provided.",
            pybind11::return_value_policy::take_ownership);

    pybind11::class_<ISerialization, IResult>(m, "ISerialization",
        pybind11::multiple_inheritance())
        .def("GetString", &ISerialization::GetString,
            "The string from the resulting serialization process.",
            pybind11::return_value_policy::take_ownership);

    pybind11::class_<IPrediction, IResult>(m, "IPrediction",
        pybind11::multiple_inheritance())
        .def("GetValues", &IPrediction::GetValues,
            "Get the calculated multiplication and "
            "accumulation of basis and active weights.",
            pybind11::return_value_policy::reference_internal)
        .def("GetActiveWeightIndices", &IPrediction::GetActiveWeightIndices,
            "Get the indices of the active weights.",
            pybind11::return_value_policy::reference_internal)
        .def("GetActiveWeights", &IPrediction::GetActiveWeights,
            "Get the values of the active weights.",
            pybind11::return_value_policy::reference_internal)
        .def("GetBasisValues", &IPrediction::GetBasisValues,
            "Get the basis function values.",
            pybind11::return_value_policy::reference_internal);

    pybind11::class_<IAdjustment, IResult>(m, "IAdjustment",
        pybind11::multiple_inheritance())
        .def("GetWeightChanges", &IAdjustment::GetWeightChanges,
            "Get the amount the each active weight changed.",
            pybind11::return_value_policy::reference_internal);

    pybind11::class_<IMarshaller>(m, "IMarshaller",
        pybind11::multiple_inheritance())
        .def("Save", &IMarshaller::Save,
            "Save the serializable object.",
            pybind11::arg("serializable"),
            "Object to save. (ISerializable)",
            pybind11::arg("directory"),
            "Folder to save the serializable object in. (str)",
            pybind11::arg("filename"),
            "Name of the object to save. (str)",
            pybind11::return_value_policy::take_ownership)
        .def("Load", &IMarshaller::Load,
            "Fills the contents of the serialzable object.",
            pybind11::arg("serializable"),
            "Object to fill. (ISerializable)",
            pybind11::arg("filepath"),
            "Location of the file that contains "
            "the serializable object's contents. (str)",
            pybind11::return_value_policy::take_ownership);

    pybind11::class_<ISerializable>(m, "ISerializable",
        pybind11::multiple_inheritance())
        .def("Serialize", &ISerializable::Serialize,
            "Serializes the object in its own unique format.",
            pybind11::return_value_policy::take_ownership)
        .def("Deserialize", &ISerializable::Deserialize,
            "Deserializes the content into its member variables.",
            pybind11::arg("content"),
            "Valid deserializable content.",
            pybind11::return_value_policy::take_ownership)
        .def("GetExtension", &ISerializable::GetExtension,
            "Extension of the serializable object",
            pybind11::return_value_policy::take_ownership);

    pybind11::class_<ICmac, ISerializable>(m, "ICmac",
        pybind11::multiple_inheritance())
        .def("Predict", &ICmac::Predict,
            "Serializes the object in its own unique format.",
            pybind11::arg("input"),
            "States. (list[float])",
            pybind11::return_value_policy::take_ownership)
        .def("Adjust", &ICmac::Adjust,
            "Deserializes the content into its member variables.",
            pybind11::arg("correction"),
            "Error of the prediction. (list[float])",
            pybind11::arg("prediction"),
            "Contains indices of weights and basis values. (IPrediction)",
            pybind11::arg("damping"),
            "Additional damping to further reduce chances of overfitting. (float)",
            pybind11::return_value_policy::take_ownership)
        .def("Zeroize", &ICmac::Zeroize,
            "Extension of the serializable object",
            pybind11::return_value_policy::take_ownership);

    pybind11::class_<Factory>(m, "Factory")
        .def(pybind11::init<>())
        .def("CreateCmac", &Factory::CreateCmac,
            "Create a raw and untrained Cmac.",
            pybind11::arg("numQ"),
            "Number of quantizations. (int)",
            pybind11::arg("numLayers"),
            "Number of layers. This would "
            "indicate number of active weights. (int)",
            pybind11::arg("maxmem"),
            "Maximum potential memory index or memory size. (int)",
            pybind11::arg("numOut"),
            "Number of outputs. (int)",
            pybind11::arg("upper"),
            "Upper limits of the Predict method inputs. (list[float])",
            pybind11::arg("lower"),
            "Lower limits of the Predict method inputs. (list[float])",
            pybind11::arg("beta"),
            "Learning rate. (float)",
            pybind11::arg("nu"),
            "Damping coefficient. (float)",
            pybind11::return_value_policy::take_ownership)
        .def("CreateDefaultCmac", &Factory::CreateDefaultCmac,
            "Create a Cmac with default values.",
            pybind11::return_value_policy::take_ownership)
        .def("CreateMarshaller", &Factory::CreateMarshaller,
            "Creates an instance of IMarshaller.",
            pybind11::return_value_policy::take_ownership);
}