#include "bram.hpp"

Bram::Bram(sc_core::sc_module_name name) : sc_module(name)
{
  bram_port_a.register_b_transport(this, &Bram::b_transport);
  bram_port_b.register_b_transport(this, &Bram::b_transport);
  mem.reserve(MEM_RESERVED);

  SC_REPORT_INFO("BRAM", "Constructed.");
}

Bram::~Bram()
{
  SC_REPORT_INFO("BRAM", "Destroyed.");
}

void Bram::b_transport(pl_t &pl, sc_core::sc_time &offset)
{
  tlm::tlm_command cmd = pl.get_command();
  sc_dt::uint64 addr = pl.get_address();
  unsigned int len = pl.get_data_length();
  unsigned char *buf = pl.get_data_ptr();

  switch(cmd)
    {
    case tlm::TLM_WRITE_COMMAND:
      for (unsigned int i = 0; i < len; ++i)
        {
          mem[addr++] = buf[i];
        }
      pl.set_response_status( tlm::TLM_OK_RESPONSE );
      break;
    case tlm::TLM_READ_COMMAND:
      for (unsigned int i = 0; i < len; ++i)
        {
          buf[i] = mem[addr++];
        }
      pl.set_response_status( tlm::TLM_OK_RESPONSE );
      break;
    default:
      pl.set_response_status( tlm::TLM_COMMAND_ERROR_RESPONSE );
    }

  offset += sc_core::sc_time(10, sc_core::SC_NS);
}
