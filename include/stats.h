/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#ifndef DEF_HEADER_ESGI_FIGHT_STATS
#define DEF_HEADER_ESGI_FIGHT_STATS

typedef struct Stats Stats;
struct Stats {
	int vie;
	int atk;
	int def;
	int vit;
};

typedef enum {
	S_NONE  = 0,
	S_VALUE = 1,
	S_VIE   = 2,
	S_ATK   = 3,
	S_DEF   = 4,
	S_VIT   = 5
} Stat;

Stats Stats_interpolate(Stats first, Stats second, float t);

#endif