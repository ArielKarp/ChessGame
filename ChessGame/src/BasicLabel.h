/*
 * BasicLabel.h
 * *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 */

#ifndef BASICLABEL_H_
#define BASICLABEL_H_

#include "Widget.h" //A label is a widget

typedef struct basiclabel_t{
	SDL_Texture* LabelTexture;
	SDL_Renderer* windowRenderer;
	SDL_Rect* location;
}BasicLabel;

/**
 * create basic label
 * @param window render, sdl_rect location and an image
 * @return is a pointer to widget struct
 */
Widget* createBasicLabel(SDL_Renderer* windowRender, SDL_Rect* location,
		const char* Image);

/**
 * destory basic widget
 */
void destroyBasicLabel(Widget*);

/**
 * draw label
 * @param src widget
 * @return void
 */
void drawBasicLabel(Widget* src);

/**
 * is label clicked
 * @param src widget, event and int
 * @return void
 */
void isBasicLabelClicked(Widget* src, SDL_Event* event, int* answer);

/**
 * draw label
 * @param src widget
 * @return void
 */
void copyRectFromGivenLocation(Widget* src, SDL_Rect* rectToCopy) ;

#endif /* BASICLABEL_H_ */
