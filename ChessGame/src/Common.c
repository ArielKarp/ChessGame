/*
 * Common.c
 *
 *  Created on: Sep 16, 2017
 *      Author: ariel
 */

#include "Common.h"


SDL_Rect* copyRect(SDL_Rect* src) {
	if (src == NULL) {
		return NULL;
	}
	SDL_Rect* res = malloc(sizeof(SDL_Rect));
	if (res == NULL) {
		return NULL;
	}
	res->h = src->h;
	res->w = src->w;
	res->x = src->x;
	res->y = src->y;
	return res;
}

void fillRect(SDL_Rect* src, int x, int y, int h, int w) {
	if (src == NULL) {
		return;
	}
	src->h = h;
	src->w = w;
	src->x = x;
	src->y = y;
	return;
}
