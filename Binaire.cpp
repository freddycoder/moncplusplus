#include <bitset>
#include <math.h>
#include "Assertion.h"
#include "Binaire.h"
#include "MesMath.h"


// *********************************************************************************
// Description : Donne le nombre de bits d'un entier basé sur le bit à 1 avec la
//				 plus grande valeur.
//
// PRÉCONDITION : La valeur doit être positive
// 
// Retourne : Pointeur de bool
// *********************************************************************************
int TrouverLeNombreDeBits(int p_Entier) {
	PRÉCONDITION(p_Entier >= 0);
	int plusGrandBit = 0;
	std::bitset<32> x(p_Entier);
	for (unsigned int i = 0; i < x.size(); i++)
		if (x[i]) plusGrandBit = i + 1;
	return plusGrandBit;
}

// *********************************************************************************
// Description : Créer une chaine binaire avec un entier donné.
//
// PRÉCONDITION : La valeur doit être positive
// 
// Retourne : Pointeur de bool
// *********************************************************************************
bool * CréerUneChaîneBinaire(int p_Entier) {
	PRÉCONDITION(p_Entier >= 0);
	bool * chaineBinaire = NULL;
	int nombreDeBits = TrouverLeNombreDeBits(p_Entier);
	if (nombreDeBits) {
		chaineBinaire = new bool[nombreDeBits];
		for (int puissance = nombreDeBits - 1; puissance >= 0; puissance--) {
			if (p_Entier - pow(2, puissance) >= 0) {
				p_Entier -= (int)pow(2, puissance);
				chaineBinaire[puissance] = 1;
			}
			else chaineBinaire[puissance] = 0;
		}
	}
	return chaineBinaire;
}

// *********************************************************************************
// Description : Créer une chaine binaire de la partie décimale d'un nombre.
//
// PRÉCONDITION : La valeur doit être positive
// 
// Retourne : Pointeur sur une structure s_Fractionnaire
// *********************************************************************************
s_Fractionnaire* CréerUneChaineBinaireFractionnaire(double p_Double) {
	PRÉCONDITION(p_Double >= 0);
	s_Fractionnaire * s_Decimal = new s_Fractionnaire;
	s_Decimal->m_MémoiresAllouées = 8;
	s_Decimal->m_NombreDeBits = 0;
	s_Decimal->m_Bits = new bool[s_Decimal->m_MémoiresAllouées];

	for (int i = 0; i < s_Decimal->m_MémoiresAllouées && p_Double != 1.0 && p_Double != 0.0; i++) {
		s_Decimal->m_NombreDeBits++;
		if (p_Double > 1.0) p_Double = p_Double - (int)p_Double;
		p_Double *= 2;

		if (p_Double >= 1) s_Decimal->m_Bits[i] = 1;
		else s_Decimal->m_Bits[i] = 0;

		if (i == s_Decimal->m_MémoiresAllouées - 1 && i != 31) {
			bool * temporaire = new bool[s_Decimal->m_MémoiresAllouées];
			for (int i = 0; i < s_Decimal->m_MémoiresAllouées; i++)
				temporaire[i] = s_Decimal->m_Bits[i];

			delete[] s_Decimal->m_Bits;
			s_Decimal->m_Bits = NULL;
			s_Decimal->m_MémoiresAllouées += 8;
			s_Decimal->m_Bits = new bool[s_Decimal->m_MémoiresAllouées];

			for (int i = 0; i <= s_Decimal->m_NombreDeBits; i++)
				s_Decimal->m_Bits[i] = temporaire[i];

			delete[] temporaire;
		}
	}
	return s_Decimal;
}

Binaire::Binaire() {
	this->m_EstNégatif = false;
	this->m_NombreDeBitsPartieEntière = 0;
	this->m_BitsPartieEntière = NULL;
	this->m_Fractionnaire = NULL;
	POSTCONDITION(this->EstVide());
	POSTCONDITION(this->CheckInvariants());
}

