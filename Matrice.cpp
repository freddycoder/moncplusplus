#include <ostream>
#include <iomanip>
#include <math.h>
#include "Matrice.h"
#include "Assertion.h"
// ************************************************************************************
// Description : Retourne une matrice null de dimenssion m x n
//
// Précondition : Le nombre de ligne et le nombre de colonne doivent être
//				  suppérieur à 0.
//
// Auteur : Frédéric Jacques
// *************************************************************************************
double** MatriceNull(const int p_nbLigne, const int p_nbColonne) {
	PRÉCONDITION(p_nbLigne > 0 && p_nbColonne > 0);
	double** matrice = new double*[p_nbLigne];
	for (int l = 0; l < p_nbLigne; l++) {
		matrice[l] = new double[p_nbColonne];
		for (int c = 0; c < p_nbColonne; c++)
			matrice[l][c] = 0.0;
	}
	return matrice;
}
// ************************************************************************************
// Description : Retourne une matrice identité d'ordre x
//
// Précondition : L'ordre doit être suppérieur à 0
//
// Auteur : Frédéric Jacques
// *************************************************************************************
double** MatriceIdentite(int p_ordre) {
	PRÉCONDITION(p_ordre > 0);
	double** I = new double*[p_ordre];
	for (int ligne = 0; ligne < p_ordre; ligne++) {
		I[ligne] = new double[p_ordre];
		for (int colonne = 0; colonne < p_ordre; colonne++) {
			if (ligne == colonne) I[ligne][colonne] = 1;
			else I[ligne][colonne] = 0;
		}
	}
	return I;
}
// ************************************************************************************
// Description : Constructeur par Défaut. Initialise une matrice à qui pointe sur NULL
//				 avec 0 ligne et 0 colonne.
//
// POSTCONDITION : La matrice est vide,
//				   Les invariantes sont respectés.
// *************************************************************************************
Matrice::Matrice() {
	this->m_nbLigne = 0;
	this->m_nbColonne = 0;
	this->m_matrice = NULL;
	POSTCONDITION(this->EstVide());
	POSTCONDITION(this->CheckInvariantes());
}
// ************************************************************************************
// Description : Constructeur d'initialisation. Initialise une matrice Identité
//				 selon l'ordre passer en paramètres.
//
// Paramètres : L'odre (dimmession m x n ou ordre = m = n.
//
// POSTCONDITION : Les invariantes sont respectés.
// *************************************************************************************
Matrice::Matrice(const int p_ordre) {
	this->m_nbLigne = p_ordre;
	this->m_nbColonne = p_ordre;
	this->m_matrice = MatriceIdentite(p_ordre);
	POSTCONDITION(this->CheckInvariantes());
}
// ************************************************************************************
// Description : Constructeur d'initialisation. Initialise une matrice Null,
//
// Paramètres : Le nombre de ligne et le nombre de colonne.
//
// POSTCONDITION : Les invariantes sont respectés.
// *************************************************************************************
Matrice::Matrice(int p_nbLignes, int p_nbColonnes) {
	this->m_nbLigne = p_nbLignes;
	this->m_nbColonne = p_nbColonnes;
	this->m_matrice = MatriceNull(this->m_nbLigne, this->m_nbColonne);
	POSTCONDITION(this->CheckInvariantes());
}
// ************************************************************************************
// Description : Constructeur d'initialisation. Selon le double pointeur de double
//				 passer en paramètres.
//
// Paramètres : Le nombre de ligne et le nombre de colonne et la matrice.
//
// POSTCONDITION : Les invariantes sont respectés.
// *************************************************************************************
Matrice::Matrice(int p_nbLignes, int p_nbColonnes, double** p_matrice) {
	this->m_nbLigne = p_nbLignes;
	this->m_nbColonne = p_nbColonnes;
	this->m_matrice = p_matrice;
	POSTCONDITION(this->CheckInvariantes());
}
// ************************************************************************************
// Description : Constructeur par copie. Initialise une matrice selon la matrice
//				 passer en paramètre.
//
// Paramètres : Le nombre de ligne et le nombre de colonne et la matrice.
//
// POSTCONDITION : Les invariantes sont respectés.
// *************************************************************************************
Matrice::Matrice(const Matrice& p_uneMatrice) {
	*this = p_uneMatrice;
	POSTCONDITION(this->CheckInvariantes());
}
// ************************************************************************************
// Description : Destructeur par défaut.
//
// POSTCONDITION : Les invariantes sont respectés.
//				   La matrice est vide.
// *************************************************************************************
Matrice::~Matrice() {
	this->Vider();
	POSTCONDITION(this->CheckInvariantes());
	POSTCONDITION(this->EstVide());
}
// ***************************************************************************************
// Description : Libère la mémoire alloué par à une matrice et met le nombre de 
//				 ligne et de colonne à 0.
//
// POSTCONDITION : L'objet courrant est vide.
//
// Retourne : Rien
// ***************************************************************************************
void Matrice::Vider() {
	for (int l = 0; l < this->m_nbLigne; l++) {
		delete[] this->m_matrice[l];
	}
	delete[] this->m_matrice;
	this->m_matrice = NULL;
	this->m_nbLigne = 0;
	this->m_nbColonne = 0;
	POSTCONDITION(this->EstVide());
}

