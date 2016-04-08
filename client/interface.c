#include "interface.h"

/*功能：主界面函数*/
/*参数：log登录者信息*/
/*返回值：res 为选择条目*/
int main_interface(struct login *log)
{
	int res = 0;
	interface(5, 16, 25, 60);	
	printf("\e[6;40H聊天系统");
	printf("\e[9;32H帐号：\e[4m                   ");
	printf("\e[0m\e[11;32H密码：\e[4m                   ");
	printf("\e[0m\e[13;40H登录");
	printf("\e[13;27H注册");
	printf("\e[13;50H找回密码");
	printf("\e[15;54H退出");
	fflush(stdout);
	res = key_interface(log);	
	return res;
}


/*功能：主界面的键值函数*/
/*参数：flag 标志位*/
/*返回值：无*/
void key_main_interface(int flag)
{
	switch (flag)
	{
		case 0:
			printf("\e[13;27H\e[30m\e[?25l注册\e[0m");
			printf("\e[13;40H\e[30m登录\e[0m");
			printf("\e[13;50H\e[30m找回密码\e[0m");
			printf("\e[15;54H\e[30m退出\e[0m");
			printf("\e[9;38H\e[?25h");
			break;
		case 1:
			printf("\e[13;27H\e[30m注册\e[?25l\e[0m");
			printf("\e[13;40H\e[30m登录\e[0m");
			printf("\e[13;50H\e[30m找回密码\e[0m");
			printf("\e[15;54H\e[30m退出\e[0m");
			printf("\e[11;38H\e[?25h");
			break;
		case 2:	
			printf("\e[13;40H\e[30m\e[?25l登录\e[0m");
			printf("\e[13;50H\e[30m找回密码\e[0m");
			printf("\e[15;54H\e[30m退出\e[0m");
			printf("\e[13;27H\e[34m注册\e[0m");
			break;
		case 3:
			printf("\e[13;27H\e[30m注册\e[0m");
			printf("\e[13;50H\e[30m找回密码\e[0m");
			printf("\e[15;54H\e[30m退出\e[0m");
			printf("\e[13;40H\e[34m登录\e[0m");
			break;
		case 4:
			printf("\e[13;27H\e[30m注册\e[0m");
			printf("\e[13;40H\e[30m登录\e[0m");
			printf("\e[15;54H\e[30m退出\e[0m");
			printf("\e[13;50H\e[34m找回密码\e[0m");
			break;
		case 5:
			printf("\e[13;27H\e[30m注册\e[0m");
			printf("\e[13;40H\e[30m登录\e[0m");
			printf("\e[13;50H\e[30m找回密码\e[0m");
			printf("\e[15;54H\e[34m退出\e[0m");
			break;
	}	

	return;
}


/*功能：键值界面*/
/*参数：log登录着信息*/
/*返回值：无*/
int key_interface(struct login *log)
{
	int temp, flag = 0;
	key_main_interface(flag);
	while (1)
	{
		temp = key_val();
		switch (temp)
		{
			case 65:
			{
				if (flag == 0)
					flag = 6;
				flag--;
				key_main_interface(flag);
				break;
			}
			case 66:
			{
				if (flag == 5)
					flag = -1;
				flag++;
				key_main_interface(flag);
				break;	 
			}	
			case 67:
			{
				if (flag == 5)
					flag = -1;
				flag++;
				key_main_interface(flag);
				break;
			}
			case 68:
			{
				if (flag == 0)
					flag = 6;
				flag--;
				key_main_interface(flag);
				break;
			}
			case 13:
			{
				if (flag == 0)
				{
					printf("\e[4m");
					scanf("%d", &log->account);
					printf("\e[11;38H\e[0m");
					flag = 1;
				}	
				else if (flag == 1)
				{
					printf("\e[4m");
					get_passwd(log->passwd);
					printf("\e[0m\e[13;40H\e[34m登录\e[0m");
					flag = 3;
				}
				else					
					return flag; 
			}
			
		}
	}
	return 0;
}


/*功能：主菜单界面*/
/*参数：无*/
/*返回值：无*/
void menu_main_interface(struct login *log_self)
{
	int res = 0, i = 13;
	interface(1, 6, 30, 50);
	interface(6, 8, 30, 40);
	interface(6, 8, 40, 50);
	interface(8, 23, 30, 50);
	printf("\e[2;32H用户名:");
	printf("\e[3;32H账户:");
	printf("\e[4;32H签名:");
	printf("\e[7;32H联系人\e[7;42H群");
	printf("\e[9;32H好友");
	printf("\e[10;32H同事");
	printf("\e[11;32H同学");
	printf("\e[12;32H亲人");
	printf("\e[22;42H退出");
	node_t *temp = online_head->next;
	struct login *log;
	while (temp != online_head)
	{
		log = (struct login *)temp->data;
		if (log_self->account == log->account)
			printf("\e[3;40H\e[31m%d\e[2;40H%s\e[0m\e[?25l", log->account, log->name);
		else
		{
			printf("\e[%d;32H%d %s", i, log->account, log->name);
			i++;
		}
		temp = temp->next;
	}
	
	fflush(stdout);
	return;
}


