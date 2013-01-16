/*
 * AMSocket.c
 *
 *  Created on: 2009-11-18
 *      Author: qinghua.liqh
 */

#include "e32def.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "arpa/inet.h"

#include "in_sock.h"
#include "sys/socket.h"

#define _SOCKET_IMP_
#define __cplus_plus
#include "AMSocket.h"
#include "stdio.h"
#include "string.h"
#include "AMMemory.h"
#include "SymbianSocket.h"

static CNetworkAccessPoint* gpNetworkAccessPoint = NULL;

ASOCKET_DLL_EXPORT AMInt32 a_IAPInit(IAPMode iapMode)
{
	if(gpNetworkAccessPoint == NULL)
		gpNetworkAccessPoint = CNetworkAccessPoint::NewL((CNetworkAccessPoint::AccessPointMode)iapMode);
	return (AMInt32)gpNetworkAccessPoint;	
}

ASOCKET_DLL_EXPORT AMVoid a_IAPUnInit()
{
	if(gpNetworkAccessPoint != NULL)
	{
		//delete gpNetworkAccessPoint;
		AMDelete(gpNetworkAccessPoint);
		
		gpNetworkAccessPoint = NULL;
	}
}

ASOCKET_DLL_EXPORT AMInt32 a_IAPGet()
{
	return (AMInt32)gpNetworkAccessPoint;	
}

#ifdef SOCKET_ASYNC
ASOCKET_DLL_EXPORT AMInt32 a_acceptASync(AMInt32 fd, struct AMSockAddr * addr, AMSize_t * len)
{
	
}

ASOCKET_DLL_EXPORT AMInt32 a_bindASync(AMInt32 fd, struct AMSockAddr * addr, AMSize_t len)
{
	
}

ASOCKET_DLL_EXPORT AMInt32 a_connectASync(AMInt32 fd, struct AMSockAddr *addr, AMSize_t len)
{
	CNetworkSocket* socket = (CNetworkSocket*)fd;
	struct AMSockAddrIn* addrin = (struct AMSockAddrIn*)addr;

	if(socket != 0)
		return socket->Connect(a_htons(addr->sa_port), a_htonl(addrin->sin_addr.S_un.S_addr));
	else
		return 0;
}

ASOCKET_DLL_EXPORT AMInt32 a_listenASync(AMInt32 fd, AMInt32 backlog)
{
	
}

ASOCKET_DLL_EXPORT AMInt32 a_recvASync(AMInt32 fd, AMChar * buffer, AMSize_t len, AMInt32 flags)
{
	CNetworkSocket* socket = (CNetworkSocket*)fd;
	if(socket != 0)
		return socket->Read((unsigned char*)buffer, len);
	else
		return 0;
}

ASOCKET_DLL_EXPORT AMInt32 a_sendASync(AMInt32 fd, const AMChar * buffer, AMSize_t len, AMInt32 flags)
{
	CNetworkSocket* socket = (CNetworkSocket*)fd;
	if(socket != 0)
		return socket->Send((unsigned char*)buffer, len);
	else
		return 0;
}

ASOCKET_DLL_EXPORT AMInt32 a_socketASync(SocketASync* sa, AMInt32 type, AMInt32 protocol)
{
	CNetworkSocket* socket = CNetworkSocket::NewL(sa, type, protocol);
	return (AMInt32)socket;
}

ASOCKET_DLL_EXPORT AMInt32 a_shutdownASync(AMInt32 fd, AMInt32 flags)
{
	CNetworkSocket* socket = (CNetworkSocket*)fd;
	if(socket != 0)
	{
		//delete socket;
		AMDelete(socket);
	}
	return AME_SOCKET_SCUESS;
}

