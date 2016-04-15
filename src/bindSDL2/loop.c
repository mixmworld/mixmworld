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
		SDL_Event	*e = sdl2_window->event;
		while(SDL_PollEvent(sdl2_window->event))
		{
			//输入事件，假设有多个时，会依次调用这个函数，
			//
			if(sdl2_window->mainUpdate){
				if(sdl2_window->mainUpdate->fptr){
					if(sdl2_window->mainUpdate->fptr->input){
						sdl2_window->mainUpdate->fptr->input(
								sdl2_window->mainUpdate,
								0,
								e
								);
					}
				}
			}


			if(e->type==SDL_QUIT)
				sdl2_window->quit	=	1;
				break;
		}
		const Uint8* key = SDL_GetKeyboardState(0);
		if(key[SDL_SCANCODE_LEFT]||
				key[SDL_SCANCODE_RIGHT]||
				key[SDL_SCANCODE_UP]||
				key[SDL_SCANCODE_DOWN]
			   ){
			CollisionDetection_input(0,e);
		}

		//更新函数
		if(sdl2_window->mainUpdate){
			if(sdl2_window->mainUpdate->fptr){
				if(sdl2_window->mainUpdate->fptr->update){
					sdl2_window->mainUpdate->fptr->update(
							sdl2_window->mainUpdate,
							0
							);
				}
			}
		}
		CollisionDetection_update(0);

		SDL_RenderClear(sdl2_window->renderer);


		//渲染函数
		if(sdl2_window->mainUpdate){
			if(sdl2_window->mainUpdate->fptr){
				if(sdl2_window->mainUpdate->fptr->render){
					sdl2_window->mainUpdate->fptr->render(
							sdl2_window->mainUpdate,
							0
							);
				}
			}
		}

		CollisionDetection_render(0);

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


