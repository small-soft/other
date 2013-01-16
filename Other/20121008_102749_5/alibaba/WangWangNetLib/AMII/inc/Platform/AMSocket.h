/*
* AMSocket.h
*
*  Created on: 2009-11-18
*      Author: qinghua.liqh
*/

#ifndef _AM_SOCKET_H_
#define _AM_SOCKET_H_
#include "AMSocketConfig.h"
#include "AMTime.h"

//socket支持的
#define	AMSOCK_STREAM	1
#ifdef AM_SOCKET_SUPPORT_UDP
#define	AMSOCK_DGRAM	2
#endif

//opt支持的选项
#ifdef AM_SOCKET_SUPPORT_OPTION
#endif

//ioctl支持的选项
#ifdef AM_SOCKET_SUPPORT_IOCTL
#endif

//地址格式
#define AMAF_INET 2  

//协议支持
#define	AMIPPROTO_IP		0x100
#define	AMIPPROTO_TCP		6
#define	AMIPPROTO_UDP		17

//socket地址.
#define __AM_SOCK_SIZE__  16
struct AMInAddr {
    union {
        struct { AMUInt8 s_b1, s_b2, s_b3, s_b4; } S_un_b;
        struct { AMUInt16 s_w1, s_w2; } S_un_w;
        AMUInt32 S_addr;
    } S_un;
};

#ifndef _SOCKET_IMP_
#define	AMS_addr	S_un.S_addr
#endif

struct AMSockAddr{
    AMUInt16	sa_family;
    AMUInt16    sa_port;	
    AMChar	    sa_data[12];	
};

struct AMSockAddrIn {
    AMUInt16 sin_family;
    AMUInt16 sin_port;
    struct AMInAddr sin_addr;
    AMUChar __pad[__AM_SOCK_SIZE__ - sizeof(AMUInt16) - sizeof(AMUInt16) - sizeof(struct AMInAddr)];
};

//特殊IP地址.
#define	AMINADDR_ANY			(AMUInt32)0x00000000

//shutdown支持的选项.
enum {
    AMSHUT_RD = 0,        /* no more receptions */
#define AMSHUT_RD         AMSHUT_RD
    AMSHUT_WR,            /* no more transmissions */
#define AMSHUT_WR         ASHUT_WR
    AMSHUT_RDWR           /* no more receptions or transmissions */
#define AMSHUT_RDWR       AMSHUT_RDWR
};

typedef enum
{
	eIAPUserChoose = 0, //让用户选择网络接入点
	eIAPSysDefault 		//无需用户选择网络接入点
}IAPMode;

#define AMSocketIAPInit	      	a_IAPInit
#define AMSocketIAPUnInit 		a_IAPUnInit
#define AMSocketIAPGet 			a_IAPGet

#ifdef SOCKET_ASYNC
	/**********************************************************************************
	 * asyncronize socket start here.
	 */
	typedef enum
	{
		eSocketInit,
		eSocketNotReady,
		eSocketConnecting,
		eSocketConnected,
		eSocketConnectFail,
		eSocketWaiting,
		eSocketSending,
		eSocketSendOK,
		eSocketSendFail,
		eSocketRecving,
		eSocketRecv,
		eSocketOverflowWarning,
		eSocketRecvInvalid,
		eSocketErrorEof,
		eSocketServerTerminated,
		eSocketClose,
		eSocketShutdown,
		eSocketError
	}SocketStatus;

	typedef void (*SocketHandle)(AMInt32 reference, AMInt32 socket, SocketStatus status);

	typedef struct
	{
		SocketHandle	connCallback;
		SocketHandle	recvCallback;
		SocketHandle	sendCallback;
		AMInt32			iap;
		AMInt32			reference;
	}SocketASync;
	
	#define AMSocketAcceptASync          a_acceptASync
	#define AMSocketBindASync            a_bindASync
	#define AMSocketConnectASync         a_connectASync
	#define AMSocketListenASync          a_listenASync
	#define AMSocketRecvASync            a_recvASync
	#define AMSocketSendASync            a_sendASync
	#define AMSocketASync                a_socketASync
	#define AMSocketShutdownASync        a_shutdownASync
	#define AMSocketCloseASync           a_closeASync
	/*	
	 * asyncronize socket start here.
	 **********************************************************************************/
