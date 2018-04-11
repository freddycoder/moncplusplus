#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include "Binaire.h"
#include "Matrice.h"

int LongueurString(const char * t) {
	int longueur = 0;
	if (t != NULL)
		for (; t[longueur] != '\0'; longueur++);
	return longueur;
}

std::ostream& operator<<(std::ostream& p_flux, const char * t) {
	for (int i = 0; i < LongueurString(t); i++)
		p_flux << t[i];
	return p_flux;
}

void �crire(const char * t, bool endl) {
	if (endl) std::cout << t << std::endl;
	else std::cout << t;
}

void �crire(const char * t, int p_unEntier) {
	std::cout << t << " " << p_unEntier << std::endl;
}

void �crire(const char * t, double p_unDouble) {
	std::cout << t << " " << p_unDouble << std::endl;
}

void �crire(const char * t, const Matrice & p_m) {
	std::cout << t << p_m << std::endl;
}

void �crire(int x, bool endl) {
	if (endl) std::cout << x << std::endl;
	else std::cout << x;
}

void �crire(int x, int p_NombreDeCaract�reAGuauche, bool endl) {
	if (endl) {
		std::cout << std::setw(p_NombreDeCaract�reAGuauche) << x << std::endl;
	}
	else {
		std::cout << x;
	}
}

void �crire(unsigned int x, bool endl) {
	if (endl) {
		std::cout << x << std::endl;
	}
	else {
		std::cout << x;
	}
}

void �crire(double db, bool endl) {
	if (endl) {
		std::cout << db << std::endl;
	}
	else {
		std::cout << db;
	}
}

void �crire(unsigned long long x, bool endl) {
	if (endl) {
		std::cout << x << std::endl;
	}
	else {
		std::cout << x;
	}
}

void �crire(const std::string &str, bool endl) {
	if (endl) {
		std::cout << str << std::endl;
	}
	else {
		std::cout << str;
	}
}

void �crire(const Binaire &p_b, const char * endl) {
	std::cout << p_b << endl;
}

void �crire(const Binaire &p_b, int p_NombreDeCaract�reAGuauche, const char * endl) {
	std::cout << std::setw(p_NombreDeCaract�reAGuauche) << p_b << endl;
}

void �crire(const Matrice &p_m, bool endl) {
	if (endl) {
		std::cout << p_m << std::endl;
	}
	else {
		std::cout << p_m;
	}
}

void Lire(bool &b, const char * text) {
	if (text != NULL)
		�crire(text, false);

	std::cin >> b;
	std::cin.ignore();
}

void Lire(int &i, const char * text) {
	if (text != NULL)
		�crire(text, false);

	std::cin >> i;
	std::cin.ignore();
}

void Lire(unsigned long long &i, const char * text) {
	if (text != NULL)
		�crire(text, false);

	std::cin >> i;
	std::cin.ignore();
}

void Lire(double &d, const char * text) {
	if (text != NULL)
		�crire(text, false);

	std::cin >> d;
	std::cin.ignore();
}

void Lire(std::string &t, const char * text) {
	if (text != NULL)
		�crire(text, false);

	std::cin.clear();
	std::getline(std::cin, t);
}

void Pause() {
	std::cin.get();
}

void SaveToFile(const Matrice &p_m, std::string p_nomDuFichier) {
	std::ofstream file;
	file.open(p_nomDuFichier);
	if (file.is_open()) {
		file << p_m;
		file.close();
	}
	else {
		std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
	}
}