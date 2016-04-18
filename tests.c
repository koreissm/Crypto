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

	//Addition
	// printPolynome (p, 32);
	// printf("+\n");
	// printPolynome (q, 32);
	// printf("___________________________________________________________________________________________________________________________\n");
	// printPolynome (add (p, q), 32);

	//Multiplication
	// printPolynome (p, 32);
	// printf("x\n");
	// printPolynome (q, 32);
	// printf("___________________________________________________________________________________________________________________________\n");
	// printPolynome (mult (p, q), 32);

	//Troncature
	// printPolynome (p, 32);
	// int d = 5;
	// p = troncate (p, d);
	// printf("Troncature du polynôme au dégré %d: ", d);
	// printPolynome (p, 32);
	// afficher_bits_octet (p);

	//Exponentiation modulaire
	printPolynome(p, 32);
	p = modularExponentiation(p, 4, 13, 497);
	printPolynome(p, 32);
}