#include "mdb_set_math.h"

void MdbSetMath::px_pos_to_cnum(int *px_x, int *px_y, Complex *pan, double long *zoom, Complex *cnum) {
    cnum->setReal(pan->getReal() + *px_x * *zoom);
    cnum->setImaginary(pan->getImaginary() - *px_y * *zoom);
}

void MdbSetMath::cnum_to_px_pos(Complex *cnum, Complex *pan, double long *zoom, int *px_x, int *px_y) {
    *px_x = int((cnum->getReal() - pan->getReal()) / *zoom);
    *px_y = int((cnum->getImaginary() - pan->getImaginary()) / *zoom);
}