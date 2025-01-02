#include "soft.hpp"
#include <fstream>
#include "AudioFile.h"  // dodato
#include <complex>      // dodato
int thr;


int resize(int samples);

SC_HAS_PROCESS(Soft);

Soft::Soft(sc_core::sc_module_name name, char *coefs, char *samples)
  : sc_module(name)
  , offset(sc_core::SC_ZERO_TIME)
{
  // -------  ENYEM TBD-----------------------------------------------
  //std::vector<num_t> coeffsFile(COEFFS_SIZE, 0);
         // itt definialjuk a BASS, TREBLE valuekat 
  //if (std::string(coefs) == "BASS") {
  //  coeffsFile = {4, 3, 2, 0, 0, 0, 0, 0, 0, 0};
  //} else if (std::string(coefs) == "TREBLE") {
  //  coeffsFile = {0, 0, 0, 4, 4, 4, 4, 0, 0, 0};
  //}
  
  //coeffsFile.open(coefs);
  samplesFile.open(samples);
  std::cout<<"arg1: "<<coefs<<std::endl;
  std::cout<<"arg2: "<<samples<<std::endl;

  //Dodato iz main ----
  AudioFile<double> audioFile;              // audiFile (vector)
  vector<complex<double>> audioFileComplex;
  vector<complex<double>> transform;
  size_t oldSize;
  size_t newSize;
  float sampleRate;
  bool loadedOK = audioFile.load(samples); // read file

  if (!loadedOK)
  {
    cout << "problem with reading the wav file";
    cout << "call with -h argument: ./filename -h" << endl;
  }
  oldSize = audioFile.getNumSamplesPerChannel(); // save original size
  sampleRate = audioFile.getSampleRate();

  std::cout<<"oldSize: "<<oldSize<<std::endl;
  std::cout<<"sampleRate: "<<sampleRate<<std::endl;

  newSize = resize(audioFile.getNumSamplesPerChannel()); 
  std::cout<<"newSize: "<<newSize<<std::endl;

  audioFile.samples[0].resize(newSize);
  for (int i = oldSize; i < newSize; i++)
    audioFile.samples[0][i] = 0;

  for (int i = 0; i < audioFile.getNumSamplesPerChannel(); i++)
    audioFileComplex.push_back(audioFile.samples[0][i]);
  // Do ovde -----

  output.open("result.txt");
  /* fd_in = fopen( "cut.wav","rb");
    if(!fd_in)
    {
        SC_REPORT_ERROR("Soft", "Cannot open file.");
    }
    else {
        std::cout<<"Wav file opened"<<std::endl;
    }
    //skip heder info
    fseek(fd_in, 44, SEEK_SET);*/
  
  //if(!coeffsFile.is_open() || !samplesFile.is_open() )
  if(!samplesFile.is_open() )
    SC_REPORT_ERROR("Soft", "Cannot open file.");

  if(samplesFile.is_open())
    {
      while(samplesFile.peek()!=EOF)
	{
	  getline(samplesFile, line);
	  count++;
	}
    std::cout<<"count: "<<count<<std::endl;
    }
  
  samplesFile.seekg(0, ios::beg);
  thr = 0; 
  SC_THREAD(gen);
  SC_REPORT_INFO("Soft", "Constructed.");

}

int resize(int samples)
  {
	  int nth_degree[21] = {1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824};

	  for (int i = 0; i < 21; i++)
	  {
		  if (samples < nth_degree[i])
		  {
			  return nth_degree[i];
			  break;
		  }
	  }
	  return samples;
  }

Soft::~Soft()
{
  //coeffsFile.close(); -Nem kell
  samplesFile.close();
 
  SC_REPORT_INFO("Soft", "Destroyed.");
}

