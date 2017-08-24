# A small polynomial implmentation
### Example
```c
#include "polynomial.h"

int main(int argc, char **argv) {

    polynom_t *P; // No need to initialize if using InitPolynomial
    P = InitPolynomial();

    // Now allocate and initialize some some exponents
    int32_t exp[8]; exp[0] = 3;

    // Append some terms to the polynomial
    AppendTermPolynomial(3, 1, exp, P);
    exp[0] = 2; exp[1] = 6;
    AppendTermPolynomial(-2, 3, exp, P);
    exp[0] = -4; exp[1] = 2;
    AppendTermPolynomial(4, 5, exp, P);
    AppendTermPolynomial(1, 0, exp, P);

    // Now initialize some variables
    polynom_var_t var; 
    var.v[0] = 3.0F; var.v[1] = -2.0F; var.v[2] = 2.5F;

    // This will print +(3a^3)+-2a^2b^6)+(4a^-4c^2)+(1)
    PrintPolynomial(P);

    // This will print the result of 3(3^3)-2(3^2)(-2^6)+4(3^-4)(2.5^2)+(1)
    // which is -1069.691406
    printf("%f\n", FunctionOfPolynomial(P, &var));
    DestroyPolynomial(P);

    return 0;
}
```
