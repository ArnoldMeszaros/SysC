#include "utils.hpp"

num_t to_fixed (unsigned char *buf){
    string s ="";
    num_t mult = 1; //sign

    for (int i = 0; i < BUFF_SIZE; ++i){
        s += bitset<CHAR_LEN>((int)buf[i]).to_string();//from unsigned char into binary
    }

    if (s[0] == '1'){
        s = bitset< TOTAL_SIZE + BUFF_EXTRA >( -stoi(s, 0, 2) ).to_string();//turn negative into positive and change mult
        mult = -1;
    }

    string w, f;//whole and fraction parts
    for(int i = 0; i < WHOLE_SIZE; i++){
        w += s[i];//whole part
    }
    for(int i = WHOLE_SIZE; i < TOTAL_SIZE; i++){
        f += s[i];//fraction part
    }

    int w_i = stoi(w, 0, 2);//turn from string into int
    double f_i = (double)stoi(f, 0, 2);//turn from string into double

    return (num_t) ( mult*(w_i + f_i / (1 << FRAC_SIZE)));//set put it back together and set sign
}

void to_uchar(unsigned char *buf, num_t d){
    string s = d.to_bin();//from num_t into binary

    s.erase(0,2);//erase 0b
    s.erase(I, 1);//erase .

    char single_char[CHAR_LEN];
    for (int i = 0; i < BUFF_SIZE; i++){
        s.copy(single_char, CHAR_LEN, i*CHAR_LEN);//copy first BUFF_SIZE bits
        buf[i] = (unsigned char) stoi(single_char, 0, 2);//change to unsigned char
    }
}

/*
double to_double(unsigned char *buf)
{
  string concated = "";
  for(int i = 0; i<CHARS_AMOUNT; ++i) //concatenate char array into eg. "10101101000"
    concated += bitset<CHAR_LEN>((int)buf[i]).to_string();

  cout << "concated = " << concated << endl;
  
  double multiplier = 1;
  
}
*/
