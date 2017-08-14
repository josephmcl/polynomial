#ifndef _POLYNOM_H
#define _POLYNOM_H

typedef struct polynom_s polynom_t;
/* A struct representing a polynomial. Supports up to 8 variables 
 * (indeterminates).
 */
typedef struct polynom_var_s { int32_t v[8]; } polynom_var_t; 
/* A struct representing arguments to a function of a polynom_t. 
 */

polynom_t *InitPolynomial();
/* Returns a pointer to an initalized polynom_t. Allocates a polynom_t, but none
 * of its members. Calls exit() on malloc() failure.
 */

void DestoryPolynomial(
	polynom_t *P);
/* Cleans up a polynom_t. Free all members and itself.
 */
int AppendTermPolynomial(
    int32_t *Exponents, 
    int32_t Coefficent, 
    uint8_t Variables,
    polynom_t *P);
/* Returns 0 on success, 1 on failure. Exponents should not be not be larger 
 * than 8. Exponents be the same size as the number of set bits in Variables. 
 * Variables represents the spesific variable to be used in the term. The nth 
 * set bit aligns with the n-1 index in Exponents.
 */
int32_t FunctionOfPolynomial(
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