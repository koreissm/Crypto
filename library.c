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

//Multiplication de deux polynomes dans F2 par l'algo du Russian Peasant
//Il nous faut un polynôme irreductible => ici : x^8 + x^4 + x^3 + x + 1
int multiplicationWithRussianPeasant (int p, int q) {
	int result = 0;

	while (q) {
		if (q & 1) //Si q impair, on ajoute le terme correspondant à notre somme
			result ^= p;

		if (p & 0x80000000) // Si on n'a pas dépassé la taille max d'un int (2^32 - 1 je crois)
			p = (p << 1) ^ 0x11B; //On fait un XOR de p décalé à gauche de 1 avec le polynôme irréductible
		else //Sinon alors il y a overflow, donc on fait décalage à gauche de p pour avoir plus de place
			p <<= 1;

		q >>= 1; //On fait bouger q de 1 (on le divise)
	}

	return result;
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

//Return the last coef (the smallest) of the p polynom
int getLastCoef (int p){
	int i;
	int tmp = 0;
	for (i = 31; i-- >= 0;) {
	 	if ((((1 << i) & p) >> i) == 1)
	  		tmp = 1 << i;
	}

	return tmp;

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

//Calculating the division by increasing powers
//Returning the quotient and the remainder
int divideByIncreasingPowers (int a, int b, int* q, int* r){
	int qtmp = 0;
	int rtmp = a;
	int cpt = 1;

    while(cpt<5){
		int t = getLastCoef(rtmp) / getLastCoef(b); //We divide the last coef of R by the last coef of B polynom
        
		qtmp ^= t;
		rtmp ^= t *  b; // A = Q . lc(Q) + R => R = A + Q.lc(Q)  (lc stands for Last coef)
		cpt++;
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

//The most effective method for modular exponentiation
int effectiveModularExponentiation (int b, int e, int m) {
	int result = 1;

	//Executed as many times as the binary size of e
	while (e > 0) {
		if ((e & 1) > 0)
			result = (result * b) % m;
		//Truncating right
		e >>= 1;
		b = (b * b) % m;
	}

	return result;
}

//An other method for modular exponentiation less effective on results with great number
int modularExponentiationBis (int b, int e, int m){
    int result = 1;

    //We create an other exponent to calculate the number of iteration
    int e2 = 0;

    //Executed while the number of iterations is different of the value of the exponent
    while(e2 < e){
        e2++;
        result = (b * result) % m;
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

//////////////////////////////////////////////////////////////// Eratosthene Sieve
//////////////////////////////////////////////////////////////// (for integers)

int * createEratostheneCrible(int nGiven) {
	int n = nGiven + 1;
	int * crible = malloc(n * sizeof(int));
	int i, j;

	// Init all values in crible to true (1)
	for (i = 0; i < n; i++) {
		crible[i] = 1;
	}

	// Start off at 2
	// Notice that we don't go any further than sqrt(n)
	for (i = 2; i * i < n; i++) {
		// Mark all multiples of i as not primes
		for (j = i * 2; j < n; j += i) {
			crible[j] = 0;
		}
	}

	return crible;
}

int displayEratostheneCrible(int nGiven) {
	int i;
	int n = nGiven + 1;
	int * crible = createEratostheneCrible(nGiven);

	for (i = 2; i < n; i++) {
		if (crible[i] == 1) {
			printf("%d ", i);
		}
	}
	printf("\n");

	free(crible);

}

int isPrimeByEratosthene(int nGiven) {
	int * crible = createEratostheneCrible(nGiven);
	int result = crible[nGiven];
	free(crible);
	return result;
}

//////////////////////////////////////////////////////////////// Eratosthene Sieve
//////////////////////////////////////////////////////////////// (for polynomials)

void getNextPolynomial(polynomial * p) {

	// getting next number
	p->coeffs++;

	// we need to increment the degree if
	// degree-th coeff is now not null
	int selection = p->coeffs >> (p->degree + 1);
	if (selection & 1 == 1)
		p->degree++;

}

int * createEratosthenePolynomialCrible(polynomial * p) {
	int n = p->coeffs + 1;
	int * crible = malloc(n * n * sizeof(int));
	int i, j;

	// Init all values in crible to true (1)
	for (i = 0; i < n * n; i++) {
		crible[i] = 1;
	}
	crible[0] = crible[1] = crible[2] = 0;

	// Every preceding polynomial is checked
	for (i = 2; i < n; i++) {
		// Mark all polynomials that are a multiplication
		// of i and a polynomial under i as not primes
		for (j = 2; j <= i; j++) {
			crible[multiplication(i, j)] = 0;
		}
	}

	return crible;
}

int displayEratosthenePolynomialCrible(polynomial * p) {
	int i;
	int * crible = createEratosthenePolynomialCrible(p);

	for (i = 0; i < p->coeffs; i++) {
		if (crible[i] == 1) {
			printf("%d\t", i);
			printPolynom(i, 32);
		}
	}
	printf("\n");

	free(crible);

}

int isPolynomialPrimeByEratosthene(polynomial * p) {
	int * crible = createEratosthenePolynomialCrible(p);
	int result = crible[p->coeffs];
	free(crible);
	return result;
}

//////////////////////////////////////////////////////////////// Primality check
//////////////////////////////////////////////////////////////// (for polynomials)

int cmp(const void *p, const void *q) {
     return ( *(int *)p - *(int *)q);
}

void getAllDivisors(int n, int ** results, int * count) {
	int i;
	*results = (int *) malloc(0);
	*count = 0;

	// iterate over all numbers below sqrt(n)
	for (i = 2; i <= sqrt(n); i++) {
		// if i is divisor
		if(n % i == 0) {
			*results = (int *) realloc(*results, sizeof(int));
			(*results)[*count] = i;
			(*count)++;
			// if dividende different, add it as well
			if (i != (n / i) && (n / i) != n) {
				*results = (int *) realloc(*results, sizeof(int));
				(*results)[*count] = n / i;
				(*count)++;
			}
		} 
	}

	// sort results
	qsort(*results, *count, sizeof(int), cmp);
}

int isPolynomialPrimitive(polynomial * p) {
	int i, power, result = 1, degree, maxOrder;
	polynomial x;
	int q, r;

	// first check if is prime
	if (isPolynomialPrimeByEratosthene(p) == 0) {
		return 0;
	}
	// printf("\t");
	// printPolynom(p->coeffs, 32);

	// get degree of p
	degree = getDegree(p->coeffs);
	maxOrder = pow(2, degree) - 1;

	// get all divisors of max order
	int * divisors;
	int nDivisors;
	getAllDivisors(maxOrder, &divisors, &nDivisors);

	// printf("\t\t%d divisors found for maxorder %d : ", nDivisors, maxOrder);
	// for (i = 0; i < nDivisors; i++) {
	// 	printf("%d, ", divisors[i]);
	// }
	// printf("\n");

	// for each divisor, test if congruent
	for (i = 0; i < nDivisors; i++) {

		if (divisors[i] > degree) {
			continue;
		}

		// create polynomial X^d where d is the divisor
		x.coeffs = 0;
		x.coeffs = pow(2, divisors[i]);
		// printf("\t\t\tdivisor %d creates polynomial ", divisors[i]);
		// printPolynom(x.coeffs, 32);

		// if rest of eucli. division is 1, then X^d is congruent to 1
		// if not, we change the result to false, because P is not primitive
		euclidianDivision(p->coeffs, x.coeffs, &q, &r);
		// printf("rest ");
		// printPolynom(r, 32);
		if (r != 1){
			result = 0;
		}
	}

	return result;
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

//////////////////////////////////////////////////////////////// PDF encoding/decoding
//////////////////////////////////////////////////////////////// using lfsr










