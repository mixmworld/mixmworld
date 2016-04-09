/*
 * mainUpdate.c
 *
 *  Created on: 2016年4月9日
 *      Author: yami
 */

/**
 * @file	mainUpdate.c
 * @author	yami
 * @date	2016年4月9日
 * @brief
 * 
 */

#include "bindSDL2.h"

/**
 * 设置窗口的主更新函数
 * @param mainUpdate	如果设置0，则不使用主更新函数
 * @return	0,表示成功，非0，表示失败
 */
int	BindSDL2_set_mainUpdate(struct WindowUpdate*mainUpdate){
	sdl2_window->mainUpdate	=	mainUpdate;
	return 0;
}

