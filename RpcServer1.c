#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<sys/un.h>
#include<string.h>
#include<arpa/inet.h>
#include"FunLibrary.h"
int toStr(char val[][100],char *str)
{
	int i=0;
	int len=strlen(str);
	int tmp=0;
	int number=0;
	for(i=0;i<len-2;i++)
	{
		if(str[i]=='\r'&&str[i+1]=='\n')
		{
			val[number++][tmp]='\0';
			tmp=0;
			i++;
		}
		else if(str[i]==' ')
		{
			val[number++][tmp]='\0';
			tmp=0;
		}
		else
		{
			val[number][tmp++]=str[i];
		}
	}
	if(tmp!=0)
	{
		val[number++][tmp]='\0';
	}
	return number ;

}
void spile(char *str,char *fun_name,int *argunum,int arguval[])
{
	char val[100][100];
	int number=0;
	int i;
	int *pi;
	number=toStr(val,str);
	strcpy(fun_name,val[1]);
	*argunum=number-3;
	for(i=0,pi=arguval;i<number-3;i++,pi++)//将传递过来的数组首地址赋值给pi，然后依次将参数值保存到数组中
	{
		*pi=atoi(val[i+3]);
	}

}
int main()
{
	int server_fd;//服务器使用到的socket文件描述符
	int client_fd;//用来接受连接的客户端socket文件描述符
	int i;
	struct sockaddr_in myaddr;
	struct sockaddr_in clientaddr;
	int clientaddr_len=sizeof(clientaddr);
	int maxfdp;
	fd_set fds;
	struct timeval timeout={3,0};//设置超时时间
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	myaddr.sin_port=htons(4600);//设置为静态端口，后期可更改
	char buf[100];//用来接收客户端数据的缓存区

	char *function_name;//用于保存接收的函数名
	int argc;//用于保存传过来的参数个数
	int *argument,a[100]={0};
	argument=&a[0];
	//socket
	server_fd=socket(AF_INET,SOCK_STREAM,0);//创建服务端socket描述符
	if(server_fd==-1)
	{
		perror("socket error");
		exit(1);
	}
	//bind
	if(bind(server_fd,(struct sockaddr *)&myaddr,sizeof(myaddr))==-1)//绑定server_fd描述符到本地
	{
		perror("bind error");
		exit(1);
	}
	//listen
	if(listen(server_fd,20)==-1)//监听客户端连接请求
	{
		perror("listen error");
		exit(1);
	}
	printf("listening~\n");
	while(1)
	{
		//使用select函数来检测接受的连接是否可写
		client_fd=accept(server_fd,(struct sockaddr *)&clientaddr,&clientaddr_len);
		FD_ZERO(&fds);
		FD_SET(server_fd,&fds);
		FD_SET(client_fd,&fds);
		maxfdp=server_fd>client_fd?server_fd+1:client_fd+1;
		switch(select(maxfdp,&fds,&fds,NULL,&timeout))
		{
			case -1:
				exit(-1);
				break;
			case 0:
				sleep(2);
				printf("time out~ \n");
				break;
			default:
				if(FD_ISSET(client_fd,&fds))
				{
					sleep(2);
					char ReplyTest[30];
					int rnum=recv(client_fd,buf,50,0);
					printf("%d\n",strlen(buf));
					buf[rnum]='\0';
					printf("receive from client %s\n",buf);
					printf("Calculating....\n");
					spile(buf,function_name,&argc,argument);


					printf("函数名:%s\n",function_name);
					printf("参数个数:%d\n",argc);
					for(i=0;i<argc;i++)
					{
						printf("参数值%d---%d \n",i+1,argument[i]);
					}
					int res=MultiFunction(function_name,argument,argc);
					printf("%d\n",res);
					sprintf(ReplyTest,"%d",res);

					int snum=send(client_fd,ReplyTest,sizeof(ReplyTest),0);
					printf("send result %d bytes to client\n ",snum);
					close(client_fd);
				}
		}
	}
	close(server_fd);
}
