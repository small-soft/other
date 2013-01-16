/*
* http_trans.c -- Functions for doing transport related stuff including
* automatically extending buffers and whatnot.
*/

//#include <sys/time.h>
//#include <sys/types.h>
//#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "http_trans.h"
#include "http_global.h"

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


static int
http_trans_buf_free(http_trans_conn *a_conn);

int
http_trans_connect(http_trans_conn *a_conn)
{
	AMInt32 retCode;
	fd_set set;

#ifdef _WIN32
	unsigned long ul = 1;
	int timeo = 5;
#else
	struct timeval timeo = {5, 0};
#endif
	struct timeval timeo2 = {10, 0};


	if ((a_conn == NULL) || (a_conn->host == NULL))
		goto ec;
	if (a_conn->hostinfo == NULL)
	{
		/* look up the name of the proxy if it's there. */
		if (a_conn->proxy_host)
		{
			//  if ((a_conn->hostinfo = gethostbyname(a_conn->proxy_host)) == NULL)
			int error = AMGetHostByName(&a_conn->hostinfo, a_conn->proxy_host);
			if ( a_conn->hostinfo == NULL)
			{
				a_conn->error_type = http_trans_err_type_host;
				a_conn->error = error;
				goto ec;
			}
		}
		else
		{
			/* look up the name */
			//  if ((a_conn->hostinfo = gethostbyname(a_conn->host)) == NULL)
			int error = AMGetHostByName(&a_conn->hostinfo, a_conn->host);
			if ( a_conn->hostinfo  == NULL)
			{
				a_conn->error_type = http_trans_err_type_host;
				a_conn->error = error;
				goto ec;
			}
		}
		/* set up the saddr */
		//     a_conn->saddr.sin_family = AF_INET;
		a_conn->saddr.sin_family = AMAF_INET;
		/* set the proxy port */
		if (a_conn->proxy_host)
			//	a_conn->saddr.sin_port = htons(a_conn->proxy_port);
			a_conn->saddr.sin_port = AMSocketHtons(a_conn->proxy_port);
		else
			//	a_conn->saddr.sin_port = htons(a_conn->port);
			a_conn->saddr.sin_port = AMSocketHtons(a_conn->port);
		/* copy the name info */
		//   memcpy(&a_conn->saddr.sin_addr.s_addr,
		memcpy(&a_conn->saddr.sin_addr.S_un,
			(char*)a_conn->hostinfo->h_addr_list[0],
			sizeof(unsigned long));
	}
	/* set up the socket */
	// if ((a_conn->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	if ((a_conn->sock = AMSocket(AMAF_INET, AMSOCK_STREAM, 0)) < 0)
	{
		a_conn->error_type = http_trans_err_type_errno;
		a_conn->error = errno;
		goto ec;
	}

	//设置非阻塞方式连接
#ifdef _WIN32
	ioctlsocket(a_conn->sock, FIONBIO, (unsigned long*)&ul);
#else
	fcntl(a_conn->sock, F_SETFL, fcntl(a_conn->sock, F_GETFL, 0) | O_NONBLOCK);
#endif

	AMSocketConnect(a_conn->sock, (struct AMSockAddr *)&a_conn->saddr, sizeof(struct AMSockAddr));

	setsockopt(a_conn->sock, SOL_SOCKET, SO_SNDTIMEO, &timeo, sizeof(timeo));
	FD_ZERO(&set);
	FD_SET(a_conn->sock, &set);

	retCode = select(a_conn->sock+1, NULL, &set, NULL, &timeo2);

	if(retCode == -1)
	{
		AMSocketClose(a_conn->sock);
		return -1;
	}
	else if(retCode == 0)
	{
		AMSocketClose(a_conn->sock);
		return -1;
	}
	else
	{
		//set block mode.
#ifdef _WIN32
		ul = 0;
		ioctlsocket(a_conn->sock, FIONBIO, (unsigned long*)&ul);
#else
		fcntl(a_conn->sock, F_SETFL, fcntl(a_conn->sock, F_GETFL, 0) & (~O_NONBLOCK));
#endif

		return 0;
	}


	/* set up the socket */
	// if (connect(a_conn->sock,
	//      (struct sockaddr *)&a_conn->saddr,
	//    sizeof(struct sockaddr)) < 0)
// 	if (AMSocketConnect(a_conn->sock,
// 		(struct AMSockAddr *)&a_conn->saddr,
// 		sizeof(struct AMSockAddr)) < 0)
// 	{
// 		a_conn->error_type = http_trans_err_type_errno;
// 		a_conn->error = errno;
// 		goto ec;
// 	}
// 
// 	return 0;
ec:
	return -1;
}

