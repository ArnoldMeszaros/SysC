#include <systemc>
#include "vp.hpp"
extern int thr;
#include <chrono>
using namespace sc_core;
using namespace tlm;

sc_core::sc_time offset, delay;
int counter;

int sc_main(int argc, char* argv[])
{
  counter = 0;
  if(argc!=3){
  	std::cout<<"Start with: "<<std::endl;
  	std::cout << "./filename 'wavFileNam' 'presets' " << std::endl;
std::cout << "presets can be: bass, mid, trebble" << std::endl;
std::cout << "example: ./program someFile.wav bass" << std::endl;
    return 0;
  }
  Vp vp("VP",argv[1],argv[2]);
  sc_start(10, sc_core::SC_MS);
  //std::printf("Throughput is: %d\n", thr*100);
  return 0;
}
