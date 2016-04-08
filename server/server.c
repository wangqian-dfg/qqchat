/*功能：client.h是客户端主函数*/
/*时间：2014—3-23*/
/*版本：1.0*/

#include "server.h"

/*功能：服务器主函数*/
/*参数：无*/
/*返回值：0代表成功 -1 代表失败*/
int main(void)
{
	if (access("./user_data", F_OK) != 0)
	{
		FILE *fp = fopen("user_data", "w");
		fclose(fp);
	}
	read_file();
	start_tcp();
	return 0;
}

/*功能：启动服务器tcp服务*/
/*参数：无*/
/*返回值：无*/
void start_tcp(void)
{
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	int n = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(int));
	struct sockaddr_in ski;

	ski.sin_family = AF_INET;
	ski.sin_port = htons(6000);
	ski.sin_addr.s_addr = inet_addr("192.168.1.1");

	int res = bind(lfd, (struct sockaddr *)&ski, sizeof(ski));
	ERROR(res, -1, "server bind error", );
	listen(lfd, 5);
	int cfd;
	pthread_t tid;

	while (1)
	{
		cfd = accept(lfd, NULL, NULL);	
		pthread_create(&tid, NULL, pthread_clientdo, &cfd);
		pthread_detach(tid);
	}

	return;
}

/*功能：线程函数*/
/*参数：arg地址*/
/*返回值：无*/
void *pthread_clientdo(void *arg)
{
	int cfd = *(int *)arg;
	char buf[1024] = {0};
	while (1)
	{
		bzero(buf, sizeof(buf));
		if (recv(cfd, buf, sizeof(buf), 0) == 0)
		{
			printf("用户%d退出\n", cfd);
			return 0;
		}
	
		switch(*(int *)buf)
		{
			case REGISE:
				{	
					do_regise(cfd, buf);
					break;
				}
			case LOGIN:
				{
					do_login(cfd, buf);
					break;
				}
			case CHAT:
				{
					break;
				}
			case LOGOUT:
				{
					do_logout(cfd, buf);
					break;
				}
			case PASSWD:
				{
					do_passwd(cfd, buf);
					break;
				}
			case EXIT:
				{
					break;
				}
			default:
				break;
		}	
	} 
	return;
}

/*功能：退出函数*/
/*参数：cfd 通信套接字， buf缓冲*/
/*返回值：无*/
void do_logout(int cfd, char *buf)
{
	struct logout *out = (struct logout *)buf;
	node_t *temp = online_head->next;
	struct login *tep;
	struct login *log;
	node_t *otemp, *otemp2;
	struct regise *tep2;
	while (temp != online_head)
	{
		
		tep = (struct login *)temp->data;
		if (out->account == tep->account)
		{
			out->result = SUCCESS;
			delete_me_clist(online_head, out, cmp_out);
			send(cfd, out, sizeof(struct logout), 0);
			node_t *temp2 = alluser_head->next;

			while (temp2 != alluser_head)
			{
				tep2 = (struct regise *)temp2->data;
			
				otemp = online_head->next;
				while (otemp != online_head)
				{
					log = (struct login *)otemp->data;
					otemp2 = online_head->next;
					while (otemp2 != online_head)
					{
						send(log->cfd, otemp2->data, sizeof(struct login), 0);
						otemp2 = otemp2->next;
					}
					if (otemp2 == online_head)
					{
						log->result = OVER;
						send(log->cfd, log, sizeof(struct login), 0);
					}
					otemp = otemp->next;
				}
				temp2 = temp2->next;
			}
		}
		temp = temp->next;
	}
	if (temp == online_head)
	{
		out->result = FAIL;
		send(cfd, out, sizeof(struct logout), 0);
	}
	return;
}


