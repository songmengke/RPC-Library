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
int toStr(char val[][100],char *str)
{
	int i=0;
	int len=strlen(str);
	int tmp=0;
	int number=0;
	for(i=0;i<len-4;i++)
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
<<<<<<< HEAD
	if(argc<2) return 0;
	int val[120],i;
	int number =0;
	char mp[120][100];
	//number=toStr(mp,argv[1]);
	printf("argument number = %d\n",argc);
	//for(i=0;i<number;i++)
	//{
//		printf("%s \n",mp[i]);
//	}
=======
	char func_name[20];
	int val[120],i;
	val[0]=0;
	toInt(val,argv[1],func_name);
	printf("%d\n",val[0]);
	for(i=1;i<=val[0];i++)
		printf("%d ",val[i]);
	puts("");
	printf("%s\n",func_name);
>>>>>>> 212b53aa9418eb2a9c29438f410687c44bd5c4e7
	return 0;
}
