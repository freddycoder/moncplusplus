#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Binaire.h"
#include "Matrice.h"

int LongueurString(const char *t);

std::ostream& operator<<(std::ostream& p_flux, const char * t);

void Écrire(const char * t, bool endl = true);
void Écrire(const char * t, int p_Entier);
void Écrire(const char * t, double p_unDouble);
void Écrire(const char * t, const Matrice & p_M);
void Écrire(int x, bool endl = true);
void Écrire(int x, int p_NombreDeCaractèreAGuauche, bool endl = true);
void Écrire(unsigned int x, bool endl = true);
void Écrire(double db, bool endl = true);
void Écrire(unsigned long long x, bool endl = true);
void Écrire(const std::string &str, bool endl = true);
void Écrire(const Binaire & p_b, const char * endl = "\n");
void Écrire(const Binaire & p_b,int p_NombreDeCaractèreAGuauche, const char * endl = "\n");
void Écrire(const Matrice &p_m, bool endl = true);

void Lire(bool &b, const char * text = NULL);
void Lire(int &i, const char * text = NULL);
void Lire(unsigned long long &i, const char * text = NULL);
void Lire(double &d, const char * text = NULL);
void Lire(std::string &t, const char * text = NULL);

void Pause();

void SaveToFile(const Matrice &p_m, std::string p_nomDuFichier);