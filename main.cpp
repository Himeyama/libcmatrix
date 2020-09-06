#include <iostream>
#include <cmath>
#include "rational.cpp"
#include "matrix.cpp"

int main(){
    Matrix<Rational> v = {{1_r, 2_r},{3_r, 4_r}};
    v.about();

    // (v + v).p();

    // std::cout << 1_r << std::endl;
    
    // std::cout << 1.0 << std::endl;


    //  (1.2 - (int)1.2 / 1)

    // Matrix <double> m(3);
    // m = {{1, 1, -1}, {-2, 0, -1}, {0, 2, 1}};
    // m.about();

    // m.p();
    // m.u().p();
    // m.l().p();
    // (m.l() * m.u()).p();
}