#include "fmb.h"


#include <assert.h>

hid_t make_fp_datatype
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
 )
{
  hid_t result = (byte_order == H5T_ORDER_LE) ?
    H5Tcopy(H5T_IEEE_F64LE) : H5Tcopy(H5T_IEEE_F64BE);
  assert(result >= 0);
  assert(H5Tset_offset(result, offset) >= 0);
  assert(H5Tset_fields(result, spos, epos, esize, mpos, msize) >= 0);
  assert(H5Tset_ebias(result, ebias) >= 0);
  assert(H5Tset_norm(result, norm) >= 0);
  assert(H5Tset_inpad(result, inpad) >= 0);
  assert(H5Tset_pad(result, lsb, msb) >= 0);
  assert(H5Tset_precision(result, precision) >= 0);
  assert(H5Tset_size(result, bytes) >= 0);

  return result;
}



hid_t make_fp16()
{
  return make_fp_datatype(FP16_BYTES, FP16_ORDER, FP16_PREC,
                          FP16_ORDER, FP16_SPOS, FP16_EPOS,
                          FP16_ESIZE, FP16_EBIAS, FP16_MPOS,
                          FP16_MSIZE, FP16_NORM, FP16_INPAD,
                          FP16_LSB, FP16_MSB);
}


hid_t make_bfloat16()
{
  return make_fp_datatype(BFLOAT16_BYTES, BFLOAT16_ORDER, BFLOAT16_PREC,
                          BFLOAT16_ORDER, BFLOAT16_SPOS, BFLOAT16_EPOS,
                          BFLOAT16_ESIZE, BFLOAT16_EBIAS, BFLOAT16_MPOS,
                          BFLOAT16_MSIZE, BFLOAT16_NORM, BFLOAT16_INPAD,
                          BFLOAT16_LSB, BFLOAT16_MSB);
}


hid_t make_tf32()
{
  return make_fp_datatype(TF32_BYTES, TF32_ORDER, TF32_PREC,
                          TF32_ORDER, TF32_SPOS, TF32_EPOS,
                          TF32_ESIZE, TF32_EBIAS, TF32_MPOS,
                          TF32_MSIZE, TF32_NORM, TF32_INPAD,
                          TF32_LSB, TF32_MSB);
}


hid_t make_fp24()
{
  return make_fp_datatype(FP24_BYTES, FP24_ORDER, FP24_PREC,
                          FP24_ORDER, FP24_SPOS, FP24_EPOS,
                          FP24_ESIZE, FP24_EBIAS, FP24_MPOS,
                          FP24_MSIZE, FP24_NORM, FP24_INPAD,
                          FP24_LSB, FP24_MSB);
}


int main(int argc, char** argv)
{
  hid_t file = H5Fcreate("float_my_boat.h5", H5F_ACC_TRUNC,
                         H5P_DEFAULT, H5P_DEFAULT);
  hid_t dtype = make_fp16();
  H5Tcommit(file, "fp16", dtype, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  H5Tclose(dtype);
  dtype = make_bfloat16();
  H5Tcommit(file, "bfloat16", dtype, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  H5Tclose(dtype);
  dtype = make_tf32();
  H5Tcommit(file, "tf32", dtype, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  H5Tclose(dtype);
  dtype = make_fp24();
  H5Tcommit(file, "fp24", dtype, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  H5Tclose(dtype);

  H5Fclose(file);
  return 0;
}
