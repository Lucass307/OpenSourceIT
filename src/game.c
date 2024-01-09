/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#include "../include/game.h"

#include <stdio.h>
#include <string.h>
#include <SDL/SDL_gfxPrimitives.h>

Personnage joueur;
Personnage adversaire;

void affichage() {
	/* Remplissage de l'écran par un gris foncé uniforme : */
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 102));
	
	Personnage_afficher_stats(&adversaire, 2 * largeur / 7, hauteur / 5);
	Personnage_afficher_stats(&joueur, 5 * largeur / 7, 3 * hauteur / 5);
	draw_data(joueur.back, 3 * largeur / 14, 3 * hauteur / 5, hauteur / 3);
	draw_data(adversaire.face, 11 * largeur / 14, hauteur / 5, hauteur / 3);
}

int afficher_choix(int mx, int my, const Personnage  * perso) {
	roundedBoxRGBA(ecran, 0, 3 * hauteur / 4, largeur, hauteur, 15, 204, 204, 204, 255);
	
	int cap = -1;
	int i, x, y;
	if(mx > 0 && mx < largeur && my > 3 * hauteur / 4 && my < hauteur) {
		x = mx / (largeur / 2);
		y = (my - 3 * hauteur / 4) / (hauteur / 8);
		cap = 2 * y + x;
		if(cap < perso->nb_caps) {
			roundedBoxRGBA(ecran, x * largeur / 2, 3 * hauteur / 4 + y * hauteur / 8, (x + 1) * largeur / 2, 3 * hauteur / 4 + (y + 1) * hauteur / 8, 15, 255, 255, 255, 255);
		} else {
			cap = -1;
		}
	}
	for(i = 0; i < perso->nb_caps; ++i) {
		x = i % 2;
		y = i / 2;
		roundedRectangleRGBA(ecran, x * largeur / 2, 3 * hauteur / 4 + y * hauteur / 8, (x + 1) * largeur / 2, 3 * hauteur / 4 + (y + 1) * hauteur / 8, 15, 102, 102, 102, 255);
		stringRGBA(ecran, (x + 0.25) * largeur / 2, 3 * hauteur / 4 + (y + 0.5) * hauteur / 8, perso->capacites[i].nom, 51, 51, 51, 255);
	}
	return cap;
}

void afficher_message(const char * message, const Personnage * self, const Personnage * other) {
	char buffer[256] = "";
	char target[64];
	char * current = NULL;
	for(current = buffer; *message != '\0'; ++message) {
		if(*message != '$') {
			*current = *message;
			++current;
			continue;
		}
		sscanf(message + 1, "%s", target);
		if(strcmp(target, "self") == 0) {
			strcpy(current, self->name);
			current += strlen(current);
			message += strlen(target);
		} else if(strcmp(target, "other") == 0) {
			strcpy(current, other->name);
			current += strlen(current);
			message += strlen(target);
		}
	}
	*current = '\0';
	roundedBoxRGBA(ecran, 0, 3 * hauteur / 4, largeur, hauteur, 15, 204, 204, 204, 255);
	stringRGBA(ecran, largeur / 8, 7 * hauteur / 8, buffer, 51, 51, 51, 255);
}

void applyCapacite(const Capacite * cap, const Personnage * self, const Personnage * other, Stats * self_stats, Stats * other_stats) {
	*self_stats = self->current;
	*other_stats = other->current;
	Action * action = NULL;
	for(action = cap->action; action != NULL; action = action->next) {
		Action_eval(action, self_stats, other_stats);
	}
	/* Vérification que les statistiques restent dans des valeurs pertinentes : */
	if(self_stats->vie < 0) self_stats->vie = 0;
	if(self_stats->atk < self->start.atk / 4) self_stats->atk = self->start.atk / 4;
	if(self_stats->def < self->start.def / 4) self_stats->def = self->start.def / 4;
	if(self_stats->vit < self->start.vit / 4) self_stats->vit = self->start.vit / 4;
	if(self_stats->vie > self->start.vie) self_stats->vie = self->start.vie;
	if(self_stats->atk > self->start.atk * 4) self_stats->atk = self->start.atk * 4;
	if(self_stats->def > self->start.def * 4) self_stats->def = self->start.def * 4;
	if(self_stats->vit > self->start.vit * 4) self_stats->vit = self->start.vit * 4;
	if(other_stats->vie < 0) other_stats->vie = 0;
	if(other_stats->atk < other->start.atk / 4) other_stats->atk = other->start.atk / 4;
	if(other_stats->def < other->start.def / 4) other_stats->def = other->start.def / 4;
	if(other_stats->vit < other->start.vit / 4) other_stats->vit = other->start.vit / 4;
	if(other_stats->vie > other->start.vie) other_stats->vie = other->start.vie;
	if(other_stats->atk > other->start.atk * 4) other_stats->atk = other->start.atk * 4;
	if(other_stats->def > other->start.def * 4) other_stats->def = other->start.def * 4;
	if(other_stats->vit > other->start.vit * 4) other_stats->vit = other->start.vit * 4;
}

void player_turn(int cap) {
	if(finished()) {
		return;
	}
	Stats jc, js, ac, as;
	jc = joueur.current;
	ac = adversaire.current;
	applyCapacite(joueur.capacites + cap, &joueur, &adversaire, &js, &as);
	int i;
	for(i = 0; i < 20; ++i) {
		float t = i / 19.;
		joueur.current = Stats_interpolate(jc, js, t);
		adversaire.current = Stats_interpolate(ac, as, t);
		affichage();
		afficher_message(joueur.capacites[cap].message, &joueur, &adversaire);
		SDL_Flip(ecran);
		SDL_Delay(100);
	}
}

void opponent_turn() {
	if(finished()) {
		return;
	}
	Stats jc, js, ac, as;
	int other_cap = rand() % 2;
	if(other_cap == 1) {
		other_cap += rand() % 3;
	}
	
	jc = joueur.current;
	ac = adversaire.current;
	applyCapacite(adversaire.capacites + other_cap, &adversaire, &joueur, &as, &js);
	int i;
	for(i = 0; i < 20; ++i) {
		float t = i / 19.;
		joueur.current = Stats_interpolate(jc, js, t);
		adversaire.current = Stats_interpolate(ac, as, t);
		affichage();
		afficher_message(adversaire.capacites[other_cap].message, &adversaire, &joueur);
		SDL_Flip(ecran);
		SDL_Delay(100);
	}
}

void display_winner() {
	char buffer[1024];
	if(adversaire.current.vie <= 0) {
		roundedBoxRGBA(ecran, largeur / 8, hauteur / 4, 7 * largeur / 8, 3 * hauteur / 4, 15, 0, 53, 0, 204);
		sprintf(buffer, "Victoire de %s", joueur.name);
	} else {
		roundedBoxRGBA(ecran, largeur / 8, hauteur / 4, 7 * largeur / 8, 3 * hauteur / 4, 15, 53, 0, 0, 204);
		sprintf(buffer, "Defaite de %s", joueur.name);
	}
	stringRGBA(ecran, 2 * largeur / 8, hauteur / 2, buffer, 255, 255, 255, 255);
}

int finished() {
	return joueur.current.vie <= 0 || adversaire.current.vie <= 0;
}