#ifndef _POLYNOM_H
#define _POLYNOM_H

#include <stdio.h>
#include <stdlib.h>
#ifdef _WINDOWS
#include <malloc.h>
#include <inttypes.h>
#endif /* _WINDOWS */
#include <stdint.h>

typedef struct polynom_s polynom_t;
/* A struct representing a polynomial. Supports up to 8 variables 
 * (indeterminates).
 */
typedef struct polynom_var_s { float v[8]; } polynom_var_t; 
/* A struct representing arguments to a function of a polynom_t. 
 */

polynom_t *InitPolynomial();
/* Returns a pointer to an initalized polynom_t. Allocates a polynom_t, but none
 * of its members. Calls exit() on malloc() failure.
 */

void DestroyPolynomial(
    polynom_t *P);
/* Cleans up a polynom_t. Free all members and itself.
 */
int AppendTermPolynomial( 
    int32_t Coefficent, 
    uint8_t Variables,
    int32_t *Exponents,
    polynom_t *P);
/* Returns 0 on success, 1 on failure. Variables represents the spesific 
 * variable to be used in the term. The 0th set bit aligns with the 0 index in 
 * Exponents.
 */
float FunctionOfPolynomial(
    polynom_t *P, 
    polynom_var_t *x);
/* Returns the result of P(x) such that P is the function representing the 
 * polynomial P and x is an int32_t array containing arbitrary values for all 
 * indeterminates of P.
 */

/*** Helpers ***/
void PrintPolynomial(
    polynom_t *P);
/* Prints a string representation of P.
 */
#endif /* _POLYNOM_H */