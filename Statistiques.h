#pragma once
#include <math.h>
#include "Matrice.h"

double Min(const Matrice &p_m);
double Max(const Matrice &p_m);
double Moyenne(const Matrice &p_m);
double Moyenne(double* p_ligne, int p_taille);
Matrice MoyenneDesLignes(const Matrice &p_m);
double �tendue(const Matrice &p_m);
double Amplitude(const Matrice &p_m);
double Variance(const Matrice &p_m);
double �cartType(const Matrice &p_m);
double CoefficientDeVariation(const Matrice &p_m);
double CoteZ(int indexLigne, int indexColonne, const Matrice& p_m);