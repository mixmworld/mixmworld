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


/*
测试 Graphics类型


*/

#include <mixmworld.h>

#include "../src/bindSDL2/bindSDL2.h"


int	test03();
int test03_clean();
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
//		SDL_Texture	*texture;
//		SDL_Surface	*surface;
		Graphics		*graphics;
		const char		*textureName;
	};
}updateData = {
				.base = {(struct WindowUpdateFPtr*)&updatePtr}
				,
				.x  = 20,
				.y  = 30,
				.textureName	=	"test01.png",
};

int test03()
{
	BindSDL2_set_mainUpdate(&updateData.u);
	return 0;
}

static int init(void*v){
	union TestUpdate *a = v;
	a->graphics	=	SDL2Graphics_new(a->textureName);
	return 0;
}

static int update(void*v,void*v1){
	union TestUpdate *a = v;

	__builtin_printf("%s :%s  .x = %d\n",__FILE__,__FUNCTION__,a->x);
	return 0;
}
static int render(void*v,void*v1){
	union TestUpdate *a = v;
	if(!a->graphics){
		init(a);
	}
//	Rect	rect;
//	rect.x	=	0;
//	rect.y	=	0;
//	rect.w	=	Graphics_GetWidth(a->graphics);
//	rect.h	=	Graphics_GetHeight(a->graphics);
	//SDL_RenderCopy(sdl2_window->renderer,a->texture,0,&rect);
	//Graphics_Draw(a->graphics,0,&rect);
	Graphics_Draw_copy(a->graphics,0,0);
	__builtin_printf("%s :%s  .x = %d\n",__FILE__,__FUNCTION__,a->x);
	return 0;
}
static int input(void*v,void*v1,void*e){
	union TestUpdate *a = v;
	__builtin_printf("%s :%s  .x = %d\n",__FILE__,__FUNCTION__,a->x);
	return 0;
}

int test03_clean(){
	if(updateData.graphics){
		SDL2Graphics_free(updateData.graphics);
	}
//	if(updateData.surface)
//	{
//		SDL_FreeSurface(updateData.surface);
//		updateData.surface = 0;
//	}
//	if(updateData.texture){
//		SDL_DestroyTexture(updateData.texture);
//		updateData.texture = 0;
//	}
	return 0;
}