Binaire::Binaire(int p_Entier) {
	*this = p_Entier;
	POSTCONDITION(this->CheckInvariants());
}

Binaire::Binaire(double p_Double) {
	*this = p_Double;
	POSTCONDITION(this->CheckInvariants());
}

Binaire::Binaire(const Binaire & p_Valeur) {
	*this = p_Valeur;
	POSTCONDITION(this->CheckInvariants());
}

Binaire::~Binaire() {
	this->Vider();
	POSTCONDITION(this->CheckInvariants());
}

void Binaire::Vider() {
	this->m_EstNégatif = false;
	this->m_NombreDeBitsPartieEntière = 0;
	delete[] this->m_BitsPartieEntière;
	this->m_BitsPartieEntière = NULL;
	if (this->m_Fractionnaire != NULL) {
		delete[] this->m_Fractionnaire->m_Bits;
		delete this->m_Fractionnaire;
		this->m_Fractionnaire = NULL;
	}
	POSTCONDITION(this->EstVide());
}

bool Binaire::GetEstNégatif() const {
	return this->m_EstNégatif;
}

int Binaire::GetNombreDeBitsPartieEntière() const {
	return this->m_NombreDeBitsPartieEntière;
}

bool * Binaire::GetBitsPartieEntère() const {
	return this->m_BitsPartieEntière;
}

int Binaire::GetNombreDeBitsPartieFractionnaire() const {
	return this->m_Fractionnaire->m_NombreDeBits;
}

bool * Binaire::GetBitsPartieFractionnaire() const {
	return this->m_Fractionnaire->m_Bits;
}

void Binaire::operator=(int p_Entier) {
	if (!this->EstVide() && this->m_NombreDeBitsPartieEntière >= 0) this->Vider();
	if (p_Entier < 0) this->m_EstNégatif = true; else this->m_EstNégatif = false;
	this->m_NombreDeBitsPartieEntière = TrouverLeNombreDeBits(ValeurAbsolue(p_Entier));
	this->m_BitsPartieEntière = CréerUneChaîneBinaire(ValeurAbsolue(p_Entier));
	this->m_Fractionnaire = NULL;
}

void Binaire::operator=(double p_Double) {
	if (!this->EstVide() && this->m_NombreDeBitsPartieEntière >= 0) this->Vider();
	if (p_Double < 0) this->m_EstNégatif = true; else this->m_EstNégatif = false;
	this->m_NombreDeBitsPartieEntière = TrouverLeNombreDeBits(ValeurAbsolue((int)p_Double));
	this->m_BitsPartieEntière = CréerUneChaîneBinaire(ValeurAbsolue((int)p_Double));
	this->m_Fractionnaire = CréerUneChaineBinaireFractionnaire(ValeurAbsolue(p_Double));
}

void Binaire::operator=(const Binaire & p_Valeur) {
	if (!this->EstVide() && this->m_NombreDeBitsPartieEntière >= 0) this->Vider();
	this->m_EstNégatif = p_Valeur.m_EstNégatif;
	this->m_NombreDeBitsPartieEntière = p_Valeur.m_NombreDeBitsPartieEntière;
	if (p_Valeur.m_BitsPartieEntière != NULL) {
		this->m_BitsPartieEntière = new bool[this->m_NombreDeBitsPartieEntière];
		for (int i = 0; i < this->m_NombreDeBitsPartieEntière; i++)
			this->m_BitsPartieEntière[i] = p_Valeur.m_BitsPartieEntière[i];
	}
	else this->m_BitsPartieEntière = NULL;
	if (p_Valeur.m_Fractionnaire != NULL) {
		this->CopierLaPartieDécimale(p_Valeur);
	}
	else this->m_Fractionnaire = NULL;
	POSTCONDITION(*this == p_Valeur);
}

