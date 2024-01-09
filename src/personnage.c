/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#include "../include/personnage.h"

#include <stdio.h>
#include <string.h>
#include "../include/draw.h"

Personnage Personnage_creer(const char * name, Stats stats) {
	Personnage perso;
	strcpy(perso.name, name);
	perso.start = stats;
	perso.current = stats;
	return perso;
}

static int cap_load(FILE * fich, Personnage * perso) {
	char buffer[50];
	int i = 0;
	for(;;) {
		fscanf(fich, "%s", buffer);
		if(strcmp(buffer, "}") == 0) {
			break;
		} else if(strcmp(buffer, "load") == 0) {
			fscanf(fich, "%s", buffer);
			if(! Capacite_load(buffer, perso->capacites + i)) {
				fprintf(stderr, "Erreur lecture capacite \"%s\"", buffer);
			}
			Capacite_debug(perso->capacites + i);
			++i;
		}
	}
	perso->nb_caps = i;
	return 1;
}

int Personnage_load(Personnage * perso, const char * path) {
	FILE * fich = NULL;
	if((fich = fopen(path, "r")) == NULL) {
		fprintf(stderr, "Erreur lecture d\'un personnage \"%s\"\n", path);
		return 0;
	}
	if(fscanf(fich, "name : %s\n", perso->name) != 1
	|| fscanf(fich, "vie : %d\n", &(perso->start.vie)) != 1
	|| fscanf(fich, "atk : %d\n", &(perso->start.atk)) != 1
	|| fscanf(fich, "def : %d\n", &(perso->start.def)) != 1
	|| fscanf(fich, "vit : %d\n", &(perso->start.vit)) != 1) {
		fprintf(stderr, "Erreur de lecture des stats pour \"%s\"\n", path);
		goto error;
	}
	perso->current = perso->start;
	
	unsigned char * draw = perso->face;
	fscanf(fich, "face : {\n");
	
	if(! data_load(fich, draw)) {
		fprintf(stderr, "Erreur lecture dessin de face pour \"%s\"\n", path);
		goto error;
	}
	
	draw = perso->back;
	fscanf(fich, "back : {\n");
	
	if(! data_load(fich, draw)) {
		fprintf(stderr, "Erreur lecture dessin de dos pour \"%s\"\n", path);
		goto error;
	}
	
	fscanf(fich, "capacities : {\n");
	
	if(! cap_load(fich, perso)) {
		fprintf(stderr, "Erreur lecture dessin de dos pour \"%s\"\n", path);
		goto error;
	}
	
	fclose(fich);
	
	printf("\"%s\" chargé.\n", path);
	return 1;
	
	error :
	fclose(fich);
	return 0;
}