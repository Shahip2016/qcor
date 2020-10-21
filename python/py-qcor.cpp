#include "base/qcor_qsim.hpp"
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
namespace py = pybind11;

PYBIND11_MODULE(_pyqcor, m) {
  m.doc() = "Python bindings for QCOR.";
  // Expose QCOR API functions
  m.def(
      "createOptimizer",
      [](const std::string &name, py::dict p = {}) {
        xacc::HeterogeneousMap params;
        std::cout << "HOWDY: " << name << "\n";
        /// TODO: reuse XACC PyHetMap here
        for (auto item : p) {
          std::cout << "key=" << std::string(py::str(item.first)) << ", "
                    << "value=" << std::string(py::str(item.second)) << "\n";
        }

        return qcor::createOptimizer(name, std::move(params));
      },
      py::arg("name"), py::arg("p") = py::dict(),
      py::return_value_policy::reference,
      "Return the Optimizer with given name.");

  // qsim sub-module bindings:
  {
    py::module qsim = m.def_submodule("qsim", "QCOR's python qsim submodule");

    // QuantumSimulationModel bindings:
    py::class_<qcor::qsim::QuantumSimulationModel>(
        qsim, "QuantumSimulationModel",
        "The QuantumSimulationModel captures the quantum simulation problem "
        "description.")
        .def(py::init<>());

    // ModelBuilder bindings:
    py::class_<qcor::qsim::ModelBuilder>(
        qsim, "ModelBuilder",
        "The ModelBuilder interface provides methods to "
        "construct qsim problem models.")
        .def(py::init<>())
        .def(
            "createModel",
            [](qcor::PauliOperator &obs, qcor::qsim::TdObservable ham_func) {
              return qcor::qsim::ModelBuilder::createModel(obs, ham_func);
            },
            "Return the Model for a time-dependent problem.");
  }
}