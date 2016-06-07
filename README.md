# RPC-Library
服务器端文件：FunLibray.h  RpcServer1.c makefile
FunLibrary.h:包含了客户端要请求的函数（这里我只写了四个），以及主服务端要调用的功能函数,比如数据解析函数
RpcServer1.c:主服务端，用来接受客户端请求，并将函数调用结果根据协议发送到客户端
makefile:用来生成主服务端的可执行文件，用make命令即生成，代码比较短

客户端文件：LocalFunLibrary.h RpcMainCall.c
LocalFunLibrary.h:封装了网络连接，发送调用请求，rpc调用以及返回的所有功能函数
RpcMainCall.c：使用服务器端函数的主程序，想调用服务器端的哪个函数直接通过函数名调用即可，前提是要包含LocalFunLibrary.h文件
通过gcc生成可执行文件