Binaire Binaire::operator!() const {
	Binaire inverse = MasquePartieEntière(31);
	//inverse.m_EstNégatif = !this->m_EstNégatif;
	for (int i = this->m_NombreDeBitsPartieEntière - 1; i >= 0; i--)
		inverse.m_BitsPartieEntière[i] = !this->m_BitsPartieEntière[i];

	inverse.SupprimerLesZerosAuDébutDUnePartieEntière();

	if (this->m_Fractionnaire != NULL) {
		inverse = inverse | MasqueDécimale(32);
		for (int i = 0; i < this->m_Fractionnaire->m_NombreDeBits; i++)
			inverse.m_Fractionnaire->m_Bits[i] = !this->m_Fractionnaire->m_Bits[i];
		inverse.SupprimerLesZerosALaFinDUnePartieDecimale();
	}
	
	return inverse;
}

bool Binaire::operator==(const Binaire & p_Valeur) const{
	bool estEgual = this->m_EstNégatif == p_Valeur.m_EstNégatif;
	if (this->m_NombreDeBitsPartieEntière == p_Valeur.m_NombreDeBitsPartieEntière)
		for (int i = 0; i < this->m_NombreDeBitsPartieEntière && estEgual; i++)
			estEgual = this->m_BitsPartieEntière[i] == p_Valeur.m_BitsPartieEntière[i];
	else estEgual = false;

	if (estEgual && this->m_Fractionnaire != NULL && p_Valeur.m_Fractionnaire != NULL) {
		if (this->m_Fractionnaire->m_NombreDeBits == p_Valeur.m_Fractionnaire->m_NombreDeBits)
			for (int i = 0; i < this->m_Fractionnaire->m_NombreDeBits && estEgual; i++)
				estEgual = this->m_Fractionnaire->m_Bits[i] == p_Valeur.m_Fractionnaire->m_Bits[i];
		else estEgual = false;
	}
	return estEgual;
}

bool Binaire::operator!=(const Binaire & p_Valeur) const {
	return !(*this == p_Valeur);
}

bool Binaire::operator<(const Binaire & p_Valeur) const {
	bool estPlusPetit = false;
	if (p_Valeur.m_Fractionnaire != NULL || this->m_Fractionnaire != NULL)
		estPlusPetit = this->ToDouble() < p_Valeur.ToDouble();
	else
		estPlusPetit = this->ToInt() < p_Valeur.ToInt();
	return estPlusPetit;
}

bool Binaire::operator<=(const Binaire & p_Valeur) const {
	bool estPlusPetit = false;
	if (p_Valeur.m_Fractionnaire != NULL || this->m_Fractionnaire != NULL)
		estPlusPetit = this->ToDouble() <= p_Valeur.ToDouble();
	else
		estPlusPetit = this->ToInt() <= p_Valeur.ToInt();
	return estPlusPetit;
}

bool Binaire::operator>(const Binaire & p_Valeur) const {
	bool estPlusPetit = false;
	if (p_Valeur.m_Fractionnaire != NULL || this->m_Fractionnaire != NULL)
		estPlusPetit = this->ToDouble() > p_Valeur.ToDouble();
	else
		estPlusPetit = this->ToInt() > p_Valeur.ToInt();
	return estPlusPetit;
}

bool Binaire::operator>=(const Binaire & p_Valeur) const {
	bool estPlusPetit = false;
	if (p_Valeur.m_Fractionnaire != NULL || this->m_Fractionnaire != NULL)
		estPlusPetit = this->ToDouble() >= p_Valeur.ToDouble();
	else
		estPlusPetit = this->ToInt() >= p_Valeur.ToInt();
	return estPlusPetit;
}

Binaire Binaire::operator&(const Binaire & p_Valeur) const {
	Binaire chaineEt(this->ToInt() & p_Valeur.ToInt());
	if (this->m_Fractionnaire != NULL && p_Valeur.m_Fractionnaire != NULL) {
		chaineEt.m_Fractionnaire = new s_Fractionnaire;
		int minBit = Min(this->m_Fractionnaire->m_NombreDeBits, p_Valeur.m_Fractionnaire->m_NombreDeBits);
		chaineEt.m_Fractionnaire->m_MémoiresAllouées = minBit;
		chaineEt.m_Fractionnaire->m_Bits = new bool[minBit];
		chaineEt.m_Fractionnaire->m_NombreDeBits = 0;
		for (int i = 0; i < minBit; i++) {
			chaineEt.m_Fractionnaire->m_Bits[i] = this->m_Fractionnaire->m_Bits[i] & p_Valeur.m_Fractionnaire->m_Bits[i];
			chaineEt.m_Fractionnaire->m_NombreDeBits++;
		}
	}
	chaineEt.SupprimerLesZerosAuDébutDUnePartieEntière();
	return chaineEt;
}

