#pragma once
#include <ostream>

struct s_Fractionnaire {
	int m_M�moiresAllou�es;
	int m_NombreDeBits;
	bool * m_Bits;
};

int TrouverLeNombreDeBits(int p_Entier);
bool * Cr�erUneCha�neBinaire(int p_Entier);
s_Fractionnaire * Cr�erUneChaineBinaireFractionnaire(double p_Double);

// *****************************************************************************
// Description : Accepte des 'int' et des 'double' et les transformes en 
//				 chaine binaire.
//
//				 Si un double est pass� en param�tres, la partie enti�re
//				 va �tre trait� comme un 'int' alors, si le nombre ne peut
//				 pas �tre contenu dans un int il y aura de la perte.
//
//				 Pour la partie d�cimale, plusieurs valeurs ne peuvent �tre
//				 calculer exactement donc ce n'est qu'une approximation.
//				 La partie d�cimale contient 32 bits.
//
// Auteur : Fr�d�ric Jacques
// *****************************************************************************
class Binaire {
public:
	Binaire();
	Binaire(int p_Entier);
	Binaire(double p_Double);
	Binaire(const Binaire & p_Valeur);

	~Binaire();
	void Vider();

	bool GetEstN�gatif() const;
	int GetNombreDeBitsPartieEnti�re() const;
	bool * GetBitsPartieEnt�re() const;
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
	void CopierLaPartieD�cimale(const Binaire & p_Source);
	void SupprimerLesZerosAuD�butDUnePartieEnti�re();
	void SupprimerLesZerosALaFinDUnePartieDecimale();
	

	bool m_EstN�gatif;
	int m_NombreDeBitsPartieEnti�re;
	bool * m_BitsPartieEnti�re;
	s_Fractionnaire * m_Fractionnaire;
};

// *********************************************************************************
// Description : Retourne un masque binaire. Les bits seront mis � 1 � partire
//				 de la plus grande puissance du nombre jusqu'� la plus petit.
//
// Exemple : Le param�tres 31 donne la partie enti�re compl�tement remplis de 1.
//			 Plus grand que 31, la partie d�cimale commence � ce remplire.
//
// PR�CONDITION : Le param�tres doit �tre de 0 � 63.
// **********************************************************************************
Binaire Masque(int p_NombreDeBits�1);
// *********************************************************************************
// Description : Retourne un masque binaire. Les bits seront mis � 1 � partire
//				 de la plus grande puissance.
//
// Exemple : Le param�tres 31 donne la partie enti�re compl�te.
//
// PR�CONDITION : Le param�tres doit �tre de 0 � 31.
// **********************************************************************************
Binaire MasquePartieEnti�re(int p_NombreDeBits�1);
// *********************************************************************************
// Description : Retourne un masque binaire de la partie d�cimale. Les bits seront
//				 mis � 1 � partire de 2^-1 jusqu'a 2^-32
//
// Exemple : Le param�tres 32 donne la partie d�cimale compl�te.
//
// PR�CONDITION : Le param�tres doit �tre de 0 � 32.
// **********************************************************************************
Binaire MasqueD�cimale(int p_NombreDeBits�1);