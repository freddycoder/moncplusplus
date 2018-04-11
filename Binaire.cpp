#include <bitset>
#include <math.h>
#include "Assertion.h"
#include "Binaire.h"
#include "MesMath.h"


// *********************************************************************************
// Description : Donne le nombre de bits d'un entier bas� sur le bit � 1 avec la
//				 plus grande valeur.
//
// PR�CONDITION : La valeur doit �tre positive
// 
// Retourne : Pointeur de bool
// *********************************************************************************
int TrouverLeNombreDeBits(int p_Entier) {
	PR�CONDITION(p_Entier >= 0);
	int plusGrandBit = 0;
	std::bitset<32> x(p_Entier);
	for (unsigned int i = 0; i < x.size(); i++)
		if (x[i]) plusGrandBit = i + 1;
	return plusGrandBit;
}

// *********************************************************************************
// Description : Cr�er une chaine binaire avec un entier donn�.
//
// PR�CONDITION : La valeur doit �tre positive
// 
// Retourne : Pointeur de bool
// *********************************************************************************
bool * Cr�erUneCha�neBinaire(int p_Entier) {
	PR�CONDITION(p_Entier >= 0);
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
// Description : Cr�er une chaine binaire de la partie d�cimale d'un nombre.
//
// PR�CONDITION : La valeur doit �tre positive
// 
// Retourne : Pointeur sur une structure s_Fractionnaire
// *********************************************************************************
s_Fractionnaire* Cr�erUneChaineBinaireFractionnaire(double p_Double) {
	PR�CONDITION(p_Double >= 0);
	s_Fractionnaire * s_Decimal = new s_Fractionnaire;
	s_Decimal->m_M�moiresAllou�es = 8;
	s_Decimal->m_NombreDeBits = 0;
	s_Decimal->m_Bits = new bool[s_Decimal->m_M�moiresAllou�es];

	for (int i = 0; i < s_Decimal->m_M�moiresAllou�es && p_Double != 1.0 && p_Double != 0.0; i++) {
		s_Decimal->m_NombreDeBits++;
		if (p_Double > 1.0) p_Double = p_Double - (int)p_Double;
		p_Double *= 2;

		if (p_Double >= 1) s_Decimal->m_Bits[i] = 1;
		else s_Decimal->m_Bits[i] = 0;

		if (i == s_Decimal->m_M�moiresAllou�es - 1 && i != 31) {
			bool * temporaire = new bool[s_Decimal->m_M�moiresAllou�es];
			for (int i = 0; i < s_Decimal->m_M�moiresAllou�es; i++)
				temporaire[i] = s_Decimal->m_Bits[i];

			delete[] s_Decimal->m_Bits;
			s_Decimal->m_Bits = NULL;
			s_Decimal->m_M�moiresAllou�es += 8;
			s_Decimal->m_Bits = new bool[s_Decimal->m_M�moiresAllou�es];

			for (int i = 0; i <= s_Decimal->m_NombreDeBits; i++)
				s_Decimal->m_Bits[i] = temporaire[i];

			delete[] temporaire;
		}
	}
	return s_Decimal;
}

Binaire::Binaire() {
	this->m_EstN�gatif = false;
	this->m_NombreDeBitsPartieEnti�re = 0;
	this->m_BitsPartieEnti�re = NULL;
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
	this->m_EstN�gatif = false;
	this->m_NombreDeBitsPartieEnti�re = 0;
	delete[] this->m_BitsPartieEnti�re;
	this->m_BitsPartieEnti�re = NULL;
	if (this->m_Fractionnaire != NULL) {
		delete[] this->m_Fractionnaire->m_Bits;
		delete this->m_Fractionnaire;
		this->m_Fractionnaire = NULL;
	}
	POSTCONDITION(this->EstVide());
}

bool Binaire::GetEstN�gatif() const {
	return this->m_EstN�gatif;
}

int Binaire::GetNombreDeBitsPartieEnti�re() const {
	return this->m_NombreDeBitsPartieEnti�re;
}

bool * Binaire::GetBitsPartieEnt�re() const {
	return this->m_BitsPartieEnti�re;
}

int Binaire::GetNombreDeBitsPartieFractionnaire() const {
	return this->m_Fractionnaire->m_NombreDeBits;
}

bool * Binaire::GetBitsPartieFractionnaire() const {
	return this->m_Fractionnaire->m_Bits;
}

void Binaire::operator=(int p_Entier) {
	if (!this->EstVide() && this->m_NombreDeBitsPartieEnti�re >= 0) this->Vider();
	if (p_Entier < 0) this->m_EstN�gatif = true; else this->m_EstN�gatif = false;
	this->m_NombreDeBitsPartieEnti�re = TrouverLeNombreDeBits(ValeurAbsolue(p_Entier));
	this->m_BitsPartieEnti�re = Cr�erUneCha�neBinaire(ValeurAbsolue(p_Entier));
	this->m_Fractionnaire = NULL;
}

void Binaire::operator=(double p_Double) {
	if (!this->EstVide() && this->m_NombreDeBitsPartieEnti�re >= 0) this->Vider();
	if (p_Double < 0) this->m_EstN�gatif = true; else this->m_EstN�gatif = false;
	this->m_NombreDeBitsPartieEnti�re = TrouverLeNombreDeBits(ValeurAbsolue((int)p_Double));
	this->m_BitsPartieEnti�re = Cr�erUneCha�neBinaire(ValeurAbsolue((int)p_Double));
	this->m_Fractionnaire = Cr�erUneChaineBinaireFractionnaire(ValeurAbsolue(p_Double));
}

void Binaire::operator=(const Binaire & p_Valeur) {
	if (!this->EstVide() && this->m_NombreDeBitsPartieEnti�re >= 0) this->Vider();
	this->m_EstN�gatif = p_Valeur.m_EstN�gatif;
	this->m_NombreDeBitsPartieEnti�re = p_Valeur.m_NombreDeBitsPartieEnti�re;
	if (p_Valeur.m_BitsPartieEnti�re != NULL) {
		this->m_BitsPartieEnti�re = new bool[this->m_NombreDeBitsPartieEnti�re];
		for (int i = 0; i < this->m_NombreDeBitsPartieEnti�re; i++)
			this->m_BitsPartieEnti�re[i] = p_Valeur.m_BitsPartieEnti�re[i];
	}
	else this->m_BitsPartieEnti�re = NULL;
	if (p_Valeur.m_Fractionnaire != NULL) {
		this->CopierLaPartieD�cimale(p_Valeur);
	}
	else this->m_Fractionnaire = NULL;
	POSTCONDITION(*this == p_Valeur);
}

Binaire Binaire::operator!() const {
	Binaire inverse = MasquePartieEnti�re(31);
	//inverse.m_EstN�gatif = !this->m_EstN�gatif;
	for (int i = this->m_NombreDeBitsPartieEnti�re - 1; i >= 0; i--)
		inverse.m_BitsPartieEnti�re[i] = !this->m_BitsPartieEnti�re[i];

	inverse.SupprimerLesZerosAuD�butDUnePartieEnti�re();

	if (this->m_Fractionnaire != NULL) {
		inverse = inverse | MasqueD�cimale(32);
		for (int i = 0; i < this->m_Fractionnaire->m_NombreDeBits; i++)
			inverse.m_Fractionnaire->m_Bits[i] = !this->m_Fractionnaire->m_Bits[i];
		inverse.SupprimerLesZerosALaFinDUnePartieDecimale();
	}
	
	return inverse;
}

bool Binaire::operator==(const Binaire & p_Valeur) const{
	bool estEgual = this->m_EstN�gatif == p_Valeur.m_EstN�gatif;
	if (this->m_NombreDeBitsPartieEnti�re == p_Valeur.m_NombreDeBitsPartieEnti�re)
		for (int i = 0; i < this->m_NombreDeBitsPartieEnti�re && estEgual; i++)
			estEgual = this->m_BitsPartieEnti�re[i] == p_Valeur.m_BitsPartieEnti�re[i];
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
		chaineEt.m_Fractionnaire->m_M�moiresAllou�es = minBit;
		chaineEt.m_Fractionnaire->m_Bits = new bool[minBit];
		chaineEt.m_Fractionnaire->m_NombreDeBits = 0;
		for (int i = 0; i < minBit; i++) {
			chaineEt.m_Fractionnaire->m_Bits[i] = this->m_Fractionnaire->m_Bits[i] & p_Valeur.m_Fractionnaire->m_Bits[i];
			chaineEt.m_Fractionnaire->m_NombreDeBits++;
		}
	}
	chaineEt.SupprimerLesZerosAuD�butDUnePartieEnti�re();
	return chaineEt;
}

