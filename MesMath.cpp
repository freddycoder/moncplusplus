#include <math.h>
#include "Matrice.h"
#include "MesMath.h"

double Min(double p_x, double p_y) {
	if (p_x < p_y)
		return p_x;
	return p_y;
}

int Min(int p_x, int p_y) {
	if (p_x < p_y)
		return p_x;
	return p_y;
}

double Max(double p_x, double p_y) {
	if (p_x > p_y)
		return p_x;
	return p_y;
}

int Max(int p_x, int p_y) {
	if (p_x > p_y)
		return p_x;
	return p_y;
}

bool EstPremier(double p_nombre) {
	bool estPremier = true;
	for (int i = 2; i < sqrt(p_nombre)+1 && estPremier; i++)
		estPremier = ((int)p_nombre == p_nombre) &&
					 ((int)p_nombre % i != 0);
	return estPremier || (p_nombre == 2);
}

bool EstPasPremier(double p_nombre) {
	return !EstPremier(p_nombre);
}

double TrouverDiviseur(double p_nombre) {
	double diviseur = p_nombre;
	if (EstPasPremier(p_nombre))
		for (int i = 2; i < sqrt(p_nombre) + 1 && diviseur == p_nombre; i++)
			if ((int)p_nombre % i == 0)
				diviseur = i;
	return diviseur;
}

double Factoriel(double x) {
	if (x <= 1) {
		return 1;
	}
	return x * Factoriel(x - 1);
}

double Somme(double * p_ligne, int p_taille) {
	double somme = 0.0;
	for (int i = 0; i < p_taille; i++)
		somme += p_ligne[i];
	return somme;
}

double Somme(const Matrice & p_m) {
	double somme = 0.0;
	for (int l = 0; l < p_m.GetNbLigne(); l++)
		for (int c = 0; c < p_m.GetNbColonne(); c++)
			somme += p_m.GetMatrice()[l][c];
	return somme;
}

int ValeurAbsolue(int p_Entier) {
	if (p_Entier < 0) 
		p_Entier *= -1;
	return p_Entier;
}

double ValeurAbsolue(double p_Double) {
	if (p_Double < 0)
		p_Double *= -1;
	return p_Double;
}