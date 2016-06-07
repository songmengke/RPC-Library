int foo(int a,int b,int m)
{
		return a+b*m;
}
int plus(int a,int b)
{
		return a+b;
}
int sub(int a,int b)
{
		return a-b;
}
int plus4(int a,int b,int c,int d)
{
		return a+b+c+d;
}
int MultiFunction(char func_name[],int argv[],int argc)
{
		//将接收到的函数名，参数个数与服务器中保存的相比较
		//匹配到则进行调用
		if((strncmp(func_name,"foo",3)==0)&&(argc==3))
		{
			return foo(argv[0],argv[1],argv[2]);
		}
		else if((strncmp(func_name,"plus",4)==0)&&(argc==2))
		{
			return plus(argv[0],argv[1]);
		}
		else if((strncmp(func_name,"sub",3)==0)&&(argc==2))
		{
			return sub(argv[0],argv[1]);
		}
		else if((strncmp(func_name,"plus4",5)==0)&&(argc==4))
		{
			return plus4(argv[0],argv[1],argv[2],argv[3]);
		}
		else 
			return 0;
}
int toStr(char val[][100],char *str)
{
		int i=0;
		int len=strlen(str);
		int tmp=0;
		int number =0 ;
		for(i=0;i<len-2;i++)
		{
				if(str[i]=='\r'&&str[i+1]=='\n')
				{
						val[number++][tmp]='\0';
						tmp=0;
						i++;
				}
				else if(str[i]==' ')
				{
						val[number++][tmp]='\0';
						tmp=0;
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
void spile(char *str,char *fun_name,int *argunum,int arguval[])
{
		char val[100][100];
		int number=0;
		int i;
		int *pi;
		number=toStr(val,str);
		strcpy(fun_name,val[1]);//将函数名保存到fun_name
		*argunum=number-3;//将参数个数保存在argunum所指向的单元中
		for(i=0,pi=arguval;i<number-3;i++,pi++)
		{
				*pi=atoi(val[i+3]);//将解析出来的参数值保存到arguval数组中
		}
}













