#pragma once
#include <time.h>
#include <stdlib.h>
#include "Matrice.h"

int GetRandomNumber();
int GetRandomNumber(int max);
int GetRandomNumber(int min, int max);
double GetRandomFloat(double p_facteur);
double GetRandomFloat();
bool FlipCoin();

Matrice GetMatriceDeR�el(int p_ligne, int p_colonne);
Matrice GetMatriceDeR�el(int p_ligne, int p_colonne, double p_facteur);
Matrice GetMatriceDEntier(int p_ligne, int p_colonne);
Matrice GetMatriceDEntier(int p_ligne, int p_colonne, int p_nombreAl�atoireMax);
Matrice GetMatriceDeBool(int p_ligne, int p_colonne);