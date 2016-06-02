/** *************************************************************************
 *
 * @file library.h
 * @brief Definition of requested operations
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

 typedef struct {
 	int coeffs;
 	int degree;
 } polynomial;


/**
 * Displays a polynomial
 */
void printPolynom (int p, int degre);

/**
 * Polynomial addition
 */
int addition (int p, int q);

/**
 * Polynomial multiplication
 */
int multiplication (int p, int q);
int multiplicationWithRussianPeasant (int p, int q);

/**
 * Polynomial Euclidian division
 */
void euclidianDivision (int a, int b, int* q, int* r);

/**
 * Polynomial division by increasing powers
 */
int divideByIncreasingPowers (int a, int b, int* q, int* r);

/**
 * Polynomial truncature at degree d
 */
int truncate (int p, int d);

/**
 * Polynomial modular exponentiation
 */
int effectiveModularExponentiation (int b, int e, int m);
int modularExponentiationBis (int b, int e, int m);

/**
 * Tests if given number is prime
 */
int isPrime (int number);

/**
 * Generates every prime number between 1 and n
 */
int* getPrimeNumbers (int n);

/**
 * Tests if given number is primitive
 */
int isPrimitive (int number);

/**
 * Berlekamp-Massey algorithm
 */
void berlekampMassey ();

//Return the degree of p polynom
int getDegree (int p);

//Return the leading coef of the p polynom
int getLeadingCoef (int p);

//Return the last coef (the smallest) of the p polynom
int getLastCoef (int p);