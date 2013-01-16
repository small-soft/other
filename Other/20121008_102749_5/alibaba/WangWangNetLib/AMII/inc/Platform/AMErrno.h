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
������˵����
1). ��û���ر�������������;��, ���д����뷵�ض��ø�����ʾ; 
2). ����  -0x000001  ~ -0xFFFFFF����ϵͳ������;
      -0x1000000 ~ -0x0x7FFFFFFF�����Զ��������;
3). ÿ��ģ�鶼���Լ��ض��Ĵ����뷶Χ, ����ͬ����ģ�鲻�ظ�, ���ҵ���ģ�������Զ���
    0x1000(4096)��������;
4). ��-0x001��-0xFFF��ϵͳԤ��, ����ģ���޹صĴ����붨��;
5). ��û���ر�������������;��,0һ���ʾ�ɹ�
6). ģ������붨��, ���ṩһ�� AME_****_BASE, ֮���ٶ���һ��ö��, ����:
    //��������
    #define AME_COND_BASE               -0x4000
    enum 
    {
        AME_COND_SCUESS = AME_SCUESS,		//�ɹ�
	    AME_COND_ERROR = AME_COND_BASE,  	//ʧ��
	    AME_COND_BUSY,			            //����ʹ��
	    AME_COND_MUTEX_DIFF,		        //�����߳����ڵȴ�, �����õ��ǲ�ͬMutex
	    AME_COND_TIMEOUT,			        //timewait��ʱ
        AME_COND_NOT_OWN_MUTEX,             //��ǰ�̲߳�ӵ��mutex
    };
*/
#define AME_SCUESS              0               //�ɹ�
#define AME_SYSTEM_MAX         -0x001           //ϵͳԤ�����      
#define AME_SYSTEM_MIN         -0xFFF           //ϵͳԤ����С
#define AME_MODULE_MAX         -0x000001        //ģ�����     
#define AME_MODULE_MIN         -0xFFFFFF        //ģ����С
#define AME_USER_MAX           -0x1000000       //�û��������
#define AME_USER_MIN           -0x0x7FFFFFFF    //�û�������С

#define AME_SYSTEM_BASE        AME_SYSTEM_MIN   //ϵͳ������Base
#define AME_MODULE_BASE        AME_MODULE_MIN   //ģ�������Base
#define AME_USER_BASE          AME_USER_MIN     //�û����������Base

//�����붨��.
#define AME_ERROR                   -1  //һ�����.
#define AME_GETTIMEOFDAY            -2
#define AME_ARG_AINVALID            -3  //�������Ϸ�.
#define AME_MALLOC_ERROR			-4
#define AME_UNIMPL_METHOD			-5	//û��ʵ�ֵķ���

//�߳�
#define AME_THREAD_BASE             -0x2000

enum
{
    AME_THREAD_SCUESS = AME_SCUESS,  
    AME_THREAD_ERROR  = AME_THREAD_BASE,
    AME_THREAD_RUNNING,				//��������
};

//Mutex
#define AME_MUTEX_BASE              -0x3000
enum 
{
    AME_MUTEX_SCUESS = AME_SCUESS,    		//�ɹ�
    AME_MUTEX_ERROR  = AME_MUTEX_BASE,  	//ʧ��
    AME_MUTEX_BUSY			                //��������
};

//��������
#define AME_COND_BASE               -0x4000
enum 
{
    AME_COND_SCUESS = AME_SCUESS,		//�ɹ�
	AME_COND_ERROR = AME_COND_BASE,  	//ʧ��
	AME_COND_BUSY,			            //����ʹ��
	AME_COND_MUTEX_DIFF,		        //�����߳����ڵȴ�, �����õ��ǲ�ͬMutex
	AME_COND_TIMEOUT,			        //timewait��ʱ
    AME_COND_NOT_OWN_MUTEX,             //��ǰ�̲߳�ӵ��mutex
};
//Socket
#define AME_SOCKET_BASE             -0x5000
//������.
enum
{
    AME_SOCKET_SCUESS = AME_SCUESS,         //�ɹ�.
    AME_SOCKET_ERROR  =  AME_SOCKET_BASE,   //һ�����.
    AME_SOCKET_NORESOURCE,                  //û���㹻���ں���Դ
    AME_SOCKET_SOCKTNOSUPPORT,              //socket type is not supported 
    AME_SOCKET_PROTONOSUPPORT,              //Э�鲻֧��.
    AME_SOCKET_AFNOSUPPORT,                 //address family is not supported
    AME_SOCKET_EACCES,                      //Permission is denied. 
    AME_SOCKET_AINVALID,                    //�������Ϸ���
    AME_SCOKET_LISTENNOTCALL,               //listenû�е���
    AME_SOCKET_ADDRINUSE,                   //�����ַ����ʹ��  
    AME_SOCKET_NOTBIND,                     //bindû�е���
    AME_SOCKET_BUFFERNOTENOUGH,             //Buffer����
    AME_SOCKET_TIMEDOUT,                    //��ʱ. 
    AME_SOCKET_ISCONN,                      //�Ѿ�����
    AME_SOCKET_NOTCONN,                     //����û������ 
    AME_SOCKET_NETUNREACH,                  //���粻�ɴ�.
    AME_SCOKET_CONNREFUSED,                 //Զ������û��listen
    AME_SOCKET_WOULDBLOCK,                  //����״̬��
    AME_SOCKET_NETRESET,                    //�Ѿ�RESET��
    AME_SOCKET_SHUTDOWN,                    //���ر�
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
