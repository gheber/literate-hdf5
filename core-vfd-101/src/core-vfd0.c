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
  int data[] = {0, 1, 2, 3, 4, 5};
  hid_t file = (*
                 
                 lambda(hid_t, (const char* name),
                   {
                     return H5Fcreate(name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
                   })
                  ) ("disk.h5"); 
  hid_t dset = (*
                 
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
                  ) (file, "2x3", H5T_STD_I32LE, 
                                        (hsize_t[]){2,3}, data);
  H5Dclose(dset);

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
     ) (file);

  H5Fclose(file);

  return 0;
}
