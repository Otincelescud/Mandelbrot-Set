#ifndef Mdb_set_math_h
#define Mdb_set_math_h

#include "complex.h"

class MdbSetMath {
public:
    template<typename T> static void px_pos_to_cnum(T *px_x, T *px_y, Complex<T> *pan, T *zoom, Complex<T> *cnum);
    template<typename T> static void cnum_to_px_pos(Complex<T> *cnum, Complex<T> *pan, T *zoom, T *px_x, T *px_y);
    template<typename T> static const bool Is_part_of_mdb_set(Complex<T> *point);

};

#endif /* Mdb_set_math_h */