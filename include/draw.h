/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#ifndef DEF_HEADER_ESGI_FIGHT_DRAW
#define DEF_HEADER_ESGI_FIGHT_DRAW

#include <SDL/SDL.h>

#include "personnage.h"

extern const int largeur;
extern const int hauteur;
extern const char * titre;
extern SDL_Surface * ecran;

typedef enum {
	NOSHAPE   = 0,
	S_LINE    = 1,
	S_CIRCLE  = 2,
	S_POLYGON = 3
} Shape;

void barre_vie(int sx, int sy, int ex, int ey, int value, int max_value);

void barre_stat(int sx, int sy, int ex, int ey, int value, int start_value, float r, float g, float b);

void Personnage_afficher_stats(const Personnage * perso, int x, int y);

void draw_data(unsigned char * data, int cx, int cy, int s);

int data_load(FILE * fich, unsigned char * draw);

#endif