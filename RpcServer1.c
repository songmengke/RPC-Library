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
int main()
{
	int server_fd;
	int client_fd;
	struct sockaddr_in myaddr;
	struct sockaddr_in clientaddr;
	int clientaddr_len=sizeof(clientaddr);
	int maxfdp;
	fd_set fds;
	struct timeval timeout={3,0};
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	myaddr.sin_port=htons(4600);
	char buf[100];
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
	while(1)
	{
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
					char ReplyTest[]="calculate result";
					int rnum=recv(client_fd,buf,100,0);
					printf("%d\n",rnum);
					buf[rnum]='\0';
					printf("receive from client %s\n",buf);
					printf("Calculating....\n");
					int snum=send(client_fd,ReplyTest,sizeof(ReplyTest),0);
					printf("send result %d butes to client\n ",snum);
					close(client_fd);
				}
		}
	}
	

	close(server_fd);
}
