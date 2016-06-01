#include<stdio.h>
#include<ctype.h>
#include<string.h>
int toInt(int *val,char *str)
{
	int tmp=0;
	int x=0;
	int i;
	int len=strlen(str);
	for(i=0;i<len;i++)
	{
		if(isdigit(str[i]))
		{
			tmp=tmp*10+str[i]-'0';
		}
		else
		{
			if(i>0&&isdigit(str[i-1]))
			{
				val[x++]=tmp;
				tmp=0;
			}
			else
			{
				continue;
			}
		}
	}
}
int main(int argc ,char **argv)
{	
	int val[120],i;
	val[0]=0;
	toInt(val,argv[1]);
	printf("%d\n",val[0]);
	for(i=1;i<=val[0];i++)
		printf("%d",val[i]);
	puts("");
	return 0;
}