http_trans_conn *
http_trans_conn_new(void)
{
	http_trans_conn *l_return = NULL;

	/* allocate a new connection struct */
	l_return = (http_trans_conn *)malloc(sizeof(http_trans_conn));
	memset(l_return, 0, sizeof(http_trans_conn));
	/* default to 80 */
	l_return->port = 80;
	/* default to 1000 bytes at a time */
	l_return->io_buf_chunksize = 1024;
	/* allocate a new trans buffer */
	l_return->io_buf = malloc(l_return->io_buf_chunksize);
	memset(l_return->io_buf, 0, l_return->io_buf_chunksize);
	l_return->io_buf_len = l_return->io_buf_chunksize;
	/* make sure the socket looks like it's closed */
	l_return->sock = -1;
	return l_return;
}

void
http_trans_conn_destroy(http_trans_conn *a_conn)
{
	/* destroy the connection structure. */
	if (a_conn == NULL)
		return;
	if (a_conn->io_buf)
		free(a_conn->io_buf);
	if (a_conn->sock != -1)
		// close(a_conn->sock);
		AMSocketClose(a_conn->sock);	
	free(a_conn);
	return;
}

const char *
http_trans_get_host_error(int a_herror)
{
	switch (a_herror)
	{
		//  case HOST_NOT_FOUND:
	case AME_SOCKET_HOST_NOT_FOUND:
		return "Host not found";
		//  case NO_ADDRESS:
	case AME_SOCKET_NO_DATA:
		return "An address is not associated with that host";
		//   case NO_RECOVERY:
	case AME_SOCKET_NO_RECOVERY:
		return "An unrecoverable name server error occured";
		//   case TRY_AGAIN:
	case AME_SOCKET_TRY_AGAIN:
		return "A temporary error occurred on an authoritative name server.  Please try again later.";
	default:
		return "No error or error not known.";
	}
}

int
http_trans_append_data_to_buf(http_trans_conn *a_conn,
							  char *a_data,
							  int   a_data_len)
{
	if (http_trans_buf_free(a_conn) < a_data_len)
	{
		a_conn->io_buf = realloc(a_conn->io_buf, a_conn->io_buf_len + a_data_len);
		a_conn->io_buf_len += a_data_len;
	}
	memcpy(&a_conn->io_buf[a_conn->io_buf_alloc], a_data, a_data_len);
	a_conn->io_buf_alloc += a_data_len;
	return 1;
}

