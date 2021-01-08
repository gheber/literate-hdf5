#ifndef LITERATE_HDF5_H
#define LITERATE_HDF5_H


#include "hdf5.h"

#include <stdio.h>
#include <stdlib.h>


#define lambda(lambda$_ret, lambda$_args, lambda$_body) \
  ({                                                    \
    lambda$_ret lambda$__anon$ lambda$_args             \
      lambda$_body                                      \
      &lambda$__anon$;                                  \
  })


#endif