/*功能：登录密码验证函数*/
/*参数：cfd 通信套接字， buf缓冲*/
/*返回值：无*/
void do_passwd(int cfd, char *buf)
{
	struct passwd *wd = (struct passwd *)buf;
	node_t *temp = alluser_head->next;
	struct regise *tep;
	while (temp != alluser_head)
	{
		
		tep = (struct regise *)temp->data;
		if (wd->account == tep->account && strcmp(wd->message, tep->message) == 0)
		{
			wd->result = SUCCESS;
			strcpy(wd->passwd, tep->passwd);
			send(cfd, wd, sizeof(struct passwd), 0);
		}
		temp = temp->next;
	}
	if (temp == alluser_head)
	{
		wd->result = FAIL;
		send(cfd, wd, sizeof(struct passwd), 0);
	}
	return;
}

/*功能：执行登录操作函数*/
/*参数：cfd 通信套接字， buf缓冲*/
/*返回值：无*/
void do_login(int cfd, char *buf)
{
	struct login *log = (struct login *)buf;
	node_t *temp = alluser_head->next;
	node_t *otemp, *otemp2;
	struct regise *tep;
	log->cfd = cfd;

	while (temp != alluser_head)
	{
		tep = (struct regise *)temp->data;
		if (log->account == tep->account && strcmp(log->passwd, tep->passwd) == 0)
		{
			log->result = SUCCESS;
			strcpy(log->name, tep->name);
			insert_clist(online_head, log, sizeof(struct login));
			send(log->cfd, log, sizeof(struct login), 0);
			
			otemp = online_head->next;
			while (otemp != online_head)
			{
				log = (struct login *)otemp->data;
				otemp2 = online_head->next;
				while (otemp2 != online_head)
				{
					send(log->cfd, otemp2->data, sizeof(struct login), 0);
					otemp2 = otemp2->next;
				}
				if (otemp2 == online_head)
				{
					log->result = OVER;
					send(log->cfd, log, sizeof(struct login), 0);
				}
				log->result = SUCCESS;
				otemp = otemp->next;
			}
			break;
		}
		temp = temp->next;
	}
	if (temp == alluser_head)
	{
		log->result = FAIL;
		send(log->cfd, log, sizeof(struct login), 0);
	}
	return;
}


/*功能：执行注册函数*/
/*参数：cfd 通信套接字， buf缓冲*/
/*返回值：无*/
void do_regise(int cfd, char *buf)
{
	struct regise *reg = (struct regise *)buf;
	struct mess mess;
	if (save_data(reg) == -1)
	{
		mess.mess = FAIL;	
	}
	else
	{
		mess.account = account - 1;
		mess.mess = SUCCESS;
	}
	printf("%d\n%s\n", reg->account, reg->passwd);
	send(cfd, &mess, sizeof(struct mess), 0);
	ERROR(write_file(), 0, "success", );
	return;
}


/*功能：保存数据函数*/
/*参数：reg 未注册的数据*/
/*返回值：无*/
int save_data(struct regise *reg)
{
	int i = 0;
	reg->account = account_f(&account);
	i = insert_clist(alluser_head, reg, sizeof(struct regise));	
	ERROR(i, -1, "insert", -1);
	write_file();	
	return 0;
}


/*功能：写入文件函数*/
/*参数：无*/
/*返回值：0代表成功 -1 代表失败*/
int write_file(void)
{
	FILE *fp = fopen("user_data", "w");
	ERROR(fp, NULL, "open file", -1);
	int i;
	node_t *temp = alluser_head->next;

	fwrite(&account, sizeof(int), 1, fp);
	for (i = 0; i < account - 1000 ; i++)
	{
		fwrite(temp->data, sizeof(struct regise), 1, fp);
		temp = temp->next;	
	}

	fclose(fp);
	return 0;
}


/*功能：读取文件函数*/
/*参数：无*/
/*返回值：无*/
void read_file(void)
{
	FILE *fp = fopen("user_data", "r");
	ERROR(fp, NULL, "open read", );
	online_head = create_clist();
	ERROR(online_head, NULL, "create clist", );
	alluser_head = create_clist();
	ERROR(alluser_head, NULL, "create clist", );

	struct regise reg;
	int i;
	fread(&account, sizeof(int), 1, fp);	
	for (i = 0; i < account - 1000; i++)
	{
		fread(&reg, sizeof(reg), 1, fp);
		insert_clist(alluser_head, &reg, sizeof(reg));
	}
	fclose(fp);
	return;
}
