#ifndef SOFT_HPP_
#define SOFT_HPP_

#include <iostream>
#include <fstream>
#include <systemc>
#include <tlm_utils/simple_initiator_socket.h>
#include <stdio.h>
#include <stdlib.h>
#include "typedefs.hpp"
#include "utils.hpp"

class Soft : public sc_core::sc_module
{
public:
  Soft(sc_core::sc_module_name name, char *coefs, char *samples);
  ~Soft();
  tlm_utils::simple_initiator_socket<Soft> interconnect_socket;

protected:
   void gen(); //main software function
   pl_t pl; //payload
   sc_core::sc_time offset; //time
   std::ifstream coeffsFile; 
   std::ifstream samplesFile; //input files
   std::ofstream output; 
   //FILE *fd_in;
   //unsigned short input[SAMPLES_SIZE];
   string line;
   int count = 0;
   //unsigned short temp;
  
  num_t read_bram(sc_dt::uint64 addr, unsigned char type); 
  void write_bram(sc_dt::uint64 addr, num_t val, unsigned char type); 

  num_t read_hard(sc_dt::uint64 addr);
  void write_hard(sc_dt::uint64 addr, int val);

};

#endif // SOFT_HPP_
