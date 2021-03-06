#include "qcor_hybrid.hpp"
#include <gtest/gtest.h>

// Define one quantum kernel that takes
// double angle parameter
__qpu__ void ansatz(qreg q, double x) {
  X(q[0]);
  Ry(q[1], x);
  CX(q[1], q[0]);
}

// Define another quantum kernel that takes
// a vector double argument, we just use one of them
// but we also demo more complicated ansatz construction
// using the exp_i_theta instruction
__qpu__ void ansatz_vec(qreg q, std::vector<double> x) {
  X(q[0]);
  auto ansatz_exponent = qcor::X(0) * qcor::Y(1) - qcor::Y(0) * qcor::X(1);
  exp_i_theta(q, x[0], ansatz_exponent);
}

__qpu__ void xasm_open_qasm_mixed_ansatz(qreg q, double xx) {
  using qcor::openqasm;
  x q[0];
  using qcor::xasm;
  // openqasm doesn't handle parameterized
  // gates, so switching to xasm here
  Ry(q[1], xx);
  using qcor::openqasm;
  cx q[1], q[0];
}

TEST(VQE_Hybrid_Tester, checkDeuteron) {

  // Define the Hamiltonian using the QCOR API
  auto H = 5.907 - 2.1433 * qcor::X(0) * qcor::X(1) -
           2.1433 * qcor::Y(0) * qcor::Y(1) + .21829 * qcor::Z(0) -
           6.125 * qcor::Z(1);

  // Create a VQE instance, must give it
  // the parameterized ansatz functor and Observable
  qcor::VQE vqe(ansatz, H);

  // Execute synchronously, providing the initial parameters to
  // start the optimization at
  const auto [energy, params] = vqe.execute(0.0);
  std::cout << "<H>(" << params[0] << ") = " << energy << "\n";

  EXPECT_NEAR(energy, -1.7488, 1e-3);

  // Now do the same for the vector double ansatz, but
  // also demonstrate the async interface
  qcor::VQE vqe_vec(ansatz_vec, H);
  auto handle = vqe_vec.execute_async(std::vector<double>{0.0});

  // Can go do other work, quantum execution is happening on
  // separate thread

  // Get the energy, this call will kick off a wait if needed
  const auto [energy_vec, params_vec] = vqe_vec.sync(handle);

  std::cout << "<H>(" << params_vec[0] << ") = " << energy_vec << "\n";

  EXPECT_NEAR(energy_vec, -1.7488, 1e-3);

  // Now run with the mixed language kernel,
  // initialize the optimization to x = .55, also
  // use a custom Optimizer
  auto optimizer =
      qcor::createOptimizer("nlopt", {std::make_pair("nlopt-maxeval", 10)});
  qcor::VQE vqe_openqasm(xasm_open_qasm_mixed_ansatz, H);
  const auto [energy_oq, params_oq] = vqe_openqasm.execute(optimizer, .55);

  std::cout << "<H>(" << params_oq[0] << ") = " << energy_oq << "\n";

  EXPECT_NEAR(energy_oq, -1.7488, 1e-3);

  // Can query information about the vqe run
  // Here, we get all parameter sets executed and correspnding energies seen
  auto all_params = vqe_openqasm.get_unique_parameters();
  auto all_energies_and_params = vqe_openqasm.get_unique_energies();
  std::cout << "All Energies and Parameters:\n";
  for (const auto energy_param : all_energies_and_params) {
      auto energy = energy_param.first;
      auto pset = energy_param.second;
      std::cout << "E: Pvec = " << energy << ": [ ";
      for (auto p : pset) { 
          std::cout << p << " ";
      }
      std::cout << "]" << std::endl;
  }
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  return ret;
}
