/*
 * main.c
 *
 *  Created on: 2016年4月8日
 *      Author: yami
 */

/**
 * @file	main.c
 * @author	yami
 * @date	2016年4月8日
 * @brief
 * 
 */

#include "bindSDL2.h"
#include <mixmworld.h>

extern int test();
extern int test_clean();

int	BindSDL2_main(int argc,char**argv)
{
	BindSDL2_init();
	test();
	BindSDL2_loop();
	test_clean();
	BindSDL2_clean();
	return 0;
}
