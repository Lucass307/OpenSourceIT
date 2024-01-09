/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "../include/personnage.h"
#include "../include/game.h"

int main(int argc, char * argv[]) {
	srand(time(NULL));
	/* Création d'une fenêtre SDL : */
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error in SDL_Init : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if((ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		fprintf(stderr, "Error in SDL_SetVideoMode : %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption(titre, NULL);
	
	int active = 1;
	SDL_Event event;
	
	if(! Personnage_load(&joueur, "media/perso/first.perso")
	|| ! Personnage_load(&adversaire, "media/perso/first.perso")) {
		goto end;
	}
	
	int last_mouse_x = 0;
	int last_mouse_y = 0;
	int cap = -1;
	int select_cap = 0;
	
	while(active) {
		
		affichage();
		cap = afficher_choix(last_mouse_x, last_mouse_y, &joueur);
		SDL_Flip(ecran);
		
		while(SDL_PollEvent(&event)) {
			
			switch(event.type) {
				/* Utilisateur clique sur la croix de la fenêtre : */
				case SDL_QUIT : {
					active = 0;
				} break;
				
				/* Utilisateur enfonce une touche du clavier : */
				case SDL_KEYDOWN : {
					switch(event.key.keysym.sym) {
						/* Touche Echap : */
						case SDLK_ESCAPE : {
							active = 0;
						} break;
						
						default : break;
					}
				} break;
				
				case SDL_MOUSEMOTION : {
					last_mouse_x = event.motion.x;
					last_mouse_y = event.motion.y;
				} break;
				
				case SDL_MOUSEBUTTONUP : {
					select_cap = 1;
				} break;
						
				default : break;
			}
		}
		
		if(select_cap && cap >= 0 && cap < joueur.nb_caps) {
			if(joueur.current.vit >= adversaire.current.vit) {
				player_turn(cap);
				opponent_turn();
			} else {
				opponent_turn();
				player_turn(cap);
			}
			active = ! finished();
			
			select_cap = 0;
			
			if(! active) {
				display_winner();
				SDL_Flip(ecran);
				SDL_Delay(2000);
			}
		}
		
		SDL_Delay(1000 / 60);
	}
	
	end:
	
	SDL_FreeSurface(ecran);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}