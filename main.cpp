#include <iostream>
#include "rational.cpp"

int main(){
    Rational a(1, 2), b(3, 2), r;
    r = a * b;
    r.p();
}