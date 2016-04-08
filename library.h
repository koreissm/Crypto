#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*

Va-t-on faire les fonctions avec des int ? (manipulation de bits) ou avec d'autres structures ?

*/

//Fonction d'affichage d'un polynôme
void printPolynome (int p, int degre);

//Addition de deux polynomes dans F2
int add (int p, int q);

//Multiplication de deux polynomes dans F2
int mult (int p, int q);

//Division Euclidienne de deux polynomes dans F2
int divideEucl (int p, int q);

//Division selon les puissances croissantes de deux polynomes dans F2
int dividePuisCroi (int p, int q);

//Troncature d'un polynome P à un dégré d
int troncate (int p, int d);

//Exponentiation modulaire d'un polynôme
int expMod (int p, int base, int exp, int m);

//Teste si number est premier
int isPrime (int number);

//Génère tous les nombres premiers entre 1 et n
int* getPrimeNumbers (int n);

//Teste si number est un primitif
int isPrimitive (int number);

//Implémentation de l'algo de Berlekamp-Massey
void berlekampMassey ();