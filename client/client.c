#include "client.h"


/*功能：客户端主函数*/
/*参数：无*/
/*返回值：0代表成功*/
int main(void)
{
	int temp = 0;
	struct login log;
	struct sockaddr_in ski_self = tcp_client_start();

	while (1)
	{
		temp = main_interface(&log);		
		switch (temp)
		{

			case 2:
				{
					struct regise reg;
					struct mess mess;
					reg.cmd = REGISE;
					char buf[SIZE] = {0};
					if (regise_interface(&reg) == 0)
						send(cfd_sys, &reg, sizeof(reg), 0);

					recv(cfd_sys, &mess, sizeof(mess), 0);
					if (mess.mess == SUCCESS)
						printf("\e[15;30H\e[41m\e[?25l注册成功! 帐号：%d\e[0m", mess.account);
					else
						printf("\e[15;40H\e[41m\e[?25l注册失败\e[0m");
		
					break;
				}

			case 3:
				{	
					log.cmd = LOGIN;
					log.addr = ski_self;
					struct login recvlog, log_self;
					online_head = create_clist();

					ERROR(online_head, NULL, "create clist", -1);
					send(cfd_sys, &log, sizeof(log), 0);
					recv(cfd_sys, &recvlog, sizeof(struct login), 0);
					log_self = recvlog;
					recvlog.account = 0;
					node_t *temp;

					if (recvlog.result == SUCCESS)
					{
						struct pollfd arr[2];
						arr[0].fd = 0;
						arr[0].events = POLLIN;
	
						arr[1].fd = cfd_sys;
						arr[1].events = POLLIN;
							
						while (1)
						{
							poll(arr, 2, -1);
							if (arr[1].revents == POLLIN)
							{	
								recv(cfd_sys, &recvlog, sizeof(struct login), 0);
								if (recvlog.result != OVER)
								{
									if (fcmp_clist(online_head, &recvlog, cmp) == NULL)		
										insert_clist(online_head, &recvlog, sizeof(struct login));
								}
								else
									menu_main_interface(&log_self);
					
							}
							if (arr[0].revents == POLLIN)
							{
								choice(&log_self); 
								menu_main_interface(&log_self);
							}
						}									
					}

					if (recvlog.result == FAIL)
						printf("\e[15;40H\e[41m\e[?25l登录失败\e[0m");		
					break;
				}
				break;
			case 4:
				{
					struct passwd wd;
					wd.cmd = PASSWD;
					getpswd(&wd);
					send(cfd_sys, &wd, sizeof(wd), 0);
					recv(cfd_sys, &wd, sizeof(wd), 0);
					if (wd.result == SUCCESS)
					{	
						printf("\e[14;35H\e[41m\e[?25l请牢记你的密码!\e[0m");	
						printf("\e[15;37H\e[41m\e[?25l密码：%s\e[0m", wd.passwd);
					}					
					else
						printf("\e[15;40H\e[41m\e[?25l获取失败\e[0m");
				}
				break;
			case 5:
				system("rm -f message_data");
				interface(5, 16, 25, 60);	
				printf("\e[10;40H感谢使用");
				fflush(stdout);
				sleep(2);
				system("clear");
				exit(0);
				break;
		}
	}
	return 0;
}

/*
int quit(void)
{
	struct logout logout;
	logout.cmd = LOGOUT;
	send(cfd_sys, &logout, sizeof(logout), 0);
	return 0;
}
*/

/*功能：创建客户端tcp和udp地址*/
/*参数：无*/
/*返回值：struct sockaddr_in udp的地址*/
struct sockaddr_in tcp_client_start(void)
{
	
	cfd_self = socket(AF_INET, SOCK_DGRAM, 0);
	cfd_sys = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in ski_sys, ski_self;
	
	ski_sys.sin_family = AF_INET;
	ski_sys.sin_port = htons(6000);
	ski_sys.sin_addr.s_addr = inet_addr("192.168.1.1");
	connect(cfd_sys, (struct sockaddr *)&ski_sys, sizeof(ski_sys));

	ski_self.sin_family = AF_INET;
	ski_self.sin_port = htons(myrand());
	ski_self.sin_addr.s_addr = htonl(INADDR_ANY);

	while (1)
	{
		if (bind(cfd_self, (struct sockaddr *)&ski_self, sizeof(ski_self)) == 0)
			break;
	}

	return ski_self;
}


/*功能：获取一个随机数*/
/*参数：无*/
/*返回值：int 产生的随机数值*/
int myrand(void)
{
	srand(time(0));
	int n = 0;
	while (1)
	{
		if (n <= 6000)
			n = rand() % 10000;
		else
			break;
	}
	return n;
}




