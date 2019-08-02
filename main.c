#include <stdio.h>
#include "vector.c"

int main(void){
    rational a4[] = {{1,1},{2,1},{3,1}};
    vector v4 = vector_new(a4, sizeof(a4)/sizeof(rational));
    print_rational(norm(v4));
    
    return 0;
}