ASOCKET_DLL_EXPORT AMInt32 a_closeASync(AMInt32 fd)
{
	CNetworkSocket* socket = (CNetworkSocket*)fd;
	if(socket != 0)
	{
		//delete socket;
		AMDelete(socket);
	}
	return AME_SOCKET_SCUESS;
}
#else  //以下为同步接口
/*
WSANOTINITIALISED  A successful WSAStartup call must occur before using this function.  
WSAENETDOWN  The network subsystem or the associated service provider has failed.  
WSAEAFNOSUPPORT  The specified address family is not supported.  
WSAEINPROGRESS  A blocking Winsock call is in progress, or the service provider is still processing a callback function.  
WSAEMFILE  No more socket descriptors are available.  
WSAENOBUFS  No buffer space is available. The socket cannot be created.  
WSAEPROTONOSUPPORT  The specified protocol is not supported.  
WSAEPROTOTYPE  The specified protocol is the wrong type for this socket.  
WSAESOCKTNOSUPPORT  The specified socket type is not supported in this address family.  
*/
ASOCKET_DLL_EXPORT AMInt32 a_socket(AMInt32 af, AMInt32 type, AMInt32 protocol)
{
	return socket(af, type, protocol);
}
/*
WSANOTINITIALISED  A successful WSAStartup call must occur before using this function. 
WSAENETDOWN  The network subsystem has failed. 
WSAEFAULT  The addrlen parameter is too small or addr is not a valid part of the user address space. 
WSAEINTR.  The socket was closed. 
WSAEINPROGRESS  A blocking Winsock call is in progress, or the service provider is still processing a callback function. 
WSAEINVAL  The listen function was not invoked prior to this function. 
WSAEMFILE  The queue is nonempty on entry to this function, and there are no descriptors available. 
WSAENOBUFS  No buffer space is available. 
WSAENOTSOCK  The descriptor is not a socket. 
WSAEOPNOTSUPP  The referenced socket is not a type that supports connection-oriented service. 
WSAEWOULDBLOCK  The socket is marked as nonblocking and no connections are present to be accepted. 
*/
ASOCKET_DLL_EXPORT AMInt32 a_accept(AMInt32 fd, struct AMSockAddr * addr, AMSize_t * len)
{
	return accept(fd, (struct sockaddr *)addr, len);
}
/*
WSANOTINITIALISED A successful WSAStartup call must occur before using this function. 
WSAENETDOWN The network subsystem has failed. 
WSAEACCES An attempt was made to access a socket in a way forbidden by its access permissions. An example is using a broadcast address for sendto without broadcast permission being set using setsockopt (Windows Sockets). 
WSAEADDRINUSE A process on the machine is already bound to the same fully qualified address and the socket has not been marked to allow address reuse with SO_REUSEADDR. For example, the IP address and port are bound in the af_inet case. (See the SO_REUSEADDR socket option under setsockopt (Windows Sockets).) 
WSAEADDRNOTAVAIL The specified address is not a valid address for this machine. 
WSAEFAULT The name or namelen parameter is not a valid part of the user address space, the namelen parameter is too small, the name parameter contains an incorrect address format for the associated address family, or the first two bytes of the memory block specified by name do not match the address family associated with the socket descriptor s. 
WSAEINPROGRESS A blocking Winsock call is in progress, or the service provider is still processing a callback function. 
WSAEINVAL The socket is already bound to an address. 
WSAENOBUFS Not enough buffers available; too many connections. 
WSAENOTSOCK The descriptor is not a socket.  
*/
ASOCKET_DLL_EXPORT AMInt32 a_bind(AMInt32 fd, struct AMSockAddr * addr, AMSize_t len)
{
	return bind(fd, (struct sockaddr *)addr, len);
}
/*
WSANOTINITIALISED  A successful WSAStartup call must occur before using this function.  
WSAENETDOWN  The network subsystem has failed.  
WSAEADDRINUSE  The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs when executing bind, but it could be delayed until the connect function if the bind was to a partially wildcard address (involving ADDR_ANY) and if a specific address needs to be committed at the time of the connect function.  
WSAEINTR  The socket was closed.  
WSAEINPROGRESS  A blocking Winsock call is in progress, or the service provider is still processing a callback function.  
WSAEALREADY  A nonblocking connect call is in progress on the specified socket. 
To preserve backward compatibility, this error is reported as WSAEINVAL to Winsock applications that link to either Winsock.dll or Wsock32.dll.

WSAEADDRNOTAVAIL  The remote address is not a valid address (such as ADDR_ANY).  
WSAEAFNOSUPPORT  Addresses in the specified family cannot be used with this socket.  
WSAECONNREFUSED  The attempt to connect was forcefully rejected.  
WSAEFAULT  The name or namelen parameter is not a valid part of the user address space, the namelen parameter is too small, or the name parameter contains incorrect address format for the associated address family. 
WSAEINVAL  The parameter s is a listening socket.  
WSAEISCONN  The socket is already connected (connection-oriented sockets only).  
WSAENETUNREACH  The network cannot be reached from this host at this time.  
WSAENOBUFS  No buffer space is available. The socket cannot be connected.  
WSAENOTSOCK  The descriptor is not a socket.  
WSAETIMEDOUT  An attempt to connect timed out without establishing a connection.  
WSAEWOULDBLOCK  The socket is marked as nonblocking and the connection cannot be completed immediately.  
WSAEACCES  An attempt to connect a datagram socket to a broadcast address failed because the setsockopt option SO_BROADCAST is not enabled.  
*/
ASOCKET_DLL_EXPORT AMInt32 a_connect(AMInt32 fd, struct AMSockAddr *addr, AMSize_t len)
{
	return connect(fd, (struct sockaddr *)addr, len);
}

