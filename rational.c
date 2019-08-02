#include <stdio.h>
#include <stdlib.h>
#include "mlib.c"
#include "sqrt.c"

typedef struct rational{
    long numerator, denominator;
} rational;

/* 約分 */
void reduction(rational *r){
    int g;
    g = gcd(r->numerator, r->denominator);
    r -> numerator /= g;
    r -> denominator /= g;
}

void print_rational(rational r){
    printf("(%ld/%ld)\n", r.numerator, r.denominator);
}

/* 有理数の和 */
rational rplusr(rational r0, rational r1){
    int l = lcm(r0.denominator, r1.denominator);
    rational r;
    r.numerator = l*r0.numerator/r0.denominator + l*r1.numerator/r1.denominator;
    r.denominator = l;
    reduction(&r);
    return r;
}

/* 有理数の積 */
rational rproductr(rational r0, rational r1){
    rational r;
    int g;
    r.numerator = r0.numerator * r1.numerator;
    r.denominator = r0.denominator * r1.denominator;
    reduction(&r);
    return r;
}

/* 平方根 */
rational rsqrt(rational r){
    rational r0;
    double d = r.numerator/r.denominator;
    double x = sqrt(d);
    r0.numerator = x*100000000000000;
    r0.denominator = 100000000000000;
    reduction(&r0);
    return r0;
}