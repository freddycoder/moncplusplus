// ***********************************************************************************************
// Description : 
//	Ce fichier contient la classe matrice et les fonctions d'opération mathématique
//  sur les matrices.
//
// Auteur : Frédéric Jacques
// ***********************************************************************************************
#pragma once
#include <ostream>

double** MatriceNull(const int p_nbLigne, const int p_nbColonne);
double** MatriceIdentite(const int p_ordre);

class Matrice {
public:
	Matrice();
	Matrice(const int p_ordre);
	Matrice(int p_nbLignes, int p_nbColonnes);
	Matrice(int p_nbLinges, int p_nbColonnes, double** p_matrice);
	Matrice(const Matrice &uneMatrice);

	~Matrice();
	void Vider();

	void SetNbLignes(int p_NbLignes);
	void SetNbColonnes(int p_NbColonnes);
	void SetMatrice(double **p_NouvelleMatrice);
	void SetMatriceElement(int p_Ligne, int p_Colonne, double p_NouvelleÉlément);

	int GetNbLigne() const;
	int GetNbColonne() const;
	double ** GetMatrice() const;

	void operator=(const Matrice& p_m);
	bool operator==(const Matrice& p_m) const;
	Matrice operator+(const Matrice &p_m) const;
	Matrice operator*(const Matrice &p_m) const;
	double* operator[](int p_indice);
	double* operator[](int p_indice) const;
	friend std::ostream& operator<<(std::ostream& p_Flux, const Matrice& p_Matrice);

	void MultiplierParScalaire(const double p_k);
	void DiviserParScalaire(const double p_k);
	void Exposant(int p_exposant);
	void Transposer();
	void MatriceAugmenter(const Matrice &p_m);
	void MéthodeDeGauss(const Matrice &p_matriceEgualite);
	

private:
	bool EstVide() const;
	bool CheckInvariantes() const;

	int m_nbLigne;
	int m_nbColonne;
	double **m_matrice;
};
