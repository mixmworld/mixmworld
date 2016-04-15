/*
 * mixmworld_collision.h
 *
 *  Created on: 2016年4月11日
 *      Author: yami
 */

/**
 * @file	mixmworld_collision.h
 * @author	yami
 * @date	2016年4月11日
 * @brief
 * 
 */

#ifndef INCLUDE_MIXMWORLD_COLLISION_H_
#define INCLUDE_MIXMWORLD_COLLISION_H_

#include "mixmworld_types.h"
#include "mixmworld_update.h"


typedef struct  CollisionDetectionFPtr  CollisionDetectionFPtr;
typedef struct  CollisionDetection 		CollisionDetection;


struct CollisionDetectionFPtr{
	void*		resever;
	int			(*get_version)(void*v1);							//获得版本号
	int			(*get_FPtr_size)(void*v1);							//获得函数指针大小，对于扩展的数据，会先检测大小，然后再做其他事
	int64_t		(*get_eee)(void*v1);								//对于个别其他扩展版本的标志

	int			(*init)(void*v1);									//但添加的时候，调用该函数指针
	int			(*free)(void*v1);									//但删除的时候，调用该函数指针
	struct WindowUpdateFPtr* (*get_update_ptr)(void*v1);			//当为NULL，不进行更新,输入，渲染
	int			(*get_show_priority)(void*v1);						//显示优先权，0为最高优先权


	int			(*is_collision_detection)(void*v1);					//当是碰断检测物体，非背景时，才进行碰撞检测
	int			(*collision_detection)(void*v1,Rect*r);				//碰撞检测函数 ,可以通过 碰撞范围 获得碰撞物体,包括特殊图形构造
	int			(*collision_detection_point)(void*v1,Point *p);		//针对圆形，有很好的效果
	int			(*collision_range)(void*v1,Rect*r);					//碰撞总体范围
	int			(*collision_detection_proc)(void*v1);				//碰撞处理，不为空，都处理该函数指针

	Rect*		(*get_collision_rangePtr)(void*v1);			//类似上面，只不过加快数据处理
	Rect*		collision_rangePtr;							//非函数指针，比以上更快，设置进去碰撞检测数据，如果是NULL，则不检测


	/**

	碰撞物类型
	空，未知?   	= 0
	玩家			=
	NPC				=
	敌人			=
	道具			=
	不可穿越物体	=
	障碍物			=
	背景或地图		=
	...以后待添加

	 */
	int			(*get_type)(void*v1);						//获得碰撞物类型
	/*
	 根据type1 来判断type2的标志，如
	 type = 玩家
	 	 type2 表示玩家编号
	 type = 道具
	 	 type2 表示道具编号
	 */
	int			(*get_type2)(void*v1);						//附属标志
	int			(*get_flag)(void*v1);						//标志，保留位
};


struct CollisionDetection{
	struct CollisionDetectionFPtr *fptr;
};


int CollisionDetection_update(void*d);
int CollisionDetection_input(void*d,void*event);
int CollisionDetection_render(void*d);
int CollisionDetection_alloc(int allocSize);
int CollisionDetection_delete(CollisionDetection *cd);
int CollisionDetection_add(CollisionDetection *cd);
CollisionDetection* CollisionDetection_iterator(int*itr);;

#endif /* INCLUDE_MIXMWORLD_COLLISION_H_ */
