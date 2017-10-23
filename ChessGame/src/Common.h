/*
 * Common.h
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <SDL.h>
#include <SDL_video.h>

/**
 * copy rect
 * @param src - SDL_Rect
 * @SDL_Rect
 */
SDL_Rect* copyRect(SDL_Rect* src);

/**
 * Returns SDL
 * @param src - SDL_Rect and ints coordinates
 * @return void
 */
void fillRect(SDL_Rect* src, int x, int y, int h, int w);

#endif /* COMMON_H_ */
