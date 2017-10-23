/*
 * BasicButton.h
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 */

#ifndef BASICBUTTON_H_
#define BASICBUTTON_H_

#include "Widget.h" //A button is a widget also

typedef struct basicbutton_t{
	SDL_Texture* ActiveButtonTexture;
	SDL_Texture* NotActiveButtonTexture;
	SDL_Renderer* windowRenderer;
	SDL_Rect* location;
	bool isActive;
}BasicButton;

//You need a create function:
Widget* createBasicButton(SDL_Renderer* windowRender, SDL_Rect* location,
		const char* activeImage, const char* inActiveImage, bool isActive);

//You need this function in order to destroy all data Associate with a button:
void destroyBasicButton(Widget*);

/**
 * Returns void
 * @param src -widget
 * @return
 */
void drawBasicButton(Widget* src);

/**
 * Returns void
 * @param src and active or not
 * @return
 */
void changeActive(Widget* src, bool active);

/**
 * Returns void
 * @param src -widget, SDL EVENT
 * @return
 */
void isBasicButtonClicked(Widget* src, SDL_Event* event, int* answer);

/**
 * @param src -widget
 * @return int
 */
int getActiveStatus(Widget* src);


#endif /* BASICBUTTON_H_ */
