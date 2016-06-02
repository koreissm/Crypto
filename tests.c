/** *************************************************************************
 *
 * @file tests.c
 * @brief implementation of functions defined in @link tests.h @endlink
 *
 ****************************************************************************/

 #include "tests.h"

void testPrimeNumbers() {
	int n = pow(10, 7);
	int i;

	int* primes = (int *) malloc (sizeof(int) * n);

	primes = getPrimeNumbers(n);

	for (i = 0; i < n; ++i) {
		if (primes[i] != 0)
			printf("%d ", primes[i]);
		else {
			printf("\n%d prime numbers between 1 and %d\n", i + 1, n);
			break;
		}
	}
}

void testPolynomes() {
	int p = 5, q = 63;
	// int p = 501, q = 130503;

	// // Addition
	// printPolynom (p, 32);
	// printf("+\n");
	// printPolynom (q, 32);
	// printf("___________________________________________________________________________________________________________________________\n");
	// printPolynom (addition (p, q), 32);

	// // Multiplication
	printPolynom (p, 32);
	printf("x\n");
	printPolynom (q, 32);
	printf("___________________________________________________________________________________________________________________________\n");
	printPolynom (multiplication (p, q), 32);
	printPolynom (multiplicationWithRussianPeasant (p, q), 32);

	// // Euclidian Division
	//int qu, r;
	//euclidianDivision (q, p, &qu, &r);
	//printf("Q : %d, R : %d\n", qu, r);
	//printPolynom (r, 32);
	//printPolynom (qu, 32);

	// // Troncature
	// printPolynom (p, 32);
	// int d = 5;
	// p = truncate (p, d);
	// printf("Troncature du polynôme au dégré %d: ", d);
	// printPolynom (p, 32);
	// afficher_bits_octet (p);

	//Exponentiation modulaire
	//printPolynom(p, 32);
	//p = modularExponentiation(p, 4, 13, 497);
	//printPolynom(p, 32);
}

void testErastothene() {

	puts("Is 20 prime ?");
	printf("%c\n", isPrimeByEratosthene(20) == 1 ? 'y' : 'n');

	puts("Is 13 prime ?");
	printf("%c\n", isPrimeByEratosthene(13) == 1 ? 'y' : 'n');

	puts("Is 67 prime ?");
	printf("%c\n", isPrimeByEratosthene(67) == 1 ? 'y' : 'n');

	puts("Is 69 prime ?");
	printf("%c\n", isPrimeByEratosthene(69) == 1 ? 'y' : 'n');

	puts("Is 1300199 prime ?");
	printf("%c\n", isPrimeByEratosthene(1300199) == 1 ? 'y' : 'n');

}

void testErastothenePolynomial() {

	polynomial p;
	p.degree = 2;
	p.coeffs = 40;
	getNextPolynomial(&p);
	getNextPolynomial(&p);
	getNextPolynomial(&p);
	printf("%d\n", p.degree);

	printPolynom(p.coeffs, p.degree);

	puts("displaying polynomial crible");
	displayEratosthenePolynomialCrible(&p);

	puts("Is this polynomial a prime ?");
	p.degree = 20;
	p.coeffs = 13;
	printPolynom(p.coeffs, p.degree);
	printf("%c\n", isPolynomialPrimeByEratosthene(&p) == 1 ? 'y' : 'n');

}

void testPrimitive() {

	polynomial p;
	p.coeffs = 40;
	p.degree = getDegree(p.coeffs);

	printPolynom(p.coeffs, 32);
	
	isPolynomialPrimitive(&p);

}