/*功能：选择登录方式*/
/*参数：无*/
/*返回值：无*/
void choice(struct login *log_self)
{
	int temp, flag = 0, temp_flag = 0;
	char buf[SIZE] = {0};
	menu_interface(flag);
	node_t *otemp;
	struct login *log;
	int i = 13;
	while (1)
	{
		temp = key_val();
		switch (temp)
		{
			case 65:
			{
				if (flag == 0)
					flag = 17;
				flag--;
				menu_interface(flag);
				break;
			}
			case 66:
			{
				if (flag == 16)
					flag = -1;
				flag++;
				menu_interface(flag);
				break;	 
			}	
			case 67:
			{
				if (flag == 16)
					flag = -1;
				flag++;
				menu_interface(flag);
				break;
			}
			case 68:
			{
				if (flag == 0)
					flag = 17;
				flag--;
				menu_interface(flag);
				break;
			}
			case 13:
			{
				switch (flag)
				{
					case 0:
					{
						break;
					}
					case 1:
					{
						chat_all(log_self, online_head);
						temp_flag = 1;
						break;					
					}
					case 2:
					{
						break;
					}
					case 3:
					{
						break;
					}
					case 4:
					{
						break;
					}
					case 5:
					{
						break;
					}
					case 6:
					{
						scanf("%s", buf);
						break;
					}
					case 7:
					{
						break;
					}
					default:
					{
						delete_me_clist(online_head, log_self, cmp);
						otemp = find_clist(online_head, flag - 8);
						if (otemp != NULL && otemp->data != NULL)
						{
							log = (struct login *)otemp->data;				
							chat_interface(log, log_self);
							temp_flag = 1;
						}
						else 
						{
							printf("\e[5;32H\e[31m\e[?25l没有此好友\e[0m");
							printf("\e[?25h");	
						}	
					}
					

				}			
				break; 
			}			
		}
		if (temp_flag == 1)
		{
			temp_flag = 0;
			break;
		}
	}		
}


/*功能：群聊天函数*/
/*参数：无*/
/*返回值：无*/
void chat_all(struct login *log_self, node_t *online_head)
{
	node_t *otemp;
	interface(2, 18, 15, 65);
	interface(18, 26, 15, 65);
	printf("\e[3;30H\e[31m群聊 输入##quit退出\e[0m");
	printf("\e[19;16H");
	fflush(stdout);
	struct pollfd arr[2];
	arr[0].fd = 0;
	arr[0].events = POLLIN;
	
	arr[1].fd = cfd_self;
	arr[1].events = POLLIN;
	struct message message;
	struct login *log;
	int i = 4;
	char *str = "##quit\n";
	umask(0);
	int fd = open("./message_data", O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		perror("open");
		return;
	}
	while (read(fd, &message, sizeof(message)))
	{
		if (message.cmd == CHAT_ALL)
		{
			if (i == 16)
			{
				
				for (i = 4; i < 16; i++)
					printf("\e[%d;16H                                                 ", i);
				i = 4;
			}
			printf("\e[%d;25H\e[31m%s\e[0m", i, message.time);
			printf("\e[%d;17H\e[31m%s\e[0m", i, message.name);
			printf("\e[%d;17H%s",i + 1, message.buf);
			printf("\e[19;16H");
			fflush(stdout);
			i = i + 2;	
		}	
		printf("\e[19;16H");
	}	
	printf("\e[19;16H");
	while (1)
	{
		poll(arr, 2, -1);
		if (arr[0].revents == POLLIN)
		{
			otemp = online_head->next;
			bzero(message.buf, sizeof(message.buf));
			printf("\e[19;16H");
			fflush(stdout);
			read(0, message.buf, sizeof(message.buf) - 1);
			message.account = log_self->account;
			strcpy(message.name, log_self->name);
			message.cmd = CHAT_ALL;			
			if (i == 16)
			{
				for (i = 4; i < 16; i++)
					printf("\e[%d;16H                                                 ", i);
				i = 4;
			}
			strcpy(message.time, mytime(i));
			printf("\e[%d;17H\e[31m%s\e[0m", i, message.name);
			printf("\e[%d;17H%s",i + 1, message.buf);
			printf("\e[19;16H");
			fflush(stdout);
			i = i + 2;
			if (strcmp(message.buf, str) == 0)
				break;
			while (otemp != online_head)
			{	
				log = (struct login *)otemp->data;
				if (log->account != log_self->account)
				{
					sendto(cfd_self, &message, sizeof(message), 0, (struct sockaddr *)&log->addr, sizeof(log->addr));						
				}				
				otemp = otemp->next;
			}
			printf("\e[19;16H                                                 ");
			printf("\e[19;16H");
			fflush(stdout);	
		}
		if (arr[1].revents == POLLIN)
		{			
			bzero(message.buf, sizeof(message.buf));
			read(cfd_self, &message, sizeof(message));
			if (message.cmd == CHAT_ALL)
			{
				if (i == 16)
				{
					for (i = 4; i < 16; i++)
						printf("\e[%d;16H                                                 ", i);
					i = 4;
				}
				printf("\e[%d;25H\e[31m%s\e[0m", i, message.time);
				printf("\e[%d;17H\e[31m%s\e[0m", i, message.name);
				printf("\e[%d;17H%s",i + 1, message.buf);
				printf("\e[19;16H"); 
				fflush(stdout);
				i = i + 2;
			}
			else
				write(fd, &message, sizeof(message));
			printf("\e[19;16H");			
		}
					
	}
	return;
}


