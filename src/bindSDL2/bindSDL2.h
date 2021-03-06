/*
 * bindSDL2.h
 *
 *  Created on: 2016年4月8日
 *      Author: yami
 */

/**
 * @file	bindSDL2.h
 * @author	yami
 * @date	2016年4月8日
 * @brief
 * 
 */

#ifndef SRC_BINDSDL2_BINDSDL2_H_
#define SRC_BINDSDL2_BINDSDL2_H_

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <mixmworld_update.h>
#include "../graphics.h"



struct SDL2Window{
	void*			fptr;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_GLContext	*context;
	SDL_Event		*event;
	uint32_t		status;
	uint8_t			quit;
	uint8_t			reserve[3];		//align 4

	//2016-04-09 16:29:40
	struct WindowUpdate	*mainUpdate;
};

extern struct SDL2Window			*sdl2_window;



int	BindSDL2_init();
int BindSDL2_loop();
int BindSDL2_clean();

//2016-04-09 16:31:54
int	BindSDL2_set_mainUpdate(struct WindowUpdate*mainUpdate);


#endif /* SRC_BINDSDL2_BINDSDL2_H_ */
