#include <stdio.h>

/* 最大公約数 */
int gcd(int a, int b){
    int r = 1;
    while(r){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/* 最小公倍数 */
int lcm(int a, int b){
    return a * b / gcd(a, b);
}