/*
 * AMSocketHelp.h
 *
 *  Created on: 2009-11-23
 *      Author: qinghua.liqh
 */
#ifndef	_AM_SOCKET_HELP_H_
#define	_AM_SOCKET_HELP_H_

#include "AMSocketTypes.h"

#if (defined (_WIN32_WCE) || defined(_WIN32)) && (!defined(__SYMBIAN32__)) 
#include <winsock2.h>


#ifdef _WIN32_WCE
#pragma comment(lib, "Ws2.lib")
#else 
#pragma comment(lib, "Ws2_32.lib")
#endif
#define ioctl  ioctlsocket
#define socket_errno (WSAGetLastError())

int s_socket (int af, int type, int protocol);
int s_close(int s);
int s_socket_init();
int s_socket_uninit();


#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
//#include <sys/select.h>
#include <sys/ioctl.h>
#define  socket_errno errno
#endif

#define AM_SOCKET_CASE(code, ret)  case code: return ret
#endif	//_AM_SOCKET_HELP_H_

