/*
 * test.c
 *
 *  Created on: 2016年4月9日
 *      Author: yami
 */

/**
 * @file	test.c
 * @author	yami
 * @date	2016年4月9日
 * @brief
 * 
 */

int test02();
int test02_clean();

int	test03();
int test03_clean();;

int mario_init();
int mario_sprite_init();;

int test()
{
	//return test02();
	//return test03();
	mario_sprite_init();
	return mario_init();
	return 0;
}

int test_clean()
{
	//__builtin_printf("%s :%s \n",__FILE__,__FUNCTION__);
	//return test02_clean();
	//return test03_clean();
	return 0;
}
