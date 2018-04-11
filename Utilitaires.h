#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Binaire.h"
#include "Matrice.h"

int LongueurString(const char *t);

std::ostream& operator<<(std::ostream& p_flux, const char * t);

void �crire(const char * t, bool endl = true);
void �crire(const char * t, int p_Entier);
void �crire(const char * t, double p_unDouble);
void �crire(const char * t, const Matrice & p_M);
void �crire(int x, bool endl = true);
void �crire(int x, int p_NombreDeCaract�reAGuauche, bool endl = true);
void �crire(unsigned int x, bool endl = true);
void �crire(double db, bool endl = true);
void �crire(unsigned long long x, bool endl = true);
void �crire(const std::string &str, bool endl = true);
void �crire(const Binaire & p_b, const char * endl = "\n");
void �crire(const Binaire & p_b,int p_NombreDeCaract�reAGuauche, const char * endl = "\n");
void �crire(const Matrice &p_m, bool endl = true);

void Lire(bool &b, const char * text = NULL);
void Lire(int &i, const char * text = NULL);
void Lire(unsigned long long &i, const char * text = NULL);
void Lire(double &d, const char * text = NULL);
void Lire(std::string &t, const char * text = NULL);

void Pause();

void SaveToFile(const Matrice &p_m, std::string p_nomDuFichier);