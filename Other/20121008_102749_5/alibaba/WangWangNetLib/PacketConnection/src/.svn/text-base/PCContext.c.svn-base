#include "PCContext.h"

#ifdef AMOS
	#include "AMOS.h"
	#include "AMThread.h"

	#ifdef WIN32
	#include "winsock.h"
	#pragma comment(lib, "Ws2_32.lib")
	#else
	#include <fcntl.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <errno.h>
	#include <time.h>
	#endif

#else
	#ifdef WIN32
	#include "windows.h"
	#include "winsock.h"
	#include "stdio.h"
	#pragma comment(lib, "Ws2_32.lib")
	#endif
#endif

/************************************************************************/
// 和平台相关性的函数实现在这里
/************************************************************************/
AMInt32 PCSocketCreate(AMChar* ip, AMUInt16 port
		#ifdef AMOS
		#ifdef SOCKET_ASYNC
			, AMInt32 reference, AMInt32 iap
			, void* connCB, void* senderCB, void* readerCB
		#endif
		#endif
		)
{
#ifdef AMOS
	#ifdef SOCKET_ASYNC
		AMInt32 socketTmp;
		AMInt32 retCode;
		SocketASync sa;
		struct AMSockAddrIn address;
		
		memset(&sa, 0, sizeof(sa));
		sa.reference    = reference;
		sa.iap 			= iap;
		sa.connCallback = (SocketHandle)connCB;
		sa.recvCallback = (SocketHandle)readerCB;
		sa.sendCallback = (SocketHandle)senderCB;
		
		address.sin_family 			= AMAF_INET;
		address.sin_port 			= AMSocketHtons(port);
		address.sin_addr.AMS_addr  = AMSocketInetAddr(ip);

		socketTmp = AMSocketASync(&sa, AMSOCK_STREAM, AMIPPROTO_TCP);
		if(socketTmp > 0)
		{
			retCode = AMSocketConnectASync(socketTmp, (struct AMSockAddr*)&address, sizeof(address));
			if(retCode < 0)
			{
				AMSocketCloseASync(socketTmp);
				return retCode;
			}
		}
		
		return socketTmp;
		
	#else
		AMInt32 socketTmp;
		AMInt32 retCode;
		struct AMSockAddrIn address;

		fd_set set;

		#ifdef WIN32
		unsigned long ul = 1;
		int timeo = 5;
		#else
		struct timeval timeo = {5, 0};
		#endif

		struct timeval timeo2 = {10, 0};

		address.sin_family = AMAF_INET;
		address.sin_port = AMSocketHtons(port);
		address.sin_addr.AMS_addr = AMSocketInetAddr(ip);
	
		socketTmp=AMSocket(AMAF_INET, AMSOCK_STREAM, AMIPPROTO_TCP);

		//设置非阻塞方式连接
		#ifdef WIN32
		ioctlsocket(socketTmp, FIONBIO, (unsigned long*)&ul);
		#else
		fcntl(socketTmp, F_SETFL, fcntl(socketTmp, F_GETFL, 0) | O_NONBLOCK);
		#endif

		retCode = AMSocketConnect(socketTmp,(struct AMSockAddr*)&address,sizeof(address));
#ifdef AMOS_DEBUG
		AMPrintf("PCSocketCreate............AMSocketConnect retCode %d\n", retCode);
#endif // AMOS_DEBUG

		setsockopt(socketTmp, SOL_SOCKET, SO_SNDTIMEO, &timeo, sizeof(timeo));
		FD_ZERO(&set);
		FD_SET(socketTmp, &set);

		retCode = select(socketTmp+1, NULL, &set, NULL, &timeo2);

		if(retCode == -1)
		{
		#ifdef AMOS_DEBUG
			AMPrintf("noble:socket connect error.\n");
		#endif
			AMSocketClose(socketTmp);
			return -1;
		}
		else if(retCode == 0)
		{
		#ifdef AMOS_DEBUG
			AMPrintf("noble:socket connect timeout.\n");
		#endif
			AMSocketClose(socketTmp);
			return 0;
		}
		else
		{
			//set block mode.
			#ifdef WIN32
			ul = 0;
			ioctlsocket(socketTmp, FIONBIO, (unsigned long*)&ul);
			#else
			fcntl(socketTmp, F_SETFL, fcntl(socketTmp, F_GETFL, 0) & (~O_NONBLOCK));
			#endif

			return socketTmp;
		}

	#endif
#else
	#ifdef WIN32
		int retCode;
		struct sockaddr_in local;
		SOCKET socketTmp;

		WORD wVersionRequested;
		WSADATA wsaData;

		wVersionRequested = MAKEWORD(2, 2);
		WSAStartup( wVersionRequested, &wsaData );

		memset(&local, 0, sizeof(local));
		//必须是AF_INET,表示该socket在Internet域中进行通信
		local.sin_family=AF_INET;

		//端口号
		local.sin_port=htons(port);

		//服务器的IP地址
		local.sin_addr.S_un.S_addr=inet_addr(ip);

		//初始化Socket
		socketTmp=socket(AF_INET,SOCK_STREAM,0);

		//连接服务器
		retCode = connect(socketTmp,(LPSOCKADDR)&local,sizeof(local));
		if(retCode < 0)
		{
			closesocket(socketTmp);
			return retCode;
		}
		else
		{
			return (AMInt32)socketTmp;
		}
	#endif
#endif
}

