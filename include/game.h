/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#ifndef DEF_HEADER_ESGI_FIGHT_GAME
#define DEF_HEADER_ESGI_FIGHT_GAME

#include "personnage.h"
#include "capacite.h"
#include "stats.h"
#include "draw.h"

extern Personnage joueur;
extern Personnage adversaire;

void affichage();

int afficher_choix(int mx, int my, const Personnage  * perso);

void afficher_message(const char * message, const Personnage * self, const Personnage * other);

void applyCapacite(const Capacite * cap, const Personnage * self, const Personnage * other, Stats * self_stats, Stats * other_stats);

void player_turn(int cap);

void opponent_turn();

void display_winner();

int finished();

#endif