/*功能：私聊函数*/
/*参数：无*/
/*返回值：无*/
void chat_interface(struct login *log, struct login *log_self)
{
		
	interface(2, 18, 15, 65);
	interface(18, 26, 15, 65);
	printf("\e[3;17H\e[31m私聊 %s  to  %s 输入##quit退出、##sendf发文件\e[0m", log_self->name, log->name);
	printf("\e[19;16H");
	fflush(stdout);
	struct pollfd arr[2];
	arr[0].fd = 0;
	arr[0].events = POLLIN;
	
	arr[1].fd = cfd_self;
	arr[1].events = POLLIN;
	struct message message;
	int i = 4;
	char *str = "##quit\n";
	char *strfile = "##sendf\n";

	umask(0);
	int fd = open("./message_data", O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		perror("open");
		return;
	}
	while (read(fd, &message, sizeof(message)))
	{
		if (log->account == message.account && message.cmd == CHAT_LONLY)
		{
			if (i == 16)
			{
				
				for (i = 4; i < 16; i++)
					printf("\e[%d;16H                                                 ", i);
				i = 4;
			}
			printf("\e[%d;25H\e[31m%s\e[0m", i, message.time);
			printf("\e[%d;17H\e[31m%s\e[0m", i, message.name);
			printf("\e[%d;17H%s",i + 1, message.buf);
			printf("\e[19;16H");
			fflush(stdout);
			i = i + 2;	
		}	
		printf("\e[19;16H");
	}
	printf("\e[19;16H");
	while (1)
	{
		
		poll(arr, 2, -1);
		if (arr[0].revents == POLLIN)
		{
			bzero(message.buf, sizeof(message.buf));
			printf("\e[19;16H");
			fflush(stdout);
			read(0, message.buf, sizeof(message.buf) - 1);
			message.account = log_self->account;
			strcpy(message.name, log_self->name);
			message.cmd = CHAT_LONLY;
			if (i == 16)
			{
				for (i = 4; i < 16; i++)
					printf("\e[%d;16H                                                 ", i);
				i = 4;
			}
			strcpy(message.time, mytime(i));
			printf("\e[%d;17H\e[31m%s\e[0m", i, message.name);
			printf("\e[%d;17H%s",i + 1, message.buf);
			fflush(stdout);
			i = i + 2;
			
			if (strcmp(message.buf, str) == 0)
				break;
			if (strcmp(message.buf, strfile) == 0)
				sendfile(log, log_self);			
			else	
				sendto(cfd_self, &message, sizeof(message), 0, (struct sockaddr *)&log->addr, sizeof(log->addr));
			printf("\e[19;16H                                                 ");
			printf("\e[19;16H");
			fflush(stdout);		
		}

		if (arr[1].revents == POLLIN)
		{ 
			bzero(&message, sizeof(message));
			read(cfd_self, &message, sizeof(message));
			if (log->account == message.account && message.cmd == CHAT_LONLY)
			{
				if (strcmp(message.buf, "please recv this file") == 0)
					recvfile();
				else
				{
					if (i == 16)
					{
				
						for (i = 4; i < 16; i++)
							printf("\e[%d;16H                                                 ", i);
						i = 4;
					}
					printf("\e[%d;25H\e[31m%s\e[0m", i, message.time);
					printf("\e[%d;17H\e[31m%s\e[0m", i, message.name);
					printf("\e[%d;17H%s",i + 1, message.buf);
					printf("\e[19;16H");
					fflush(stdout);
					i = i + 2;
				}	
			}
			else 
				write(fd, &message, sizeof(message));
			printf("\e[19;16H");	
		}			
	}
	
	return;
}


