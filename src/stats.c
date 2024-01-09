/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#include "../include/stats.h"

/* Interpolation de statistiques pour animation : */
Stats Stats_interpolate(Stats first, Stats second, float t) {
	return (Stats){
		.vie = first.vie * (1 - t) + second.vie * t,
		.atk = first.atk * (1 - t) + second.atk * t,
		.def = first.def * (1 - t) + second.def * t,
		.vit = first.vit * (1 - t) + second.vit * t
	};
}