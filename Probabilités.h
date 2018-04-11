#pragma once
#include "Matrice.h"

double Population(const Matrice &p_m);
double D�nombrement(double p_�v�nement, const Matrice& p_m);
double Probabilit�Classique(double p_�v�nement, const Matrice& p_m);
double Probabilit�Empirique(double p_�v�nement, const Matrice& p_m);
double Fr�quenceRelative(double p_�v�nement, const Matrice & p_m);
bool EstUn�v�nementCertain(double p_�v�nement, const Matrice &p_m);
bool EstPasUn�v�nementCertain(double p_�v�nement, const Matrice &p_m);
double InverseDeProbabilit�Classique(double p_�v�nement, const Matrice &p_m);
double InverseDeProbabilit�Empirique(double p_�v�nement, const Matrice & p_m);
double Intersection(double p_�v�nementA, double p_�v�nementB, const Matrice &p_m);
double Union(double p_�v�nementA, double p_�v�nementB, const Matrice &p_m);
double Probabilit�Conditionnelle(double p_�v�nement, double p_sachant�v�nement, const Matrice &p_m);