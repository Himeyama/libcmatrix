#include <stdio.h>
#include <stdlib.h>
#include "rational.c"

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

/* 成分がすべて1のベクトル */
vector one_vector_new(int size){
    vector vector;
    vector.size = size;
    vector.vector = _vector_new(size, 1);
    return vector;
}

/* 零ベクトル */
vector zero_vector_new(int size){
    vector vector;
    vector.size = size;
    vector.vector = _vector_new(size, 0);
    return vector;
}

/* ベクトル生成 */
vector vector_new(rational value[], int size){
    int i;
    vector v;
    v.size = size;
    v.vector = value;
    return v;
}

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