void Soft::gen()
{
  num_t write_val, read_val;
  int t = 0;
  
  int num =(int) std::ceil(count / BLOCK_SIZE);
  
  std::cout<<"Number of blocks: "<<num<<std::endl;

  for (int i = 0; i<COEFFS_SIZE; ++i) 
  {
    coeffsFile >> write_val;
    //coeffs >> write_val;
    write_bram(i, write_val,1);
    //std::cout<<"coeff: "<<coeffsFile<<std::endl;

  }
  // ---------- ENYEM TBD---------------------------- 
  
  // Ugy fog mukodni ahogy a fenti kommentben van
  // Definialni kell hozza fent a 16line-on a coeffs ertekeket
  //num_t write_val, read_val;
  //int t = 0;
  
  //int num =(int) std::ceil(count / BLOCK_SIZE);
  
  //std::cout<<"Number of blocks: "<<num<<std::endl;

  // Determine coefficients based on arg1
  //std::vector<num_t> coeffs(COEFFS_SIZE, 0); // Initialize with zeros
  //if (std::string(coefs) == "BASS") {
  //  coeffs = {4, 3, 2, 0, 0, 0, 0, 0, 0, 0};
  //} else if (std::string(coefs) == "TREBLE") {
  //  coeffs = {0, 0, 0, 4, 4, 4, 4, 0, 0, 0};
  //}

  //for (int i = 0; i < COEFFS_SIZE; ++i) {
  // write_bram(i, coeffs[i], 1);
  //}
  // ---------------------------------------
  
  
  std::cout<<"Coeffs written to BRAM. "<<std::endl;
  //wait (21*10.8,sc_core::SC_NS);  
  do
   {
      std::cout<<t+1<<". block "<<std::endl;

      for(int i = 0; i < SAMPLES_SIZE; ++i)
	{
	  samplesFile >> write_val;
	  //fread(&temp, 2, 1, fd_in);
	  //write_val = (num_t)temp;
	  //std::cout<<"Wav["<<i<<"]="<<temp<<std::endl;
	  write_bram(i , write_val, 0);
	}
	
      std::cout<<"Samples written to BRAM " <<std::endl<<std::endl;
     // wait (1024*10.8,sc_core::SC_NS);
     
     /*std::cout<<"TEST READ FROM BRAM's" <<std::endl;
     std::cout<<"-----------------------------------"<<std::endl;
     std::cout<<"Samples from BRAM " << std::endl;
     std::cout<<"-----------------------------------"<<std::endl;
     for(int i = 0; i<SAMPLES_SIZE; ++i)
     {
     	read_val = read_bram(i,0);
     	std::cout<<"samples["<<i<<"]= "<<read_val<<std::endl;
     }*/
     
     /*
     std::cout<<"-----------------------------------"<<std::endl;
     std::cout<<"Coeffs from BRAM " << std::endl;
     std::cout<<"-----------------------------------"<<std::endl;
     for(int i = 0; i<COEFFS_SIZE; ++i)
     {
     	read_val = read_bram(i,1);
     	std::cout<<"coefs["<<i<<"]= "<<read_val<<std::endl;
     }
     */

   
  write_hard(ADDR_CMD, 1);  //start hardware

  while(read_hard(ADDR_STATUS) == 0) // wait for hardwarw to finish
    {
       
    }

  std::cout << std::endl << "Hardware finished. " << std::endl<<std::endl;
 
  num_t temp;
  
  for(int i = 0; i< OUTPUT_SIZE; i++)
    {
       temp = read_bram(i, 2);
       
       output <<temp << "," <<std::endl;
    }
   
  std::cout<<"Finished "<<t<<". block of samples. " <<std::endl<<std::endl;
  
  t++;
  
    } while(t<num);
      
  //int timeDelay;
  //sscanf(delay.to_string().c_str()," %d ns", &timeDelay);
  //double throughput = 1024.0*counter/timeDelay;
  //std::cout<<"Throughput: "<<throughput<<" Mb/s"<<std::endl;
     

}



num_t Soft::read_bram(sc_dt::uint64 addr, unsigned char type)
{
  pl_t pl; //payload
  unsigned char buf[BUFF_SIZE]; //buffer that converts num_t into unsigned_char

  sc_dt::uint64 taddr= (addr*BUFF_SIZE) | VP_ADDR_BRAM_BASE;

  switch(type)
    {
    case 0:
      taddr |= VP_ADDR_SAMPLES_BASE;
      break;
    case 1:
      taddr |= VP_ADDR_COEFFS_BASE;
      break;
    case 2:
      taddr |= VP_ADDR_RESULT_BASE;
      break;
    default:
      break;
    }
  pl.set_address(taddr);
  pl.set_data_length(BUFF_SIZE); //length of buffer
  pl.set_data_ptr(buf);
  pl.set_command( tlm::TLM_READ_COMMAND );
  pl.set_response_status ( tlm::TLM_INCOMPLETE_RESPONSE );
  interconnect_socket->b_transport(pl,offset);
  wait (10.8,sc_core::SC_NS);
  return to_fixed(buf); //unsigned_char to buff;
}

void Soft::write_bram(sc_dt::uint64 addr, num_t val, unsigned char type)
{
  pl_t pl;
  unsigned char buf[BUFF_SIZE]; //buffer that converts num_t into unsigned char for ic
  to_uchar(buf,val);
  sc_dt::uint64 taddr = (addr*BUFF_SIZE) | VP_ADDR_BRAM_BASE;

  switch(type)
    {
    case 0:
      taddr |= VP_ADDR_SAMPLES_BASE;
      break;
    case 1:
      taddr |= VP_ADDR_COEFFS_BASE;
      break;
    case 2:
      taddr |= VP_ADDR_RESULT_BASE;
      break;
    default:
      break;
    }
  
  pl.set_address(taddr);
  pl.set_data_length(BUFF_SIZE);
  pl.set_data_ptr(buf);
  pl.set_command( tlm::TLM_WRITE_COMMAND );
  pl.set_response_status ( tlm::TLM_INCOMPLETE_RESPONSE );
  interconnect_socket->b_transport(pl,offset);
  wait (10.8,sc_core::SC_NS); 
}


num_t Soft::read_hard(sc_dt::uint64 addr)
{
  pl_t pl;
  unsigned char buf[BUFF_SIZE]; //buffer that converts num_t into unsigned_char
  pl.set_address(addr | VP_ADDR_HARD_BASE);
  pl.set_data_length(BUFF_SIZE);
  pl.set_data_ptr(buf);
  pl.set_command( tlm::TLM_READ_COMMAND );
  pl.set_response_status ( tlm::TLM_INCOMPLETE_RESPONSE );
  sc_core::sc_time offset = sc_core::SC_ZERO_TIME;
  interconnect_socket->b_transport(pl,offset); //trasnfer

  return to_fixed(buf);
}

void Soft::write_hard(sc_dt::uint64 addr, int val)
{
  pl_t pl;
  unsigned char buf[BUFF_SIZE];
  to_uchar (buf, val); //convert val to unsigned char
  pl.set_address(addr | VP_ADDR_HARD_BASE);
  pl.set_data_length(BUFF_SIZE);
  pl.set_data_ptr(buf);
  pl.set_command( tlm::TLM_WRITE_COMMAND );
  pl.set_response_status ( tlm::TLM_INCOMPLETE_RESPONSE );
  interconnect_socket->b_transport(pl,offset); //transfer
}


