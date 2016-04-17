/*
 * mario.c
 *
 *  Created on: 2016年4月14日
 *      Author: yami
 */

/**
 * @file	mario.c
 * @author	yami
 * @date	2016年4月14日
 * @brief
 * 
 */


#include <mixmworld.h>
#include "../../src/graphics.h"

#include "mario.h"

int mario_init();
static int priority();
static int collision_detection(void*v,Rect*r);
static int collision_range(void*v,Rect *r);
static Rect* get_collision_rangePtr(void*v);
static int get_type(void*v);
static int get_type2(void*v);


static struct WindowUpdateFPtr* get_update_ptr(void*v);
static int render(void*v,void*v2);
static int input(void*v,void*v2,void*e);
static int update(void*v,void*v2);

static void* process(void*v1,void*sender,uint32_t type,uint32_t flg /*, ... */);

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
		.process = process,

};

static struct{
	CollisionDetectionFPtr *fptr;
}data = {
		&fptr,
};
static Rect rect={
		0,0,
		256,224,
};
static Graphics *enermy = 0;
static Rect enermyRect = {72+16+16+16,199 - 16,16,16};
static frame_count = 0;


int mario_init()
{
	CollisionDetection_add((CollisionDetection*)&data);
	return 0;
}

static int priority(){
	return 0;
}

static void* process(void*v1,void*sender,uint32_t type,uint32_t flg /*, ... */){
	if(type==mario_enemy_proc_death){
		enermyRect.y = 250;
	}
	return 0;
}

static int collision_detection_enermy(void*v1,Rect*r)
{
	Rect *ptr = &enermyRect;
	if(
			(r->x+r->w <=ptr->x)||  //left
			( r->x>=ptr->x+ptr->w)  //right
			)
	{
		return -1;
	}
	if(
			(r->y+r->h<=ptr->y)||  	//top
			(r->y>=ptr->y+ptr->h)		//bottom
	)
	{
		return -1;
	}
	return mario_enemy;
}


static int collision_detection(void*v,Rect*r){
	static Rect list[] = {
			{	0,200,
				256,24,
			},
			{
				23+1,136,
				32-2,16,

			},
			{
				71+1,136,
				16-2,16,
			},
			{
				151+1,168,
				32-2,32
			},
			{
				55+1,72,
				16-2,16,
			},
	};
	if(r){
		Rect *ptr = list;
		char *end = (char*)list;
		int  type;
		end += sizeof(list);
		if((type=collision_detection_enermy(v,r))>0){
			return type;
		}
		for(;ptr<(Rect*)end;ptr++)
		{
			if(
					(r->x+r->w <=ptr->x)||  //left
					( r->x>=ptr->x+ptr->w)  //right
					)
			{
				continue;
			}
			if(
					(r->y+r->h<=ptr->y)||  	//top
					(r->y>=ptr->y+ptr->h)		//bottom
			)
			{
				continue;
			}
			return mario_obstacles;
		}
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
	frame_count++;
	if(!g){
		g = (void*)SDL2Graphics_new("test02.png");
	}
	else{
		Graphics_Draw_copy(g,0,0);
	}
	if(!enermy){
		enermy = (void*)SDL2Graphics_new("test02b.png");
	}
	else{
		Graphics_Draw_dst(enermy,&enermyRect);
		if(frame_count&1)
		{
			enermyRect.x--;
		}
	}
	return 0;
}


static int input(void*v,void*v2,void*e){
	return 0;
}
static int update(void*v,void*v2){
	return 0;
}