void PcSocketClose(AMUInt32* pSocket)
{
#ifdef AMOS
	#ifdef SOCKET_ASYNC
		AMSocketCloseASync(*pSocket);
	#else
		AMSocketShutdown(*pSocket, 0x02); //SD_BOTH: 0x02
		AMSocketClose(*pSocket);
	#endif
#else
	#ifdef WIN32
		closesocket(*pSocket);
		WSACleanup();
	#endif
#endif
	*pSocket = 0;
}

AMInt32 PcSend(AMUInt32 socketFd, AMUInt8 *buffer, AMInt32 length)
{
#ifdef AMOS
	#ifdef SOCKET_ASYNC
		return AMSocketSendASync(socketFd, (AMChar*)buffer, length, 0);
	#else
		return AMSocketSend(socketFd, (AMChar*)buffer, length, 0);
	#endif
#else
	#ifdef WIN32
		return send(socketFd, buffer, length, 0);
	#endif
#endif
}

AMInt32 PcRecv(AMUInt32 socketFd, AMUInt8 *buffer, AMInt32 length)
{
	AMInt32 cnt=length;
	AMInt32 rc=0;

	while(cnt>0)
	{
	#ifdef AMOS
		#ifdef SOCKET_ASYNC
			rc = AMSocketRecvASync(socketFd,(AMChar*)buffer,cnt,0);
		#else
		{
#ifdef AMOS_DEBUG
		AMPrintf("noble:AMSocketRecv <<<<< \n");
#endif
			rc = AMSocketRecv(socketFd,(AMChar*)buffer,cnt,0);
#ifdef AMOS_DEBUG
		AMPrintf("noble:AMSocketRecv, rc=%d >>>>>\n", rc);
#endif
		}
		#endif
	#else
		#ifdef WIN32
			rc = recv(socketFd,buffer,cnt,0);
		#endif
	#endif
		if(rc < 0)
			return rc;

		if(rc == 0) 
			return length-cnt;

		buffer+=rc;
		cnt-=rc;
	}
	return length;
}

// 单位为毫秒
void PcSleep(AMUInt32 time)
{
#ifdef AMOS
	AMSleep(time);
#else
	#ifdef WIN32
		Sleep(time);
	#endif
#endif
}

AMInt32 PcThreadCreate(ThreadHandle* pThread, Runner runner, void* pModule, Runner pre, Runner post, AMInt32 now)
{
#ifdef AMOS
	return AMThreadCreate (pThread, NULL, runner, pModule);
#else
	#ifdef WIN32
		DWORD dwThreadId, dwThrdParam = 1; 
		//HANDLE hThread; 
		char szMsg[80];
	
		*pThread = CreateThread( 
			NULL,                        // no security attributes 
			0,                           // use default stack size  
			(unsigned long (WINAPI*)(void*))runner, // thread function 
			pModule,					 // argument to thread function 
			0,                           // use default creation flags 
			&dwThreadId);                // returns the thread identifier 
	
		if (*pThread == NULL) 
		{
			wsprintf( szMsg, "CreateThread failed." ); 
			MessageBox( NULL, szMsg, "main", MB_OK );
		}
		return (AMInt32)(*pThread);
	#endif
#endif
}

