#include "mdb_set_math.h"

void MdbSetMath::px_pos_to_cnum(int *px_x, int *px_y, Complex *pan, double long *zoom, Complex *cnum) {
    cnum->setReal(pan->getReal() + *px_x * *zoom);
    cnum->setImaginary(pan->getImaginary() - *px_y * *zoom);
}