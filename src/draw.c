/**
 * ESGI : Cours de Langage C avancé de Kevin TRANCHO.
 * Correction du mini-projet du CC1 (alternants)
 */

#include "../include/draw.h"

#include <stdio.h>
#include <SDL/SDL_gfxPrimitives.h>

const int largeur = 800;
const int hauteur = 600;
const char * titre = "ESGI fight";
SDL_Surface * ecran = NULL;

void barre_vie(int sx, int sy, int ex, int ey, int value, int max_value) {
	roundedBoxRGBA(ecran, sx, sy, ex, ey, 3, 51, 51, 51, 255);
	int i;
	for(i = 1; i < 4; ++i) {
		vlineRGBA(ecran, sx + (i / 4.) * (ex - sx), sy, ey, 102, 102, 102, 255);
	}
	if(value <= 0) {
		return;
	}
	float t = (float)value / max_value;
	float r, g, b;
	if(t > 0.6) {
		r = 0.; g = 1.; b = 0.; 
	} else if(t > 0.3) {
		r = (0.6 - t) / 0.3; g = 1.; b = 0.;
	} else {
		r = 1.; g = t / 0.3; b = 0.;
	}
	roundedBoxRGBA(ecran, sx, sy, sx + t * (ex - sx), ey, 3, 51 + 153 * r, 51 + 153 * g, 51 + 153 * b, 255);
	if(t * (ex - sx) > 6) {
		roundedBoxRGBA(ecran, sx + 3, sy + 3, sx + t * (ex - sx) - 3, ey - 3, 2, 51 + 102 * r, 51 + 102 * g, 51 + 102 * b, 255);
	}
	char buffer[100];
	sprintf(buffer, "%d / %d", value, max_value);
	stringRGBA(ecran, sx + 15, sy + 2, buffer, 255, 255, 255, 255);
}

void barre_stat(int sx, int sy, int ex, int ey, int value, int start_value, float r, float g, float b) {
	roundedBoxRGBA(ecran, sx, sy, ex, ey, 3, 102, 102, 102, 255);
	int i;
	for(i = 1; i < 6; ++i) {
		vlineRGBA(ecran, sx + (pow(2., i) / pow(2., 6.)) * (ex - sx), sy, ey, 153, 153, 153, 255);
	}
	start_value *= 4;
	if(value > start_value) {
		value = start_value;
	}
	float t = (float)value / start_value;
	roundedBoxRGBA(ecran, sx, sy, sx + t * (ex - sx), ey, 3, 51 + 153 * r, 51 + 153 * g, 51 + 153 * b, 255);
	if(t * (ex - sx) > 6) {
		roundedBoxRGBA(ecran, sx + 3, sy + 3, sx + t * (ex - sx) - 3, ey - 3, 2, 51 + 102 * r, 51 + 102 * g, 51 + 102 * b, 255);
	}
	char buffer[100];
	sprintf(buffer, "%d", value);
	stringRGBA(ecran, sx + 15, sy + 2, buffer, 255, 255, 255, 255);
}

void Personnage_afficher_stats(const Personnage * perso, int x, int y) {
	int sx = x - largeur / 4;
	int sy = y - hauteur / 9;
	int ex = x + largeur / 4;
	int ey = y + hauteur / 13;
	roundedBoxRGBA(ecran, sx, sy, ex, ey, 20, 255, 255, 255, 255);
	roundedBoxRGBA(ecran, sx + 5, sy + 5, ex - 5, ey - 5, 15, 204, 204, 204, 255);
	stringRGBA(ecran, sx + 15, sy + 15, perso->name, 51, 51, 51, 255);
	hlineRGBA(ecran, sx + 25, ex - 25, sy + 28, 51, 51, 51, 255);
	stringRGBA(ecran, sx + 15, sy + 35, "Vie : ", 51, 51, 51, 255);
	barre_vie(sx + 60, sy + 32, ex - 15, sy + 44, perso->current.vie, perso->start.vie);
	stringRGBA(ecran, sx + 15, sy + 50, "Attaque : ", 51, 51, 51, 255);
	barre_stat(sx + 100, sy + 47, ex - 15, sy + 59, perso->current.atk, perso->start.atk, 1., 0., 0.);
	stringRGBA(ecran, sx + 15, sy + 65, "Defense : ", 51, 51, 51, 255);
	barre_stat(sx + 100, sy + 62, ex - 15, sy + 74, perso->current.def, perso->start.def, 0., 0., 1.);
	stringRGBA(ecran, sx + 15, sy + 80, "Vitesse : ", 51, 51, 51, 255);
	barre_stat(sx + 100, sy + 77, ex - 15, sy + 89, perso->current.vit, perso->start.vit, 1., 1., 0.);
}

/* Modélisation d'un dessin en mémoire : */

typedef struct Color Color;
struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

typedef struct Point Point;
struct Point {
	short int x;
	short int y;
};

/* Différentes formes possibles : */

typedef struct Circle Circle;
struct Circle {
	Point center;
	short int r;
};

