/*
 * test02.c
 *
 *  Created on: 2016年4月9日
 *      Author: yami
 */

/**
 * @file	test02.c
 * @author	yami
 * @date	2016年4月9日
 * @brief
 * 
 */

#include <mixmworld.h>

#include "../src/bindSDL2/bindSDL2.h"


int	test02();
int test02_clean();
static const struct WindowUpdateFPtr updatePtr;
static int update(void*v,void*v1);
static int render(void*v,void*v1);
static int input(void*v,void*v1,void*e);
static int init(void*v);



static const struct WindowUpdateFPtr updatePtr = {
		0,
		.update	=	update,
		.render = 	render,
		.input	=	input,
};


static union TestUpdate{
	struct WindowUpdateFPtr		*fptr;
	struct WindowUpdate 		u;
	struct{
		struct WindowUpdate base;
		int x,y,z;
		SDL_Texture	*texture;
		SDL_Surface	*surface;
		const char		*textureName;
	};
}updateData = {
				.base = {(struct WindowUpdateFPtr*)&updatePtr}
				,
				.x  = 20,
				.y  = 30,
				.textureName	=	"test01.png",
};

int test02()
{
	BindSDL2_set_mainUpdate(&updateData.u);
	return 0;
}

static int init(void*v){
	union TestUpdate *a = v;
	if(!a->surface)
		a->surface	=	IMG_Load(a->textureName);
	if(a->surface){
		a->texture	=	SDL_CreateTextureFromSurface(sdl2_window->renderer,a->surface);
	}
	return 0;
}

static int update(void*v,void*v1){
	union TestUpdate *a = v;

	__builtin_printf("%s :%s  .x = %d\n",__FILE__,__FUNCTION__,a->x);
	return 0;
}
static int render(void*v,void*v1){
	union TestUpdate *a = v;
	if(!a->texture){
		init(a);
	}
	SDL_Rect	rect;
	rect.x	=	0;
	rect.y	=	0;
	rect.w	=	a->surface->w;
	rect.h	=	a->surface->h;
	SDL_RenderCopy(sdl2_window->renderer,a->texture,0,&rect);
	__builtin_printf("%s :%s  .x = %d\n",__FILE__,__FUNCTION__,a->x);
	return 0;
}
static int input(void*v,void*v1,void*e){
	union TestUpdate *a = v;
	__builtin_printf("%s :%s  .x = %d\n",__FILE__,__FUNCTION__,a->x);
	return 0;
}

int test02_clean(){
	if(updateData.surface)
	{
		SDL_FreeSurface(updateData.surface);
		updateData.surface = 0;
	}
	if(updateData.texture){
		SDL_DestroyTexture(updateData.texture);
		updateData.texture = 0;
	}
	return 0;
}
