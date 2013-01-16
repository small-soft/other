/*
 ============================================================================
 Name	 : AMSocket.h
 Author	 : Iava
 Version	 : 1.0
 Copyright     : Your copyright notice
 Description  : CNetworkSocket declaration
 ============================================================================
 */

#ifndef SYMBIAN_SOCKET_H
#define SYMBIAN_SOCKET_H

#include <e32base.h>	// For CActive, link against: euser.lib
#include <e32std.h>		// For RTimer, link against: euser.lib
#include <es_sock.h>
#include <in_sock.h>

#include "AMSocket.h"

#define	KsOCRecvPoolSize	20*1024 //20K buffer
const TUint KSocReadBufferMax=KsOCRecvPoolSize;
const TUint KSocSendBufferMax=KsOCRecvPoolSize;

class CAlibabaActive : public CActive
{
public:
	~CAlibabaActive();
	
protected:
	CAlibabaActive(TInt aPriority);
	
protected:
	SocketStatus 	iSocStatus;
};

/********************************************************************
 * 								接入点								*
 ********************************************************************/
class CNetworkAccessPoint : public CBase
{
public:
	enum AccessPointMode
	{
		eIAPUserChoose = 0,
		eIAPAutoDefault
	};
	
	~CNetworkAccessPoint();
	static CNetworkAccessPoint* NewL(AccessPointMode mode);
	RSocketServ& GetRSocketServ();
	RConnection& GetRConnection();
	
private:
	CNetworkAccessPoint(AccessPointMode mode);
	TInt ConstructL();
	
private:
	AccessPointMode iMode;
    RSocketServ 	iSocketServ;
    RConnection		iConnection;
};

/********************************************************************
 * 								套接字								*
 ********************************************************************/
class CNetworkSocketSend;
class CNetworkSocketRecv;
class CNetworkSocket : public CAlibabaActive
	{
public:
	~CNetworkSocket();
	static CNetworkSocket* NewL(SocketASync* sa, TUint DataType, TUint Protocol);
	
private:
	CNetworkSocket(SocketASync* sa, RSocketServ& ss, RConnection& conn);
	void ConstructL(TUint DataType, TUint Protocol);

public:
	TInt Connect(TInt aPort, TUint32 aAddr);
	TInt Read(TUint8* aBuffer, TUint32 aLength);
	TInt Send(TUint8* aBuffer, TUint32 aLength);
	TInt SendTo(TUint8* aBuffer, TUint32 aLength, TInt aPort, TUint32 aAddr);
	TInt RecvFrom(TUint8* aBuffer, TUint32 aLength, TUint8* aPort, TUint8* aAddr);
	void Bind(TUint32 aAddr);
	void Listen(TUint32 aSize);
	TInt ShutDown(RSocket::TShutdown aHow);
	
public:
	RSocket& GetSocket();
	
private:
	void RunL();
	void DoCancel();
	TInt RunError(TInt aError);

private:
	SocketASync		iSA;
	
    RSocketServ& 	iSocketServ;
    RConnection&	iConnection;
    RSocket 		iSocket;
	
    TInetAddr 		iAddress;
    TBool			iIsStartRecv;

    CNetworkSocketSend* iSocSend;
    CNetworkSocketRecv* iSocRecv;
    
	RSemaphore 			iConnectBeginSemaphore; 
	RSemaphore			iConnectEndSemaphore;
	};

/********************************************************************
 * 								发送									*
 ********************************************************************/
class CNetworkSocketSend : public CAlibabaActive
	{
public:
	~CNetworkSocketSend();

	static CNetworkSocketSend* NewL(CNetworkSocket& aSocket, SocketASync* sa);
	
public:
	TInt Send(TUint8* aBuffer, TUint32 aLength);
	TInt SendTo(TUint8* aBuffer, TUint32 aLength, TInt aPort, TUint32 aAddr);
	
private:
	CNetworkSocketSend(CNetworkSocket& aSocket, SocketASync* sa);
	void ConstructL();
	void RunL();
	void DoCancel();
	TInt RunError(TInt aError);

	CNetworkSocket& iSocket;
	SocketASync 	iSA;
    
    TInetAddr 		iAddress;
    TSockXfrLength 	iSendLength;
    TBuf8 <KSocSendBufferMax> iSendBuffer;
    
	RSemaphore 		iSendBeginSemaphore; 
	RSemaphore		iSendEndSemaphore;
	};

/********************************************************************
 * 								接收									*
 ********************************************************************/
typedef struct 
	{
	TUint8	Ptr[KsOCRecvPoolSize*2];
	TUint32	Pos;
	}SocetRecvPool;

class CNetworkSocketRecv : public CAlibabaActive
	{
public:
	~CNetworkSocketRecv();

	static CNetworkSocketRecv* NewL(CNetworkSocket& aSocket, SocketASync* sa);
	TInt Recv(TUint8* aBuffer, TUint32 aLength);
	TInt RecvFrom(TUint8* aBuffer, TUint32 aLength, TUint8* aPort, TUint8* aAddr);
	void StartRecv();
	void StartRecvFrom();
	void CancelEx();
	
private:
	CNetworkSocketRecv(CNetworkSocket& aSocket, SocketASync* sa);
	void ConstructL();
	void RunL();
	void DoCancel();
	TInt RunError(TInt aError);

private:
    CNetworkSocket&	iSocket;
    SocketASync 	iSA;
    
    TBuf8 <KSocReadBufferMax> iRevBuffer;
    SocetRecvPool	iRecvPool;
    TSockXfrLength  iRevLength;
    
	RSemaphore 		iStartRecvSemaphore; 
	RSemaphore		iStartRecvReturnSemaphore;
	RSemaphore		iRecvQuitSemaphore;
	};

/********************************************************************
 * 							域名解析									*
 ********************************************************************/
class CNetworkHostResolver : public CAlibabaActive
	{
public:
	~CNetworkHostResolver();
	static CNetworkHostResolver* NewL(
			TInt aHid,
			RSocketServ& aSocketServ,
			RConnection& aSocketConnection,
			TUint8* aServerName,
			TUint8* aIpAddress);
private:
	CNetworkHostResolver(
			RSocketServ& aSocketServ,
			RConnection& aSocketConnection);
	void ConstructL(
			TInt aHid,
			TUint8* aServerName,
			TUint8* aIpAddress);
	void RunL();
	void DoCancel();
	TInt RunError(TInt aError);
private:
	TInt			iHid;
    RSocketServ& 	iSocketServ;
    RConnection&	iConnection;
    RHostResolver 	iHostResolver;
    TNameEntry 		iNameEntry;
    TNameRecord 	iNameRecord;
    TUint8*			iIpAddress;
    TBuf<128> 		iServerName;
	};

#endif // AMSocket_H
