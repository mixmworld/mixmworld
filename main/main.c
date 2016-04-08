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

#include <stdio.h>
#include <stdlib.h>

extern int	BindSDL2_main(int argc,char**argv);

int main(int argc,char**argv)
{
	printf("%s\n","hello mixmworld");

	return
	BindSDL2_main(argc,argv);
}
