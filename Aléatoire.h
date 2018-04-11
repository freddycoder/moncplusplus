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

Matrice GetMatriceDeRéel(int p_ligne, int p_colonne);
Matrice GetMatriceDeRéel(int p_ligne, int p_colonne, double p_facteur);
Matrice GetMatriceDEntier(int p_ligne, int p_colonne);
Matrice GetMatriceDEntier(int p_ligne, int p_colonne, int p_nombreAléatoireMax);
Matrice GetMatriceDeBool(int p_ligne, int p_colonne);