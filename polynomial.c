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
    uint8_t a, b;

    j = 0; s = 0;
    a = Variables;
    b = (uint8_t) 1;
    P->Degree++;
    for(i = 0;i < 8;++i){
        if ((a & b) == 1)
            s += 1;
        a >>= 1;
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

float _PowPolynomial(
    float X, 
    int32_t N){

    int i, d;
    float rv;
    
    d = (int) N;
    rv = X;
    if (d > 0) {
        for (i = 1;i < d;++i)
            rv *= X;
    }
    else if (d < 0) {
        for (i = -1;i > d;--i)
            rv *= X;
        rv = 1.0F / rv;
    }
    else {
        return 1.0F;
    }

    return rv;
}

float FunctionOfPolynomial(
    polynom_t *P, 
    polynom_var_t *X){

    int i, j, d, var, exp;
    float rv, temp;
    uint8_t a, b;

    d = (int) P->Degree;
    exp = 0;
    rv = 0.0F;
    for (i = 0;i < d; ++i) { /* term loop */
        a = P->Variables[i];
        var = 0;
        b = (uint8_t) 1;
        temp = 1.0F;
        for (j = 0;j < 8; ++j){ /* variable loop */
            if ((a & b) == 1){ 
                temp *= _PowPolynomial(
                    X->v[var], 
                    P->Exponents[exp]); 
                exp += 1;
            }
            var += 1;
            a >>= 1;
        }
        temp *= P->Coefficent[i]; /* multiply by coefficent */
        rv += temp; //TODO: Implement a decimal type to ensure assoc.
    }

    return rv;
}

void PrintPolynomial(polynom_t *P){

    int i, j, d, exp;
    uint8_t a, b;

    d = (int) P->Degree;
    exp = 0;
    for (i = 0;i < d;++i){
        printf("+(%d", (int)P->Coefficent[i]);
        a = P->Variables[i];
        b = (uint8_t) 1;
        for (j = 0;j < 8;++j){
            if ((a & b) == 1){
                printf("%c^%d", j + 97, P->Exponents[exp]);
                exp += 1;
            }
            a >>= 1;
        }
        printf(")");
    }
    printf("\n");

    return;
}