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

int test()
{
	//return test02();
	return test03();
}

int test_clean()
{
	__builtin_printf("%s :%s \n",__FILE__,__FUNCTION__);
	//return test02_clean();
	return test03_clean();
}
