/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#ifndef DEF_HEADER_ESGI_FIGHT_ACTION
#define DEF_HEADER_ESGI_FIGHT_ACTION

#include "stats.h"

typedef enum {
	T_NONE  = 0,
	T_SELF  = 1,
	T_OTHER = 2
} Target;

typedef enum {
	O_NONE    = 0,
	O_EVAL    = 1,
	O_AFFECT  = 2,
	O_ADD     = 3,
	O_AFF_ADD = 4,
	O_SUB     = 5,
	O_AFF_SUB = 6,
	O_MUL     = 7,
	O_AFF_MUL = 8,
	O_DIV     = 9,
	O_AFF_DIV = 10
} Operation;

typedef struct Action Action;
struct Action {
	Stat stat;
	Target target;
	float value;
	Operation op;
	Action * left;
	Action * right;
	Action * next;
};

Target Target_trad(const char * v);

Stat Stat_trad(const char * v);

Action * Action_alloc(Action * next);

int Action_read(Action ** action, const char * start, const char * end);

void Action_debug(const Action * action);

float Action_eval(const Action * action, Stats * self_stats, Stats * other_stats);

#endif