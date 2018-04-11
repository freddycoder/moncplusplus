#include "AG.h"
#include "Binaire.h"

int Reproduction(int p_Premi�reValeur, int p_Deuxi�meValeur, int p_BitDeCroisement) {
	Binaire un = p_Premi�reValeur;
	Binaire deux = p_Deuxi�meValeur;
	Binaire masque = MasquePartieEnti�re(32 - p_BitDeCroisement);
	return ((un & masque) | (deux & (!masque))).ToInt();
}

