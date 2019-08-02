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

/* ベクトルのコピー */
vector copy_vector(struct vector v){
    int i;
    vector tmp_v;
    tmp_v = zero_vector_new(v.size);
    for(i=0; i<v.size; i++){
        tmp_v.vector[i] = v.vector[i];
    }
    return tmp_v;
}

/* ベクトルのスカラー倍(破壊) */
void _scalar_product_vector(vector v, int scalar){
    int size = v.size;
    _vector *p = v.vector;
    int i;
    for(i=0;i<size;i++)
        p[i].numerator = scalar * (p[i].numerator);
}

/* 逆ベクトル(破壊) */
void _inverse_vector(vector v){
    _scalar_product_vector(v, -1);
}

/* ベクトルのスカラー倍(非破壊) */
vector scalar_product_vector(struct vector v, int scalar){
    vector vec;
    vec = copy_vector(v);
    _scalar_product_vector(vec, scalar);
    return vec;
}

/* 逆ベクトル(非破壊) */
vector inverse_vector(vector v){
    return scalar_product_vector(v, -1);
}

/* 内積 */
rational inner_product_vector(struct vector *v0, struct vector *v1){
    int i;
    rational sum = {0, 1};
    for(i=0; i<v1 -> size; i++)
        sum = rplusr(sum, rproductr((v0 -> vector)[i], (v1 -> vector)[i]));
    return sum;
}
