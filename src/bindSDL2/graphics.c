/*
 * graphics.c
 *
 *  Created on: 2016年4月9日
 *      Author: yami
 */

/**
 * @file	graphics.c
 * @author	yami
 * @date	2016年4月9日
 * @brief
 * 
 */

#include "bindSDL2.h"


struct Graphics{
	struct GraphicsFPtr *fptr;
	SDL_Window	*	window;
	SDL_Renderer*	renderer;
	SDL_Surface*	surface;
	SDL_Texture*	texture;
	const char*		img_name;
};

typedef struct Graphics SDL2Graphics;


void			SDL2Graphics_clean(SDL2Graphics*self);
void			SDL2Graphics_free(SDL2Graphics*self);
int				SDL2Graphics_init(SDL2Graphics*self,const char*fname);
SDL2Graphics*	SDL2Graphics_new(const char*fname);
static 	int		draw(void*v,Rect*src,Rect*dst);
static 	int		draw_dst(void*v,Rect*dst);
static	int		draw_dst_xywh(void*v,int x,int y,int w,int h);
static  int		draw_copy(void*v,int x,int y);
static int		get_width(void*v);
static int		get_height(void*v);


static const struct GraphicsFPtr SDL2Graphics_fptr = {
		.r		=	0,
		.Draw 		=	draw,
		.Draw_dst	=	draw_dst,
		.Draw_dst_xywh	=	draw_dst_xywh,
		.Draw_copy	=	draw_copy,
		.GetWidth	=	get_width,
		.GetHeight	=	get_height,
};


int
SDL2Graphics_init(SDL2Graphics*self,const char*fname){
	if(self){
		self->surface	=	IMG_Load(fname);
		if(self->surface){

			self->img_name	=	fname;
			self->texture	=	SDL_CreateTextureFromSurface(sdl2_window->renderer,self->surface);
			self->fptr		=	(struct GraphicsFPtr*)&SDL2Graphics_fptr;
			self->renderer	=	sdl2_window->renderer;
			return 0;
		}
	}
	return 1;
}

void
SDL2Graphics_clean(SDL2Graphics*self){
	if(self){
		if(self->surface){
			SDL_FreeSurface(self->surface);
			self->surface	=	0;
		}
		if(self->texture){
			SDL_DestroyTexture(self->texture);
			self->texture	=	0;
		}
	}
}

void
SDL2Graphics_free(SDL2Graphics*self){
	if(self){
		SDL2Graphics_clean(self);
		SDL_free(self);
	}
}

SDL2Graphics*
SDL2Graphics_new(const char*fname)
{
	SDL2Graphics *self;
	self = SDL_calloc(1,sizeof(*self));
	if(SDL2Graphics_init(self,fname)){
		SDL2Graphics_clean(self);
		SDL_free(self);
		self	=	0;
	}
	return self;
}

static 	int		draw(void*v,Rect*src,Rect*dst){
	SDL2Graphics *self = v;
	return SDL_RenderCopy(self->renderer,self->texture,(SDL_Rect*)src,(SDL_Rect*)dst);
}
static 	int		draw_dst(void*v,Rect*dst){
	return draw(v,0,dst);
}
static	int		draw_dst_xywh(void*v,int x,int y,int w,int h){
	Rect	dst;
	dst.x	=	x;
	dst.y	=	y;
	dst.w	=	w;
	dst.h	=	h;
	return draw_dst(v,&dst);
}

static int		get_width(void*v){
	SDL2Graphics *self = v;
	return self->surface->w;
}
static int		get_height(void*v){
	SDL2Graphics *self = v;
	return self->surface->h;
}

static  int		draw_copy(void*v,int x,int y){
	SDL2Graphics *self = v;
	Rect	dst;
	dst.x 	= 	x;
	dst.y	=	y;
	dst.w	=	self->surface->w;
	dst.h	=	self->surface->h;
	return draw(self,0,&dst);
}
