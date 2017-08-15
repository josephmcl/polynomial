#include <stdio.h>
#include <stdlib.h>
#ifdef _WINDOWS
#include <malloc.h>
#include <inttypes.h>
#endif /* _WINDOWS */
#include <stdint.h>

#include "polynomial.h"

int
main(int argc, char **argv){

    polynom_t *p;
    int32_t exp[2];
    polynom_var_t var;

    p = InitPolynomial();
    exp[0] = (int32_t) 2;
    exp[1] = (int32_t) 2;

    AppendTermPolynomial(exp, 10, 3, p);
    AppendTermPolynomial(exp, 2, 2, p);
    AppendTermPolynomial(exp, -4, 1, p);
    PrintPolynomial(p);

    DestroyPolynomial(p);

    return 0;
}