#include <iostream>
#include "rational.cpp"
#include "matrix.cpp"

int main(){
    Rational a(1, 2), b(3, 2), r;
    r = a * b;
    r.p();

    Matrix <double> m = Matrix<double>::identity(3);
    // Matrix <double> m(3);
    // m.matrix[0][0] = 1;
    // m.matrix[0][1] = 1;
    // m.matrix[0][2] = -1;
    // m.matrix[1][0] = -2;
    // m.matrix[1][1] = 0;
    // m.matrix[1][2] = 1;
    // m.matrix[2][0] = 0;
    // m.matrix[2][1] = 2;
    // m.matrix[2][2] = 1;
    // m.inv().p().del();
    m.p().del();
    
    // Vector<int> vec = Vector<int>(10);
    // std::cout << vec[0] << std::endl;
    // vec.p().del();
}