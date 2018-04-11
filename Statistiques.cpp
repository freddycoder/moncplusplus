#include <math.h>
#include <vector>
#include "Matrice.h"
#include "MesMath.h"
#include "Statistiques.h"

double Min(const Matrice &p_m) {
	double min = p_m.GetMatrice()[0][0];
	for (int l = 0; l < p_m.GetNbLigne(); l++)
		for (int c = 0; c < p_m.GetNbColonne(); c++)
			if (p_m.GetMatrice()[l][c] < min)
				min = p_m.GetMatrice()[l][c];
	return min;
}

double Max(const Matrice &p_m) {
	double max = p_m.GetMatrice()[0][0];
	for (int l = 0; l < p_m.GetNbLigne(); l++)
		for (int c = 0; c < p_m.GetNbColonne(); c++)
			if (p_m.GetMatrice()[l][c] > max)
				max = p_m.GetMatrice()[l][c];
	return max;
}

double Moyenne(double * p_ligne, int p_taille) {
	return Somme(p_ligne, p_taille) / p_taille;
}

Matrice MoyenneDesLignes(const Matrice & p_m) {
	Matrice moyenneDesLignes(p_m.GetNbLigne(), 1);
	double somme = 0.0;
	for (int l = 0; l < p_m.GetNbLigne(); l++)
		moyenneDesLignes.
			SetMatriceElement(l, 0, 
				Moyenne(p_m.GetMatrice()[l], p_m.GetNbColonne()));

	return moyenneDesLignes;
}

double Moyenne(const Matrice &p_m) {
	return Somme(p_m) / (p_m.GetNbLigne() * p_m.GetNbColonne());
}

double Étendue(const Matrice &p_m) {
	return Max(p_m) - Min(p_m);
}

double Amplitude(const Matrice &p_m){
	return Étendue(p_m) / (p_m.GetNbLigne() * p_m.GetNbColonne());
}

double Variance(const Matrice &p_m) {
	double variance = 0.0;
	double moyenne = Moyenne(p_m);
	for (int l = 0; l < p_m.GetNbLigne(); l++)
		for (int c = 0; c < p_m.GetNbColonne(); c++)
			variance += pow((p_m.GetMatrice()[l][c] - moyenne), 2);
	return variance / (p_m.GetNbLigne() * p_m.GetNbColonne());
}

double ÉcartType(const Matrice &p_m) {
	return sqrt(Variance(p_m));
}

double CoefficientDeVariation(const Matrice & p_m) {
	return ÉcartType(p_m) / Moyenne(p_m);
}

double CoteZ(int indexLigne, int indexColonne, const Matrice & p_m) {
	return (p_m.GetMatrice()[indexLigne][indexColonne] - Moyenne(p_m)) / ÉcartType(p_m);
}
