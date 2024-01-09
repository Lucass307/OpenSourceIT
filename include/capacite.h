/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#ifndef DEF_HEADER_ESGI_FIGHT_CAPACITE
#define DEF_HEADER_ESGI_FIGHT_CAPACITE

#include "action.h"

typedef struct Capacite Capacite;
struct Capacite {
	char nom[64];
	char message[1024];
	Action * action;
};

int Capacite_update(Capacite * cap, const char * data);

int Capacite_load(const char * path, Capacite * cap);

void Capacite_debug(const Capacite * cap);

#endif