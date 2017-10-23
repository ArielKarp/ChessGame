#ifndef WIDGET_H_
#define WIDGET_H_

#include <SDL.h>
#include <SDL_video.h>
#include <stdbool.h>
#include "Common.h"

typedef struct widget_t Widget;
struct widget_t {
	void (*drawWidget)(Widget*);
	void (*isClicked)(Widget*, SDL_Event*, int* answer);
	void (*destroyWidget)(Widget*);
	void* data;
};


/**
 * Destroy widget
 */
void destroyWidget(Widget* src);
#endif
