#pragma once
#include "Matrice.h"

double Population(const Matrice &p_m);
double Dénombrement(double p_événement, const Matrice& p_m);
double ProbabilitéClassique(double p_événement, const Matrice& p_m);
double ProbabilitéEmpirique(double p_événement, const Matrice& p_m);
double FréquenceRelative(double p_événement, const Matrice & p_m);
bool EstUnÉvénementCertain(double p_Événement, const Matrice &p_m);
bool EstPasUnÉvénementCertain(double p_Événement, const Matrice &p_m);
double InverseDeProbabilitéClassique(double p_événement, const Matrice &p_m);
double InverseDeProbabilitéEmpirique(double p_événement, const Matrice & p_m);
double Intersection(double p_événementA, double p_événementB, const Matrice &p_m);
double Union(double p_événementA, double p_événementB, const Matrice &p_m);
double ProbabilitéConditionnelle(double p_événement, double p_sachantÉvénement, const Matrice &p_m);