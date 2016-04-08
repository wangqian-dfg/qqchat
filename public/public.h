/*功能：public.h是链表的增、删除、显示、创建、查找以及密码隐藏、获取键码、id自动生成*/
/*时间：2014—3-23*/
/*版本：1.0*/

#ifndef __PUBLIC_H_
#define __PUBLIC_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "protocol.h"
#include <termios.h>
#include <unistd.h>
#include <time.h>


//定义个错误安全检查的宏
#define ERROR(x, y, message, z)		if (x == y)		\
					{			\
				  		perror(message);\
						return z;	\
					}

//链表结构体
typedef struct clist
{
	void *data;
	struct clist *next;

}node_t;


//比较退出链表成员
int cmp_out(void *data1, void *data2);

//创建单项循环链表
node_t *create_clist(void);

//查找链表的第几个成员
node_t *find_clist(node_t *head, int index);

//实现在终端上打印出方框
void interface(int x, int w, int y, int l);

//向链表的尾部插入元素
int insert_clist(node_t *head, void *data, int size);

//显示链表中的成员
void show(void *data);

//定义显示函数指针
typedef void (*showfun_t)(void *data);

//显示全部链表成员
void show_all_clist(node_t *head, showfun_t f);

//获取本地时间
char * mytime(int i);

//自动增加id
int account_f(int *account);

//定义比较函数指针
typedef int (*cmpfun_t)(void *data1, void *data2);

//查找链表中的某个成员
node_t *fcmp_clist(node_t *head, void *data, cmpfun_t f);

//删除链表中的某个成员
int delete_me_clist(node_t *head, void *data, cmpfun_t f);

//比较两个数据
int cmp(void *data1, void *data2);

//获取密码隐藏
void get_passwd(char *passwd);

//获取键码
int key_val(void);

#endif



