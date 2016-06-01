#include<stdio.h>
#include<ctype.h>
#include<string.h>
int toInt(int *val,char *str,char func[])
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
		else if(isalpha(str[i]))
		{
			func[i]=str[i];
			if((i>0)&&(!isalnum(str[i+1])))
			{
				func[i+1]='\0';
			}
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
	char func_name[20];
	int val[120],i;
	val[0]=0;
	toInt(val,argv[1],func_name);
	printf("%d\n",val[0]);
	for(i=1;i<=val[0];i++)
		printf("%d ",val[i]);
	puts("");
	printf("%s\n",func_name);
	return 0;
}
