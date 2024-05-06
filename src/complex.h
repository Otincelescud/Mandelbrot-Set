#ifndef Complex_h
#define Complex_h

template<typename T> class Complex {
public:
    Complex(T r, T i);
    ~Complex();

    void setReal(T r);
    void setImaginary(T i);

    T getReal();
    T getImaginary();

    Complex<T> operator+(Complex<T> complex_num);
    Complex<T> operator-(Complex<T> complex_num);
    Complex<T> operator*(Complex<T> complex_num);
    Complex<T> operator/(Complex<T> complex_num);

private:
    T real;
    T imaginary;
};

#endif /* Complex_h */