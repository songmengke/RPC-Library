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
int toStr(char val[][100],char *str)
{
	int i=0;
	int len=strlen(str);
	int tmp=0;
	int number=0;
	for(i=0;i<len-2;i++)
	{
		if(str[i]=='r'&&str[i+1]=='n')
		{
			val[number++][tmp]='\0';
			tmp=0;
			i+=1;
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
	return number;
}
int main(int argc ,char **argv)
{	
	if(argc<2) return 0;
	int val[120],i;
	int number =0;
	char mp[120][100];
	//number=toStr(mp,argv[1]);
	//for(i=0;i<number;i++)
	//{
//		printf("%s \n",mp[i]);
//	}
	number = toStr(mp,argv[1]);
	printf("number = %d\n",number);
	for(i=0;i<number;i++)
		printf("%s\n",mp[i]);
	return 0;
}
