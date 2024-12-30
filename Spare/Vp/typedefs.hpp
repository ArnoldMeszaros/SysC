#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#define SC_INCLUDE_FX
#include <systemc>
#include <tlm>

#define W 32 // DATA_WIDTH
#define I 16// FIXED_POINT_WIDTH
#define Q sc_dt::SC_RND // quantization methods: SC_RND_ZERO, SC_RND_MIN_INF, SC_RND_INF, SC_RND_CONV, SC_TRN, SC_TRN_ZERO
#define O sc_dt::SC_WRAP // overflow methods: SC_SAT_ZERO, SC_SAT_SYM, SC_WRAP, SC_WRAP_SYM
typedef sc_dt::sc_fixed_fast <W, I, Q, O> num_t;

typedef tlm::tlm_base_protocol_types::tlm_payload_type pl_t;
typedef tlm::tlm_base_protocol_types::tlm_phase_type ph_t;

#define ADDR_CMD 0x18
#define ADDR_STATUS 0x1c
#define ADDR_RES 0x20
//#define ADDR_INIT 0x30
#define ADDR_STATUS_INIT 0x38


#define VP_ADDR_BRAM_BASE 0x01000000
#define VP_ADDR_BRAM_L 0x01000000
#define VP_ADDR_BRAM_H 0x01D00000

#define VP_ADDR_HARD_BASE 0x02000000
#define VP_ADDR_HARD_L 0x02000000
#define VP_ADDR_HARD_H 0x0200001c

#define VP_ADDR_SAMPLES_BASE 0x00000000
#define VP_ADDR_SAMPLES_L 0x00000000
#define VP_ADDR_SAMPLES_H 0x0000FFFF

#define VP_ADDR_COEFFS_BASE 0x00010000
#define VP_ADDR_COEFFS_L  0x00010000
#define VP_ADDR_COEFFS_H  0x0001FFFF

#define VP_ADDR_RESULT_BASE 0x00020000
#define VP_ADDR_RESULT_L 0x00020000
#define VP_ADDR_RESULT_H 0x0002FFFF

#define SAMPLES_SIZE 1024
#define OUTPUT_SIZE 1024
#define COEFFS_SIZE 21
#define BLOCK_SIZE 1024
#define BUFFER_LEN (SAMPLES_SIZE -1 + COEFFS_SIZE)
#define MEM_RESERVED 100000

#endif // TYPEDEFS_HPP
