#ifndef BASICWINDOW_H_
#define BASICWINDOW_H_

#include <SDL.h>
#include <SDL_video.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define WHITE_COLOR 255
#define BACKROUND "graphics/background_scratches.bmp"
#define BACK_BTN "graphics/back_pushed.bmp"
#define BACK_BTN_NOT_SELECTED "graphics/back_not.bmp"
#define BACK_BTN_HEIGHT 53
#define BACK_BTN_WIDTH  53

typedef struct basic_window_t BasicWindow;
struct basic_window_t {
	void* data;
	void (*drawWindow)(BasicWindow*);
	void (*handleEventWindow)(BasicWindow*, SDL_Event*, int*);
	void (*destroyWindow)(BasicWindow*);
};

/**
 * Destroy window function
 */
void destroyWindow(BasicWindow* src);

#endif