Binaire Binaire::operator|(const Binaire & p_Valeur) const {
	Binaire chaineOu(this->ToInt() | p_Valeur.ToInt());
	if (this->m_Fractionnaire != NULL && p_Valeur.m_Fractionnaire != NULL) {
		chaineOu.m_Fractionnaire = new s_Fractionnaire;
		int minBit = Min(this->m_Fractionnaire->m_NombreDeBits, p_Valeur.m_Fractionnaire->m_NombreDeBits);
		int maxBit = Max(this->m_Fractionnaire->m_NombreDeBits, p_Valeur.m_Fractionnaire->m_NombreDeBits);
		chaineOu.m_Fractionnaire->m_M�moiresAllou�es = maxBit;
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
		if (this->m_Fractionnaire != NULL) chaineOu.CopierLaPartieD�cimale(*this);
		else chaineOu.CopierLaPartieD�cimale(p_Valeur);
	}
	return chaineOu;
}

std::ostream& operator<<(std::ostream& p_Flux, const Binaire & p_Valeur) {
	if (p_Valeur.m_EstN�gatif) p_Flux << "-";

	if (p_Valeur.m_NombreDeBitsPartieEnti�re == 0) p_Flux << 0;
	for (int i = p_Valeur.m_NombreDeBitsPartieEnti�re - 1; i >= 0; i--)
		p_Flux << p_Valeur.m_BitsPartieEnti�re[i];

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
	for (int i = this->m_NombreDeBitsPartieEnti�re - 1; i >= 0; i--)
		unEntier += this->m_BitsPartieEnti�re[i] * (int)pow(2, i);
	if (this->m_EstN�gatif) unEntier *= -1;
	return unEntier;
}

