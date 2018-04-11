#include "Matrice.h"
#include "Probabilit�s.h"

double Population(const Matrice & p_m) {
	return (p_m.GetNbLigne() * p_m.GetNbColonne());
}

double D�nombrement(double p_�v�nement, const Matrice & p_m) {
	double nombreDElement = 0.0;
	for (int l = 0; l < p_m.GetNbLigne(); l++)
		for (int c = 0; c < p_m.GetNbColonne(); c++)
			if (p_m.GetMatrice()[l][c] == p_�v�nement)
				nombreDElement++;
	return nombreDElement;
}

double Probabilit�Classique(double p_�v�nement, const Matrice & p_m) {
	return D�nombrement(p_�v�nement, p_m) /	Population(p_m);
}

double Probabilit�Empirique(double p_�v�nement, const Matrice & p_m) {
	return D�nombrement(p_�v�nement, p_m) / (p_m.GetNbColonne());
}

double Fr�quenceRelative(double p_�v�nement, const Matrice & p_m) {
	return Probabilit�Empirique(p_�v�nement, p_m);
}

bool EstUn�v�nementCertain(double p_�v�nement, const Matrice & p_m) {
	return D�nombrement(p_�v�nement, p_m) == Population(p_m);
}

bool EstPasUn�v�nementCertain(double p_�v�nement, const Matrice & p_m) {
	return !EstUn�v�nementCertain(p_�v�nement, p_m);
}

double InverseDeProbabilit�Classique(double p_�v�nement, const Matrice & p_m) {
	return 1 - Probabilit�Classique(p_�v�nement, p_m);
}

double InverseDeProbabilit�Empirique(double p_�v�nement, const Matrice & p_m) {
	return 1 - Probabilit�Empirique(p_�v�nement, p_m);
}

double Intersection(double p_�v�nementA, double p_�v�nementB, const Matrice & p_m) {
	return Probabilit�Empirique(p_�v�nementA, p_m) * Probabilit�Empirique(p_�v�nementB, p_m);
}

double Union(double p_�v�nementA, double p_�v�nementB, const Matrice & p_m) {
	return (Probabilit�Empirique(p_�v�nementA, p_m) + Probabilit�Empirique(p_�v�nementB, p_m)) - Intersection(p_�v�nementA, p_�v�nementB, p_m);
}

double Probabilit�Conditionnelle(double p_�v�nement, double p_sachant�v�nement, const Matrice & p_m) {
	return Intersection(p_�v�nement, p_sachant�v�nement, p_m) / Probabilit�Empirique(p_sachant�v�nement, p_m);
}
