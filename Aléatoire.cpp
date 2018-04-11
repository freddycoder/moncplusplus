#include <time.h>
#include <stdlib.h>
#include "Matrice.h"

int GetRandomNumber() {
	return rand();
}

int GetRandomNumber(int max) {
	return rand() % max;
}

int GetRandomNumber(int min, int max) {
	return GetRandomNumber(max - min) + min;
}

double GetRandomFloat(double p_facteur) {
	return GetRandomNumber(1000)*p_facteur;
}

double GetRandomFloat() {
	return GetRandomFloat(0.001);
}

bool FlipCoin() {
	return rand() % 2;
}

Matrice GetMatriceDeRéel(int p_ligne, int p_colonne, double p_facteur) {
	Matrice A(p_ligne, p_colonne);
	for (int l = 0; l < p_ligne; l++)
		for (int c = 0; c < p_colonne; c++)
			A[l][c] = GetRandomFloat(p_facteur);
	return A;
}

Matrice GetMatriceDeRéel(int p_ligne, int p_colonne) {
	return GetMatriceDeRéel(p_ligne, p_colonne, GetRandomFloat());
}

Matrice GetMatriceDEntier(int p_ligne, int p_colonne) {
	Matrice A(p_ligne, p_colonne);
	for (int l = 0; l < p_ligne; l++)
		for (int c = 0; c < p_colonne; c++)
			A[l][c] = GetRandomNumber(100);
	return A;
}

Matrice GetMatriceDEntier(int p_ligne, int p_colonne, int p_nombreAléatoireMax) {
	Matrice A(p_ligne, p_colonne);
	for (int l = 0; l < p_ligne; l++)
		for (int c = 0; c < p_colonne; c++)
			A[l][c] = GetRandomNumber(p_nombreAléatoireMax);
	return A;
}

Matrice GetMatriceDeBool(int p_ligne, int p_colonne) {
	Matrice A(p_ligne, p_colonne);
	for (int l = 0; l < p_ligne; l++)
		for (int c = 0; c < p_colonne; c++)
			A[l][c] = FlipCoin();
	return A;
}