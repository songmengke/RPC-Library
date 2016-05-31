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
	struct sockaddr_in myaddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=inet_addr("115.159.44.20");
	myaddr.sin_port=htons(4600);
	char buf[]="songmengke";
	
	server_fd=socket(AF_INET,SOCK_STREAM,0);

	
	if(connect(server_fd,(struct sockaddr *)&myaddr,sizeof(myaddr))==-1)
	{
		perror("connect error");
		exit(1);
	}
	send(server_fd,buf,10,0);
	printf("send to server %s\n",buf);
	close(server_fd);
}