void Matrice::SetNbLignes(int p_nbLignes) {
	PRÉCONDITION(p_nbLignes > 0);
	this->m_nbLigne = p_nbLignes;
}
void Matrice::SetNbColonnes(int p_NbColonnes) {
	PRÉCONDITION(p_NbColonnes > 0);
	this->m_nbColonne = p_NbColonnes;
}
void Matrice::SetMatrice(double **p_NouvelleMatrice) {
	PRÉCONDITION(&p_NouvelleMatrice != NULL);
	this->m_matrice = p_NouvelleMatrice;
}
int Matrice::GetNbLigne() const {
	PRÉCONDITION(this != NULL);
	return this->m_nbLigne;
}
int Matrice::GetNbColonne() const {
	PRÉCONDITION(this != NULL);
	return this->m_nbColonne;
}
double ** Matrice::GetMatrice() const {
	PRÉCONDITION(this != NULL);
	return this->m_matrice;
}
void Matrice::SetMatriceElement(int p_Ligne, int p_Colonne, double p_NouvelleÉlément) {
	PRÉCONDITION(this != NULL);
	this->m_matrice[p_Ligne][p_Colonne] = p_NouvelleÉlément;
}
// ***************************************************************************************
// Description : Opérateur d'affectation de d'objet matrice
//
// Postcondition : L'objet courrant est égual à l'objet passer en paramètre
//
// Retourne : Rien
// ***************************************************************************************
void Matrice::operator=(const Matrice & p_m) {
	if (this->m_matrice != NULL && this->m_nbLigne > 0 && this->m_nbColonne > 0) {
		this->Vider();
	}
	this->m_nbLigne = p_m.m_nbLigne;
	this->m_nbColonne = p_m.m_nbColonne;
	this->m_matrice = MatriceNull(this->m_nbLigne, this->m_nbColonne);
	for (int l = 0; l < this->m_nbLigne; l++) {
		for (int c = 0; c < this->m_nbColonne; c++) {
			this->m_matrice[l][c] = p_m.m_matrice[l][c];
		}
	}
	POSTCONDITION(*this == p_m);
}
// ***************************************************************************************
// Description : Vérifie que deux matrice sont identique.
//
// Retourne : Vrai si les matrices sont identique. Sinon faux.
// Auteur : Frédéric Jacques
// ***************************************************************************************
bool Matrice::operator==(const Matrice& p_m) const {
	bool egual = this->m_nbLigne == p_m.m_nbLigne && this->m_nbColonne == p_m.m_nbColonne;
	for (int l = 0; l < this->m_nbLigne && egual; l++)
		for (int c = 0; c < this->m_nbColonne && egual; c++)
			egual = this->m_matrice[l][c] == p_m.m_matrice[l][c];
	return egual;
}
// ***************************************************************************************
// Description : Additionne la une matrice à la matrice passer en paramètre.
//
// Retourne : Pointeur sur la matrice somme, si la matrice ne peut pas être multiplier
//			  la fonction retourne une matrice initialiser par le constructeur par défaut.
// ***************************************************************************************
Matrice Matrice::operator+(const Matrice &p_m) const {
	Matrice somme;
	if (this->m_nbLigne == p_m.m_nbLigne && this->m_nbColonne == p_m.m_nbColonne) {
		somme = Matrice(this->m_nbLigne, this->m_nbColonne);
		for (int l = 0; l < somme.m_nbLigne; l++) {
			for (int c = 0; c < somme.m_nbColonne; c++)
				somme.m_matrice[l][c] = this->m_matrice[l][c] + p_m.m_matrice[l][c];
		}
	}
	return somme;
}
// ***************************************************************************************
// Description : Multiplie une matrice à la matrice passer en paramètre.
//
// Retourne : Pointeur sur la matrice produit le pointeur est NULL s'il est impossible
//			  défectuer la multiplication
// ***************************************************************************************
Matrice Matrice::operator*(const Matrice &p_m) const {
	Matrice matriceProduit;
	if (this->m_nbColonne == p_m.m_nbLigne) {
		matriceProduit = Matrice(this->m_nbLigne, p_m.m_nbColonne);
		for (int l = 0; l < matriceProduit.m_nbLigne; l++) {
			for (int c = 0; c < matriceProduit.m_nbColonne; c++) {
				double unProduit = 0.0;
				for (int iDeMultiplic = 0; iDeMultiplic < p_m.m_nbLigne; iDeMultiplic++)
					unProduit += this->m_matrice[l][iDeMultiplic] * p_m.m_matrice[iDeMultiplic][c];
				
				matriceProduit.m_matrice[l][c] = unProduit;
			}
		}
	}
	return matriceProduit;
}

double * Matrice::operator[](int p_indice) {
	return this->m_matrice[p_indice];
}

