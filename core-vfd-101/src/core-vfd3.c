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
                    ) ("core.h5", 1024*1024, (argc > 1));
  hid_t dset_m = (*
                   
                   lambda(hid_t,
                     (hid_t file, const char* name, hid_t dtype, const hsize_t* dims, void* buffer),
                     {
                       hid_t retval;
                       hid_t dspace = H5Screate_simple(2, dims,
                                                       (hsize_t[]){H5S_UNLIMITED, H5S_UNLIMITED}); 
                       hid_t dcpl = H5Pcreate(H5P_DATASET_CREATE);
                   
                       H5Pset_chunk(dcpl, 2, (hsize_t[]){1024, 1024}); 
                       retval = H5Dcreate(file, name, dtype, dspace, 
                                          H5P_DEFAULT, dcpl, H5P_DEFAULT); 
                   
                       if (buffer)
                         H5Dwrite(retval, dtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, buffer); 
                   
                       H5Pclose(dcpl);
                       H5Sclose(dspace);
                       return retval;
                     })
                    ) (file_m, "2x3", 
                                              H5T_NATIVE_INT32,
                                              (hsize_t[]){2,3}, data);
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

  { /* UNCERTAINTY */
    H5Dset_extent(dset_m, (hsize_t[]){200,300}); 

    H5Dset_extent(dset_m, (hsize_t[]){200000,300000});

    H5Dset_extent(dset_m, (hsize_t[]){2,3}); 
  }

  if ((*
        
        lambda(hid_t, (hid_t dset),
          {
            size_t retval;
            hid_t ftype = H5Dget_type(dset);
            hid_t dspace = H5Dget_space(dset);
        
            retval = H5Tget_size(ftype) *  
                       (size_t) H5Sget_simple_extent_npoints(dspace); 
        
            H5Sclose(dspace);
            H5Tclose(ftype);
            return retval;
          })
        ) (dset_m) < 60000) 
  {
     hid_t dset_d = (*
                      
                      lambda(hid_t, (hid_t src_dset, hid_t file, const char* name),
                        {
                          hid_t retval;
                          hid_t ftype = H5Dget_type(src_dset);
                          hid_t src_dspace = H5Dget_space(src_dset); 
                          hid_t dcpl = H5Pcreate(H5P_DATASET_CREATE);
                      
                          hid_t dspace = H5Scopy(src_dspace); 
                          hsize_t dims[H5S_MAX_RANK]; 
                          H5Sget_simple_extent_dims(dspace, dims, NULL);
                          H5Sset_extent_simple(dspace, H5Sget_simple_extent_ndims(dspace),
                                               dims, NULL); 
                      
                          H5Pset_layout(dcpl, H5D_COMPACT); 
                          retval = H5Dcreate(file, name, ftype, dspace,
                                             H5P_DEFAULT, dcpl, H5P_DEFAULT); 
                      
                          H5Pclose(dcpl);
                          H5Sclose(dspace);
                          H5Tclose(ftype);
                          return retval;
                        })
                       ) (dset_m, file_d, "2x3copy"); 
     (*
       
       lambda(void, (hid_t src, hid_t dst),
         {
           hid_t ftype = H5Dget_type(src);
           hid_t dspace = H5Dget_space(src);
           size_t size = H5Tget_size(ftype) * H5Sget_simple_extent_npoints(dspace); 
           char* buffer = (char*) malloc(size);
       
           H5Dread(src, ftype, H5S_ALL, H5S_ALL, H5P_DEFAULT, buffer); 
           H5Dwrite(dst, ftype, H5S_ALL, H5S_ALL, H5P_DEFAULT, buffer); 
       
           free(buffer);
           H5Sclose(dspace);
           H5Tclose(ftype);
         })
        ) (dset_m, dset_d); 

     H5Dclose(dset_d);
  }
  else
  {
    H5Ocopy(file_m, "2x3", file_d, "2x3copy", H5P_DEFAULT, H5P_DEFAULT); 
  }

  H5Dclose(dset_m);
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
