/*
* AMErrno.h
*
*  Created on: 2009-11-19
*      Author: qinghua.liqh
*/
#ifndef _AM_ERRNO_H_
#define _AM_ERRNO_H_
#include "AMConfig.h"


/*
错误码说明：
1). 在没有特别声明和特殊用途下, 所有错误码返回都用负数表示; 
2). 其中  -0x000001  ~ -0xFFFFFF用作系统错误码;
      -0x1000000 ~ -0x0x7FFFFFFF用作自定义错误码;
3). 每个模块都有自己特定的错误码范围, 并且同其它模块不重复, 并且单个模块最多可以定义
    0x1000(4096)个错误码;
4). 从-0x001到-0xFFF是系统预留, 用作模块无关的错误码定义;
5). 在没有特别声明和特殊用途下,0一般表示成功
6). 模块错误码定义, 现提供一个 AME_****_BASE, 之后再定义一个枚举, 例如:
    //条件变量
    #define AME_COND_BASE               -0x4000
    enum 
    {
        AME_COND_SCUESS = AME_SCUESS,		//成功
	    AME_COND_ERROR = AME_COND_BASE,  	//失败
	    AME_COND_BUSY,			            //正在使用
	    AME_COND_MUTEX_DIFF,		        //其它线程正在等待, 但是用的是不同Mutex
	    AME_COND_TIMEOUT,			        //timewait超时
        AME_COND_NOT_OWN_MUTEX,             //当前线程不拥有mutex
    };
*/
#define AME_SCUESS              0               //成功
#define AME_SYSTEM_MAX         -0x001           //系统预留最大      
#define AME_SYSTEM_MIN         -0xFFF           //系统预留最小
#define AME_MODULE_MAX         -0x000001        //模块最大     
#define AME_MODULE_MIN         -0xFFFFFF        //模块最小
#define AME_USER_MAX           -0x1000000       //用户定义最大
#define AME_USER_MIN           -0x0x7FFFFFFF    //用户定义最小

#define AME_SYSTEM_BASE        AME_SYSTEM_MIN   //系统错误码Base
#define AME_MODULE_BASE        AME_MODULE_MIN   //模块错误码Base
#define AME_USER_BASE          AME_USER_MIN     //用户定义错误码Base

//错误码定义.
#define AME_ERROR                   -1  //一般错误.
#define AME_GETTIMEOFDAY            -2
#define AME_ARG_AINVALID            -3  //参数不合法.
#define AME_MALLOC_ERROR			-4
#define AME_UNIMPL_METHOD			-5	//没有实现的方法

//线程
#define AME_THREAD_BASE             -0x2000

enum
{
    AME_THREAD_SCUESS = AME_SCUESS,  
    AME_THREAD_ERROR  = AME_THREAD_BASE,
    AME_THREAD_RUNNING,				//还在运行
};

//Mutex
#define AME_MUTEX_BASE              -0x3000
enum 
{
    AME_MUTEX_SCUESS = AME_SCUESS,    		//成功
    AME_MUTEX_ERROR  = AME_MUTEX_BASE,  	//失败
    AME_MUTEX_BUSY			                //正被锁定
};

//条件变量
#define AME_COND_BASE               -0x4000
enum 
{
    AME_COND_SCUESS = AME_SCUESS,		//成功
	AME_COND_ERROR = AME_COND_BASE,  	//失败
	AME_COND_BUSY,			            //正在使用
	AME_COND_MUTEX_DIFF,		        //其它线程正在等待, 但是用的是不同Mutex
	AME_COND_TIMEOUT,			        //timewait超时
    AME_COND_NOT_OWN_MUTEX,             //当前线程不拥有mutex
};
//Socket
#define AME_SOCKET_BASE             -0x5000
//错误码.
enum
{
    AME_SOCKET_SCUESS = AME_SCUESS,         //成功.
    AME_SOCKET_ERROR  =  AME_SOCKET_BASE,   //一般错误.
    AME_SOCKET_NORESOURCE,                  //没有足够的内核资源
    AME_SOCKET_SOCKTNOSUPPORT,              //socket type is not supported 
    AME_SOCKET_PROTONOSUPPORT,              //协议不支持.
    AME_SOCKET_AFNOSUPPORT,                 //address family is not supported
    AME_SOCKET_EACCES,                      //Permission is denied. 
    AME_SOCKET_AINVALID,                    //参数不合法。
    AME_SCOKET_LISTENNOTCALL,               //listen没有调用
    AME_SOCKET_ADDRINUSE,                   //网络地址正在使用  
    AME_SOCKET_NOTBIND,                     //bind没有调用
    AME_SOCKET_BUFFERNOTENOUGH,             //Buffer不够
    AME_SOCKET_TIMEDOUT,                    //超时. 
    AME_SOCKET_ISCONN,                      //已经连接
    AME_SOCKET_NOTCONN,                     //网络没有连接 
    AME_SOCKET_NETUNREACH,                  //网络不可达.
    AME_SCOKET_CONNREFUSED,                 //远程主机没有listen
    AME_SOCKET_WOULDBLOCK,                  //阻塞状态。
    AME_SOCKET_NETRESET,                    //已经RESET了
    AME_SOCKET_SHUTDOWN,                    //被关闭
	AME_SOCKET_HOST_NOT_FOUND,    
	AME_SOCKET_TRY_AGAIN,    
	AME_SOCKET_NO_RECOVERY,    
	AME_SOCKET_NO_DATA,    
};
//Http
#define AME_HTTP_BASE               -0x6000


//Looper, Handler, Message
#define AME_LOOPER_BASE             -0x7000
enum
{
     AME_LOOPER_SCUESS      = AME_SCUESS,
     AME_LOOPER_LOOPER_NULL = AME_LOOPER_BASE,
     AME_LOOPER_HANDLE_NULL,
     AME_LOOPER_MESSAGE_NULL,	
     AME_LOOPER_CALLBACK_NULL,	
     AME_LOOPER_HANDLE_INVALID,
     AME_LOOPER_LOOPER_INVALID,
     AME_LOOPER_HANDLE_NOT_EXIST,
     AME_LOOPER_MESSAGE_NOT_EXIST,
     AME_LOOPER_ALLOC_MEMORY_ERROR,
     AME_LOOPER_LOOPER_NOT_STARTED,
     AME_LOOPER_TIMEVAL_NULL,
     AME_LOOPER_TIMEVAL_INVALID,
     AME_LOOPER_OTHER_ERROR
};

#define AME_TIMER_BASE              -0x8000
enum
{
	AME_TIMER_SCUESS      = AME_SCUESS,
	AME_TIMER_CREATE_ERR = AME_TIMER_BASE,
	AME_TIMER_HAS_FINISHED,
};
#endif //end of _AM_ERRNO_H_
