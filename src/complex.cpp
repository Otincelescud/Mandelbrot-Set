#include "complex.h"
#include <cmath>

Complex::Complex(long double r, long double i) { real = r; imaginary= i; }
Complex::~Complex() {}

void Complex::setReal(long double r) { real = r; }
void Complex::setImaginary(long double i) { imaginary = i; }

long double Complex::getReal() { return real; }
long double Complex::getImaginary() { return imaginary; }

Complex Complex::operator+(Complex complex_num) { return Complex(real + complex_num.getReal(), imaginary + complex_num.getImaginary()); }
Complex Complex::operator-(Complex complex_num) { return Complex(real - complex_num.getReal(), imaginary + complex_num.getImaginary()); }

Complex Complex::operator*(Complex complex_num) {
    return Complex(real*complex_num.getReal() - imaginary*complex_num.getImaginary(),
                   real*complex_num.getImaginary() + imaginary*complex_num.getReal());
}

Complex Complex::operator/(Complex complex_num) {
    return Complex((real*complex_num.getReal() + imaginary*complex_num.getImaginary())/(complex_num.getReal()*complex_num.getReal() + complex_num.getImaginary()*complex_num.getImaginary()),
                   (imaginary*complex_num.getImaginary() - real*complex_num.getReal())/(complex_num.getReal()*complex_num.getReal() + complex_num.getImaginary()*complex_num.getImaginary()));
}

const long double Complex::modulus() { return sqrt(real*real + imaginary*imaginary); }