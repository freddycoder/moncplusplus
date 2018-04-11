#pragma once
#include <ostream>

struct s_Fractionnaire {
	int m_MémoiresAllouées;
	int m_NombreDeBits;
	bool * m_Bits;
};

int TrouverLeNombreDeBits(int p_Entier);
bool * CréerUneChaîneBinaire(int p_Entier);
s_Fractionnaire * CréerUneChaineBinaireFractionnaire(double p_Double);

// *****************************************************************************
// Description : Accepte des 'int' et des 'double' et les transformes en 
//				 chaine binaire.
//
//				 Si un double est passé en paramètres, la partie entière
//				 va être traité comme un 'int' alors, si le nombre ne peut
//				 pas être contenu dans un int il y aura de la perte.
//
//				 Pour la partie décimale, plusieurs valeurs ne peuvent être
//				 calculer exactement donc ce n'est qu'une approximation.
//				 La partie décimale contient 32 bits.
//
// Auteur : Frédéric Jacques
// *****************************************************************************
class Binaire {
public:
	Binaire();
	Binaire(int p_Entier);
	Binaire(double p_Double);
	Binaire(const Binaire & p_Valeur);

	~Binaire();
	void Vider();

	bool GetEstNégatif() const;
	int GetNombreDeBitsPartieEntière() const;
	bool * GetBitsPartieEntère() const;
	int GetNombreDeBitsPartieFractionnaire() const;
	bool * GetBitsPartieFractionnaire() const;

	void operator=(int p_Entier);
	void operator=(double p_Double);
	void operator=(const Binaire & p_Valeur);
	Binaire operator!() const;
	bool operator==(const Binaire & p_Valeur) const;
	bool operator!=(const Binaire & p_Valeur) const;
	bool operator<(const Binaire & p_Valeur) const;
	bool operator<=(const Binaire & p_Valeur) const;
	bool operator>(const Binaire & p_Valeur) const;
	bool operator>=(const Binaire & p_Valeur) const;
	Binaire operator&(const Binaire & p_Valeur) const;
	Binaire operator|(const Binaire & p_Valeur) const;

	friend std::ostream& operator<<(std::ostream& p_Flux, const Binaire & p_Valeur);

	int ToInt() const;
	double ToDouble() const;

private:
	bool CheckInvariants();
	bool EstVide();
	void CopierLaPartieDécimale(const Binaire & p_Source);
	void SupprimerLesZerosAuDébutDUnePartieEntière();
	void SupprimerLesZerosALaFinDUnePartieDecimale();
	

	bool m_EstNégatif;
	int m_NombreDeBitsPartieEntière;
	bool * m_BitsPartieEntière;
	s_Fractionnaire * m_Fractionnaire;
};

// *********************************************************************************
// Description : Retourne un masque binaire. Les bits seront mis à 1 à partire
//				 de la plus grande puissance du nombre jusqu'à la plus petit.
//
// Exemple : Le paramètres 31 donne la partie entière complètement remplis de 1.
//			 Plus grand que 31, la partie décimale commence à ce remplire.
//
// PRÉCONDITION : Le paramètres doit être de 0 à 63.
// **********************************************************************************
Binaire Masque(int p_NombreDeBitsÀ1);
// *********************************************************************************
// Description : Retourne un masque binaire. Les bits seront mis à 1 à partire
//				 de la plus grande puissance.
//
// Exemple : Le paramètres 31 donne la partie entière complète.
//
// PRÉCONDITION : Le paramètres doit être de 0 à 31.
// **********************************************************************************
Binaire MasquePartieEntière(int p_NombreDeBitsÀ1);
// *********************************************************************************
// Description : Retourne un masque binaire de la partie décimale. Les bits seront
//				 mis à 1 à partire de 2^-1 jusqu'a 2^-32
//
// Exemple : Le paramètres 32 donne la partie décimale complète.
//
// PRÉCONDITION : Le paramètres doit être de 0 à 32.
// **********************************************************************************
Binaire MasqueDécimale(int p_NombreDeBitsÀ1);