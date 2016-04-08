/*
 * init.c
 *
 *  Created on: 2016年4月8日
 *      Author: yami
 */

/**
 * @file	init.c
 * @author	yami
 * @date	2016年4月8日
 * @brief
 * 
 */


#include <mixmworld.h>
#include "bindSDL2.h"


typedef struct SDL2Window SDL2Window;

SDL2Window			*sdl2_window;


static int sdl2_clean();
static int sdl2_window_init();
static int sdl2_init();

static
int
openGLBind_init(void){
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);
	SDL_GL_SetSwapInterval(1);
	return 0;
}

static int sdl2_window_init()
{
	openGLBind_init();
	sdl2_window		=	SDL_calloc(1,sizeof(*sdl2_window));
	//创建窗体，opengl并且显示
	sdl2_window->window	=	SDL_CreateWindow(
			mixmworld_get_game_name(),
			100,100,
			mixmworld_get_width(),
			mixmworld_get_heitht(),
			SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN
			);
	if(!sdl2_window->window){
		return -1;
	}

	//创建渲染器
	sdl2_window->renderer	=	SDL_CreateRenderer(sdl2_window->window,-1,
			//SDL_RENDERER_ACCELERATED
			SDL_RENDERER_PRESENTVSYNC
			|SDL_RENDERER_TARGETTEXTURE
			);
	if(!sdl2_window->renderer){
		sdl2_clean();
		return -2;
	}

	SDL_SetRenderDrawBlendMode(sdl2_window->renderer,SDL_BLENDMODE_BLEND);

	//创建GL
	sdl2_window->context	=	SDL_GL_CreateContext(sdl2_window->window);

	//初始化事件
	sdl2_window->event	=	SDL_calloc(1,sizeof(*sdl2_window->event));
	return 0;
}

static int sdl2_init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING)){
		return -1;
	}
	if(!IMG_Init(IMG_INIT_PNG|IMG_INIT_WEBP))
	{
		SDL_Quit();
		return -1;
	}
	if(TTF_Init()){
		return -1;
	}
	if(!Mix_Init(MIX_INIT_OGG)){
		return -1;
	}
	sdl2_window_init();
	return 0;
}

static int sdl2_clean()
{
	if(sdl2_window){
		if(sdl2_window->event){
			SDL_free(sdl2_window->event);
		}
		if(sdl2_window->context){
			SDL_GL_DeleteContext(sdl2_window->context);
		}
		if(sdl2_window->renderer){
			SDL_DestroyRenderer(sdl2_window->renderer);
		}
		if(sdl2_window->window){
			SDL_DestroyWindow(sdl2_window->window);
		}
		SDL_free(sdl2_window);
		sdl2_window	=	0;
	}
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	return 0;
}


/**
 * 初始化绑定的SDL2
 * @return	0表示成功，非0失败
 */
int	BindSDL2_init()
{
	return sdl2_init();
}

/**
 * 清理绑定的SDL2
 * @return
 */
int BindSDL2_clean()
{
	return sdl2_clean();
}
