#include "public.h"


/*功能：自动生成id*/
/*参数：int * 数据的地址*/
/*返回值：int 自加之后的值*/
int account_f(int *account)
{
	int result;
	result = (*account)++;
	return result;
}


/*功能：创建单项循环链表*/
/*参数：无*/
/*返回值：node_t * head 链表头*/
node_t *create_clist(void)
{
	node_t *head = (node_t *)malloc(sizeof(node_t));
	ERROR(head, NULL, "create clist", NULL);
	head->data = NULL;
	head->next = head;
	
	return head;
}


/*功能：向链表尾部插入成员*/
/*参数：head 链表头， data 成员数据， size 数据大小*/
/*返回值：0 成功 -1 失败*/
int insert_clist(node_t *head, void *data, int size)
{
	ERROR(head, NULL, "insert head", -1);
	ERROR(data, NULL, "insert data", -1);
	node_t *newnode = (node_t *)malloc(sizeof(node_t));
	ERROR(newnode, NULL, "insert newnode", -1);

	newnode->data = malloc(size);
	ERROR(newnode->data, NULL, "insert newnode->data", -1);
	memcpy(newnode->data, data, size);
	node_t *temp = head;

	while (temp->next != head)
	{
		temp = temp->next;
	}
	
	newnode->next = temp->next;
	temp->next = newnode;
	return 0;
}


/*功能：查找链表中的第几个元素*/
/*参数：head 链表头 index 第几个*/
/*返回值：before 找到的成员*/
node_t *find_clist(node_t *head, int index)
{
	ERROR(head, NULL, "find", NULL);
	if (index < 0)
	{
		perror("index > 0");
		return NULL;
	}
	
	node_t *before = head->next;
	int i = 0;
	while (before != head && i < index)
	{
		before = before->next;
		i++;
	}
	
	if (i != index)
	{
		perror("list end");
		return NULL;
	}

	return before;
}


/*功能：查找链表中的成员*/
/*参数：head 链表头 data 查找的数据 f比较函数*/
/*返回值：temp找到的链表*/
node_t *fcmp_clist(node_t *head, void *data, cmpfun_t f)
{
	ERROR(head, NULL, "head", NULL);
	ERROR(data, NULL, "data", NULL);
		
	node_t *temp = head->next;
	while (temp != head)
	{
		if (!f(temp->data, data))
			return temp;
		temp = temp->next;
	}
	return NULL;
}


/*功能：比较数据函数*/
/*参数：data1 数据1， data2 数据2*/
/*返回值：0代表相等 非0代表不等*/
int cmp(void *data1, void *data2)
{
	ERROR(data1, NULL, "data1", -1);
	ERROR(data2, NULL, "data2", -1);
	struct login *log1 = (struct login *)data1;
	struct login *log2 = (struct login *)data2;	

	return log1->account - log2->account;
}


/*功能：比较两个数据的值*/
/*参数：data1 数据1， data2 数据2*/
/*返回值：0代表相等 非0代表不等*/
int cmp_out(void *data1, void *data2)
{
	ERROR(data1, NULL, "data1", -1);
	ERROR(data2, NULL, "data2", -1);
	struct login *log1 = (struct login *)data1;
	struct logout *log2 = (struct logout *)data2;	

	return log1->account - log2->account;
}


/*功能：显示链表中的成员*/
/*参数：head 链表头 f比较函数*/
/*返回值：无*/
void show_all_clist(node_t *head, showfun_t f)
{
	ERROR(head, NULL, "show_all_clist head", );
	ERROR(f, NULL, "showfun_t", );
	node_t *temp = head->next;
	
	while (temp != head)
	{
		f(temp->data);
		temp = temp->next;
	}	

	return;
}


/*功能：显示某个热成员*/
/*参数：data 数据*/
/*返回值：无*/
void show(void *data)
{
	ERROR(data, NULL, "data is null", );
	struct login *log = (struct login *)data;
	printf("%d\n", log->addr.sin_port);
	return;
}


/*功能：删除链表中的成员*/
/*参数：head 链表头， data 比较数据， f比较函数*/
/*返回值：0代表成功 -1代表失败*/
int delete_me_clist(node_t *head, void *data, cmpfun_t f)
{
	ERROR(head, NULL, "head", -1);
	ERROR(data, NULL, "data", -1);

	node_t *current = head->next;
	node_t *before = head;
	while (current != head)
	{
		if (f(current->data, data))
		{
			before = current;
			current = current->next;
		}
		break;
	}
	before->next = current->next;
	free(current->data);
	free(current);
	return 0;
}


/*功能：隐藏密码函数*/
/*参数：passd 要保存的密码*/
/*返回值：无*/
void get_passwd(char *passwd)
{
	struct termios newattr, oldattr;
	tcgetattr(0, &oldattr);
	cfmakeraw(&newattr);
	int ret, i = 0;
	char key[3];
	while(1)
	{
		bzero(key, sizeof(key));
		tcsetattr(0, TCSANOW, &newattr);
		ret = read(0, key, 3);
		*(passwd + i) = *key;
		tcsetattr(0, TCSANOW, &oldattr);
		i++;
		
		if(ret == 1)
		{
			if(key[0] == 13)
				break;
		}
		printf("*");
		fflush(stdout);
	}

	*(passwd + i) = '\0';	
	
	return;
}


/*功能：获取键值函数*/
/*参数：无*/
/*返回值：0 代表成功 -1代表失败*/
int key_val(void)
{
	struct termios newattr, oldattr;
	tcgetattr(0, &oldattr);
	cfmakeraw(&newattr);
	int ret;

	char key[3]= {0};
	bzero(key, sizeof(key));
	tcsetattr(0,TCSANOW,&newattr);
	fflush(stdout);
	ret = read(0,key,3); 
	fflush(stdout);
	tcsetattr(0,TCSANOW,&oldattr);
	if(ret == 1)
	{
		if(key[0] == 13)
			return 13;

	}

	else if(ret == 3)
	{
		if (key[0] == 27 && key[1] == 91 && key[2] == 65)
			return 65;		
		if (key[0] == 27 && key[1] == 91 && key[2] == 66)
			return 66;
		if (key[0] == 27 && key[1] == 91 && key[2] == 67)
			return 67;
		if (key[0] == 27 && key[1] == 91 && key[2] == 68)
			return 68;
	}
	return 0;
}


/*功能：终端上获取一个正方形区域*/
/*参数：x 横坐标 y 纵坐标 w长 l宽*/
/*返回值：无*/
void interface(int x, int w, int y, int l)
{
	char buf[128] = {0};
	int i;
	for(i = y; i < l; i++)
		buf[i - y] = '1';
	system("clear");
	printf("\e[%d;%dH\e[45m\e[35m%s", x, y, buf);
	for (i = x; i < w; i++)
		printf("\e[%d;%dH1\e[%d;%dH1", i, y, i, l);
	printf("\e[%d;%dH%s1", w, y, buf);
	printf("\e[0m");
	return;
}


/*功能：获取本地时间*/
/*参数：i打印位置*/
/*返回值：无*/
char *mytime(int i)
{
	struct tm *local;
	time_t t;
	t = time(0);
	local = localtime(&t);

	printf("\e[%d;25H\e[31m%s\e[0m", i, asctime(local));
	fflush(stdout);
	return asctime(local);
}
