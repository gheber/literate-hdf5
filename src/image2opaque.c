#include "literate-hdf5.h"

int main(int argc, char** argv)
{
  size_t size;
  char* buf = (*
               
               lambda(char*, (const char* name, size_t* size),
                      {
                        char* result;
                        FILE* fp = fopen(name, "rb");
                        fseek(fp, 0L, SEEK_END);
                        *size = ftell(fp);
                        fseek(fp, 0, SEEK_SET);
                        result = (char*) malloc(*size);
                        fread(result, size, 1, fp);
                        fclose(fp);
                        return result;
                      })
               ) ("./img/timeseries_vis.png", &size);
  printf("%ld\n", size);

  (*
   
   lambda(void,
          (const char* fname, const char* dname,
           const char* buf, size_t size),
          {
            hid_t file = H5Fopen(fname, H5F_ACC_RDWR, H5P_DEFAULT);
            hid_t dtype = H5Tcreate(H5T_OPAQUE, size);
            hid_t dspace = H5Screate(H5S_SCALAR);
            hid_t dset;
            H5Tset_tag(dtype, "image/png");
            dset = H5Dcreate(file, dname, dtype, dspace,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
            H5Dwrite(dset, dtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
            H5Dclose(dset);
            H5Sclose(dspace);
            H5Tclose(dtype);
            H5Fclose(file);
          })
   ) ("hello.hdf5", "bytes", buf, size);

  free(buf);
  return 0;
}
