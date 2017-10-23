#include "BasicWindow.h"

#include <stdlib.h>

//destroy window
void destroyWindow(BasicWindow* src){
	if(!src){
		return;
	}
	src->destroyWindow(src);
}
