#include "library.h"

//Fonction d'affichage d'un polynôme
void printPolynome (int p, int degre) {
	int i;
	int nbBits = 8 * sizeof p;
	int tmp;

	printf("\t");
	for (i = degre-1; i >= 0; i--) {
		//On fait un décalage à gauche
		tmp = 1 << i;
		tmp = (tmp & p) >> i;
		//Affichage
		if ((tmp & 1) != 0 && (i != 0))
			printf("x^%d + ", i);
		if (i == 0 && ((tmp & 1) != 0))
			printf("1");
	}
	printf("\n");
}

void afficher_bits_octet (int octet) {

	int i, tmp;

	int nbBits = 8 * sizeof octet;

	//Initialisation
	for (i = nbBits-1; i >= 0; i--) {
		//On fait un décalage à gauche
		tmp = 1 << i;
		tmp = (tmp & octet) >> i;
		
		//Affichage
		if ((tmp & 1) == 0)
			printf("%d ", tmp);
		else 
			printf("1 ");
	}

	printf("\n");
}

//Addition de deux polynomes dans F2
//P et Q sont des int (sur 32 bits), ils representent les coefficients du i-ème élément du polynôme 
//L'addition dans F2 revient à faire un XOR entre chaque i-ème coef de P et Q
int add (int p, int q) {
	return p ^ q;
}

//Multiplication de deux polynomes dans F2 par l'algo du Russian Peasant
//Il nous faut un polynôme irreductible => ici : x^8 + x^4 + x^3 + x + 1
int mult (int p, int q) {
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

//Troncature d'un polynome P à un dégré d
//On additionne tous les puissances de 2 inférieures au dégré d,
//Puis on fait une opération ET de l'entier obtenu avec le polynôme initial
//Ce qui aura pour effet de prendre uniquement les bits de poids inférieur au dégré
int troncate (int p, int d) {
	int degre;
	int i;
	for (i = d; i > 0; i--) {
		degre += pow (2, i);
	}
	return (p & ((int) degre));
}

//Exponentiation modulaire d'un polynôme
int expMod (int p, int base, int exp, int m) {
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