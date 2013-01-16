/*
 * AMSocket.c
 *
 *  Created on: 2009-11-18
 *      Author: qinghua.liqh
 */
#define _SOCKET_IMP_
#include "AMSocket.h"
#include "AMSocketHelp.h"


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
ASOCKET_DLL_EXPORT AMInt32 a_socket(AMInt32 fd, AMInt32 type, AMInt32 protocol)
{
    AMInt32 s = s_socket(fd, type, protocol);
    if(-1 == s)
    {
        AMInt32 errCode = socket_errno;
        switch(errCode)
        {
            AM_SOCKET_CASE(WSANOTINITIALISED,   AME_SOCKET_ERROR);
            AM_SOCKET_CASE(WSAENETDOWN,         AME_SOCKET_ERROR);
            AM_SOCKET_CASE(WSAEAFNOSUPPORT,     AME_SOCKET_AFNOSUPPORT);
            AM_SOCKET_CASE(WSAEINPROGRESS,      AME_SOCKET_ERROR);
            AM_SOCKET_CASE(WSAEMFILE,           AME_SOCKET_NORESOURCE);
            AM_SOCKET_CASE(WSAENOBUFS,          AME_SOCKET_NORESOURCE);
            AM_SOCKET_CASE(WSAEPROTONOSUPPORT,  AME_SOCKET_PROTONOSUPPORT);
            AM_SOCKET_CASE(WSAEPROTOTYPE,       AME_SOCKET_PROTONOSUPPORT);
            AM_SOCKET_CASE(WSAESOCKTNOSUPPORT,  AME_SOCKET_SOCKTNOSUPPORT);
            default:
                return AME_SOCKET_ERROR;
        }
    }

    return  s;
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
    AMInt32 ret_code = 0;
    if(NULL == addr || NULL == len)
        return AME_SOCKET_AINVALID;

    ret_code = accept(fd, (struct sockaddr *)addr, len);
    if(-1 == ret_code)
    {
        AMInt32 errCode = socket_errno;
        switch(errCode)
        {
            AM_SOCKET_CASE(WSANOTINITIALISED,   AME_SOCKET_ERROR);
            AM_SOCKET_CASE(WSAENETDOWN,         AME_SOCKET_ERROR);
            AM_SOCKET_CASE(WSAEFAULT,           AME_SOCKET_AINVALID);
            AM_SOCKET_CASE(WSAEINTR,            AME_SOCKET_SHUTDOWN);
            AM_SOCKET_CASE(WSAEINPROGRESS,      AME_SOCKET_ERROR);
            AM_SOCKET_CASE(WSAEINVAL,           AME_SCOKET_LISTENNOTCALL);
            AM_SOCKET_CASE(WSAEMFILE,           AME_SOCKET_NORESOURCE);
            AM_SOCKET_CASE(WSAENOBUFS,          AME_SOCKET_NORESOURCE);
            AM_SOCKET_CASE(WSAENOTSOCK,         AME_SOCKET_ERROR);
            AM_SOCKET_CASE(WSAEOPNOTSUPP,       AME_SOCKET_ERROR);
            AM_SOCKET_CASE(WSAEWOULDBLOCK,      AME_SOCKET_ERROR);
            default:
                return AME_SOCKET_ERROR;
        }
    }

    return AME_SOCKET_SCUESS;
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
    AMInt32 ret_code = 0;
    if(NULL == addr)
        return AME_SOCKET_AINVALID;

   ret_code = bind(fd, (struct sockaddr *)addr, len);
   if(-1 == ret_code)
   {
        AMInt32 errCode = socket_errno;
        switch(errCode)
        {
            AM_SOCKET_CASE(WSAEACCES,           AME_SOCKET_EACCES);
            AM_SOCKET_CASE(WSAEADDRNOTAVAIL,    AME_SOCKET_AINVALID);
            AM_SOCKET_CASE(WSAEFAULT,           AME_SOCKET_AINVALID);
            AM_SOCKET_CASE(WSAENOBUFS,          AME_SOCKET_NORESOURCE);
            default:
                return AME_SOCKET_ERROR;
        }
    }

   return AME_SOCKET_SCUESS;
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
    AMInt32 ret_code = 0;
    if(NULL == addr)
        return AME_SOCKET_ERROR;

    ret_code = connect(fd, (struct sockaddr *)addr, len);
    if(ret_code == -1)
    {
        AMInt32 errCode = socket_errno;
        switch(errCode)
        {
            AM_SOCKET_CASE(WSAEADDRINUSE,           AME_SOCKET_ADDRINUSE);
            AM_SOCKET_CASE(WSAEINTR,                AME_SOCKET_SHUTDOWN);
            AM_SOCKET_CASE(WSAEADDRNOTAVAIL,        AME_SOCKET_AINVALID);
            AM_SOCKET_CASE(WSAENOBUFS,              AME_SOCKET_NORESOURCE);
            AM_SOCKET_CASE(WSAETIMEDOUT,            AME_SOCKET_TIMEDOUT);
            AM_SOCKET_CASE(WSAEACCES,               AME_SOCKET_EACCES);
            AM_SOCKET_CASE(WSAEISCONN,              AME_SOCKET_ISCONN);
            AM_SOCKET_CASE(WSAENETUNREACH,          AME_SOCKET_NETUNREACH);
            AM_SOCKET_CASE(WSAECONNREFUSED,         AME_SCOKET_CONNREFUSED);
            AM_SOCKET_CASE(WSAEWOULDBLOCK,          AME_SOCKET_WOULDBLOCK);
            AM_SOCKET_CASE(WSAEINPROGRESS,          AME_SOCKET_WOULDBLOCK);
            AM_SOCKET_CASE(WSAEALREADY,             AME_SOCKET_WOULDBLOCK);
            default:
                return AME_SOCKET_ERROR;
        }
    }
    return AME_SOCKET_SCUESS;
}

