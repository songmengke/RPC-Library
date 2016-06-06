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
	argument=&a[0];//用于保存参数值
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
		maxfdp=server_fd>client_fd?server_fd+1:client_fd+1;//将描述符最大值保存到maxfdp
		switch(select(maxfdp,&fds,&fds,NULL,&timeout))
		{
			case -1:
				exit(-1);
				break;
			case 0:
				sleep(2);
				printf("time out~ \n");//超时提示
				break;
			default:
				if(FD_ISSET(client_fd,&fds))
				{
					sleep(2);
					char ReplyTest[30];//用于保存计算后的结果用于发送
					int rnum=recv(client_fd,buf,50,0);//接收客户端数据
					int res=0;//用于保存计算后返回的整型数据
					buf[rnum]='\0';
					printf("Calculating....\n");
					spile(buf,function_name,&argc,argument);//解析客户端请求
					/*
					printf("函数名:%s\n",function_name);
					printf("参数个数:%d\n",argc);
					for(i=0;i<argc;i++)
					{
						printf("参数值%d---%d \n",i+1,a[i]);
					}
					*/
					res=MultiFunction(function_name,a,argc);//调用函数库计算并返回
					printf("%d\n",res);//打印计算结果
					sprintf(ReplyTest,"%d",res);//将整型数据转换为字符串类型用于发送

					int snum=send(client_fd,ReplyTest,strlen(ReplyTest),0);//发送结果
					printf("send result %d bytes to client\n ",snum);
					close(client_fd);
				}
		}
	}
	close(server_fd);
}