double Binaire::ToDouble() const {
	double unDouble = 0.0;
	unDouble = this->ToInt();
	if (this->m_Fractionnaire != NULL)
		for (int i = 0; i < this->m_Fractionnaire->m_NombreDeBits; i++)
			unDouble += this->m_Fractionnaire->m_Bits[i] * pow(2, (-1*(i+1)));
	if (this->m_EstN�gatif) unDouble *= -1;
	return unDouble;
}

bool Binaire::EstVide() {
	return (this->m_BitsPartieEnti�re == NULL) && (this->m_NombreDeBitsPartieEnti�re == 0)
			&& (this->m_Fractionnaire == NULL);
}

bool Binaire::CheckInvariants() {
	return (this->m_BitsPartieEnti�re == NULL) == (this->m_NombreDeBitsPartieEnti�re == 0)
			&& this->m_NombreDeBitsPartieEnti�re >= 0;
}

// *****************************************************************************************
// Description : Copie la partie d�cimale du nombre. Va allou�e de la nouvelle m�moire
//				 et ne lib�rera pas la m�moire si elle �tait d�j� allou�e. Attention
//				 avant d'utiliser cette m�thode.
//
// *****************************************************************************************
void Binaire::CopierLaPartieD�cimale(const Binaire & p_Source) {
	this->m_Fractionnaire = new s_Fractionnaire;
	this->m_Fractionnaire->m_M�moiresAllou�es = p_Source.m_Fractionnaire->m_M�moiresAllou�es;
	this->m_Fractionnaire->m_NombreDeBits = p_Source.m_Fractionnaire->m_NombreDeBits;
	this->m_Fractionnaire->m_Bits = new bool[this->m_Fractionnaire->m_M�moiresAllou�es];
	for (int i = 0; i < this->m_Fractionnaire->m_NombreDeBits; i++)
		this->m_Fractionnaire->m_Bits[i] = p_Source.m_Fractionnaire->m_Bits[i];
}

void Binaire::SupprimerLesZerosAuD�butDUnePartieEnti�re() {
	if (this->m_NombreDeBitsPartieEnti�re > 1)
		for (int i = this->m_NombreDeBitsPartieEnti�re - 1; this->m_BitsPartieEnti�re[i] == 0 && i > 0; i--)
			this->m_NombreDeBitsPartieEnti�re--;
}

void Binaire::SupprimerLesZerosALaFinDUnePartieDecimale() {
	for (int i = this->m_Fractionnaire->m_NombreDeBits - 1; this->m_Fractionnaire->m_Bits[i] == 0 && i != 0; i--)
		this->m_Fractionnaire->m_NombreDeBits--;
}

Binaire Masque(int p_NombreDeBits�1) {
	PR�CONDITION(p_NombreDeBits�1 <= 63 && p_NombreDeBits�1 >= 0);
	Binaire leMasque;
	if (p_NombreDeBits�1 <= 31)
		leMasque = MasquePartieEnti�re(p_NombreDeBits�1);
	else if (p_NombreDeBits�1 > 31)
		leMasque = MasquePartieEnti�re(31) | MasqueD�cimale(p_NombreDeBits�1 - 31);
	return leMasque;
}

Binaire MasquePartieEnti�re(int p_NombreDeBits�1) {
	PR�CONDITION(p_NombreDeBits�1 < 32 && p_NombreDeBits�1 >= 0);
	int valeurDuMasque = 0;
	for (int i = 0; i < p_NombreDeBits�1 && i < 32; i++)
		valeurDuMasque += (int)pow(2, 30 - i);
	// return Binaire(-1 * valeurDuMasque);
	return Binaire(valeurDuMasque);
}

Binaire MasqueD�cimale(int p_NombreDeBits�1) {
	PR�CONDITION(p_NombreDeBits�1 <= 32 && p_NombreDeBits�1 >= 0);
	p_NombreDeBits�1 *= -1;
	double valeurDuMasque = 0.0;
	for (int i = -1; i >= p_NombreDeBits�1; i--)
		valeurDuMasque += pow(2, i);
	return Binaire(valeurDuMasque);
}