ASOCKET_DLL_EXPORT AMInt32 a_syn_connect(AMInt32 fd, struct AMSockAddr *addr, 
        AMSize_t len, struct AMTimeval *timeout)
{
    AMUInt32 flag = 1;
    if(NULL == timeout)
        return a_connect(fd, addr, len);
    else
    {
        fd_set wset;
        AMInt32 connect_err;
        //ÉèÖÃconnectÎª·Ç×èÈû,
	    if(ioctl(fd, FIONBIO, &flag) == -1)
            return AME_SOCKET_ERROR;
        if((connect_err = connect(fd, (struct sockaddr*)&addr, sizeof(struct AMSockAddr))) ==  -1)
        {
            int err = socket_errno;
            if(err == NET_EWOULDBLOCK)	
            {
                int select_err; 
                FD_ZERO(&wset);
                FD_SET(fd, &wset); 

                if((select_err = select(fd + 1, &wset, &wset, NULL, (AMPVoid)timeout)) == 0 )		//the count.
                {
                    goto AM_CONNECT_FAILED;
                }

                if(FD_ISSET(fd, &wset))		//connect successful.
                {
                    goto AM_CONNECT_SCUESS;
                }
            }
            else if(connect_err == 0)
            {
                goto AM_CONNECT_SCUESS;
            }
        }
        
    }
AM_CONNECT_FAILED:
    {
        AMInt32 errCode = socket_errno;
        flag = 0;  
        ioctl(fd, FIONBIO, &flag);
        switch(errCode)
        {
            AM_SOCKET_CASE(WSAEINVAL  ,           AME_SOCKET_AINVALID);
            default:
                return AME_SOCKET_ERROR;
        }
    }

AM_CONNECT_SCUESS:
    flag = 0;
    ioctl(fd, FIONBIO, &flag);
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
    AMInt32 err_code = listen(fd, backlog);
    if(err_code == -1)
    {
        AMInt32 errCode = socket_errno;
        switch(errCode)
        {
            AM_SOCKET_CASE(WSAEADDRINUSE,           AME_SOCKET_ADDRINUSE);
            AM_SOCKET_CASE(WSAEINVAL,               AME_SOCKET_NOTBIND);
            AM_SOCKET_CASE(WSAEISCONN,              AME_SOCKET_ISCONN);
            AM_SOCKET_CASE(WSAEMFILE,               AME_SOCKET_NORESOURCE);
            AM_SOCKET_CASE(WSAENOBUFS,              AME_SOCKET_NORESOURCE);
            AM_SOCKET_CASE(WSAEOPNOTSUPP,           AME_SOCKET_SOCKTNOSUPPORT);
            AM_SOCKET_CASE(WSAEINPROGRESS,          AME_SOCKET_WOULDBLOCK);
            default:
                return AME_SOCKET_ERROR;
        }
    }
    return AME_SOCKET_SCUESS;
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
    AMInt32 ret_code = 0;
    if(NULL == buffer)
        return AME_SOCKET_ERROR;


    ret_code = recv(fd, buffer, len, flags);
    if(ret_code > 0)
        return ret_code;
    else if(ret_code == 0)
        return AME_SOCKET_SHUTDOWN;
    else
    {
        AMInt32 errCode = socket_errno;
        switch(errCode)
        {
            AM_SOCKET_CASE(WSAEFAULT,               AME_SOCKET_AINVALID);
            AM_SOCKET_CASE(WSAENOTCONN,             AME_SOCKET_NOTCONN);
            AM_SOCKET_CASE(WSAEINTR,                AME_SOCKET_SHUTDOWN);
            AM_SOCKET_CASE(WSAEINPROGRESS,          AME_SOCKET_WOULDBLOCK);
            AM_SOCKET_CASE(WSAENETRESET,            AME_SOCKET_NETRESET);
            AM_SOCKET_CASE(WSAESHUTDOWN,            AME_SOCKET_SHUTDOWN);
            AM_SOCKET_CASE(WSAEWOULDBLOCK,          AME_SOCKET_WOULDBLOCK);
            AM_SOCKET_CASE(WSAEMSGSIZE,             AME_SOCKET_BUFFERNOTENOUGH);
            AM_SOCKET_CASE(WSAEINVAL,               AME_SOCKET_NOTBIND);
            AM_SOCKET_CASE(WSAETIMEDOUT,            AME_SOCKET_TIMEDOUT);
            default:
                return AME_SOCKET_ERROR;
        }
    }
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
    AMInt32 ret_code = 0;
    if(NULL == buffer)
        return AME_SOCKET_ERROR;

    ret_code = send(fd, buffer, len, flags);
    if(ret_code != -1)
        return  ret_code;
    else
    {
        AMInt32 errCode = socket_errno;
        switch(errCode)
        {
            AM_SOCKET_CASE(WSAEINTR,                AME_SOCKET_SHUTDOWN);
            AM_SOCKET_CASE(WSAEINPROGRESS,          AME_SOCKET_WOULDBLOCK);
            AM_SOCKET_CASE(WSAENETRESET,            AME_SOCKET_NETRESET);
            AM_SOCKET_CASE(WSAENOBUFS,              AME_SOCKET_NORESOURCE);
            AM_SOCKET_CASE(WSAENOTCONN,             AME_SOCKET_NOTCONN);
            AM_SOCKET_CASE(WSAESHUTDOWN,            AME_SOCKET_SHUTDOWN);
            AM_SOCKET_CASE(WSAEPROTONOSUPPORT,      AME_SOCKET_PROTONOSUPPORT);
            AM_SOCKET_CASE(WSAETIMEDOUT,            AME_SOCKET_TIMEDOUT);
            AM_SOCKET_CASE(WSAEWOULDBLOCK,          AME_SOCKET_WOULDBLOCK);
            default:
                return AME_SOCKET_ERROR;
        }
    }
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
    if(shutdown(fd, flags) == 0)
        return AME_SOCKET_SCUESS;
    else 
        return AME_SOCKET_ERROR;
}
/*
RETURN VALUE
close returns zero on success, or -1 if an error occurred. 
ERRORS
EBADF  fd isn¡¯t a valid open file descriptor.  
EINTR  The close() call was interrupted by a signal.  
EIO  An I/O error occurred.  
*/
ASOCKET_DLL_EXPORT AMInt32 a_close(AMInt32 fd)
{
    if(s_close(fd) == 0)
        return AME_SOCKET_SCUESS;
    else 
        return AME_SOCKET_ERROR;
}