#else
	
	#ifndef _SOCKET_IMP_
	#define AMSocketAccept          a_accept
	#define AMSocketBind            a_bind
	#define AMSocketConnect         a_connect
	#define AMSocketListen          a_listen
	#define AMSocketRecv            a_recv
	#define AMSocketSend            a_send
	#define AMSocket                a_socket
	#define AMSocketShutdown        a_shutdown
	#define AMSocketClose           a_close
	#define AMSocketTimeOutConnect  a_syn_connect       //超时返回的connect
	#endif

#endif

#ifdef __cplusplus 
extern "C" {
#endif

	ASOCKET_DLL_EXPORT AMInt32 a_IAPInit(IAPMode iapMode);
	ASOCKET_DLL_EXPORT AMVoid  a_IAPUnInit();
	ASOCKET_DLL_EXPORT AMInt32 a_IAPGet();
		
#ifdef SOCKET_ASYNC
    ASOCKET_DLL_EXPORT AMInt32 a_acceptASync(AMInt32 fd, struct AMSockAddr * addr, AMSize_t * len);
    ASOCKET_DLL_EXPORT AMInt32 a_bindASync(AMInt32 fd, struct AMSockAddr * addr, AMSize_t len);
    ASOCKET_DLL_EXPORT AMInt32 a_connectASync(AMInt32 fd, struct AMSockAddr *addr, AMSize_t len);
    ASOCKET_DLL_EXPORT AMInt32 a_listenASync(AMInt32 fd, AMInt32 backlog);
    ASOCKET_DLL_EXPORT AMInt32 a_recvASync(AMInt32 fd, AMChar * buffer, AMSize_t len, AMInt32 flags);
    ASOCKET_DLL_EXPORT AMInt32 a_sendASync(AMInt32 fd, const AMChar * buffer, AMSize_t len, AMInt32 flags);
    ASOCKET_DLL_EXPORT AMInt32 a_socketASync(SocketASync* sa, AMInt32 type, AMInt32 protocol);
    ASOCKET_DLL_EXPORT AMInt32 a_shutdownASync(AMInt32 fd, AMInt32 flags);
    ASOCKET_DLL_EXPORT AMInt32 a_closeASync(AMInt32 fd);
#else
    //一般API
    ASOCKET_DLL_EXPORT AMInt32 a_accept(AMInt32 fd, struct AMSockAddr * addr, AMSize_t * len);
    ASOCKET_DLL_EXPORT AMInt32 a_bind(AMInt32 fd, struct AMSockAddr * addr, AMSize_t len);
    ASOCKET_DLL_EXPORT AMInt32 a_connect(AMInt32 fd, struct AMSockAddr *addr, AMSize_t len);
    ASOCKET_DLL_EXPORT AMInt32 a_listen(AMInt32 fd, AMInt32 backlog);
    ASOCKET_DLL_EXPORT AMInt32 a_recv(AMInt32 fd, AMChar * buffer, AMSize_t len, AMInt32 flags);
    ASOCKET_DLL_EXPORT AMInt32 a_send(AMInt32 fd, const AMChar * buffer, AMSize_t len, AMInt32 flags);
    ASOCKET_DLL_EXPORT AMInt32 a_socket(AMInt32 af, AMInt32 type, AMInt32 protocol);
    ASOCKET_DLL_EXPORT AMInt32 a_shutdown(AMInt32 fd, AMInt32 flags);
    ASOCKET_DLL_EXPORT AMInt32 a_close(AMInt32 fd);
    ASOCKET_DLL_EXPORT AMInt32 a_syn_connect(AMInt32 fd, struct AMSockAddr *addr, 
        AMSize_t len, struct AMTimeval *timeout);
#endif

#ifdef __cplusplus 
}
#endif

