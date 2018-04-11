#include "AG.h"
#include "Binaire.h"

int Reproduction(int p_PremièreValeur, int p_DeuxièmeValeur, int p_BitDeCroisement) {
	Binaire un = p_PremièreValeur;
	Binaire deux = p_DeuxièmeValeur;
	Binaire masque = MasquePartieEntière(32 - p_BitDeCroisement);
	return ((un & masque) | (deux & (!masque))).ToInt();
}

