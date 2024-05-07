#ifndef Complex_h
#define Complex_h

class Complex {
public:
    Complex(long double r, long double i);
    ~Complex();

    void setReal(long double r);
    void setImaginary(long double i);

    long double getReal();
    long double getImaginary();

    Complex operator+(Complex complex_num);
    Complex operator-(Complex complex_num);
    Complex operator*(Complex complex_num);
    Complex operator/(Complex complex_num);

private:
    long double real;
    long double imaginary;
};

#endif /* Complex_h */