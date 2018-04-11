#pragma once
#include "Matrice.h"

double Min(double p_x, double p_y);
int Min(int p_x, int p_y);
double Max(double p_x, double p_y);
int Max(int p_x, int p_y);
bool EstPremier(double p_nombre);
bool EstPasPremier(double p_nombre);
double TrouverDiviseur(double p_nombre);
double Factoriel(double x);
double Somme(double* p_ligne, int p_taille);
double Somme(const Matrice & p_m);
int ValeurAbsolue(int p_Entier);
double ValeurAbsolue(double p_Double);