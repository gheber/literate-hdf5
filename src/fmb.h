#ifndef FMB_H
#define FMB_H

#include "hdf5.h"


#define FP16_BYTES  2
#define FP16_ORDER  H5T_ORDER_LE
#define FP16_PREC   16
#define FP16_OFFSET 0
#define FP16_SPOS   15
#define FP16_EPOS   10
#define FP16_ESIZE  5
#define FP16_EBIAS  15
#define FP16_MPOS   0
#define FP16_MSIZE  10
#define FP16_NORM   H5T_NORM_MSBSET
#define FP16_INPAD  H5T_PAD_ZERO
#define FP16_LSB    H5T_PAD_ZERO
#define FP16_MSB    H5T_PAD_ZERO

extern hid_t make_fp16();


#define BFLOAT16_BYTES  2
#define BFLOAT16_ORDER  H5T_ORDER_LE
#define BFLOAT16_PREC   16
#define BFLOAT16_OFFSET 0
#define BFLOAT16_SPOS   15
#define BFLOAT16_EPOS   7
#define BFLOAT16_ESIZE  8
#define BFLOAT16_EBIAS  127
#define BFLOAT16_MPOS   0
#define BFLOAT16_MSIZE  7
#define BFLOAT16_NORM   H5T_NORM_MSBSET
#define BFLOAT16_INPAD  H5T_PAD_ZERO
#define BFLOAT16_LSB    H5T_PAD_ZERO
#define BFLOAT16_MSB    H5T_PAD_ZERO

extern hid_t make_bfloat16();


#define TF32_BYTES  3
#define TF32_ORDER  H5T_ORDER_LE
#define TF32_PREC   19
#define TF32_OFFSET 0
#define TF32_SPOS   18
#define TF32_EPOS   10
#define TF32_ESIZE  8
#define TF32_EBIAS  127
#define TF32_MPOS   0
#define TF32_MSIZE  10
#define TF32_NORM   H5T_NORM_MSBSET
#define TF32_INPAD  H5T_PAD_ZERO
#define TF32_LSB    H5T_PAD_ZERO
#define TF32_MSB    H5T_PAD_ZERO

extern hid_t make_tf32();


#define FP24_BYTES  3
#define FP24_ORDER  H5T_ORDER_LE
#define FP24_PREC   24
#define FP24_OFFSET 0
#define FP24_SPOS   23
#define FP24_EPOS   16
#define FP24_ESIZE  7
#define FP24_EBIAS  63
#define FP24_MPOS   0
#define FP24_MSIZE  16
#define FP24_NORM   H5T_NORM_MSBSET
#define FP24_INPAD  H5T_PAD_ZERO
#define FP24_LSB    H5T_PAD_ZERO
#define FP24_MSB    H5T_PAD_ZERO

extern hid_t make_fp24();


extern hid_t make_fp_datatype
(
 size_t      bytes,
 H5T_order_t byte_order,
 size_t      precision,
 size_t      offset,
 size_t      spos,
 size_t      epos,
 size_t      esize,
 size_t      ebias,
 size_t      mpos,
 size_t      msize,
 H5T_norm_t  norm,
 H5T_pad_t   inpad,
 H5T_pad_t   lsb,
 H5T_pad_t   msb
 );

#endif /* FMB_H */
