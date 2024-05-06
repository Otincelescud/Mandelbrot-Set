#include "complex.h"

template<typename T> Complex<T>::Complex(T r, T i) { real = r; imaginary= i; }
template<typename T> Complex<T>::~Complex() {}

template<typename T> void Complex<T>::setReal(T r) { real = r; }
template<typename T> void Complex<T>::setImaginary(T i) { imaginary = i; }

template<typename T> T Complex<T>::getReal() { return real; }
template<typename T> T Complex<T>::getImaginary() { return imaginary; }

template<typename T> Complex<T> Complex<T>::operator+(Complex<T> complex_num) { return Complex(real + complex_num.getReal(), imaginary + complex_num.getImaginary()); }
template<typename T> Complex<T> Complex<T>::operator-(Complex<T> complex_num) { return Complex(real - complex_num.getReal(), imaginary + complex_num.getImaginary()); }

template<typename T> Complex<T> Complex<T>::operator*(Complex<T> complex_num) {
    return Complex(real*complex_num.getReal() - imaginary*complex_num.getImaginary(),
                   real*complex_num.getImaginary() + imaginary*complex_num.getReal())
}

template<typename T> Complex<T> Complex<T>::operator/(Complex<T> complex_num) {
    return Complex((real*complex_num.getReal() + imaginary*complex_num.getImaginary())/(complex_num.getReal()*complex_num.getReal() + complex_num.getImaginary()*complex_num.getImaginary()),
                   (imaginary*complex_num.getImaginary() - real*complex_num.getReal())/(complex_num.getReal()*complex_num.getReal() + complex_num.getImaginary()*complex_num.getImaginary()))
}