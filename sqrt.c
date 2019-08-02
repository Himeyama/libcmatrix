#include <stdio.h>

double sqrt(double a){
    double x = a;
    int i;
    for(i=0;i<12;i++)
        x = (x*x+a)/(2*x);
    return x;
}