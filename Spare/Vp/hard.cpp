#include "hard.hpp"
extern int thr;

Hard::Hard(sc_core::sc_module_name name)
  : sc_module(name)
  , start(0)
  , done(0)
  , offset(sc_core::SC_ZERO_TIME)
{
  soft_socket.register_b_transport(this, &Hard::b_transport); 
 
  SC_REPORT_INFO("Hard", "Constructed.");
}

Hard::~Hard()
{
  SC_REPORT_INFO("Hard", "Destroyed.");
}

void Hard::firFunction()
{
  num_t temp;
  num_t acc ;
  // done = false;

   //read coeffs from bram and store in array
  for(int i = 0; i < COEFFS_SIZE; i++)
    {
      temp = read_bram(i , 1);
       //std::cout<<"coefsH["<<i<<"]=" << temp<<std::endl;
       coeffsH[i] = temp;
    }
  //wait (21*10.8,sc_core::SC_NS);
  std::cout<<"Read samples from Bram... "<<std::endl;
  //read samples from bram and store in array
  for(int i = 0; i < SAMPLES_SIZE; i++)
    {
      temp = read_bram(i,0);
       //std::cout<<"samplesH["<<i<<"]=" << temp <<std::endl;
      samplesH[i] = temp;
    }
    
  std::cout<<"Samples read from BRAM."<<std::endl;
  //wait (1024*10.8,sc_core::SC_NS);
   

  // memcpy(&inputSamples[COEFFS_SIZE -1], &samplesH, SAMPLES_SIZE * sizeof(num_t) );
  std::cout<<"Filtering... "<<std::endl;
   num_t *coeffp = NULL;
   num_t *inputp = NULL;
  //apply filter to each input sample
  for(int i = 0; i < SAMPLES_SIZE; i++)
    {
      counter++;
      
      delay+=sc_core::sc_time(10.8, sc_core::SC_NS);
      coeffp = coeffsH;
      // inputp = &inputSamples[i];
      inputp = &samplesH[i];
      acc = 0;
      for(int k = 0; k < COEFFS_SIZE; k++)
	{
	  delay+=sc_core::sc_time(10.8, sc_core::SC_NS);
	  acc += (*coeffp++) *(*inputp--);
	}
      result[i] = acc * gain ;
      write_bram(i,result[i], 2);
      // std::cout<<"result["<<i<<"]="<<result[i]<<std::endl;
    }
      //wait (1024*10.8,sc_core::SC_NS);
  // memmove(&samplesH[0], &samplesH[SAMPLES_SIZE], (COEFFS_SIZE-1)*sizeof(num_t));
 std::cout<<"Filtering done! "<<std::endl;
 thr++;
 done = true;
  
}

void Hard::b_transport(pl_t &pl, sc_core::sc_time &offset)
{
  tlm::tlm_command cmd = pl.get_command();
  sc_dt::uint64 addr = pl.get_address();
  unsigned int len = pl.get_data_length();
  unsigned char *buf = pl.get_data_ptr();
  pl.set_response_status( tlm::TLM_OK_RESPONSE );

  if(len != BUFF_SIZE)
    {
      pl.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
    }

  if(cmd == tlm::TLM_WRITE_COMMAND)
    {
      if(addr == ADDR_CMD)
	{
	  // start = to_fixed(buf);
	  start = true;
	  done = !start;
	  std::cout<<"Call firFunction()"<<std::endl;
	  firFunction();
	}
      else
	{
	  pl.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
	}
      
    }
  else if(cmd == tlm::TLM_READ_COMMAND)
    {
      if(addr == ADDR_STATUS)
	{
	  to_uchar(buf, done);
	}
      
      else if(addr >= VP_ADDR_SAMPLES_BASE)
	{
	  to_uchar(buf, result[addr - VP_ADDR_SAMPLES_BASE]);
	  }
      else{
	
	pl.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
	
      }

    }
  else{
    
    pl.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
    
  }
    
   offset += sc_core::sc_time(10, sc_core::SC_NS);
}
    

num_t Hard::read_bram(int addr, unsigned char type)
{
  pl_t pl;
  unsigned char buf[BUFF_SIZE];
  pl.set_address(addr*BUFF_SIZE);
  pl.set_data_length(BUFF_SIZE);
  pl.set_data_ptr(buf);
  pl.set_command( tlm::TLM_READ_COMMAND );
  pl.set_response_status ( tlm::TLM_INCOMPLETE_RESPONSE );
  sc_core::sc_time offset = sc_core::SC_ZERO_TIME;

  switch(type)
    {
    case 0:
      bram_samples_socket->b_transport(pl, offset);
      break;
    case 1:
      bram_coeffs_socket->b_transport(pl, offset);
      break;
    case 2:
      bram_result_socket->b_transport(pl, offset);
      break;
    default:
      break;
    }
  wait (10.8,sc_core::SC_NS);
  return to_fixed(buf);
}

void Hard::write_bram(int addr, num_t val, unsigned char type)
{
  pl_t pl;
  unsigned char buf[BUFF_SIZE];
  to_uchar(buf,val);
  pl.set_address(addr*BUFF_SIZE);
  pl.set_data_length(BUFF_SIZE);
  pl.set_data_ptr(buf);
  pl.set_command( tlm::TLM_WRITE_COMMAND );
  pl.set_response_status ( tlm::TLM_INCOMPLETE_RESPONSE );

  switch(type)
    {
    case 0:
      bram_samples_socket->b_transport(pl, offset);
      break;
    case 1:
      bram_coeffs_socket->b_transport(pl, offset);
      break;
    case 2:
      bram_result_socket->b_transport(pl, offset);
      break;
    default:
      break;
      
    }
  wait (10.8,sc_core::SC_NS);    
  
}