int
http_trans_read_into_buf(http_trans_conn *a_conn)
{
	int l_read = 0;
	int l_bytes_to_read = 0;

	/* set the length if this is the first time */
	if (a_conn->io_buf_io_left == 0)
	{
		a_conn->io_buf_io_left = a_conn->io_buf_chunksize;
		a_conn->io_buf_io_done = 0;
	}
	/* make sure there's enough space */
	if (http_trans_buf_free(a_conn) < a_conn->io_buf_io_left)
	{
		a_conn->io_buf = realloc(a_conn->io_buf,
			a_conn->io_buf_len + a_conn->io_buf_io_left);
		a_conn->io_buf_len += a_conn->io_buf_io_left;
	}
	/* check to see how much we should try to read */
	if (a_conn->io_buf_io_left > a_conn->io_buf_chunksize)
		l_bytes_to_read = a_conn->io_buf_chunksize;
	else
		l_bytes_to_read = a_conn->io_buf_io_left;
	/* read in some data */
	//if ((a_conn->last_read = l_read = read(a_conn->sock,
	//			 &a_conn->io_buf[a_conn->io_buf_alloc],
	//			 l_bytes_to_read)) < 0)
	if ((a_conn->last_read = l_read = AMSocketRecv(a_conn->sock,
		&a_conn->io_buf[a_conn->io_buf_alloc],
		l_bytes_to_read , 0)) < 0)

	{
		if (errno == EINTR)
			l_read = 0;
		else
			return HTTP_TRANS_ERR;
	}
	else if (l_read == 0)
		return HTTP_TRANS_DONE;
	/* mark the buffer */
	a_conn->io_buf_io_left -= l_read;
	a_conn->io_buf_io_done += l_read;
	a_conn->io_buf_alloc += l_read;
	/* generate the result */
	if (a_conn->io_buf_io_left == 0)
		return HTTP_TRANS_DONE;
	return HTTP_TRANS_NOT_DONE;
}

int
http_trans_write_buf(http_trans_conn *a_conn)
{
	int l_written = 0;

	if (a_conn->io_buf_io_left == 0)
	{
		a_conn->io_buf_io_left = a_conn->io_buf_alloc;
		a_conn->io_buf_io_done = 0;
	}
	/* write out some data */
	/*if ((a_conn->last_read = l_written = write (a_conn->sock,
	&a_conn->io_buf[a_conn->io_buf_io_done],
	a_conn->io_buf_io_left)) <= 0)*/
	if ((a_conn->last_read = l_written = AMSocketSend (a_conn->sock,
		&a_conn->io_buf[a_conn->io_buf_io_done],
		a_conn->io_buf_io_left , 0)) <= 0)
	{
		if (errno == EINTR)
			l_written = 0;
		else
			return HTTP_TRANS_ERR;
	}
	if (l_written == 0)
		return HTTP_TRANS_DONE;
	/* advance the counters */
	a_conn->io_buf_io_left -= l_written;
	a_conn->io_buf_io_done += l_written;
	if (a_conn->io_buf_io_left == 0)
		return HTTP_TRANS_DONE;
	return HTTP_TRANS_NOT_DONE;
}

void
http_trans_buf_reset(http_trans_conn *a_conn)
{
	if (a_conn->io_buf)
		free(a_conn->io_buf);
	a_conn->io_buf = malloc(a_conn->io_buf_chunksize);
	memset(a_conn->io_buf, 0, a_conn->io_buf_chunksize);
	a_conn->io_buf_len = a_conn->io_buf_chunksize;
	a_conn->io_buf_alloc = 0;
	a_conn->io_buf_io_done = 0;
	a_conn->io_buf_io_left = 0;
}

void
http_trans_buf_clip(http_trans_conn *a_conn, char *a_clip_to)
{
	int l_bytes = 0;

	/* get the number of bytes to clip off of the front */
	l_bytes = a_clip_to - a_conn->io_buf;
	if (l_bytes > 0)
	{
		memmove(a_conn->io_buf, a_clip_to, a_conn->io_buf_alloc - l_bytes);
		a_conn->io_buf_alloc -= l_bytes;
	}
	a_conn->io_buf_io_done = 0;
	a_conn->io_buf_io_left = 0;
}

char *
http_trans_buf_has_patt(char *a_buf, int a_len,
						char *a_pat, int a_patlen)
{
	int i = 0;
	for ( ; i <= ( a_len - a_patlen ); i++ )
	{
		if (a_buf[i] == a_pat[0])
		{
			if (memcmp(&a_buf[i], a_pat, a_patlen) == 0)
				return &a_buf[i];
		}
	}
	return NULL;
}

/* static functions */

static int
http_trans_buf_free(http_trans_conn *a_conn)
{
	return (a_conn->io_buf_len - a_conn->io_buf_alloc);
}