ASOCKET_DLL_EXPORT AMUInt32 a_inet_addr(const AMChar* ipstr)
{
    return inet_addr(ipstr);
}

ASOCKET_DLL_EXPORT AMUInt16 a_htons(AMUInt16 hs)
{
/*
#if _BYTE_ORDER == _BIG_ENDIAN
	return hs;
#else
	AMChar ret_hs[2];
	ret_hs[0] = *(((AMChar*)&hs) + 1);
	ret_hs[1] = *(((AMChar*)&hs) + 0);
	return *(AMUInt16*)ret_hs;
#endif
*/
	return htons(hs);
}

ASOCKET_DLL_EXPORT AMUInt32  a_htonl(AMUInt32 hl)
{
/*
#if _BYTE_ORDER == _BIG_ENDIAN
	return hl;
#else
	unsigned AMChar ret_hl[4];
	ret_hl[0] = *(((unsigned AMChar*)&hl) + 3);
	ret_hl[1] = *(((unsigned AMChar*)&hl) + 2);
	ret_hl[2] = *(((unsigned AMChar*)&hl) + 1);
	ret_hl[3] = *(((unsigned AMChar*)&hl) + 0);
	return *(AMUInt32*)ret_hl;
#endif
*/
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
    AMInt32 ret_code = 0;
    ret_code = select(n, readfds, writefds, exceptfds, (struct timeval*)timeout);
    if(ret_code != -1)
        return  ret_code;
    else
    {
        AMInt32 errCode = socket_errno;
        switch(errCode)
        {
        default:
            return AME_SOCKET_ERROR;
        }
    }
    return AME_SOCKET_SCUESS;
}
#endif

ASOCKET_DLL_EXPORT AMInt32 a_gethostbyname(struct AMHostent** host,const AMChar* name)
{
	AMInt32 ret_code = 0;
	//struct hostent	*hostinfo;
    s_socket_init();
	if(NULL == name)
		return AME_SOCKET_ERROR;
	
	*host = (struct AMHostent*) gethostbyname(name);
	if(*host == NULL)
	{
		AMInt32 errCode = socket_errno;
		switch(errCode)
		{
			/*AM_SOCKET_CASE(WSAHOST_NOT_FOUND ,     AME_SOCKET_HOST_NOT_FOUND);
			AM_SOCKET_CASE(WSATRY_AGAIN,          AME_SOCKET_TRY_AGAIN);
			AM_SOCKET_CASE(WSANO_RECOVERY,         AME_SOCKET_NO_RECOVERY);
			AM_SOCKET_CASE(WSANO_DATA,              AME_SOCKET_NO_DATA);*/
		default:
			return AME_SOCKET_ERROR;
		}
	}
	return 0;
}

ASOCKET_DLL_EXPORT AMInt32 a_init()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return ERROR_COMMON;
	}
	return 0;
}
ASOCKET_DLL_EXPORT AMInt32 a_exit()
{
	WSACleanup();
	return 0;
}