typedef struct Line Line;
struct Line {
	Point start;
	Point end;
	short int r;
};

typedef struct Polygon Polygon;
struct Polygon {
	unsigned char count;
	Point * data;
};

/* Représentation d'une forme : */

typedef struct ShapeData ShapeData;
struct ShapeData {
	Shape shape;
	Color color;
	union {
		Circle circle;
		Line line;
		Polygon polygon;
	};
	ShapeData * next;
};

void draw_data(unsigned char * raw_data, int cx, int cy, int s) {
	ShapeData * data = (ShapeData *)raw_data;
	for(; data->shape != NOSHAPE; data = data->next) {
		switch(data->shape) {
			case S_CIRCLE : {
				filledCircleRGBA(ecran, data->circle.center.x * s / 100. + cx, data->circle.center.y * s / 100. + cy, data->circle.r * s / 100.,
					data->color.r, data->color.g, data->color.b, data->color.a);
			} break;
			
			case S_LINE : {
				thickLineRGBA(ecran, data->line.start.x * s / 100. + cx, data->line.start.y * s / 100. + cy, 
					data->line.end.x * s / 100. + cx, data->line.end.y * s / 100. + cy, data->line.r * s / 100.,
					data->color.r, data->color.g, data->color.b, data->color.a);
			} break;
			
			case S_POLYGON : {
				Sint16 xs[32];
				Sint16 ys[32];
				int n = data->polygon.count, i;
				for(i = 0; i < n; ++i) {
					xs[i] = data->polygon.data[i].x;
					ys[i] = data->polygon.data[i].y;
					xs[i] = cx + xs[i] * s / 100.;
					ys[i] = cy + ys[i] * s / 100.;
				}
				filledPolygonRGBA(ecran, xs, ys, n, data->color.r, data->color.g, data->color.b, data->color.a);
			} break;
			
			default : break;
		}
	}
}

int data_load(FILE * fich, unsigned char * draw) {
	char buffer[50];
	ShapeData * data = (ShapeData *)draw;
	for(;;) {
		if(fscanf(fich, "%s", buffer) != 1) {
			fprintf(stderr, "Erreur lecture commande\n");
			return 0;
		}
		if(strcmp(buffer, "}") == 0) {
			break;
		} else if(strcmp(buffer, "circle") == 0) {
			int x, y, d;
			int r, g, b, a;
			if(fscanf(fich, "%d, %d, %d rgba %d, %d, %d, %d\n", &x, &y, &d, &r, &g, &b, &a) != 7) {
				fprintf(stderr, "Erreur lecture cercle\n");
				return 0;
			}
			data->shape = S_CIRCLE;
			data->circle.center.x = x;
			data->circle.center.y = y;
			data->circle.r = d;
			data->color.r = r;
			data->color.g = g;
			data->color.b = b;
			data->color.a = a;
			data->next = data + 1;
			data = data->next;
		} else if(strcmp(buffer, "line") == 0) {
			int sx, sy, ex, ey, d;
			int r, g, b, a;
			if(fscanf(fich, "%d, %d, %d, %d, %d rgba %d, %d, %d, %d\n", &sx, &sy, &ex, &ey, &d, &r, &g, &b, &a) != 9) {
				fprintf(stderr, "Erreur lecture line\n");
				return 0;
			}
			data->shape = S_LINE;
			data->line.start.x = sx;
			data->line.start.y = sy;
			data->line.end.x = ex;
			data->line.end.y = ey;
			data->line.r = d;
			data->color.r = r;
			data->color.g = g;
			data->color.b = b;
			data->color.a = a;
			data->next = data + 1;
			data = data->next;
		} else if(strcmp(buffer, "polygon") == 0) {
			Sint16 xs[32];
			Sint16 ys[32];
			int n, x, y, i;
			int r, g, b, a;
			if(fscanf(fich, "%d %d, %d", &n, &x, &y) != 3) {
				fprintf(stderr, "Erreur lecture polygon : init\n");
				return 0;
			}
			xs[0] = x;
			ys[0] = y;
			for(i = 1; i < n; ++i) {
				if(fscanf(fich, ", %d, %d", &x, &y) != 2) {
					fprintf(stderr, "Erreur lecture polygon : vertex %d\n", i);
					return 0;
				}
				xs[i] = x;
				ys[i] = y;
			}
			if(fscanf(fich, " rgba %d, %d, %d, %d\n", &r, &g, &b, &a) != 4) {
				fprintf(stderr, "Erreur lecture polygon : color\n");
				return 0;
			}
			data->shape = S_POLYGON;
			data->polygon.count = n;
			data->color.r = r;
			data->color.g = g;
			data->color.b = b;
			data->color.a = a;
			data->polygon.data = (Point *)(data + 1);
			Point * points = data->polygon.data;
			for(i = 0; i < n; ++i) {
				points[i].x = xs[i];
				points[i].y = ys[i];
			}
			data->next = (ShapeData *)(((Point *)(data + 1)) + n);
			data = data->next;
		}
	}
	data->shape = NOSHAPE;
	data->next = NULL;
	return 1;
}