/*
 * BasicButton.c
 *
 *  Created on: Sep 9, 2017
 *      Author: ariel
 */
#include <stdlib.h>
#include "BasicButton.h"

Widget* createBasicButton(SDL_Renderer* windowRender, SDL_Rect* location,
		const char* activeImage, const char* inActiveImage, bool isActive) {
	if (windowRender == NULL || location == NULL || activeImage == NULL
			|| inActiveImage == NULL) {
		return NULL;
	}
	//Allocate widget - free if failed
	Widget* res = (Widget*) malloc(sizeof(Widget));
	if (NULL == res) {
		return NULL;
	}
	//Allocate button - free if failed
	BasicButton* data = (BasicButton*) malloc(sizeof(BasicButton));
	if (NULL == data) {
		free(res);
		return NULL;
	}
	//We use the surface as a temp var;
	SDL_Surface* loadingSurfaceActive = SDL_LoadBMP(activeImage);
	if (NULL == loadingSurfaceActive) {
		free(res);
		free(data);
		return NULL;
	}
	SDL_Surface* loadingSurfaceInActive = SDL_LoadBMP(inActiveImage);
	if (NULL == loadingSurfaceInActive) {
		free(res);
		free(data);
		return NULL;
	}
	SDL_Texture* buttonTextureActive = SDL_CreateTextureFromSurface(
			windowRender, loadingSurfaceActive);
	if (NULL == buttonTextureActive) {
		free(res);
		free(data);
		SDL_FreeSurface(loadingSurfaceInActive); //It is safe to pass NULL
		return NULL;
	}
	//set texture
	int setBlendActive = SDL_SetTextureBlendMode(buttonTextureActive, SDL_BLENDMODE_BLEND);
	if (setBlendActive != 0) {
		free(res);
		free(data);
		SDL_FreeSurface(loadingSurfaceInActive); //It is safe to pass NULL
		SDL_FreeSurface(loadingSurfaceActive); //It is safe to pass NULL
		return NULL;
	}
	SDL_Texture* buttonTextureInActive = SDL_CreateTextureFromSurface(
			windowRender, loadingSurfaceInActive);
	if (NULL == buttonTextureInActive) {
		free(res);
		free(data);
		SDL_FreeSurface(loadingSurfaceInActive); //It is safe to pass NULL
		SDL_FreeSurface(loadingSurfaceActive); //It is safe to pass NULL
		return NULL;
	}
	int setBlendNotActive = SDL_SetTextureBlendMode(buttonTextureActive, SDL_BLENDMODE_BLEND);
	if (setBlendNotActive != 0) {
		free(res);
		free(data);
		SDL_FreeSurface(loadingSurfaceActive); //It is safe to pass NULL
		SDL_DestroyTexture(buttonTextureActive); //It is safe to pass NULL
		SDL_DestroyTexture(buttonTextureInActive); //It is safe to pass NULL

		return NULL;
	}

	SDL_FreeSurface(loadingSurfaceActive); //Surface is not actually needed after texture is created
	SDL_FreeSurface(loadingSurfaceInActive);
	data->isActive = isActive;
	data->ActiveButtonTexture = buttonTextureActive;
	data->NotActiveButtonTexture = buttonTextureInActive;
	data->location = copyRect(location);
	data->windowRenderer = windowRender;
	res->destroyWidget = destroyBasicButton;
	res->drawWidget = drawBasicButton;
	res->isClicked = isBasicButtonClicked;
	res->data = data;
	return res;
}

//destroy all data Associate with a button
void destroyBasicButton(Widget* src) {
	if (src == NULL) {
		return;
	}
	BasicButton* castData = (BasicButton*) src->data;
	free(castData->location);
	SDL_DestroyTexture(castData->ActiveButtonTexture);
	SDL_DestroyTexture(castData->NotActiveButtonTexture);
	free(castData);
	free(src);
}

//drawing widget
void drawBasicButton(Widget* src) {
	if (src == NULL) {
		return;
	}
	BasicButton* castData = (BasicButton*) src->data;
	if (castData->isActive == true) {
		SDL_RenderCopy(castData->windowRenderer, castData->ActiveButtonTexture,
			NULL, castData->location);
	}
	else {
		SDL_RenderCopy(castData->windowRenderer, castData->NotActiveButtonTexture,
			NULL, castData->location);
	}
}

void changeActive(Widget* src, bool active) {
	if (src == NULL) {
		return;
	}
	BasicButton* castData = (BasicButton*) src->data;
	castData->isActive = active;
}

int getActiveStatus(Widget* src) {
	if (src == NULL) {
		return - 1;
	}
	BasicButton* castData = (BasicButton*) src->data;
	if (castData->isActive == true) {
		return 1;
	}
	return 0;
}

void isBasicButtonClicked(Widget* src, SDL_Event* event, int* answer) {
	if (src == NULL || event == NULL) {
		return; //Better to return an error value
	}
	BasicButton* castData = (BasicButton*) src->data;
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
