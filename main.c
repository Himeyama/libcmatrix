#include <stdio.h>
#include "vector.c"

int main(void){
    rational a4[] = {{1,1},{2,1},{3,1}};
    vector v4 = vector_new(a4, sizeof(a4)/sizeof(rational));
    rational a5[] = {{4,1},{5,1},{6,1}};
    vector v5 = vector_new(a5, sizeof(a5)/sizeof(rational));
    print_vector(v4);
    print_vector(v5);

    print_rational(inner_product_vector(&v4, &v5));
    
    return 0;
}