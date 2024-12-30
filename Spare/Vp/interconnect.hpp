#ifndef INTERCONNECT_HPP_
#define INTERCONNECT_HPP_

#include <iostream>
#include <fstream>
#include <systemc>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include "typedefs.hpp"
#include "utils.hpp"

class Interconnect : public sc_core::sc_module
{
public:
  Interconnect(sc_core::sc_module_name name);
  ~Interconnect();
  tlm_utils::simple_initiator_socket<Interconnect> bram_socket;
  tlm_utils::simple_initiator_socket<Interconnect> hard_socket;
  tlm_utils::simple_target_socket<Interconnect> soft_socket;

protected:
  pl_t pl;
  sc_core::sc_time offset;
  void b_transport(pl_t &pl, sc_core::sc_time &offset);
};

#endif // INTERCONNECT_HPP_
