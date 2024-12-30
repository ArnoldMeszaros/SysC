# all: main

# # main: main.cpp generator.cpp generator.hpp memory.cpp memory.hpp top.cpp top.hpp utils.cpp utils.hpp conv.cpp conv.hpp
# # 	g++ -I/opt/systemc/include -L/opt/systemc/lib-linux64 -lsystemc -o main main.cpp generator.cpp memory.cpp top.cpp utils.cpp conv.cpp

# main: main.cpp vp.hpp vp.cpp soft.hpp soft.cpp bram.hpp bram.cpp
# 	g++ -std=c++11 -DSC_INCLUDE_FX -I/opt/systemc/include -L/opt/systemc/lib-linux64 -lsystemc -o main main.cpp vp.cpp soft.cpp bram.cpp

# .PHONY: clean
# clean:
# 	rm main
SYSTEMC=/opt/systemc
SRC_CPP=$(wildcard *.cpp)
SRC_HPP=$(wildcard *.hpp)
MAIN_TARGET=main*.cpp
TARGET=$(patsubst %.cpp,%,$(wildcard main*.cpp))
all: $(TARGET)
$(TARGET): $(SRC_CPP) $(SRC_HPP)
	g++ -DSC_INCLUDE_FX -w -g -I ${SYSTEMC}/include -L${SYSTEMC}/lib-linux64 -lsystemc -o $@ *.cpp
.PHONY: clean
clean:
	rm $(TARGET)