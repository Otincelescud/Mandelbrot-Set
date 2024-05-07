#ifndef Mdb_set_math_h
#define Mdb_set_math_h

#include "complex.h"

class MdbSetMath {
public:
    static void px_pos_to_cnum(int *px_x, int *px_y, Complex *pan, long double *zoom, Complex *cnum);
    static void cnum_to_px_pos(Complex *cnum, Complex *pan, long double *zoom, int *px_x, int *px_y);
    static bool is_part_of_mdb_set(Complex *cnum, int max_iteration);

};

#endif /* Mdb_set_math_h */