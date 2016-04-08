/*功能：client.h是客户端主函数*/
/*时间：2014—3-23*/
/*版本：1.0*/

#ifndef __CLINET_H__
#define __CLINET_H__

#include <sys/types.h>          
#include <sys/socket.h>
#include "../public/public.h"
#include "interface.h"
#include <poll.h>

//定义全局变量
node_t *online_head;
int cfd_sys;
int cfd_self;
struct login mylog;

//创建客户端套接字
struct sockaddr_in tcp_client_start(void);

//随机数获取函数
int myrand(void);

#endif
