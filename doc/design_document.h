/*
 * design_document.h
 *
 *  Created on: 2016年4月8日
 *      Author: yami
 */

/**
 * @file	design_document.h
 * @author	yami
 * @date	2016年4月8日
 * @brief
 * 
 */

#ifndef DOC_DESIGN_DOCUMENT_H_
#define DOC_DESIGN_DOCUMENT_H_

/*
文件夹说明:
include/
	提供系统的主要API，类型指针
src/
	源码位置
main/
	主程序和初始化所在位置
lib/
	一些库的引用？




2016-04-10 15:13:08
一,先设计横版2D动作
	X,Y坐标 (Z以后再添加)

	1,	横版平面，物体碰撞体系用Rect{ x,y,w,h}
	2,	或者碰撞体系用 函数指针来   ,<mixmworld_collision.h>
		1.collision_detection(void*v1,Rect*src)			碰撞检测函数 ,可以通过 碰撞范围 获得碰撞物体,包括特殊图形构造
		2.collision_range(void*v1,Rect*r)		碰撞范围
		2.1 get_collision_rangePtr(void*v1)		类似上面，只不过加快数据处理
		3.Rect*collision_rangePtr				设置进去碰撞检测数据，如果是NULL，则不检测

		注: 思路是，当游戏进行时，先判断物体A是否要进行碰撞检测，
			然后调用该函数，该函数再遍历所有碰撞物或非碰撞物(地形背景)
			根据get_collision_rangePtr(void*v1)捕捉到物体B时，再调用collision_detection(void*v1,Rect*src);  src参数是物体A的范围
			如果物体A是不可定型的形状(如五角星),则多次执行碰撞检测，
			正方形的碰撞检测是最简单的，并且资源消耗最少
	3






*/

#endif /* DOC_DESIGN_DOCUMENT_H_ */
