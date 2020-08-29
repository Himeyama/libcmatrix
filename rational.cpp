#include <iostream>

class Rational{
    public:
        long numerator;
        long denominator;

        Rational(){
            numerator = 1;
            denominator = 1;
        }

        Rational(long n){
            numerator = n;
            denominator = 1;
        }

        Rational(long n, long d){
            numerator = n;
            denominator = d;
        }

        static long gcd(long a, long b){
            return b ? gcd(b, a % b) : a;
        }

        Rational operator +(Rational a){
            Rational r(
                numerator * a.denominator + denominator * a.numerator,
                denominator * a.denominator
            );
            return r.reduction();
        }

        Rational operator -(Rational a){
            a.numerator *= -1;
            return *this + a;
        }

        Rational operator *(Rational a){
            Rational r(
                numerator * a.numerator,
                denominator * a.denominator
            );
            return r.reduction();
        }

        Rational operator /(Rational a){
            long tmp = a.numerator;
            a.numerator = a.denominator;
            a.denominator = tmp;
            return *this * a;
        }

        Rational reduction(){
            long gcd = Rational::gcd(numerator, denominator);
            if(gcd < 0) gcd *= -1;
            numerator /= gcd;
            denominator /= gcd;
            return *this;
        }

        std::string inspect(){
            return "(" + std::to_string(numerator) + "/" + std::to_string(denominator) + ")";
        }

        void p(){
            std::cout << inspect() << std::endl;
        }
};