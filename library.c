/** *************************************************************************
 *
 * @file library.c
 * @brief implementation of functions defined in @link library.h @endlink
 *
 ****************************************************************************/

#include "library.h"

// Printing a polynom
void printPolynom (int p, int degre) {
	int i;

	printf("\t");
	for (i = degre-1; i-- >= 0;) {
		// Selecting the i -th element of P
		int tmp = 1 << i;
		tmp = (tmp & p) >> i;

		//Printing
		if (tmp != 0 && i != 0)
			printf("x^%d + ", i);
		if (i == 0 && tmp != 0)
			printf("1");
	}
	printf("\n");
}

//Polynomial addition in F2
//P and Q are int (on 32 bits).
//As long as we are in the Z/2Z ring, the addition will be considerated like a simple XOR between P and Q
int addition (int p, int q) {
	return p ^ q;
}

//Polynomial multiplication
int multiplication (int p, int q) {

	if (q == 0) //We terminate if q null
		return 0;
	else {
		if (q == 1) //If we have to multiply by 1, the result doesn't change
			return p;
		else {
			int tmp = (q&1) * p; //Multiplying the current item of b by p's items
			q >>= 1; //Passing to the next element of B

			int result = multiplication (p, q); //Recursive call with the new value of Q
			result <<= 1; //Shifting the result to the left (like in real multiplication)
			return tmp ^ result; //Returning the result
		}
	}
}

//Return the degree of p polynom
int getDegree (int p) {
	int i;
	for (i = 31; i-- >= 0;) {
		if ((((1 << i) & p) >> i) == 1)
			return i;
	}
}

//Return the leading coef of the p polynom
int getLeadingCoef (int p) {
	int i;
	for (i = 31; i-- >= 0;) {
		if ((((1 << i) & p) >> i) == 1)
			return 1 << i;
	}
}

//Calculating the euclidian Division
//Returning the quotient and the remainder
void euclidianDivision (int a, int b, int* q, int* r) {
	//if (b == 0) return 0;
	int qtmp = 0;
	int rtmp = a;

	//Stop condition => d°R < d°B or R == null
	while (rtmp != 0 && getDegree(rtmp) >= getDegree(b)) { 
		int t = getLeadingCoef(rtmp) / getLeadingCoef(b); //We divide the leading coef of R by the leading coef of B in order to get Q's next coef

		qtmp ^= t; //
		rtmp ^= t * b; // A = Q . lc(Q) + R => R = A + Q.lc(Q)  (lc stands for Leading coef)
	}

	*q = qtmp;
	*r = rtmp;
}

//Troncature d'un polynome P à un dégré d
//On additionne tous les puissances de 2 inférieures au dégré d,
//Puis on fait une opération ET de l'entier obtenu avec le polynôme initial
//Ce qui aura pour effet de prendre uniquement les bits de poids inférieur au dégré
int truncate (int p, int d) {
	int degre;
	int i;
	for (i = d; i > 0; i--) {
		degre += pow (2, i);
	}
	return (p & ((int) degre));
}

//Exponentiation modulaire d'un polynôme
int modularExponentiation (int p, int base, int exp, int m) {
	int result = 1;

	while (exp > 0) {
		if ((exp & 1) > 0)
			result = (result * base) % m;
		exp >>= 1;
		base = (base * base) % m;
	}

	return result;
}

//Teste si number est premier
int isPrime (int number) {
	int i = 3;

	if (number % 2 == 0) //Si nombre pair on sort
		return 0;

	while (i <= sqrt(number)) { //On cherche un diviseur de number entre 3 et sqrt(numer), si on en trouve pas, il n'est pas premier
		if (number % i == 0)
			return 0;

		i += 2;
	}

	return 1;
}

int isPrimeByEratosthene(int n) {
	int * crible = malloc((n + 1) * sizeof(int));
}

//Génère tous les nombres premiers entre 1 et n
//On incrémente par pas de 2 à chaque fois à partir de 3
//Ce qui élimine déjà tous les nombres pairs
int* getPrimeNumbers (int n) {
	int i = 3, j = 0;
	int* primes = malloc (sizeof(int) * n);

	while (i < n) {
		if (isPrime (i)) {
			primes[j] = i;
			++j;
		}
		i += 2;
	}

	return primes;
}

//Teste si number est un primitif
int isPrimitive (int number) {

	return 0;
}