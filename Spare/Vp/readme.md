#Task
1. Correct Soft::Gen() for option selection
  //if (std::string(coefs) == "BASS") {
  //  coeffsFile = {4, 3, 2, 0, 0, 0, 0, 0, 0, 0};

# bram_ctrl
interconnect variacio, atnezni
# bram
sablon (160 old gpio), atirni
# soft
read vaw file, send data points to bram (sima .cpp filebol kiszedni), minden a mainbol kiveve az fft + ifft
# hard
to be changed to fft + ifft + filter?
# interconnect
nincs benne nagy fantazia, sablon a vezbankabol (167old sys_bus)
# main
part with args #tbd 
ok
# typedefs.hpp
atirni sajatokra - def data, addr, size..
# utils
atirni sajatokra - num_t to_fixed, void to_uchar, #tbd
# vp
ok



