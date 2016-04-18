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

/*

Va-t-on faire les fonctions avec des int ? (manipulation de bits) ou avec d'autres structures ?

*/

/**
 * Displays a polynomial
 */
void printPolynome (int p, int degre);

/**
 * Polynomial addition
 */
int addition (int p, int q);

/**
 * Polynomial multiplication
 */
int multiplication (int p, int q);

/**
 * Polynomial Euclidian division
 */
int euclidianDivision (int p, int q);

/**
 * Polynomial division by increasing powers
 */
int divideByIncreasingPowers (int p, int q);

/**
 * Polynomial truncature at degree d
 */
int truncate (int p, int d);

/**
 * Polynomial modular exponentiation
 */
int modularExponentiation (int p, int base, int exp, int m);

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