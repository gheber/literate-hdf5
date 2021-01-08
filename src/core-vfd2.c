#include "literate-hdf5.h"

int main(int argc, char** argv)
{
  int data[] = {0, 1, 2, 3, 4, 5};

  hid_t file_d = (*
                  
                  lambda(hid_t, (const char* name),
                         {
                           return H5Fcreate(name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
                         })
                   ) ("disk.h5"); 
  hid_t file_m = (*
                  
                  lambda(hid_t, (const char* name, size_t increment, hbool_t flg),
                         {
                           hid_t retval;
                           hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
                  
                           H5Pset_fapl_core(fapl, increment, flg); 
                  
                           retval = H5Fcreate(name, H5F_ACC_TRUNC, H5P_DEFAULT, fapl);
                           H5Pclose(fapl);
                           return retval;
                         })
                   ) ("core.h5", 4096, (argc > 1)); 
  hid_t dset_m = (*
                  
                  lambda(hid_t,
                         (hid_t file, const char* name, hid_t dtype, const hsize_t* dims, void* buffer),
                         {
                           hid_t retval;
                           hid_t dspace = H5Screate_simple(2, dims, NULL);
                  
                           retval = H5Dcreate(file, name, dtype, dspace, 
                                              H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
                  
                           if (buffer)
                             H5Dwrite(retval, dtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, buffer); 
                  
                           H5Sclose(dspace);
                           return retval;
                         })
                   ) (file_m, "2x3", H5T_STD_I32LE, 
                                         (hsize_t[]){2,3}, data);
  H5Dclose(dset_m);

  (*
   
   lambda(void, (void),
          {
            unsigned majnum;
            unsigned minnum;
            unsigned relnum;
            H5get_libversion(&majnum, &minnum, &relnum);
            printf("HDF5 library version %d.%d.%d\n", majnum, minnum, relnum);
          })
    ) ();
  (*
   
   lambda(void, (hid_t file),
          {
            hsize_t size;
            H5Fget_filesize(file, &size);
            printf("File size: %ld bytes\n", size);
          })
    ) (file_m);

  H5Ocopy(file_m, "2x3", file_d, "2x3copy", H5P_DEFAULT, H5P_DEFAULT); 

  H5Fclose(file_m);

  (*
   
   lambda(void, (hid_t file),
          {
            hsize_t size;
            H5Fget_filesize(file, &size);
            printf("File size: %ld bytes\n", size);
          })
    ) (file_d);

  H5Fclose(file_d);

  return 0;
}
