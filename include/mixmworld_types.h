/*
 * mixmworld_types.h
 *
 *  Created on: 2016年4月11日
 *      Author: yami
 */

/**
 * @file	mixmworld_types.h
 * @author	yami
 * @date	2016年4月11日
 * @brief
 * 
 */

#ifndef INCLUDE_MIXMWORLD_TYPES_H_
#define INCLUDE_MIXMWORLD_TYPES_H_


#include <stdint.h>

typedef struct Rect Rect;
typedef struct Point Point;


struct Rect{
	int32_t x,y,w,h;
};

struct Point{
	int32_t x,y;
};


#endif /* INCLUDE_MIXMWORLD_TYPES_H_ */
