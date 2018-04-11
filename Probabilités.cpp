#include "Matrice.h"
#include "Probabilités.h"

double Population(const Matrice & p_m) {
	return (p_m.GetNbLigne() * p_m.GetNbColonne());
}

double Dénombrement(double p_événement, const Matrice & p_m) {
	double nombreDElement = 0.0;
	for (int l = 0; l < p_m.GetNbLigne(); l++)
		for (int c = 0; c < p_m.GetNbColonne(); c++)
			if (p_m.GetMatrice()[l][c] == p_événement)
				nombreDElement++;
	return nombreDElement;
}

double ProbabilitéClassique(double p_événement, const Matrice & p_m) {
	return Dénombrement(p_événement, p_m) /	Population(p_m);
}

double ProbabilitéEmpirique(double p_événement, const Matrice & p_m) {
	return Dénombrement(p_événement, p_m) / (p_m.GetNbColonne());
}

double FréquenceRelative(double p_événement, const Matrice & p_m) {
	return ProbabilitéEmpirique(p_événement, p_m);
}

bool EstUnÉvénementCertain(double p_Événement, const Matrice & p_m) {
	return Dénombrement(p_Événement, p_m) == Population(p_m);
}

bool EstPasUnÉvénementCertain(double p_Événement, const Matrice & p_m) {
	return !EstUnÉvénementCertain(p_Événement, p_m);
}

double InverseDeProbabilitéClassique(double p_événement, const Matrice & p_m) {
	return 1 - ProbabilitéClassique(p_événement, p_m);
}

double InverseDeProbabilitéEmpirique(double p_événement, const Matrice & p_m) {
	return 1 - ProbabilitéEmpirique(p_événement, p_m);
}

double Intersection(double p_événementA, double p_ÉvénementB, const Matrice & p_m) {
	return ProbabilitéEmpirique(p_événementA, p_m) * ProbabilitéEmpirique(p_ÉvénementB, p_m);
}

double Union(double p_événementA, double p_événementB, const Matrice & p_m) {
	return (ProbabilitéEmpirique(p_événementA, p_m) + ProbabilitéEmpirique(p_événementB, p_m)) - Intersection(p_événementA, p_événementB, p_m);
}

double ProbabilitéConditionnelle(double p_événement, double p_sachantÉvénement, const Matrice & p_m) {
	return Intersection(p_événement, p_sachantÉvénement, p_m) / ProbabilitéEmpirique(p_sachantÉvénement, p_m);
}
