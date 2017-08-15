#include <stdio.h>
#include <stdlib.h>
#ifdef _WINDOWS
#include <malloc.h>
#include <inttypes.h>
#endif /* _WINDOWS */
#include <stdint.h>

#include "polynomial.h"

struct polynom_s {
    uint32_t Degree;
    int32_t *Exponents, *Coefficent; //TODO: Handle negative exp
    uint8_t *Variables, *Terms; 
};

/* struct polynom_var_s { int32_t v[8]; }; */

polynom_t *InitPolynomial(){

    polynom_t *rv;

    rv = NULL;
    if ((rv = (polynom_t *) malloc(sizeof(polynom_t))) == NULL){
        fprintf(stderr, "Err in InitPolynomial: malloc (1)\n");
        exit(1);
    }
    rv->Degree = (uint32_t) 0;
    rv->Exponents = NULL;
    rv->Coefficent = NULL;
    rv->Variables = NULL;
    rv->Terms = NULL;

    return rv;
}
void DestroyPolynomial(polynom_t *P){

    if (P->Degree > (uint32_t) 0){
        free(P->Exponents);
        free(P->Coefficent);
        free(P->Variables);
        free(P->Terms);
    }
    free(P);
}
int AppendTermPolynomial(
    int32_t *Exponents, 
    int32_t Coefficent, 
    uint8_t Variables,
    polynom_t *P){ 

    int i, j, s;
    uint8_t x, b;

    j = 0; s = 0;
    x = Variables;
    b = (uint8_t) 1;
    P->Degree++;
    for(i = 0;i < 8;++i){
        if (x & b == 1)
            s += 1;
        x >>= 1;
    }
    /* Don't expand the array if there are no exponents to add*/
    if (s != 0 && 
        (P->Exponents = (int32_t *) realloc(P->Exponents, sizeof(int32_t *) * (P->Degree + s))) == NULL){
        fprintf(stderr, "Err in PolynomialAppendTerm: realloc (1)\n");
        return 1;
    }
    if ((P->Coefficent = (int32_t *) realloc(P->Coefficent, sizeof(int32_t) * P->Degree)) == NULL){
        fprintf(stderr, "Err in PolynomialAppendTerm: realloc (2)\n");
        return 1;
    }
    if ((P->Variables = (uint8_t *) realloc(P->Variables, sizeof(uint8_t) * P->Degree)) == NULL){
        fprintf(stderr, "Err in PolynomialAppendTerm: realloc (3)\n");
        return 1;
    }
    if ((P->Terms = (uint8_t *) realloc(P->Terms, sizeof(uint8_t) * P->Degree)) == NULL){
        fprintf(stderr, "Err in PolynomialAppendTerm: realloc (4)\n");
        return 1;
    }
    P->Terms[P->Degree - 1] = (uint8_t) s; /* Set Term Step */
    if (s != 0){
        for(i = 0;i < ((int) P->Degree - 1);++i) /* Read Depth */
            j += P->Terms[i];
        for(i = 0;i < s;++i)
            P->Exponents[j + i] = Exponents[i];
    }
    P->Coefficent[P->Degree - 1] = Coefficent;
    P->Variables[P->Degree - 1] = Variables;

    return 0;
}
uint8_t GetVariablesPolynomial(polynom_t *P){

    int i, d;
    uint8_t rv;

    d = (int) P->Degree;
    rv = (uint8_t) 0;
    for(i = 0;i < d;++i) 
        rv = rv | P->Variables[i];

    return rv;
}

int32_t _PowPolynomial(
    int32_t x, 
    int32_t n){

    int i, d;
    int32_t rv;
    
    d = (int) n;
    rv = x;
    if (d > 0) {
        for (i = 1;i < d;++i)
            rv *= x;
    }
    else if (d < 0) {
        for (i = 1;i < d;++i)
            rv /= x;
    }
    else {
        return (int32_t) 1;
    }

    return rv;
}

int32_t FunctionOfPolynomial(
    polynom_t *P, 
    polynom_var_t *x){

    int i, j, k, d, v, n;
    int32_t rv, temp;
    uint8_t a, b;

    d = (int) P->Degree;
    n = 0;
    rv = (int32_t) 0;
    for (i = 0;i < d; ++i){
        a = P->Variables[i];
        v = 0;
        b = (uint8_t) 1;
        temp = (int32_t) 1;
        for (j = 0;j < 8; ++j){
            if (a & b == 1){
                temp *= _PowPolynomial(x->v[v], P->Exponents[n]);
                v += 1;
                n += 1;
            }
            a >>= 1;
        }
        temp *= P->Coefficent[i]; /* Mul coef */
        rv += temp;
    }

    return rv;
}

void PrintPolynomial(polynom_t *P){

    int i, j, d, e, r;
    uint8_t a, b;

    d = (int) P->Degree;
    r = 0;
    for (i = 0;i < d;++i){
        if ((int)P->Coefficent[i] >= 0){
            printf("+");
        }
        printf("%d", (int)P->Coefficent[i]);
        e = (int) P->Terms[i];
        a = P->Variables[i];
        b = (uint8_t) 1;
        for (j = 0;j < e;++j){
            if (a & b == 1){
                printf("%c^%d", j + 65, P->Exponents[r]);
                
            }
            a >>= 1;
            r += 1;
        }
    }
    printf("\n");

    return;
}
