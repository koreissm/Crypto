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
	int p = 12000, q = 63444;
	// int p = 501, q = 130503;

	// // Addition
	// printPolynom (p, 32);
	// printf("+\n");
	// printPolynom (q, 32);
	// printf("___________________________________________________________________________________________________________________________\n");
	// printPolynom (addition (p, q), 32);

	// // Multiplication
	clock_t begin, end;
	double time_spent;
	/* here, do your time-consuming job */
	
	printPolynom (p, 32);
	printf("x\n");
	printPolynom (q, 32);
	printf("___________________________________________________________________________________________________________________________\n");
	begin = clock();
	printPolynom (multiplication (p, q), 32);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time spent by normal multiplication : %f\n", time_spent);

	begin = clock();
	printPolynom (multiplicationWithRussianPeasant (p, q), 32);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time spent by russiant peasant multiplication : %f\n", time_spent);

	// // Euclidian Division
	//int qu, r;
	//euclidianDivision (q, p, &qu, &r);
	//printf("Q : %d, R : %d\n", qu, r);
	//printPolynom (r, 32);
	//printPolynom (qu, 32);

	// // Division by increasing powers
	//int qu, r;
	//divideByIncreasingPowers(q, p, &qu, &r);
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

	// Modular Exponentiation
	// effectiveModularExponentiation (4,13, 450);
	// modularExponentiationBis (4, 13, 450);
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

void testDivision() {
	// X^4 + X^3 + 1
	int a = 25;
	printPolynom(a, 32);

	// X^3
	int b = 8;
	printPolynom(b, 32);

	// Should be X + 1
	int q = 0;
	// Should be 1
	int r = 0;
	euclidianDivision(a, b, &q, &r);
	printPolynom(q, 32);
	printPolynom(r, 32);
}

void testDivision2() {
	// X^4 + X + 1
	int a = 19;
	printPolynom(a, 32);

	// X^3
	int b = 8;
	printPolynom(b, 32);

	// Should be X
	int q = 0;
	// Should be X + 1
	int r = 0;
	euclidianDivision(a, b, &q, &r);
	printPolynom(q, 32);
	printPolynom(r, 32);
}

void testErastothenePolynomial() {

	polynomial p;
	p.degree = 2;
	p.coeffs = 100;
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

	int i;

	polynomial p;
	p.coeffs = 40;
	p.degree = getDegree(p.coeffs);

	printPolynom(p.coeffs, 32);
	
	isPolynomialPrimitive(&p);

	puts("find divisors of 12");
	int * tab;
	int n;
	getAllDivisors(12, &tab, &n);
	printf("size is %d\n", n);
	for (i = 0; i < n; i++) {
		printf("i %d divisor %d\n", i, tab[i]);
	}

	puts("is this polynomial a primitive ?");
	p.degree = 20;
	p.coeffs = 19;
	printPolynom(p.coeffs, p.degree);
	printf("%c\n", isPolynomialPrimitive(&p) == 1 ? 'y' : 'n');

}

void printAllPrimitivePolynomials(int max) {

	int i;
	polynomial p;

	printf("List of all primitive polynomials until");
	printPolynom(max, 32);
	for (i = 1; i < max; i++) {
		p.coeffs = i;
		if (isPolynomialPrimitive(&p) == 1) {
			printPolynom(p.coeffs, 32);
		}
	}

}

void perfCrible() {

	int i;
	double begin, end, time_spent1, time_spent2, time_spent3;
	polynomial p;

	FILE *fp;
	fp = fopen("crible.txt", "w+");

	for(p.coeffs = 2; p.coeffs < 300; p.coeffs++) {

		begin = clock();
		displayExhaustivePolynomialCrible(&p);
		end = clock();
		time_spent1 = (double)(end - begin) / CLOCKS_PER_SEC;

		begin = clock();
		displayExhaustivePolynomialCribleOptimized(&p);
		end = clock();
		time_spent2 = (double)(end - begin) / CLOCKS_PER_SEC;

		begin = clock();
		displayEratosthenePolynomialCrible(&p);
		end = clock();
		time_spent3 = (double)(end - begin) / CLOCKS_PER_SEC;

		fprintf(fp, "%d\t%f\t%f\t%f\n", p.coeffs, time_spent1, time_spent2, time_spent3);

	}

	close(fp);

}

void testPdfEncryption() {
	pdfEncrypt("pdf/cours-1.pdf", "pdf/key.txt");
}


