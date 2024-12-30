#include "bram_ctrl.hpp"

BramCtrl::BramCtrl(sc_core::sc_module_name name) : sc_module(name)
{
  soft_socket.register_b_transport(this, &BramCtrl::b_transport);
  SC_REPORT_INFO("BRAM Controller", "Constructed.");
}

BramCtrl::~BramCtrl()
{
  SC_REPORT_INFO("BRAM Controller", "Destroyed.");
}

void BramCtrl::b_transport(pl_t &pl, sc_core::sc_time &offset)
{
  tlm::tlm_command cmd = pl.get_command();
  sc_dt::uint64 addr = pl.get_address();
  sc_dt::uint64 taddr = addr & 0x000FFFF; //mask to get local addres
  unsigned int len = pl.get_data_length();
  unsigned char *buf = pl.get_data_ptr();

  /*
  pl_samples.set_command(cmd);
  pl_samples.set_address(addr);
  pl_samples.set_data_length(BUFF_SIZE);
  pl_samples.set_data_ptr(buf);
  pl_samples.set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

  pl_coeffs.set_command(cmd);
  pl_coeffs.set_address(addr);
  pl_coeffs.set_data_length(BUFF_SIZE);
  pl_coeffs.set_data_ptr(buf+4);
  pl_coeffs.set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

   bram_samples_socket->b_transport(pl_samples,offset);
  if (pl_samples.is_response_error()) SC_REPORT_ERROR("Bram_SE",pl_samples.get_response_string().c_str());

  bram_coeffs_socket->b_transport(pl_coeffs,offset);
  if (pl_coeffs.is_response_error()) SC_REPORT_ERROR("Bram_CO",pl_coeffs.get_response_string().c_str());
  */

  pl_pt.set_command(cmd);
  pl_pt.set_data_length(len);
  pl_pt.set_data_ptr(buf);
  pl_pt.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE );

  if(addr >= VP_ADDR_SAMPLES_L && addr <= VP_ADDR_SAMPLES_H)
    {
      pl_pt.set_address(taddr & 0x00000FFF);
      bram_samples_socket->b_transport(pl_pt, offset);
    }
  else if(addr >= VP_ADDR_COEFFS_L && addr <= VP_ADDR_COEFFS_H)
    {
       pl_pt.set_address(taddr & 0x00000FFF);
      bram_coeffs_socket->b_transport(pl_pt, offset);
      
    }
  else if(addr >= VP_ADDR_RESULT_L && addr <= VP_ADDR_RESULT_H)
    {
      pl_pt.set_address(taddr & 0x00000FFF);
      bram_result_socket->b_transport(pl_pt, offset);
    }
  else
    {
      SC_REPORT_ERROR("Interconnect", "Wrong addres.");
      pl_pt.set_response_status (tlm::TLM_ADDRESS_ERROR_RESPONSE );
      
    }
  
 

}
