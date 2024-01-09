/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#include "../include/capacite.h"

#include <stdio.h>
#include <string.h>

int Capacite_update(Capacite * cap, const char * data) {
	char buffer[128];
	if(strlen(data) < 3) {
		return 1;
	}
	sscanf(data, "%s", buffer);
	if(strcmp(buffer, "action") == 0) {
		return Action_read(&(cap->action), data + strlen(buffer) + 1, data + strlen(data));
	} else if(strcmp(buffer, "message") == 0) {
		strcpy(cap->message, data + strlen(buffer) + 1);
	} else if(strcmp(buffer, "nom") == 0) {
		strcpy(cap->nom, data + strlen(buffer) + 1);
	}
	return 1;
}

int Capacite_load(const char * path, Capacite * cap) {
	FILE * file = NULL;
	if((file = fopen(path, "r")) == NULL) {
		return 0;
	}
	char buffer[1024];
	int i;
	strcpy(cap->message, "");
	cap->action = NULL;
	int car;
	while((car = fgetc(file)) != EOF) {
		i = 0;
		do {
			buffer[i++] = car;
			car = fgetc(file);
		} while(car != EOF && car != '\n');
		buffer[i] = '\0';
		Capacite_update(cap, buffer);
	}
	fclose(file);
	return 1;
}

void Capacite_debug(const Capacite * cap) {
	printf("Action : {\n");
	printf(" - nom : %s\n", cap->nom);
	printf(" - message : %s\n", cap->message);
	Action * action;
	for(action = cap->action; action != NULL; action = action->next) {
		printf(" - action : "); Action_debug(action); printf("\n");
	}
	printf("}\n");
}