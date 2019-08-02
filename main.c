#include <stdio.h>
#include <stdlib.h>

typedef struct rational{
    int numerator, denominator;
} rational;

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

/* 約分 */
void reduction(rational *r){
    int g;
    g = gcd(r->numerator, r->denominator);
    r -> numerator /= g;
    r -> denominator /= g;
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

void print_rational(rational r){
    printf("(%d/%d)\n", r.numerator, r.denominator);
}

/* ベクトルの定義 */
typedef rational _vector;

typedef struct vector{
    int size;
    _vector *vector;
} vector;

void print_vector(vector v){
    int i;
    _vector *p = v.vector;
    printf("[\n");
    for(i=0; i<v.size; i++){
        printf("    (%d/%d)\n", p[i].numerator, p[i].denominator );
    }
    printf("]\n");
}

_vector *_vector_new(int size, int numerator){
    int i;
    rational *vector = malloc(sizeof(rational) * size);
    for(i=0;i<size;i++){
        vector[i].denominator = 1;
        vector[i].numerator = numerator;
    }
    return vector;
}

vector one_vector_new(int size){
    vector vector;
    vector.size = size;
    vector.vector = _vector_new(size, 1);
    return vector;
}

vector zero_vector_new(int size){
    vector vector;
    vector.size = size;
    vector.vector = _vector_new(size, 0);
    return vector;
}

vector vector_new(rational value[], int size){
    int i;
    vector v;
    v.size = size;
    v.vector = value;
    return v;
}

/* ベクトルに関する関数*/

/* ベクトルのスカラー倍 */
void scalar_product_vector(int scalar, vector v){
    int size = v.size;
    _vector *p = v.vector;
    int i;
    for(i=0;i<size;i++){
        p[i].numerator = scalar * (p[i].numerator);
    }
}

/* 逆ベクトル */
void inverse_vector(vector v){
    scalar_product_vector(-1, v);
}

/* 内積 */
rational inner_product_vector(struct vector *v0, struct vector *v1){
    int i;
    rational sum = {0, 1};
    rational *r0 = v0 -> vector;
    rational *r1 = v1 -> vector;
    int size = v1 -> size;
    for(i=0; i<size; i++){
        sum = rplusr(sum, rproductr(r0[i], r1[i]));
    }
    return sum;
}

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
