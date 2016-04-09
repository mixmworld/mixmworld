/*
 * mixmworld_update.h
 *
 *  Created on: 2016年4月8日
 *      Author: yami
 */

/**
 * @file	mixmworld_update.h
 * @author	yami
 * @date	2016年4月8日
 * @brief
 * 
 */

/*

游戏的主体更新结构体数据和函数指针
	类似一种接口的形式

*/


#ifndef INCLUDE_MIXMWORLD_UPDATE_H_
#define INCLUDE_MIXMWORLD_UPDATE_H_


struct WindowUpdateFPtr{
	void*		reserve;
	int			(*update)(void*,void*);
	int			(*render)(void*,void*);
	int			(*input)(void*,void*,void* /*SDL_Event */);
};

struct WindowUpdate{
	struct WindowUpdateFPtr	*fptr;
};



#endif /* INCLUDE_MIXMWORLD_UPDATE_H_ */
