/*
 * system.c
 *
 *  Created on: 2016年4月8日
 *      Author: yami
 */

/**
 * @file	system.c
 * @author	yami
 * @date	2016年4月8日
 * @brief
 * 
 */


static char*	game_name = 0;

/**
 * 获得游戏名
 * @return	返回游戏名
 */
char*	mixmworld_get_game_name(){
	return game_name;
}

/**
 * 设置游戏名
 * @param name	游戏名
 * @return	返回0 表示正确，非0则错误
 */
int		mixmworld_set_game_name(const char*name){
	game_name = name;
	return 0;
}