ASOCKET_DLL_EXPORT AMInt32 a_syn_connect(AMInt32 fd, struct AMSockAddr *addr, 
        AMSize_t len, struct AMTimeval *timeout)
{
    return AME_SOCKET_SCUESS;
}

/*
WSANOTINITIALISED  A successful WSAStartup call must occur before using this function. 
WSAENETDOWN  The network subsystem has failed. 
WSAEADDRINUSE  The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs during execution of the bind (Windows Sockets) function, but it could be delayed until the listen function if the bind was to a partially wildcard address (involving ADDR_ANY) and if a specific address needs to be committed at the time of the listen function. 
WSAEINPROGRESS  A blocking Winsock call is in progress, or the service provider is still processing a callback function. 
WSAEINVAL  The socket has not been bound with bind. 
WSAEISCONN  The socket is already connected. 
WSAEMFILE  No more socket descriptors are available. 
WSAENOBUFS  No buffer space is available. 
WSAENOTSOCK  The descriptor is not a socket.  
WSAEOPNOTSUPP  The referenced socket is not of a type that supports the listen operation.  
*/
ASOCKET_DLL_EXPORT AMInt32 a_listen(AMInt32 fd, AMInt32 backlog)
{
	return listen(fd, backlog);
}

/*
WSANOTINITIALISED  A successful WSAStartup call must occur before using this function.  
WSAENETDOWN  The network subsystem has failed.  
WSAEFAULT  The buf parameter is not completely contained in a valid part of the user address space.  
WSAENOTCONN  The socket is not connected.  
WSAEINTR  The socket was closed.  
WSAEINPROGRESS  A blocking Winsock call is in progress, or the service provider is still processing a callback function.  
WSAENETRESET  The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress.  
WSAENOTSOCK  The descriptor is not a socket. 
WSAEOPNOTSUPP MSG_OOB was specified, but the socket is not stream style such as type SOCK_STREAM, out of band (OOB) data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only send operations. 
 
WSAESHUTDOWN  The socket has been shut down; it is not possible to receive on a socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH.  
WSAEWOULDBLOCK  The socket is marked as nonblocking and the receive operation would block.  
WSAEMSGSIZE  The message was too large to fit into the specified buffer and was truncated. 
WSAEINVAL  The socket has not been bound with bind (Windows Sockets), an unknown flag was specified, MSG_OOB was specified for a socket with SO_OOBINLINE enabled, or (for byte stream sockets only) len was zero or negative.  
WSAECONNABORTED  The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.  
WSAETIMEDOUT  The connection has been dropped because of a network failure or because the peer system failed to respond.  
WSAECONNRESET  The virtual circuit was reset by the remote side executing a hard or abortive close. The application should close the socket because it is no longer usable.  
*/
ASOCKET_DLL_EXPORT AMInt32 a_recv(AMInt32 fd, AMChar * buffer, AMSize_t len, AMInt32 flags)
{
	return recv(fd, buffer, len, flags);
}
/*
WSANOTINITIALISED  A successful WSAStartup call must occur before using this function.  
WSAENETDOWN  The network subsystem has failed.  
WSAEACCES  The requested address is a broadcast address, but the appropriate flag was not set. Call setsockopt (Windows Sockets) with the SO_BROADCAST parameter to allow the use of the broadcast address.  
WSAEINTR  The socket was closed. 
WSAEINPROGRESS  A blocking Winsock call is in progress, or the service provider is still processing a callback function.  
WSAEFAULT  The buf parameter is not completely contained in a valid part of the user address space.  
WSAENETRESET  The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress.  
WSAENOBUFS  No buffer space is available.  
WSAENOTCONN  The socket is not connected.  
WSAENOTSOCK  The descriptor is not a socket.  
WSAEOPNOTSUPP  MSG_OOB was specified, but the socket is not stream style such as type SOCK_STREAM, out of band (OOB) data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only receive operations. 
WSAESHUTDOWN  The socket has been shut down. It is not possible to send on a socket after shutdown has been invoked with how set to SD_SEND or SD_BOTH.  
WSAEWOULDBLOCK  The socket is marked as nonblocking and the requested operation would block.  
WSAEMSGSIZE  The socket is message-oriented, and the message is larger than the maximum supported by the underlying transport.  
WSAEHOSTUNREACH  The remote host cannot be reached from this host at this time.  
WSAEINVAL  The socket has not been bound with bind (Windows Sockets), an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled.  
WSAECONNABORTED  The virtual circuit was terminated due to a time-out or other failure. The application should close the socket because it is no longer usable.  
WSAECONNRESET  The virtual circuit was reset by the remote side executing a hard or abortive close. For UDP sockets, the remote host was unable to deliver a previously sent UDP datagram and responded with a "Port Unreachable" ICMP packet. The application should close the socket because it is no longer usable.  
WSAETIMEDOUT  The connection has been dropped because of a network failure or because the system on the other end went down without notice.  
WSAEPROTONOSUPPORT  Protocol is not supported. For example, for raw sockets, if the IP_HDRINCL option set for the socket, and in the header the protocol field is set to TCP. 
*/

