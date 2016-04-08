/*
 * loop.c
 *
 *  Created on: 2016年4月8日
 *      Author: yami
 */

/**
 * @file	loop.c
 * @author	yami
 * @date	2016年4月8日
 * @brief
 * 
 */

#include <mixmworld.h>
#include "bindSDL2.h"

static int loop()
{
	while(!sdl2_window->quit)
	{
		while(SDL_PollEvent(sdl2_window->event))
		{
			SDL_Event	*e = sdl2_window->event;
			if(e->type==SDL_QUIT)
				sdl2_window->quit	=	1;
				break;
		}
		SDL_RenderPresent(sdl2_window->renderer);
	}
	return 0;
}

/**
 * 游戏循环
 * @return	0，成功，非0失败
 */
int BindSDL2_loop()
{
	return loop();
}


