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
int main(int argc,char **argv)
{
	int server_fd,i;
	struct sockaddr_in myaddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=inet_addr("115.159.44.20");//设定服务器静态IP
	myaddr.sin_port=htons(4600);
	char buf[50]="call ";//要发送给服务器的字符串
	strcat(buf,argv[1]);
	strcat(buf," ");
	strcat(buf,argv[2]);
	printf("%d\n",argunum);
	for(i=0;i<argunum+1;i++)
	{
		strcat(buf,"\r\n");
		strcat(buf,argv[i+argunum]);
	}
	strcat(buf,"\r\n\0");
	printf("字符串长度:%d",strlen(buf));

	char RecvBuf[100];//用来接收服务器数据的缓冲区
	server_fd=socket(AF_INET,SOCK_STREAM,0);//创建要连接的服务器socket描述符
	if(connect(server_fd,(struct sockaddr *)&myaddr,sizeof(myaddr))==-1) //用创建好的描述符来建立连接
	{
		perror("connect error");
		exit(1);
	}
	send(server_fd,buf,sizeof(buf),0);//连接成功之后即发送消息
	printf("send to server %s\n",buf);
	int RecvNum=recv(server_fd,RecvBuf,100,0);//发送完消息之后进行接收操作
	if(RecvNum>0) //若接收到的内容不为空，即在屏幕上打印
	{
		RecvBuf[RecvNum]='\0';
		printf("receive from server %s\n",RecvBuf);
	}
	close(server_fd);
	return 0;
}

