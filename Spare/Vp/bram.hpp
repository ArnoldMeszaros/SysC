#ifndef BRAM_HPP
#define BRAM_HPP

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_target_socket.h>
#include <vector>
#include "typedefs.hpp"
#include <iostream>

class Bram : public sc_core::sc_module
{
public:
  Bram (sc_core::sc_module_name name);
  ~Bram();
  tlm_utils::simple_target_socket<Bram> bram_port_a;
  tlm_utils::simple_target_socket<Bram> bram_port_b;
protected:
  void b_transport(pl_t &, sc_core::sc_time &);
  std::vector<num_t> mem;
};

#endif // BRAM_HPP