/*
 * mario_sprite.c
 *
 *  Created on: 2016年4月14日
 *      Author: yami
 */

/**
 * @file	mario_sprite.c
 * @author	yami
 * @date	2016年4月14日
 * @brief
 * 
 */


#include <mixmworld.h>
#include "../../src/graphics.h"

int mario_sprite_init();
static int priority();
static int collision_detection(void*v,Rect*r);
static int collision_range(void*v,Rect *r);
static Rect* get_collision_rangePtr(void*v);
static int get_type(void*v);
static int get_type2(void*v);
static int collision_detection_proc(void*v1);


static struct WindowUpdateFPtr* get_update_ptr(void*v);
static int render(void*v,void*v2);
static int input(void*v,void*v2,void*e);
static int update(void*v,void*v2);


/*



*/


static Graphics *g = 0;
static
CollisionDetectionFPtr  fptr={
		.get_version = 0,
		.get_FPtr_size = 0,
		.get_eee = 0,
		.init = 0,
		.free = 0,
		.get_show_priority = priority,
		.collision_detection = collision_detection,
		.collision_range = collision_range,
		.get_collision_rangePtr = get_collision_rangePtr,
		.get_type = get_type,
		.get_type2 = get_type2,
		.get_update_ptr = get_update_ptr,
		.collision_detection_proc = collision_detection_proc,
};

static struct{
	CollisionDetectionFPtr *fptr;
}data = {
		&fptr,
};
static Rect rect={
		0,0,
		16,32,
};

static struct{
	int status;
	struct{
		float x,y,w,h;
	}offset;
}status;

enum{
	status_none,
	status_jump	=1,
	status_down	=2,
};



int mario_sprite_init()
{
	CollisionDetection_add((CollisionDetection*)&data);
	return 0;
}

static int priority(){
	return 0;
}

static int collision_detection(void*v,Rect*r){
	if(v==&data)
	{
		return -1;
	}
	return -1;
}
static int collision_range(void*v,Rect *r){
	if(r){
		*r = rect;
		return 0;
	}
	return 1;
}
static Rect* get_collision_rangePtr(void*v){
	return &rect;
}
static int get_type(void*v){
	return 0x100; //test
}
static int get_type2(void*v){
	return 0x100; //test
}


static struct WindowUpdateFPtr* get_update_ptr(void*v){
	static struct WindowUpdateFPtr ptr = {
			.update = update,
			.render = render,
			.input = input,
	};
	return &ptr;
}



static int render(void*v,void*v2){
	if(!g){
		g = (void*)SDL2Graphics_new("test02a.png");
	}
	else{
		Graphics_Draw_copy(g,rect.x,rect.y);
	}
	return 0;
}

#include <SDL.h>


static int input(void*v,void*v2,void*e){
	CollisionDetection *cc;
	int flg = 0;
	int itr = 0;
	int kk;
	int value = 0;
	Rect r = rect;
	const Uint8* key = SDL_GetKeyboardState(0);
	if(key[SDL_SCANCODE_RIGHT]){
		r.x += 1;
		//__builtin_printf("%s\n",__FUNCTION__);
		kk = 1;
		value = -1;
	}
	else if(key[SDL_SCANCODE_LEFT]){
		r.x -= 1;
		kk=1;
		value = 1;
	}
	if(key[SDL_SCANCODE_Z]){
		if(!(status.status&status_down))
		{
			if(!(status.status&status_jump))
			{
				status.offset.y = -3.1;
				status.status   |= status_jump;
			}
		};
	}
	else if(key[SDL_SCANCODE_X]){
		return 1;
//		r.y += 6;
//		kk=2;
//		value = -1;
	}

	while((cc=CollisionDetection_iterator(&itr)))
	{
		if(cc==(void*)&data)
			continue;
		if(cc->fptr){
			if(cc->fptr->collision_detection){
				if(cc->fptr->collision_detection(cc,&r)>0)
				{
					while(cc->fptr->collision_detection(cc,&r)>0){
						if(kk==1){
							r.x += value;
							//__builtin_printf("%s\n",__FUNCTION__);
						}
						else if(kk==2){
							r.y += value;
						}
					}
					//__builtin_printf("%s\n",__FUNCTION__);
					flg |= 2;
				}
				else{
					flg |= 1;
				}
			}
		}
	}

	rect = r;


	return 0;
}
static int update(void*v,void*v2){
	return 0;
}

static int collision_detection_proc(void*v1){
	CollisionDetection *cc;
	int flg = 0;
	int itr = 0;
	Rect r = rect;

	while((cc=CollisionDetection_iterator(&itr)))
	{
		if(cc==(void*)&data)
			continue;
		if(cc->fptr){
			if(cc->fptr->collision_detection){



				if(status.status&(status_jump|status_down)){
					//跳起状态
					//和落下状态
					r.y += status.offset.y;
					status.offset.y += 0.1;
					if(status.status&status_jump)
					{
						if(status.offset.y > 0)
						{
							status.status &= ~status_jump;
							status.status |= status_down;
						}
					}
					else if(status.status&status_down)
					{

					}
				}



				if(cc->fptr->collision_detection(cc,&r)<0){
					//没有碰撞物体
					if(!(status.status&(status_jump|status_down)))
					{
						status.status 		|= 	status_down;
						status.offset.y		=	1.0f;
					}
				}
				else{
					//有碰撞物
					if(status.status&status_down)
					{
						status.status	&=	(~status_down);
						status.offset.y		=	0;
						while((cc->fptr->collision_detection(cc,&r)>0)){
							r.y -= 1;
						}
					}
					else if(status.status&status_jump)
					{
						status.status	&=	(~status_jump);
						status.status	|=  status_jump;
						status.offset.y		=	-status.offset.y;
						while((cc->fptr->collision_detection(cc,&r)>0)){
							r.y += 1;
						}
					}

					while((cc->fptr->collision_detection(cc,&r)>0)){
						r.y -= 1;
					}

				}
			}
		}
	}

	rect = r;


	return 0;
}
