#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main()
{
	int server_fd;
	struct sockaddr_in myaddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=inet_addr("115.159.44.20");
	myaddr.sin_port=htons(4600);
	char buf[16];
	
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	if(server_fd==-1)	
	{
		perror("socket error");
	}
	if(connect(server_fd,(struct sockaddr *)&myaddr,sizeof(myaddr))==-1)
	{
		perror("connect error");
		exit(1);
	}
	recv(server_fd,buf,16,0);
	printf("get message: %s\n",buf);
	close(server_fd);
}

