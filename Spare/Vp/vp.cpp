#include "vp.hpp"

Vp::Vp (sc_core::sc_module_name name, char *coefs, char *samples)
  : sc_module (name)
  , soft("Soft", coefs, samples)
  , hard("Hard")
  , bram_smpl("Bram_S")
  , bram_coef("Bram_C")
  , bram_result("Bram_R")
  , bram_ctrl("BramCtrl")
  , interconnect("Interconnect")
{
  soft.interconnect_socket.bind(interconnect.soft_socket);
  interconnect.bram_socket.bind(bram_ctrl.soft_socket);
  bram_ctrl.bram_samples_socket.bind(bram_smpl.bram_port_a);
  bram_ctrl.bram_coeffs_socket.bind(bram_coef.bram_port_a);
  bram_ctrl.bram_result_socket.bind(bram_result.bram_port_a);
  interconnect.hard_socket.bind(hard.soft_socket);
  hard.bram_samples_socket.bind(bram_smpl.bram_port_b);
  hard.bram_coeffs_socket.bind(bram_coef.bram_port_b);
  hard.bram_result_socket.bind(bram_result.bram_port_b);

  SC_REPORT_INFO("Virtual Platform", "Constructed.");
}

Vp::~Vp()
{
  SC_REPORT_INFO("Virtual Platform", "Destroyed.");
}
