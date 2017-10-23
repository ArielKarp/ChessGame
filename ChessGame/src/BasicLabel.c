/*
 * BasicLabel.c
 *
 *  Created on: Sep 15, 2017
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 */


#include "BasicLabel.h"

#include <stdlib.h>


Widget* createBasicLabel(SDL_Renderer* windowRender, SDL_Rect* location,
		const char* Image) {
	if (windowRender == NULL || location == NULL || Image == NULL) {
		return NULL;
	}
	//Allocate data
	Widget* res = (Widget*) malloc(sizeof(Widget));
	BasicLabel* data = (BasicLabel*) malloc(sizeof(BasicLabel));
	SDL_Surface* loadingSurface = SDL_LoadBMP(Image); //We use the surface as a temp var;
	SDL_Texture* LabelTexture = SDL_CreateTextureFromSurface(
			windowRender, loadingSurface);
	int setBlend = SDL_SetTextureBlendMode(LabelTexture, SDL_BLENDMODE_BLEND);
	if (res == NULL || data == NULL || loadingSurface == NULL
			|| LabelTexture == NULL ||  setBlend != 0) {
		free(res);
		free(data);
		SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
		SDL_DestroyTexture(LabelTexture); ////It is safe to pass NULL
		return NULL;
	}
	SDL_FreeSurface(loadingSurface); //Surface is not actually needed after texture is created
	data->LabelTexture = LabelTexture;
	data->location = copyRect(location);
	data->windowRenderer = windowRender;
	res->destroyWidget = destroyBasicLabel;
	res->drawWidget = drawBasicLabel;
	res->data = data;
	return res;
}

void destroyBasicLabel(Widget* src) {
	if (src == NULL) {
		return;
	}
	BasicLabel* castData = (BasicLabel*) src->data;
	free(castData->location);
	SDL_DestroyTexture(castData->LabelTexture);
	free(castData);
	free(src);
}

void drawBasicLabel(Widget* src) {
	if (src == NULL) {
		return;
	}
	BasicLabel* castData = (BasicLabel*) src->data;
	SDL_RenderCopy(castData->windowRenderer, castData->LabelTexture,
			NULL, castData->location);
}


void isBasicLabelClicked(Widget* src, SDL_Event* event, int* answer) {
	if (src == NULL || event == NULL) {
		return;
	}
	BasicLabel* castData = (BasicLabel*) src->data;
	SDL_Point point;
	point.x = event->button.x;
	point.y = event->button.y;
	// prepare answer to false
	*answer = 0;
	if (SDL_PointInRect(&point, castData->location)) {
		*answer = 1;
	}
	return;

}

void copyRectFromGivenLocation(Widget* src, SDL_Rect* rectToCopy) {
	if (NULL == src || NULL == rectToCopy) {
		return;
	}
	BasicLabel* data = (BasicLabel*) src->data;
	SDL_Rect* dest = data->location;
	if (NULL == dest) {
		return;
	}
	// Copy data
	dest->h = rectToCopy->h;
	dest->w = rectToCopy->w;
	dest->x = rectToCopy->x;
	dest->y = rectToCopy->y;
}
