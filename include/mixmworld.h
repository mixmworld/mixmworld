/*
 * mixmworld.h
 *
 *  Created on: 2016年4月8日
 *      Author: yami
 */

/**
 * @file	mixmworld.h
 * @author	yami
 * @date	2016年4月8日
 * @brief
 * 
 */

#ifndef INCLUDE_MIXMWORLD_H_
#define INCLUDE_MIXMWORLD_H_

#include <stdint.h>
#include "mixmworld_update.h"


#define INLINE static inline


extern char*	mixmworld_get_game_name();
extern int		mixmworld_set_game_name(const char*);

//extern int		mixmworld_set_width(int width);
//extern int		mixmworld_get_width();
//extern int		mixmworld_set_height(int height);
//extern int		mixmworld_get_heitht();
#define mixmworld_get_width()		1280
#define mixmworld_get_heitht()	720


#endif /* INCLUDE_MIXMWORLD_H_ */
