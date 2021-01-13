#include "literate-hdf5.h"
#define SIZE 1024*1024

int main(int argc, char** argv)
{
  hid_t fapl, file, dset, file_space, mem_space;
  float* buffer;
  hsize_t file_size;

  fapl = H5Pcreate(H5P_FILE_ACCESS);
  file = H5Fcreate("single-proc.h5", H5F_ACC_TRUNC, H5P_DEFAULT,
                   fapl); 

  dset = (*
          
          lambda(hid_t, (hid_t file, const char* name, hsize_t elt_count),
                 {
                   hid_t result;
                   hid_t fspace = H5Screate_simple(1, (hsize_t[]) { elt_count },
                                                   NULL); 
                   result = H5Dcreate(file, name, H5T_IEEE_F32LE, fspace,
                                      H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT); 
                   H5Sclose(fspace);
                   return result;
                 })
          ) (file, "1Mi-floats", SIZE); 
  file_space = H5Dget_space(dset);
  H5Sselect_all(file_space);  

  
  buffer = (float*) malloc(SIZE*sizeof(float));
  { /* Do something interesting with buffer! */
    size_t i;
    for (i = 0; i < SIZE; ++i)
      buffer[i] = (float) i;
  }
  
  mem_space = H5Screate_simple(1, (hsize_t[]) { SIZE }, NULL); 
  H5Sselect_all(mem_space); 
  
  H5Dwrite(dset, H5T_NATIVE_FLOAT, mem_space, file_space, H5P_DEFAULT,
           buffer);
   

  
  H5Pclose(fapl);
  free(buffer);
  H5Sclose(mem_space);
  H5Sclose(file_space);
  H5Dclose(dset);
  H5Fclose(file);
  
}
