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
int MultiFunction(const char * func_name,int argv[],int argc)
{
		if(strncmp(func_name,"foo",3)&&argc==3)
		{
			return foo(argv[0],argv[1],argv[2]);
		}
		else if(strncmp(func_name,"plus",4)&&argc==2)
		{
			return plus(argv[0],argv[1]);
		}
		else if(strncmp(func_name,"sub",3)&&argc==3)
		{
			return sub(argv[0],argv[1]);
		}
}