Binaire Binaire::operator|(const Binaire & p_Valeur) const {
	Binaire chaineOu(this->ToInt() | p_Valeur.ToInt());
	if (this->m_Fractionnaire != NULL && p_Valeur.m_Fractionnaire != NULL) {
		chaineOu.m_Fractionnaire = new s_Fractionnaire;
		int minBit = Min(this->m_Fractionnaire->m_NombreDeBits, p_Valeur.m_Fractionnaire->m_NombreDeBits);
		int maxBit = Max(this->m_Fractionnaire->m_NombreDeBits, p_Valeur.m_Fractionnaire->m_NombreDeBits);
		chaineOu.m_Fractionnaire->m_MémoiresAllouées = maxBit;
		chaineOu.m_Fractionnaire->m_Bits = new bool[maxBit];
		chaineOu.m_Fractionnaire->m_NombreDeBits = 0;
		for (int i = 0; i < minBit; i++) {
			chaineOu.m_Fractionnaire->m_Bits[i] = this->m_Fractionnaire->m_Bits[i] | p_Valeur.m_Fractionnaire->m_Bits[i];
			chaineOu.m_Fractionnaire->m_NombreDeBits++;
		}
		for (int i = minBit; i < maxBit; i++) {
			if (this->m_Fractionnaire->m_NombreDeBits > p_Valeur.m_Fractionnaire->m_NombreDeBits)
				chaineOu.m_Fractionnaire->m_Bits[i] = this->m_Fractionnaire->m_Bits[i];
			else chaineOu.m_Fractionnaire->m_Bits[i] = p_Valeur.m_Fractionnaire->m_Bits[i];
			chaineOu.m_Fractionnaire->m_NombreDeBits++;
		}
		chaineOu.SupprimerLesZerosALaFinDUnePartieDecimale();
	}
	else if (this->m_Fractionnaire != NULL || p_Valeur.m_Fractionnaire != NULL) {
		if (this->m_Fractionnaire != NULL) chaineOu.CopierLaPartieDécimale(*this);
		else chaineOu.CopierLaPartieDécimale(p_Valeur);
	}
	return chaineOu;
}

std::ostream& operator<<(std::ostream& p_Flux, const Binaire & p_Valeur) {
	if (p_Valeur.m_EstNégatif) p_Flux << "-";

	if (p_Valeur.m_NombreDeBitsPartieEntière == 0) p_Flux << 0;
	for (int i = p_Valeur.m_NombreDeBitsPartieEntière - 1; i >= 0; i--)
		p_Flux << p_Valeur.m_BitsPartieEntière[i];

	if (p_Valeur.m_Fractionnaire != NULL) {
		p_Flux << ".";
		if (p_Valeur.m_Fractionnaire->m_NombreDeBits == 0) p_Flux << 0;
		for (int i = 0; i < p_Valeur.m_Fractionnaire->m_NombreDeBits; i++)
			p_Flux << p_Valeur.m_Fractionnaire->m_Bits[i];
	}

	return p_Flux;
}

int Binaire::ToInt() const {
	int unEntier = 0;
	for (int i = this->m_NombreDeBitsPartieEntière - 1; i >= 0; i--)
		unEntier += this->m_BitsPartieEntière[i] * (int)pow(2, i);
	if (this->m_EstNégatif) unEntier *= -1;
	return unEntier;
}

