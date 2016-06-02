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
	int p = 501, q = 130503;

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
	isPrimeByEratosthene(20);

	puts("Is 13 prime ?");
	isPrimeByEratosthene(13);

	puts("Is 67 prime ?");
	isPrimeByEratosthene(67);

	puts("Is 69 prime ?");
	isPrimeByEratosthene(69);


}