#ifdef AM_SOCKET_SUPPORT_UDP
#ifndef _SOCKET_IMP_
#define AMSocketRecvfrom a_recvfrom
#define AMSocketSendto   a_sendto
#endif

#ifdef __cplusplus 
extern "C" {
#endif
    ASOCKET_DLL_EXPORT AMInt32 a_recvfrom(AMInt32 fd, AMChar* buffer, AMSize_t len, 
        AMInt32 flags, struct AMSockAddr * from, AMSize_t * fromlen);
    ASOCKET_DLL_EXPORT AMInt32 a_sendto(AMInt32 fd, const AMChar* buffer, AMSize_t len,
        AMInt32 flags, struct AMSockAddr * to, AMSize_t tolen);
#ifdef __cplusplus 
}
#endif
#endif

#ifdef AM_SOCKET_SUPPORT_OPTION
#ifndef _SOCKET_IMP_
#define AMSocketGetsockopt a_getsockopt
#define AMSocketSetsockopt a_setsockopt
#endif
#ifdef __cplusplus 
extern "C" {
#endif
    ASOCKET_DLL_EXPORT AMInt32 a_getsockopt(AMInt32 fd, AMInt32 level, AMInt32 optname, 
        AMPVoid optval,  AMSize_t* optlen);
    ASOCKET_DLL_EXPORT AMInt32 a_setsockopt(AMInt32 fd, AMInt32 level, AMInt32 optname, 
        AMPVoid optval,  AMSize_t optlen);
#ifdef __cplusplus 
}
#endif
#endif

#ifdef AM_SOCKET_SUPPORT_IOCTL
#ifndef _SOCKET_IMP_
#define AMSocketIoctl     a_ioctl
#define AMSocketSelect    a_select
#endif

#if defined(_WIN32)
#include <winsock2.h>
#else
#include <sys/select.h>
#endif

#define AMFdSet     fd_set
#define AMFD_ZERO   FD_ZERO
#define AMFD_CLR    FD_CLR
#define AMFD_SET    FD_SET
#define AMFD_ISSET  FD_ISSET

#ifdef __cplusplus 
extern "C" {
#endif
    ASOCKET_DLL_EXPORT AMInt32 a_ioctl(AMInt32 fd, AMInt32 request, ...);
    ASOCKET_DLL_EXPORT AMInt32 a_select(AMInt32 n, AMFdSet *readfds, AMFdSet *writefds, AMFdSet *exceptfds, struct AMTimeval *timeout); 
#ifdef __cplusplus 
}
#endif
#endif

//辅助函数.
#ifndef _SOCKET_IMP_
#define AMSocketInetAddr    a_inet_addr
#define AMSocketHtons       a_htons
#define AMSocketHtonl       a_htonl
#define AMSocketNtohl	    a_htonl
#define AMSocketNtohs	    a_htons
#define AMGetHostByName	    a_gethostbyname
#define AMSocketInit		a_init
#define AMSocketExit	    a_exit
#endif

//结构同标准BSDsocket的hostent
struct AMHostent 
{
  AMChar* h_name;
  AMChar** h_aliases;
#if defined(_WIN32)
  AMInt16 h_addrtype;
  AMInt16 h_length;
#else
  AMInt32 h_addrtype;
  AMInt32 h_length;
#endif
  AMChar** h_addr_list;
};

#ifdef __cplusplus 
extern "C" {
#endif
    ASOCKET_DLL_EXPORT AMUInt32  a_inet_addr(const AMChar* ipstr);
    ASOCKET_DLL_EXPORT AMUInt16  a_htons(AMUInt16 hs);
    ASOCKET_DLL_EXPORT AMUInt32  a_htonl(AMUInt32 hl);
    ASOCKET_DLL_EXPORT AMInt32 a_gethostbyname(struct AMHostent** host,const AMChar* name);
	ASOCKET_DLL_EXPORT AMInt32 a_init();
	ASOCKET_DLL_EXPORT AMInt32 a_exit();
#ifdef __cplusplus 
}
#endif
#endif /* _AM_SOCKET_H_ */
