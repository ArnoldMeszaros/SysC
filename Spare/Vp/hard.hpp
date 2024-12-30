#ifndef HARD_HPP_
#define HARD_HPP_

#include <systemc>
#include <math.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include "typedefs.hpp"
#include "utils.hpp"

class Hard : public sc_core::sc_module
{
public:
  Hard(sc_core::sc_module_name name);
  ~Hard();
  
  tlm_utils::simple_initiator_socket<Hard> bram_samples_socket;
  tlm_utils::simple_initiator_socket<Hard> bram_coeffs_socket;
  tlm_utils::simple_initiator_socket<Hard> bram_result_socket;
  tlm_utils::simple_target_socket<Hard> soft_socket;

protected:
  pl_t pl;
  sc_core::sc_time offset;

  // num_t start, done;
  bool start, done;

  num_t result[10*SAMPLES_SIZE];
  num_t samplesH[10*SAMPLES_SIZE];
  num_t coeffsH[COEFFS_SIZE];
  num_t inputSamples[BUFFER_LEN];
  num_t gain = 1.0;

  void firFunction();
  void b_transport(pl_t &pl, sc_core::sc_time &offset);
  num_t read_bram(int addr, unsigned char type);
  void write_bram(int addr, num_t val, unsigned char type);
  
};

#endif // HARD_HPP_
