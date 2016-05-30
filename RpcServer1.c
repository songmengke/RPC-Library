#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
	int server_fd,client_fd;
	struct sockaddr_in myaddr;
	struct sockaddr_in clientaddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	myaddr.sin_port=htons(4600);
	int clientaddr_len=sizeof(clientaddr);
	char buf[]="songmengke\0";
	//socket
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	if(server_fd==-1)
	{
		perror("socket error");
		exit(1);
	}
	//bind
	if(bind(server_fd,(struct sockaddr *)&myaddr,sizeof(myaddr))==-1)
	{
		perror("bind error");
		exit(1);
	}
	//listen
	if(listen(server_fd,20)==-1)
	{
		perror("listen error");
		exit(1);
	}
	printf("listening~\n");
	//accept
	
	client_fd=accept(server_fd,(struct sockaddr *)&clientaddr,&clientaddr_len);
	if(client_fd==-1)	
	{
		perror("accept error");
		exit(1);
	}
	send(client_fd,buf,strlen(buf),0);
	printf("send to client\n");
	close(client_fd);

	close(server_fd);
}
