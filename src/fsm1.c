#include "hdf5.h"

#include <stdio.h>
#include <stdlib.h>


#define lambda(lambda$_ret, lambda$_args, lambda$_body) \
  ({                                                    \
    lambda$_ret lambda$__anon$ lambda$_args             \
      lambda$_body                                      \
      &lambda$__anon$;                                  \
  })


int main(int argc, char** argv)
{
  hid_t file = (*
                lambda(hid_t, (const char* name, hsize_t threshold),
                       {
                         hid_t result;
                         hid_t fcpl = H5Pcreate(H5P_FILE_CREATE);
                         hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
                         H5Pset_file_space_strategy(fcpl, H5F_FSPACE_STRATEGY_PAGE, 1, // 
                                                    threshold);
                         H5Pset_libver_bounds(fapl, H5F_LIBVER_V110, H5F_LIBVER_LATEST); // 
                
                         result = H5Fcreate(name, H5F_ACC_TRUNC, fcpl, fapl);
                         H5Pclose(fapl);
                         H5Pclose(fcpl);
                
                         return result;
                       }) ) ("fsm.h5", 1048576); // 
  H5Dclose((*
             lambda(hid_t, (hid_t file, const char* name, hid_t dtype),
                    {
                      hid_t result;
                      hid_t fspace = H5Screate_simple(2, (hsize_t[]) {1024, 1024}, NULL);
                      hid_t lcpl = H5Pcreate(H5P_LINK_CREATE);
                      hid_t dcpl = H5Pcreate(H5P_DATASET_CREATE);
             
                      H5Pset_create_intermediate_group(lcpl, 1);
                      H5Pset_alloc_time(dcpl, H5D_ALLOC_TIME_EARLY);
             
                      result = H5Dcreate(file, name, dtype, fspace, lcpl, dcpl,
                                         H5P_DEFAULT);
                      H5Pclose(dcpl);
                      H5Pclose(lcpl);
                      H5Sclose(fspace);
             
                      return result;
                    }) ) (file, "1Mi-double", H5T_IEEE_F64LE));
  H5Dclose((*
             lambda(hid_t, (hid_t file, const char* name, hid_t dtype),
                    {
                      hid_t result;
                      hid_t fspace = H5Screate_simple(2, (hsize_t[]) {1024, 1024}, NULL);
                      hid_t lcpl = H5Pcreate(H5P_LINK_CREATE);
                      hid_t dcpl = H5Pcreate(H5P_DATASET_CREATE);
             
                      H5Pset_create_intermediate_group(lcpl, 1);
                      H5Pset_alloc_time(dcpl, H5D_ALLOC_TIME_EARLY);
             
                      result = H5Dcreate(file, name, dtype, fspace, lcpl, dcpl,
                                         H5P_DEFAULT);
                      H5Pclose(dcpl);
                      H5Pclose(lcpl);
                      H5Sclose(fspace);
             
                      return result;
                    }) ) (file, "1Mi-float", H5T_IEEE_F32LE));

  H5Ldelete(file, "1Mi-double", H5P_DEFAULT);
  H5Fclose(file);

  file = H5Fopen("fsm.h5", H5F_ACC_RDWR, H5P_DEFAULT);
  H5Dclose((*
            lambda(hid_t, (hid_t file, const char* name, hid_t dtype),
                   {
                     hid_t result;
                     hid_t fspace = H5Screate_simple(2, (hsize_t[]) {1024, 1024}, NULL);
                     hid_t lcpl = H5Pcreate(H5P_LINK_CREATE);
                     hid_t dcpl = H5Pcreate(H5P_DATASET_CREATE);
            
                     H5Pset_create_intermediate_group(lcpl, 1);
                     H5Pset_alloc_time(dcpl, H5D_ALLOC_TIME_EARLY);
            
                     result = H5Dcreate(file, name, dtype, fspace, lcpl, dcpl,
                                        H5P_DEFAULT);
                     H5Pclose(dcpl);
                     H5Pclose(lcpl);
                     H5Sclose(fspace);
            
                     return result;
                   }) ) (file, "1Mi-uint64", H5T_STD_U64LE));
  H5Fclose(file);
}
