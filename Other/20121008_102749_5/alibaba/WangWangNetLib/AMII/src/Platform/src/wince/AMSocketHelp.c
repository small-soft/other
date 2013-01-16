/*
 * AMSocketHelp.c
 *
 *  Created on: 2009-11-23
 *      Author: qinghua.liqh
 */
#include "AMSocket.h"
#include "AMSocketHelp.h"


#if (defined (_WIN32_WCE) || defined(_WIN32)) && (!defined(__SYMBIAN32__)) 
int s_socket (int af, int type, int protocol)
{
	int err;
	err = s_socket_init();
	if ( err != 0 ) {
		return ERROR_COMMON;
	}
	err = socket(af, type, protocol);
	return err;
}

int s_close(int s)
{
	int err = closesocket(s);
	s_socket_uninit();
	return err;
}

int s_socket_init()
{
    WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );
    return err;
}

int s_socket_uninit()
{
    return WSACleanup();
}

#else 
#endif

