#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <bitset>
#include "typedefs.hpp"

using namespace std;

static const int TOTAL_SIZE = W;//num of bits in num_t
static const int WHOLE_SIZE = I;//num of whole bits in num_t
static const int FRAC_SIZE = TOTAL_SIZE - WHOLE_SIZE;//num of fractional bits in num_t
static const int CHAR_LEN = 8;  //8  //num of bits in char
static const int CHARS_AMOUNT = TOTAL_SIZE / CHAR_LEN;
static const int BUFF_SIZE = (int) std::ceil( (float)TOTAL_SIZE / CHAR_LEN);//how many chars are needed for num_t
static const int BUFF_EXTRA = BUFF_SIZE*CHAR_LEN - TOTAL_SIZE;//how many chars are extra

extern sc_core::sc_time offset;
extern sc_core::sc_time delay;
extern int counter;

num_t to_fixed (unsigned char *buf); //change unsigned char * into num_t
void to_uchar (unsigned char *buf, num_t d); //change num_t into unsigned char*
//double to_double(unsigned char *buf);



#endif // _UTILS_HPP_
