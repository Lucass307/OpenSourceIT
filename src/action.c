/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#include "../include/action.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int isop(char c) {
	return c == '+'
	|| c == '-'
	|| c == '*'
	|| c == '/';
}

static Operation getop(char c) {
	switch(c) {
		case '=' : return O_AFFECT;
		case '+' : return O_ADD;
		case '-' : return O_SUB;
		case '*' : return O_MUL;
		case '/' : return O_DIV;
		default : return O_NONE;
	}
}

/* Utilise l'idée que l'opérateur classique et celui */
/* d'affectation se suivent dans l'enum. */
static Operation getaffop(char c) {
	Operation op = getop(c);
	if(op > O_AFFECT) {
		return op + 1;
	}
	return O_AFFECT;
}

static int getprio(char c) {
	switch(c) {
		case '=' : return 3;
		case '+' : return 4;
		case '-' : return 4;
		case '*' : return 5;
		case '/' : return 5;
		default : return 0;
	}
}

Target Target_trad(const char * v) {
	if(strcmp(v, "self") == 0) {
		return T_SELF;
	} else if(strcmp(v, "other") == 0) {
		return T_OTHER;
	}
	return T_NONE;
}

Stat Stat_trad(const char * v) {
	if(strcmp(v, "vie") == 0) {
		return S_VIE;
	} else if(strcmp(v, "atk") == 0) {
		return S_ATK;
	} else if(strcmp(v, "def") == 0) {
		return S_DEF;
	} else if(strcmp(v, "vit") == 0) {
		return S_VIT;
	}
	return S_NONE;
}

Action * Action_alloc(Action * next) {
	Action * action = NULL;
	if((action = (Action *)malloc(sizeof(Action))) == NULL) {
		return NULL;
	}
	action->stat = S_VALUE;
	action->target = T_NONE;
	action->op = O_EVAL;
	action->value = 0.f;
	action->left = NULL;
	action->right = NULL;
	action->next = next;
	return action;
}

/* Évalue une opérande atomique : */
static int Action_read_eval(Action ** action, const char * start, const char * end) {
	const char * c;
	char target[50];
	char stat[50];
	if((*action = Action_alloc(*action)) == NULL) {
		fprintf(stderr, "Erreur allocation action.\n");
		exit(EXIT_FAILURE);
	}
	for(c = start; c != end; ++c) {
		/* Cas d'une variable : */
		if(*c == '$') {
			sscanf(c + 1, "%[^.].%s", target, stat);
			(*action)->stat = Stat_trad(stat);
			(*action)->target = Target_trad(target);
			return 1;
		}
	}
	float val;
	/* Lecture d'une constante : */
	if(sscanf(start, "%f", &val) != 1) {
		fprintf(stderr, "Erreur evaluation de \"%s\".", start);
		free(*action);
		*action = NULL;
		return 0;
	}
	(*action)->stat = S_VALUE;
	(*action)->value = val;
	return 1;
}

int Action_read(Action ** action, const char * start, const char * end) {
	int par = 0;
	const char * op_offset = NULL;
	int op_prio = -1;
	const char * c;
	int has_content = 0;
	/* Pour une portion de texte recherche l'opétateur de plus faible priorité : */
	for(c = start; c != end; ++c) {
		/* Compte les parenthèses imbriquées : */
		if(*c == '(') {
			++par;
			continue;
		}
		if(*c == ')') {
			--par;
			continue;
		}
		/* Ignore les espacements : */
		if(*c == ' ' || *c == '\t' || *c == '\n') {
			continue;
		}
		/* Ignore le texte imbriqué dans une parenthèse : */
		if(par) {
			continue;
		}
		has_content = 1;
		/* Trouve un opérateur : */
		if(isop(*c) || *c == '=') {
			int prio = getprio(*c);
			if(op_prio <= 0 || prio < op_prio) {
				op_offset = c;
				op_prio = prio;
			}
			continue;
		}
	}
	/* Si tout est espacement ou parenthèses : */
	if(! has_content) {
		/* Réduit l'expression à l'intérieur de parenthèses : */
		for(; *start != '(' && start < end; ++start);
		for(; *end != ')' && start < end; --end);
		if(start >= end) {
			return 0;
		}
		++start;
		++end;
		return Action_read(action, start, end);
	}
	/* Pas d'opérateur : lecture d'une donnée */
	if(op_prio <= 0) {
		return Action_read_eval(action, start, end);
	}
	if((*action = Action_alloc(*action)) == NULL) {
		fprintf(stderr, "Erreur allocation action.\n");
		exit(EXIT_FAILURE);
	}
	/* Cas particulier d'un opérateur d'affectation : */
	if(*op_offset == '=') {
		(*action)->op = getaffop(*(op_offset - 1));
		/* Cas d'opétateur : */
		if(isop(*(op_offset - 1))) {
			return Action_read(&((*action)->left), start, op_offset - 1)
			&& Action_read(&((*action)->right), op_offset + 1, end);
		}
		/* Cas d'affectation unique : */
		return Action_read(&((*action)->left), start, op_offset)
		&& Action_read(&((*action)->right), op_offset + 1, end);
	}
	/* Cas d'opérateur : */
	(*action)->op = getop(*op_offset);
	return Action_read(&((*action)->left), start, op_offset)
	&& Action_read(&((*action)->right), op_offset + 1, end);
}

