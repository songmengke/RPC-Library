#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/times.h>
#include<sys/select.h>
int main()
{
	int server_fd;
	int maxfdp;//描述符最大值
	struct sockaddr_in myaddr;
	fd_set fds;//使用select方法
	struct timeval timeout={3,0};
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=inet_addr("115.159.44.20");
	myaddr.sin_port=htons(4600);
	char buf[16];
	
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	while(1)
	{
		FD_ZERO(&fds);
		FD_SET(server_fd,&fds);
		maxfdp=server_fd+1;
		switch(select(maxfdp,&fds,&fds,NULL,&timeout))
		{
			case -1:
				exit(-1);break;
			case 0:
				break;
			default:
				if(FD_ISSET(server_fd,&fds))
				{
					sleep(1);
					recv(server_fd,buf,16,0);
					
					printf("get message: %s\n",buf);

				}
		}
	}

	/*
	if(connect(server_fd,(struct sockaddr *)&myaddr,sizeof(myaddr))==-1)
	{
		perror("connect error");
		exit(1);
	}*/
	close(server_fd);
}