ASOCKET_DLL_EXPORT AMInt32 a_send(AMInt32 fd, const AMChar* buffer, AMSize_t len, AMInt32 flags)
{
	return send(fd, buffer, len, flags);
}
/*
WSANOTINITIALISED
 A successful WSAStartup call must occur before using this function.
WSAENETDOWN
 The network subsystem has failed
WSAEINVAL
 The how parameter is not valid, or is not consistent with the socket type. For example, SD_SEND is used with a UNI_RECV socket type.
WSAEINPROGRESS
 A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
WSAENOTCONN
 The socket is not connected (connection-oriented sockets only). 
WSAENOTSOCK
 The descriptor is not a socket.
*/
ASOCKET_DLL_EXPORT AMInt32 a_shutdown(AMInt32 fd, AMInt32 flags)
{
	return shutdown(fd, flags);
}
/*
RETURN VALUE
close returns zero on success, or -1 if an error occurred. 
ERRORS
EBADF  fd isn’t a valid open file descriptor.  
EINTR  The close() call was interrupted by a signal.  
EIO  An I/O error occurred.  
*/
ASOCKET_DLL_EXPORT AMInt32 a_close(AMInt32 fd)
{
	return shutdown(fd, 0);
}
#endif //同步接口结束

ASOCKET_DLL_EXPORT AMUInt32 a_inet_addr(const AMChar* ipstr)
{
	return inet_addr(ipstr);
}

ASOCKET_DLL_EXPORT AMUInt16 a_htons(AMUInt16 hs)
{
	return htons(hs);
}

ASOCKET_DLL_EXPORT AMUInt32  a_htonl(AMUInt32 hl)
{
	return htonl(hl);
}

#ifdef AM_SOCKET_SUPPORT_UDP
AMInt32 a_recvfrom(AMInt32 fd, AMChar * buffer, AMSize_t len, AMInt32 flags, 
    struct AMSockAddr * from, AMSize_t * fromlen)
{
    return AME_SOCKET_ERROR;
}
AMInt32 a_sendto(AMInt32 fd, const AMChar * buffer, AMSize_t len, AMInt32 flags, 
    struct AMSockAddr * to, AMSize_t tolen)
{
    return AME_SOCKET_ERROR;
}
#endif

#ifdef AM_SOCKET_SUPPORT_OPTION
AMInt32 a_getsockopt(AMInt32 fd, AMInt32 level, AMInt32 optname, AMPVoid optval,  AMSize_t* optlen)
{
     return AME_SOCKET_ERROR;
}
AMInt32 a_setsockopt(AMInt32 fd, AMInt32 level, AMInt32 optname, AMPVoid optval,  AMSize_t optlen)
{
    return AME_SOCKET_ERROR;
}
#endif

#ifdef AM_SOCKET_SUPPORT_IOCTL
AMInt32 a_ioctl(AMInt32 fd, AMInt32 request, ...)
{
    return AME_SOCKET_ERROR;
}
AMInt32 a_select(AMInt32 n, AMFdSet *readfds, AMFdSet *writefds, AMFdSet *exceptfds, struct AMTimeval *timeout)
{
    return AME_SOCKET_ERROR;
}
#endif
