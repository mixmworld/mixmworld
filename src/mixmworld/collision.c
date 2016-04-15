/*
 * collision.c
 *
 *  Created on: 2016年4月11日
 *      Author: yami
 */

/**
 * @file	collision.c
 * @author	yami
 * @date	2016年4月11日
 * @brief
 * 
 */


#include <mixmworld.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int CollisionDetection_update(void*d);
int CollisionDetection_input(void*d,void*event);
int CollisionDetection_render(void*d);
int CollisionDetection_alloc(int allocSize);
int CollisionDetection_delete(CollisionDetection *cd);
int CollisionDetection_add(CollisionDetection *cd);
CollisionDetection* CollisionDetection_iterator(int*itr);


static int	collisionDetection_size = 0;
static int	collisionDetection_allocSize	=	0;
static int	collisionDetection_show_sortFlag = 0;
static CollisionDetection **collisionDetection = 0;



static int ccmp(CollisionDetection**ptr1,CollisionDetection**ptr2);

CollisionDetection* CollisionDetection_iterator(int*itr){
	if(!collisionDetection)
		return 0;
	if(*itr>collisionDetection_size)
		return 0;
	CollisionDetection*cc;
	cc = collisionDetection[*itr];
	(*itr) ++;
	return cc;
}

static int csort()
{
	qsort(collisionDetection,collisionDetection_size,sizeof(void*),(void*)ccmp);
	collisionDetection_show_sortFlag = 0;
	return 0;
}

static int ccmp(CollisionDetection**ptr1,CollisionDetection**ptr2)
{
	if(!*ptr1)
		return -(-1);
	if(!*ptr2)
		return -(1);
	CollisionDetection *p1,*p2;
	p1 = *ptr1;
	p2 = *ptr2;
	if(!p1->fptr)
		return -(-1);
	if(!p2->fptr)
		return -(1);
	if(!p1->fptr->get_show_priority)
		return -(-1);
	if(!p2->fptr->get_show_priority)
		return -(1);
	return -(p1->fptr->get_show_priority(p1) - p2->fptr->get_show_priority(p2));
}


int CollisionDetection_update(void*d)
{
	CollisionDetection *cd = 0;
	struct WindowUpdateFPtr *fptr = 0;
	CollisionDetectionFPtr *cdfptr = 0;
	int i;
	if(collisionDetection_show_sortFlag&1){
		csort();
	}
	for(i=0;i<collisionDetection_size;i++){
		cd = collisionDetection[i];
		if(cd){
			if((cdfptr=cd->fptr)){
				if(cd->fptr->get_update_ptr){
					fptr = cd->fptr->get_update_ptr(cd);
					if(fptr){
						if(fptr->update)
						{
							fptr->update(cd,d);
						}
					}
				}
			}
		}
	}

	for(i=0;i<collisionDetection_size;i++){
		cd = collisionDetection[i];
		if(cd){
			if((cdfptr=cd->fptr)){
				if(cdfptr->collision_detection_proc)
				{
					cdfptr->collision_detection_proc(cd);
				}
			}
		}
	}

	return 0;
}

int CollisionDetection_input(void*d,void*event)
{
	CollisionDetection *cd;
	struct WindowUpdateFPtr *fptr;
	int i;
	for(i=0;i<collisionDetection_size;i++){
		cd = collisionDetection[i];
		if(cd){
			if(cd->fptr){
				if(cd->fptr->get_update_ptr){
					fptr = cd->fptr->get_update_ptr(cd);
					if(fptr){
						if(fptr->input)
						{
							fptr->input(cd,d,event);
						}
					}
				}
			}
		}
	}
	return 0;
}

int CollisionDetection_render(void*d)
{
	CollisionDetection *cd;
	struct WindowUpdateFPtr *fptr;
	int i;
	for(i=0;i<collisionDetection_size;i++){
		cd = collisionDetection[i];
		if(cd){
			if(cd->fptr){
				if(cd->fptr->get_update_ptr){
					fptr = cd->fptr->get_update_ptr(cd);
					if(fptr){
						if(fptr->render)
						{
							fptr->render(cd,d);
						}
					}
				}
			}
		}
	}
	return 0;
}

int
CollisionDetection_alloc(int allocSize){
	collisionDetection_allocSize = allocSize;
	if(!collisionDetection){
		collisionDetection = malloc(allocSize*sizeof(void*));
		memset(collisionDetection,0,allocSize * sizeof(void*));

	}
	else{
		collisionDetection = realloc(collisionDetection,allocSize*sizeof(void*));
	}
	return 0;
}

int
CollisionDetection_add(CollisionDetection *cd){
	if(!cd)
		return 1;
	int	i;
	for(i=0;i<collisionDetection_size;i++){
		if(cd == collisionDetection[i])
			return 2;
	}

	while(i>=collisionDetection_allocSize){
		collisionDetection_allocSize += BUFSIZ;
		CollisionDetection_alloc(collisionDetection_allocSize);
	}
	if(cd->fptr)
	{
		if(cd->fptr->init)
		{
			cd->fptr->init(cd);
		}
	}
	collisionDetection[i] = cd;
	collisionDetection_size +=1;
	collisionDetection_show_sortFlag |= 1;
	return 0;
}

static
int _update_data(int offset)
{
	int i,ii;
	i = offset;
	ii = offset;
	for(;ii<collisionDetection_size;){

		if(collisionDetection[i]==0){
			//下一个数往前移
			ii++;
		}
		if(i!=ii){
			collisionDetection[i] = collisionDetection[ii];
		}

		i++;
		ii++;
	}
	return 0;
}

int CollisionDetection_delete(CollisionDetection *cd){
	int	i;
	for(i=0;i<collisionDetection_size;i++){
		if(cd == collisionDetection[i])
		{
			if(cd->fptr)
			{
				if(cd->fptr->free)
				{
					cd->fptr->free(cd);

				}
			}
			collisionDetection[i] = 0;
			collisionDetection_size -= 1;
			_update_data(i);
			collisionDetection_show_sortFlag |= 1;
			return 0;
		}
	}
	return -1;
}



