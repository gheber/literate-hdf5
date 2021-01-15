#include "literate-hdf5.h"
#define SIZE 1024*1024

int main(int argc, char** argv)
{
  int size, rank;
  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  

  {
    hid_t fapl, file, dset, file_space;
    float* buffer;
    hsize_t file_size;

    fapl = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_mpio(fapl, MPI_COMM_WORLD, MPI_INFO_NULL); // 
    file = H5Fcreate("multi-proc.h5", H5F_ACC_TRUNC, H5P_DEFAULT,
                     fapl); // 

    dset = (*
            
            lambda(hid_t, (hid_t file, const char* name, hsize_t elt_count),
                   {
                     hid_t result;
                     hid_t fspace = H5Screate_simple(1, (hsize_t[]) { elt_count },
                                                     NULL); // 
                     result = H5Dcreate(file, name, H5T_IEEE_F32LE, fspace,
                                        H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT); // 
                     H5Sclose(fspace);
                     return result;
                   })
            ) (file, "xMi-floats", size*SIZE); // 
    file_space = H5Dget_space(dset);
    { // 
      hsize_t start = rank*SIZE, count = 1, block = SIZE;
      H5Sselect_hyperslab(file_space, H5S_SELECT_SET,
                          &start, NULL, &count, &block);
    } // 

    
    buffer = (float*) malloc(SIZE*sizeof(float));
    { /* Do something interesting with buffer! */
      size_t i;
      for (i = 0; i < SIZE; ++i)
        buffer[i] = (float) i;
    }
    
    {
      hid_t mem_space = H5Screate_simple(1, (hsize_t[]) { SIZE }, NULL); // 
      H5Sselect_all(mem_space); // 
    
      H5Dwrite(dset, H5T_NATIVE_FLOAT, mem_space, file_space, H5P_DEFAULT,
             buffer);
    
      H5Sclose(mem_space);
    }
     // 

    
    H5Pclose(fapl);
    free(buffer);
    H5Sclose(file_space);
    H5Dclose(dset);
    H5Fclose(file);
    
  }

  MPI_Finalize(); // 
}
