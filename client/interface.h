/*功能：interface.h是客户端界面、聊天函数*/
/*时间：2014—3-23*/
/*版本：1.0*/

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "../public/public.h"
#include "poll.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>

//引用全局变量
extern int cfd_self;
extern node_t *online_head;
extern struct login mylog;


//选择聊天对象函数
void choice(struct login *log_self);

//群聊天函数
void chat_all(struct login *log_self, node_t *online_head);

//获得密码函数
int getpswd(struct passwd *wd);

//主界面函数
int main_interface(struct login *log);

//主界面键码获得函数
void key_main_interface(int flag);

//私聊函数
void chat_interface(struct login *log, struct login *log_self);

//私聊主界面
void menu_main_interface(struct login *log_self);

//注册界面函数
void menu_regise_interface(int flag);

//注册界面键码获取函数
int key_regise_interface(struct regise *reg);

//注册信息输入
int regise_interface(struct regise *reg);

//键码获得应用函数
void key_menu_interface(void);

//菜单显示函数
void menu_interface(int flag);


int recvfile(void);


int sendfile(struct login *log, struct login *log_self);
#endif
