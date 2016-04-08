/*功能：protocol.h是聊天系统中客户端和服务器之间的协议*/
/*时间：2014—3-23*/
/*版本：1.0*/

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#define SIZE 32		//定义数组大小
#define EXIT 0		//退出命令
#define REGISE 1	//注册命令
#define LOGIN 2		//登录命令
#define CHAT 3		//聊天命令
#define LOGOUT 4	//下线命令
#define PASSWD 5	//密码
#define SUCCESS 100	//成功标志
#define FAIL -1		//失败标志
#define OVER 10		//链表结束标志
#define CHAT_ALL 102	//群聊标志
#define CHAT_LONLY 101	//私聊标志


//退出、注册、登录、聊天、下线、消息等结构体


struct message
{
	int cmd;
	int account;
	char name[SIZE];
	char buf[128];
	char time[128];
};

struct regise
{
	int cmd;
	int account;
	char name[SIZE];
	char passwd[SIZE];
	int age;
	char sex;
	char message[SIZE];	
};

struct passwd
{
	int cmd;
	int result;
	int account;
	char passwd[SIZE];
	char message[SIZE];
};

struct mess
{
	int mess;
	int account;
};

struct login
{
	int cmd;
	int cfd;
	int result;
	int account;
	char passwd[SIZE];
	char name[SIZE];
	struct sockaddr_in addr;
};

struct chat
{
	int cmd;
	int count_to;
};

struct logout
{
	int cmd;
	int result;
	int account;
	char passwd[SIZE];
};

#endif

