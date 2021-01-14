#include "literate-hdf5.h"

int main()
{
  unsigned majnum, minnum, relnum;
  H5get_libversion(&majnum, &minnum, &relnum);

  printf
    ("%f\n",
     (*
      lambda (float, (float x),
              {
                return x*x;
              })) (majnum+minnum+relnum)
     );

  return 0;
}