/*功能：接收文件*/
/*参数：无*/
/*返回值：无*/
int recvfile(void)
{
	//read(cfd_self, &message, sizeof(message));
	umask(0);
	int fd = open("/home/user/a.txt", O_RDWR | O_CREAT, 0777);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}
	char temp[SIZE] = {0};
	while (strcmp(temp, "send file over"))
	{
		read(cfd_self, temp, sizeof(temp));
		printf("%s\n", temp);
		write(fd, temp, sizeof(temp));
	}
	close(fd);
	return 0;
}


/*功能：发送文件函数*/
/*参数：无*/
/*返回值：无*/
int sendfile(struct login *log, struct login *log_self)
{
	struct message message;
	strcpy(message.buf, "please recv this file");
	strcpy(message.name, log_self->name);
	message.cmd = CHAT_LONLY;
	message.account = log_self->account;
	sendto(cfd_self, &message, sizeof(message), 0, (struct sockaddr *)&log->addr, sizeof(log->addr));
	//strcpy(message.buf, filename);
	//sendto(cfd_self, &message, sizeof(message), 0, (struct sockaddr *)&log->addr, sizeof(log->addr));
	int fd = open("2.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}
	char temp[SIZE] = {0};
	while (read(fd, temp, sizeof(temp)))
	{
		sendto(cfd_self, temp, sizeof(temp), 0, (struct sockaddr *)&log->addr, sizeof(log->addr));
	}
	close(fd);
	strcpy(message.buf, "send file over");
	sendto(cfd_self, &message, sizeof(message), 0, (struct sockaddr *)&log->addr, sizeof(log->addr));
	return 0;
}


/*功能：注册界面函数*/
/*参数：无*/
/*返回值：无*/
int regise_interface(struct regise *reg)
{
	int res = 0;
	while (1)
	{
		interface(3, 22, 30, 60);
		printf("\e[4;40H个人注册信息");
		printf("\e[7;35H昵称：\e[4m              ");
	
		printf("\e[0m\e[9;35H密码：\e[4m              ");
		printf("\e[0m\e[11;35H确认密码：\e[4m          ");
		printf("\e[0m\e[13;35H年龄：\e[4m              ");
		printf("\e[0m\e[15;36H性别：(M/W)\e[4m         ");
	
		printf("\e[0m\e[17;35H密保问题：\e[4m          ");
		printf("\e[0m\e[19;45H注册\e[0m");
		fflush(stdout);
		if (key_regise_interface(reg) == 0)
			return 0;
	}
	return -1;
}


/*功能：注册主菜单界面函数*/
/*参数：无*/
/*返回值：无*/
void menu_regise_interface(int flag)
{
	switch (flag)
	{
		case 0:
			printf("\e[19;45H\e[30m注册\e[0m");
			printf("\e[7;41H\e[?25h");
			break;
		case 1:
			printf("\e[19;45H\e[30m注册\e[0m");
			printf("\e[9;41H");
			break;
		case 2:	
			printf("\e[19;45H\e[30m注册\e[0m");
			printf("\e[11;45H");
			break;
		case 3:
			printf("\e[19;45H\e[30m注册\e[0m");
			printf("\e[13;41H");
			break;
		case 4:
			printf("\e[19;45H\e[30m注册\e[0m");
			printf("\e[15;47H");
			break;
		case 5:
			printf("\e[19;45H\e[30m注册\e[0m");
			printf("\e[17;45H");
			break;
		case 6:
			printf("\e[19;45H\e[34m\e[?25l注册\e[0m");
			break;
	}	

	return;
}


/*功能：注册键值界面函数*/
/*参数：无*/
/*返回值：无*/
int key_regise_interface(struct regise *reg)
{
	int temp, flag = 0;
	int exitflag = 0;
	char passwd1[SIZE], passwd2[SIZE];
	menu_regise_interface(flag);
	while (1)
	{
		temp = key_val();
		switch (temp)
		{
			case 65:
			{
				if (flag == 0)
					flag = 7;
				flag--;
				menu_regise_interface(flag);
				break;
			}
			case 66:
			{
				if (flag == 6)
					flag = -1;
				flag++;
				menu_regise_interface(flag);
				break;	
			}	
			case 67:
			{
				if (flag == 6)
					flag = -1;
				flag++;
				menu_regise_interface(flag);
				break;
			}
			case 68:
			{
				if (flag == 0)
					flag = 7;
				flag--;
				menu_regise_interface(flag);
				break;
			}
			case 13:
			{
				switch (flag)
				{
					case 0:
						printf("\e[4m");
						scanf("%s", reg->name);
						printf("\e[9;41H");
						flag = 1;
						break;
					case 1:
						get_passwd(passwd1);
						printf("\e[11;45H");
						flag = 2;
						break;
					case 2:
						get_passwd(passwd2);
						if (strcmp(passwd1, passwd2) == 0)
							strcpy(reg->passwd, passwd2);
						else
						{
							printf("\e[0m\e[20;42H\e[?25l\e[31m密码不一致\e[0m");
							exitflag = 1;
						}
						printf("\e[13;41H");
						flag = 3;
						break;
					case 3:
						scanf("%d", &reg->age);
						printf("\e[15;47H");
						flag = 4;
						break;
					case 4:
						{
							while (1)
							{
								char ch = getchar();
								if (ch == 'M' || ch == 'm' || ch == 'W' || ch == 'w')
								{
									reg->sex = ch;
									printf("\e[17;45H");
									flag = 5;
									break;
								}
								else
								{
									printf("\e[0m\e[20;37H\e[?25l\e[31m请输入M、m、W、w\e[0m");
									printf("\e[15;47H");
									flag = 4;
								}
							}
						}
						break;
					case 5:
						scanf("%s", reg->message);
						printf("\e[0m\e[19;45H\e[34m注册\e[0m");
						flag = 6;
						break;
					case 6:
						return 0;
						break;
				}					
				break;
			}
		}
		if (exitflag == 1)
		{
			exitflag = 0;
			break;
		}
	}
	return -1;
}


/*功能：主界面函数*/
/*参数：无*/
/*返回值：无*/
void menu_interface(int flag)
{
	switch (flag)
	{
		case 0:
			printf("\e[4;32H\e[30m\e[?25l签名:\e[0m");
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;32H\e[34m联系人\e[0m");
			break;
		case 1:
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;42H\e[34m群\e[0m");
			break;
		case 2:	
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[9;32H\e[34m好友\e[0m");
			break;
		case 3:
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[10;32H\e[34m同事\e[0m");
			break;
		case 4:
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[11;32H\e[34m同学\e[0m");
			break;
		case 5:
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[12;32H\e[34m亲人\e[0m");
			break;
		case 6:
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[4;32H\e[34m签名:\e[0m");
			break;
		case 7:
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[22;42H\e[34m退出\e[0m");
			break;
		case 8:
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[?25h\e[13;32H\e[43m\e[0m");
			break;
		case 9:
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[14;32H\e[43m\e[0m");
			break;
		case 10:
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[15;32H\e[43m\e[0m");
			break;
		case 11:
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[16;32H\e[43m\e[0m");
			break;
		case 12:
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[17;32H\e[43m\e[0m");
			break;
		case 13:
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[18;32H\e[43m\e[0m");
			break;
		case 14:
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[19;32H\e[43m\e[0m");
			break;
		case 15:
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[20;32H\e[43m\e[0m");
			break;
		case 16:
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[21;32H\e[43m\e[0m");
			break;
		case 17:
			printf("\e[7;42H\e[30m群\e[0m");
			printf("\e[22;42H\e[30m退出\e[0m");
			printf("\e[9;32H\e[30m好友\e[0m");
			printf("\e[10;32H\e[30m同事\e[0m");
			printf("\e[11;32H\e[30m同学\e[0m");
			printf("\e[12;32H\e[30m亲人\e[0m");
			printf("\e[7;32H\e[30m联系人\e[0m");
			printf("\e[4;32H\e[30m签名:\e[0m");
			printf("\e[22;32H\e[43m\e[0m\e[?25h");
			break;
	}	

	return;
}


/*功能：密码获取界面*/
/*参数：无*/
/*返回值：无*/
int getpswd(struct passwd *wd)
{	
	interface(5, 16, 25, 60);
	printf("\e[6;40H找回密码");
	printf("\e[8;32H请输入你的帐号");
	printf("\e[9;32H\e[?25h\e[4m                   \e[9;32H");
	scanf("%d", &wd->account);
	printf("\e[4m");
	printf("\e[0m\e[10;30H请输入密码保护问题答案");
	printf("\e[11;32H\e[?25h\e[4m                   \e[11;32H");
	scanf("%s", wd->message);
	printf("\e[4m\e[0m");
	return 0;
}

