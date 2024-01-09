/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#ifndef DEF_HEADER_ESGI_FIGHT_PERSONNAGE
#define DEF_HEADER_ESGI_FIGHT_PERSONNAGE

#include "stats.h"
#include "capacite.h"

typedef struct Personnage Personnage;
struct Personnage {
	char name[50];
	Stats start;
	Stats current;
	unsigned char face[4096];
	unsigned char back[4096];
	Capacite capacites[4];
	int nb_caps;
};

Personnage Personnage_creer(const char * name, Stats stats);

int Personnage_load(Personnage * perso, const char * path);

#endif