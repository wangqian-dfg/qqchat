/*功能：server.h是服务器主函数*/
/*时间：2014—3-23*/
/*版本：1.0*/

#ifndef __SERVER_H__
#define __SERVER_H__

#include "../public/public.h"
#include <sys/types.h>          
#include <sys/socket.h>
#include <pthread.h>

//定义全局变量
int account = 1000;
node_t *alluser_head;
node_t *online_head;

//执行下线操作
void do_logout(int cfd, char *buf);

//执行密码操作
void do_passwd(int cfd, char *buf);

//开启服务器tcp服务
void start_tcp(void);

//执行登录操作
void do_login(int cfd, char *buf);

//线程处理函数
void *pthread_clientdo(void *arg);

//执行注册操作
void do_regise(int cfd, char *buf);

//读取文件操作
void read_file(void);

//写文件操作
int write_file(void);

#endif 