double Binaire::ToDouble() const {
	double unDouble = 0.0;
	unDouble = this->ToInt();
	if (this->m_Fractionnaire != NULL)
		for (int i = 0; i < this->m_Fractionnaire->m_NombreDeBits; i++)
			unDouble += this->m_Fractionnaire->m_Bits[i] * pow(2, (-1*(i+1)));
	if (this->m_EstNégatif) unDouble *= -1;
	return unDouble;
}

bool Binaire::EstVide() {
	return (this->m_BitsPartieEntière == NULL) && (this->m_NombreDeBitsPartieEntière == 0)
			&& (this->m_Fractionnaire == NULL);
}

bool Binaire::CheckInvariants() {
	return (this->m_BitsPartieEntière == NULL) == (this->m_NombreDeBitsPartieEntière == 0)
			&& this->m_NombreDeBitsPartieEntière >= 0;
}

// *****************************************************************************************
// Description : Copie la partie décimale du nombre. Va allouée de la nouvelle mémoire
//				 et ne libèrera pas la mémoire si elle était déjà allouée. Attention
//				 avant d'utiliser cette méthode.
//
// *****************************************************************************************
void Binaire::CopierLaPartieDécimale(const Binaire & p_Source) {
	this->m_Fractionnaire = new s_Fractionnaire;
	this->m_Fractionnaire->m_MémoiresAllouées = p_Source.m_Fractionnaire->m_MémoiresAllouées;
	this->m_Fractionnaire->m_NombreDeBits = p_Source.m_Fractionnaire->m_NombreDeBits;
	this->m_Fractionnaire->m_Bits = new bool[this->m_Fractionnaire->m_MémoiresAllouées];
	for (int i = 0; i < this->m_Fractionnaire->m_NombreDeBits; i++)
		this->m_Fractionnaire->m_Bits[i] = p_Source.m_Fractionnaire->m_Bits[i];
}

void Binaire::SupprimerLesZerosAuDébutDUnePartieEntière() {
	if (this->m_NombreDeBitsPartieEntière > 1)
		for (int i = this->m_NombreDeBitsPartieEntière - 1; this->m_BitsPartieEntière[i] == 0 && i > 0; i--)
			this->m_NombreDeBitsPartieEntière--;
}

void Binaire::SupprimerLesZerosALaFinDUnePartieDecimale() {
	for (int i = this->m_Fractionnaire->m_NombreDeBits - 1; this->m_Fractionnaire->m_Bits[i] == 0 && i != 0; i--)
		this->m_Fractionnaire->m_NombreDeBits--;
}

Binaire Masque(int p_NombreDeBitsÀ1) {
	PRÉCONDITION(p_NombreDeBitsÀ1 <= 63 && p_NombreDeBitsÀ1 >= 0);
	Binaire leMasque;
	if (p_NombreDeBitsÀ1 <= 31)
		leMasque = MasquePartieEntière(p_NombreDeBitsÀ1);
	else if (p_NombreDeBitsÀ1 > 31)
		leMasque = MasquePartieEntière(31) | MasqueDécimale(p_NombreDeBitsÀ1 - 31);
	return leMasque;
}

Binaire MasquePartieEntière(int p_NombreDeBitsÀ1) {
	PRÉCONDITION(p_NombreDeBitsÀ1 < 32 && p_NombreDeBitsÀ1 >= 0);
	int valeurDuMasque = 0;
	for (int i = 0; i < p_NombreDeBitsÀ1 && i < 32; i++)
		valeurDuMasque += (int)pow(2, 30 - i);
	// return Binaire(-1 * valeurDuMasque);
	return Binaire(valeurDuMasque);
}

Binaire MasqueDécimale(int p_NombreDeBitsÀ1) {
	PRÉCONDITION(p_NombreDeBitsÀ1 <= 32 && p_NombreDeBitsÀ1 >= 0);
	p_NombreDeBitsÀ1 *= -1;
	double valeurDuMasque = 0.0;
	for (int i = -1; i >= p_NombreDeBitsÀ1; i--)
		valeurDuMasque += pow(2, i);
	return Binaire(valeurDuMasque);
}