void Action_debug(const Action * action) {
	if(! action) {
		return;
	}
	if(action->op == O_EVAL) {
		if(action->stat == S_VALUE) {
			printf("%g", action->value);
			return;
		}
		switch(action->target) {
			case T_SELF : printf("self"); break;
			case T_OTHER : printf("other"); break;
			default : break;
		}
		printf(".");
		switch(action->stat) {
			case S_VIE : printf("vie"); break;
			case S_ATK : printf("atk"); break;
			case S_DEF : printf("def"); break;
			case S_VIT : printf("vit"); break;
			default : break;
		}
		return;
	}
	printf("(");
	Action_debug(action->left);
	switch(action->op) {
		case O_AFFECT : printf(" = "); break;
		case O_ADD : printf(" + "); break;
		case O_SUB : printf(" - "); break;
		case O_MUL : printf(" * "); break;
		case O_DIV : printf(" / "); break;
		case O_AFF_ADD : printf(" += "); break;
		case O_AFF_SUB : printf(" -= "); break;
		case O_AFF_MUL : printf(" *= "); break;
		case O_AFF_DIV : printf(" /= "); break;
		default : break;
	}
	Action_debug(action->right);
	printf(")");
}

/* Évaluation d'une expression d'action : */
float Action_eval(const Action * action, Stats * self_stats, Stats * other_stats) {
	if(! action) {
		return 0.f;
	}
	if(action->op == O_EVAL) {
		if(action->stat == S_VALUE) {
			return action->value;
		}
		Stats * look = NULL;
		switch(action->target) {
			case T_SELF : look = self_stats; break;
			case T_OTHER : look = other_stats; break;
			default : return 0.f;
		}
		switch(action->stat) {
			case S_VIE : return look->vie;
			case S_ATK : return look->atk;
			case S_DEF : return look->def;
			case S_VIT : return look->vit;
			default : break;
		}
		return 0.f;
	}
	if(action->op == O_AFFECT
	|| action->op == O_AFF_ADD
	|| action->op == O_AFF_SUB
	|| action->op == O_AFF_MUL
	|| action->op == O_AFF_DIV) {
		int * left = NULL;
		Action * leftNode = action->left;
		Stats * look = NULL;
		switch(leftNode->target) {
			case T_SELF : look = self_stats; break;
			case T_OTHER : look = other_stats; break;
			default : return 0.f;
		}
		switch(leftNode->stat) {
			case S_VIE : left = &(look->vie); break;
			case S_ATK : left = &(look->atk); break;
			case S_DEF : left = &(look->def); break;
			case S_VIT : left = &(look->vit); break;
			default : return 0.f;
		}
		float right = Action_eval(action->right, self_stats, other_stats);
		switch(action->op) {
			case O_AFFECT : return (*left) = right;
			case O_AFF_ADD : return (*left) += right;
			case O_AFF_SUB : return (*left) -= right;
			case O_AFF_MUL : return (*left) *= right;
			case O_AFF_DIV : return (*left) /= right;
			default : return 0.f;
		}
	} else {
		float left = Action_eval(action->left, self_stats, other_stats);
		float right = Action_eval(action->right, self_stats, other_stats);
		switch(action->op) {
			case O_ADD : return left + right;
			case O_SUB : return left - right;
			case O_MUL : return left * right;
			case O_DIV : return left / right;
			default : return 0.f;
		}
	}
}