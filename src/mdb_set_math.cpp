#include "mdb_set_math.h"

void MdbSetMath::px_pos_to_cnum(int *px_x, int *px_y, Complex *pan, double long *zoom, Complex *cnum) {
    cnum->setReal(pan->getReal() + *px_x * *zoom);
    cnum->setImaginary(pan->getImaginary() - *px_y * *zoom);
}

void MdbSetMath::cnum_to_px_pos(Complex *cnum, Complex *pan, double long *zoom, int *px_x, int *px_y) {
    *px_x = int((cnum->getReal() - pan->getReal()) / *zoom);
    *px_y = int((cnum->getImaginary() - pan->getImaginary()) / *zoom);
}

bool MdbSetMath::is_part_of_mdb_set(Complex *cnum, int max_iteration) {
    // Checks if cnum is outside the rectangle that encloses the Mandelbrot Set
    if (cnum->getReal() < -2 || cnum->getReal() > 0.25 || cnum->getImaginary() < -1.12 || cnum->getImaginary() > 1.12) return false;

    // Checks if fc(fc(fc(...))) blows up to infinity, where fc(z) = z^2 + c and z is initialy 0
    Complex num = Complex(0, 0);
    int iteration = 0;
    while (num.modulus() <= 2 && iteration < max_iteration) {
        num = num*num + *cnum;
    }

    return iteration == max_iteration;
}