double * Matrice::operator[](int p_indice) const {
	return this->m_matrice[p_indice];
}

// ***************************************************************************************
// Description : Opérateur de sortie. Il met un ";" après chque élément de la matrice
//				 et il met des saut de ligne après chaque ligne.
//
// Retourne : Une référence vers un ostream
// ***************************************************************************************
std::ostream& operator<<(std::ostream& p_Flux, const Matrice& p_Matrice) { 
	for (int l = 0; l < p_Matrice.GetNbLigne(); l++) {
		for (int c = 0; c < p_Matrice.GetNbColonne(); c++)
			if (p_Matrice.GetMatrice()[l][c] - (int)p_Matrice.GetMatrice()[l][c] == 0)
				p_Flux << p_Matrice.GetMatrice()[l][c] << ' ';
				//p_Flux << std::setprecision(8) << std::setw(10) << p_Matrice.GetMatrice()[l][c] << ';';
			else p_Flux << std::setprecision(5) << std::setw(10) << p_Matrice.GetMatrice()[l][c] << ';';
		p_Flux << std::endl;
	}
	return p_Flux;
}
// ***************************************************************************************
// Description : Multiplie tout les éléments de la matrice par un scalaire
//
// Retourne : Rien
// ***************************************************************************************
void Matrice::MultiplierParScalaire(const double p_k) {
	for (int l = 0; l < this->m_nbLigne; l++)
		for (int c = 0; c < this->m_nbColonne; c++)
			this->m_matrice[l][c] = p_k * this->m_matrice[l][c];
}
// ***************************************************************************************
// Description : Divise tout les éléments de la matrice par un scalaire
//
// Paramètres : Une constante 
//
// Retourne : Rien
// ***************************************************************************************
void Matrice::DiviserParScalaire(const double p_k) {
	for (int l = 0; l < this->m_nbLigne; l++)
		for (int c = 0; c < this->m_nbColonne; c++)
			this->m_matrice[l][c] = this->m_matrice[l][c] / p_k;
}
// ***************************************************************************************
// Description : Va augmenter à la puissance de p_exposant chaque élément de la matrice
//
// Paramètres : Un exposant
//
// Retourne : Rien
// ***************************************************************************************
void Matrice::Exposant(int p_exposant) {
	for (int l = 0; l < this->m_nbLigne; l++)
		for (int c = 0; c < this->m_nbColonne; c++)
			this->m_matrice[l][c] = pow(this->m_matrice[l][c], p_exposant);
}
// ***************************************************************************************
// Description : Transpose une matrice
//
// Retourne : Rien
// ***************************************************************************************
void Matrice::Transposer() {
	Matrice mt(this->m_nbColonne, this->m_nbLigne);
	for (int l = 0; l < mt.m_nbLigne; l++)
		for (int c = 0; c < mt.m_nbColonne; c++)
			mt.m_matrice[l][c] = this->m_matrice[c][l];
	*this = mt;
}
// ***************************************************************************************
// Description : Augmente une matrice
//
// Paramètres : La matrice qui va être ajouter à gauche. Habituellement une matrice
//				d'égualité.
//
// Retourne : Rien
// ***************************************************************************************
void Matrice::MatriceAugmenter(const Matrice &p_m) {
	Matrice mA(this->m_nbLigne, this->m_nbColonne + p_m.m_nbColonne);
	for (int l = 0; l < this->m_nbLigne; l++) {
		for (int c = 0; c < this->m_nbColonne; c++) {
			mA.m_matrice[l][c] = this->m_matrice[l][c];
			mA.m_matrice[l][this->m_nbColonne + c] = p_m.m_matrice[l][c];
		}
	}
	*this = mA;
}
// ***************************************************************************************
// Description : Effectue la méthode de Gauss
//
// Paramètres : La matrice qui sert de matrice égualité pour résoudre le système
//				d'équation.
//
// Retourne : Rien
// ***************************************************************************************
void Matrice::MéthodeDeGauss(const Matrice &p_matriceEgualite) {
	this->MatriceAugmenter(p_matriceEgualite);
	double k1 = 0.0;
	double k2 = 0.0;
	for (int l = 1; l <this->m_nbLigne; l++) {
		for (int c = 0; c < l; c++) {
			if (this->m_matrice[l][c]) {
				k1 = this->m_matrice[0][c];
				k2 = this->m_matrice[l][c];
				for (int col = c; col < this->m_nbColonne; col++)
					this->m_matrice[l][col] = (k1 * this->m_matrice[l][col]) - (k2 * this->m_matrice[0][col]);
			}
		}
	}
}


bool Matrice::EstVide() const {
	return this->m_nbLigne == 0 && this->m_nbColonne == 0;
}
bool Matrice::CheckInvariantes() const {
	bool estOK = false;
	if (this->m_matrice == NULL) {
		estOK = this->m_nbLigne == 0 && this->m_nbColonne == 0;
	}
	else {
		estOK = this->m_nbLigne > 0 && this->m_nbColonne > 0;
	}
	return estOK;
}