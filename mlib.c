#include <stdio.h>

/* 最大公約数 */
long gcd(long a, long b){
    long r = 1;
    while(r){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/* 最小公倍数 */
long lcm(long a, long b){
    return a * b / gcd(a, b);
}