AMInt32 PcThreadExit(ThreadHandle* pThread)
{
#ifdef AMOS
	//nothing to do.
	AMPVoid value_ptr = NULL;
	return AMThreadWait(*pThread, &value_ptr);
#else
	#ifdef WIN32
		CloseHandle((HANDLE)(*pThread));
		return 0;
	#endif
#endif
}

void PcMutexLock(Mutex* pMutex)
{
#ifdef AMOS
	AMThreadMutexLock(pMutex);
#else
#ifdef WIN32
	DWORD dwWaitResult; 

	dwWaitResult = WaitForSingleObject( 
		*pMutex,  // handle to mutex
		INFINITE);   // five-second time-out interval
#endif
#endif
}

void PcMutexUnlock(Mutex* pMutex)
{
#ifdef AMOS
	AMThreadMutexUnlock(pMutex);
#else
#ifdef WIN32
	ReleaseMutex(*pMutex);
#endif
#endif
}

void PcMutexCreate(Mutex* pMutex)
{
#ifdef AMOS
	AMThreadMutexCreate (pMutex);
#else
#ifdef WIN32
	// Create a mutex with no initial owner.

	*pMutex = CreateMutex( 
		NULL,                       // no security attributes
		FALSE,                      // initially not owned
		NULL);						// name of mutex

	if (*pMutex == NULL) 
	{
		// Check for error.
	}
#endif
#endif
}

void PcMutexDestory(Mutex* pMutex)
{
#ifdef AMOS
	AMThreadMutexDestroy(pMutex);
	*pMutex = NULL;
#else
#ifdef WIN32
	CloseHandle((HANDLE)(*pMutex));
#endif
#endif
}

void PcSemaphoreWait(Semaphore* pSemaphore)
{
#ifdef AMOS
	while(pSemaphore->nInit <= 0)
	{
		PcSleep(100);
	}

	pSemaphore->nInit--;
#else
#ifdef WIN32
	WaitForSingleObject(*pSemaphore, INFINITE);
#endif
#endif
}

void PcSemaphoreSignal(Semaphore* pSemaphore)
{
#ifdef AMOS
	while(pSemaphore->nInit >= pSemaphore->nMax)
	{
		PcSleep(100);
	}
	pSemaphore->nInit++;
#else
#ifdef WIN32
	ReleaseSemaphore( 
		*pSemaphore,    // handle to semaphore
		1,		        // increase count by one
		NULL);			// not interested in previous count
#endif
#endif
}

void PcSemaphoreCreate(Semaphore* pSemaphore, AMInt32 initCount, AMInt32 maxCount)
{
#ifdef AMOS
	if(initCount>=0 && initCount<maxCount)
	{
		pSemaphore->nInit = initCount;
		pSemaphore->nMax  = maxCount;
	}
#else
#ifdef WIN32
	*pSemaphore = CreateSemaphore( 
		NULL,					// no security attributes
		initCount,				// initial count
		maxCount,				// maximum count
		NULL);					// unnamed semaphore

#endif
#endif
}

void PcSemaphoreDestory(Semaphore* pSemaphore)
{
#ifdef AMOS
	//nothing to do.
#else
#ifdef WIN32
	CloseHandle((HANDLE)(*pSemaphore));
#endif
#endif
}

/************************************************************************/
// PCContext* PCContextGetInstance()
/************************************************************************/
PCContext* PCContextGetInstance()
{
	static PCContext Context = {
		PCSocketCreate,
		PcSocketClose,
		PcSend,
		PcRecv,
		PcSleep,
		PcThreadCreate,
		PcThreadExit,
		PcMutexLock,
		PcMutexUnlock,
		PcMutexCreate,
		PcMutexDestory,
		PcSemaphoreWait,
		PcSemaphoreSignal,
		PcSemaphoreCreate,
		PcSemaphoreDestory
	};
	
	return &Context;
}

