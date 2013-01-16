/*
 ============================================================================
 Name	: AMSocket.cpp
 Author	: Iava
 Version	: 1.0
 Copyright    : Your copyright notice
 Description : CNetworkSocket implementation
 ============================================================================
 */
#include "SymbianSocket.h"
#include <CommDbConnPref.h>
#include <e32debug.h>
#include "SymbianMainScheduler.h"
#include "AMMemory.h"

CAlibabaActive::~CAlibabaActive()
{
}
	
CAlibabaActive::CAlibabaActive(TInt aPriority)
	: CActive(aPriority)
{
}

/********************************************************************
 * 								接入点								*
 ********************************************************************/
CNetworkAccessPoint::CNetworkAccessPoint(AccessPointMode mode)
{	
	iMode = mode;
}

CNetworkAccessPoint::~CNetworkAccessPoint()
{
	//iConnection.Stop(); //denx:关闭了一个物理连接，不建议使用，改用Close.
	iConnection.Close();
	iSocketServ.Close();
}

CNetworkAccessPoint* CNetworkAccessPoint::NewL(AccessPointMode mode)
{
	//CNetworkAccessPoint* self = new ( ELeave ) CNetworkAccessPoint(mode);
	AMNewLD(CNetworkAccessPoint, self, ELeave, CNetworkAccessPoint(mode));
	
	CleanupStack::PushL(self);
	if(self->ConstructL() == 0)
	{
		//delete self;
		AMDelete(self);
		self = 0;
	}
	CleanupStack::Pop();
	return self;
}

TInt CNetworkAccessPoint::ConstructL()
{
	User::LeaveIfError(iSocketServ.Connect());
	iSocketServ.ShareAuto(); //denx add this for share this connection in each thread.
	User::LeaveIfError(iConnection.Open(iSocketServ));
	
	TCommDbConnPref pref;
	if(iMode == eIAPUserChoose)
	{
		pref.SetDialogPreference(ECommDbDialogPrefPrompt);
		pref.SetBearerSet(ECommDbBearerGPRS | ECommDbBearerWLAN);
		TInt ret = iConnection.Start(pref); //waiting for user choose network access point.
		if(ret == KErrCancel) //用户取消选择
			return 0;
		else
			return 1;
	}
	else
	{
		//异步不弹出选择框
		//pref.SetIapId(iSelectedIap);
		//pref.SetDialogPreference( ECommDbDialogPrefDoNotPrompt);
		//pref.SetDirection(ECommDbConnectionDirectionOutgoing );
		//iConnection.Start(pref,iStatus);
		//SetActive();
		return 0;
	}
}
	
RSocketServ& CNetworkAccessPoint::GetRSocketServ()
{
	return iSocketServ;
}

RConnection& CNetworkAccessPoint::GetRConnection()
{
	return iConnection;
}

/********************************************************************
 * 								套接字								*
 ********************************************************************/
CNetworkSocket::CNetworkSocket(SocketASync* sa, RSocketServ& ss, RConnection& conn) 
	: CAlibabaActive(EPriorityStandard)
	, iSocketServ(ss)
	, iConnection(conn)
{
	iSA.connCallback = sa->connCallback;
	iSA.recvCallback = sa->recvCallback;
	iSA.sendCallback = sa->sendCallback;
	iSA.iap 		 = sa->iap;
	iSA.reference    = sa->reference;
	iStatus = KRequestPending;
	
	iSocSend = NULL;
	iSocRecv = NULL;
	
	iConnectBeginSemaphore.CreateLocal(1);
	iConnectEndSemaphore.CreateLocal(1);
	iConnectEndSemaphore.Wait(); //denx:先消耗掉一个位置。
}

CNetworkSocket::~CNetworkSocket()
{
	Cancel();
	
	//iSocket.CancelAll();
	iSocket.Close();
	
	//delete iSocSend;
	AMDelete(iSocSend);
	
	//delete iSocRecv;
	AMDelete(iSocRecv);
	
	iConnectBeginSemaphore.Close();
	iConnectEndSemaphore.Close();
}

void CNetworkSocket::DoCancel()
{
}

TInt CNetworkSocket::RunError(TInt aError)
{
	return aError;
}

CNetworkSocket* CNetworkSocket::NewL(SocketASync* sa, TUint DataType, TUint Protocol)
{	
	CNetworkAccessPoint* p = (CNetworkAccessPoint*)sa->iap;
	if(p == NULL)
		return NULL;
	
	//CNetworkSocket* self = new ( ELeave ) CNetworkSocket(sa, p->GetRSocketServ(), p->GetRConnection());
	AMNewLD(CNetworkSocket, self, ELeave, CNetworkSocket(sa, p->GetRSocketServ(), p->GetRConnection()));
	
	CleanupStack::PushL(self);
	self->ConstructL(DataType, Protocol);
	CleanupStack::Pop();
	return self;
}

void CNetworkSocket::ConstructL(TUint DataType, TUint Protocol)
{
	iSocket.Open(iSocketServ, KAfInet, DataType, Protocol, iConnection);
	
	SymbianMainScheduler::GetInstance()->Add(this);
}

TInt CNetworkSocket::Connect(TInt aPort, TUint32 aAddr)
{
	iConnectBeginSemaphore.Wait();
	RThread th;
	TThreadId currentTH = th.Id();
	TThreadId mainTH = SymbianMainScheduler::GetInstance()->GetMainThreadId();
	
	if(!IsActive())
	{
		iAddress.SetPort( aPort );
		iAddress.SetAddress( aAddr );
		
		Cancel();
		if(currentTH == mainTH)
		{
			iSocket.Connect( iAddress, iStatus );
			iSocStatus=eSocketConnecting;
			SetActive();		
		}
		else
		{
			th.Open(mainTH);
			iStatus = KRequestPending; 
			TRequestStatus* status = &iStatus;
					
			iSocStatus=eSocketNotReady;
			th.RequestComplete(status, KErrNone);
			SetActive();
			iConnectEndSemaphore.Wait();
		}
		iConnectBeginSemaphore.Signal();
		return 0;
	}
	else
	{
		iConnectBeginSemaphore.Signal();
		return -1;
	}
}

TInt CNetworkSocket::Read(TUint8* aBuffer, TUint32 aLength)
{
	if(iSocRecv)
		return iSocRecv->Recv(aBuffer, aLength);
	else 
		return 0;
}

TInt CNetworkSocket::Send(TUint8* aBuffer, TUint32 aLength)
{
	if(iSocSend)
		return iSocSend->Send(aBuffer, aLength);
	else
		return 0;
}

TInt CNetworkSocket::SendTo(TUint8* aBuffer, TUint32 aLength, TInt aPort, TUint32 aAddr)
{
	if(iSocSend)
		return iSocSend->SendTo(aBuffer, aLength, aPort, aAddr);
	else
		return 0;
}
TInt CNetworkSocket::RecvFrom(TUint8* aBuffer, TUint32 aLength, TUint8* aPort, TUint8* aAddr)
{
	if(iSocRecv)
		return iSocRecv->RecvFrom(aBuffer, aLength, aPort, aAddr);
	else
		return 0;
}

void CNetworkSocket::Bind(TUint32 aAddr)
{
    iAddress.SetAddress( aAddr );
	iSocket.Bind(iAddress);
}

void CNetworkSocket::Listen(TUint32 aSize)
{
	iSocket.Listen(aSize);
}

TInt CNetworkSocket::ShutDown(RSocket::TShutdown aHow)
{
	Cancel();
	if(!IsActive())
	{
		iSocket.Shutdown(aHow, iStatus);
		iSocStatus=eSocketShutdown;
		SetActive();
		return 0;
	}
	return -1;
}


void CNetworkSocket::RunL()
{
	TInt error = iStatus.Int();
	
    switch( iSocStatus )
    {
		case eSocketNotReady:
			iSocket.Connect( iAddress, iStatus );
			SetActive();
			iSocStatus = eSocketConnecting;
			iConnectEndSemaphore.Signal();
			break;
			
        case eSocketConnecting:
            if ( iStatus == KErrNone )
            {
                iSocStatus=eSocketConnected;
                
            	iSocSend=CNetworkSocketSend::NewL(*this, &iSA);
            	iSocRecv=CNetworkSocketRecv::NewL(*this, &iSA);
            }
            else
            {
				iSocStatus=eSocketConnectFail;
				RDebug::Printf("[AMII	]: CNetworkSocket: %d", error);
            }
            iSA.connCallback(iSA.reference, (TInt)this, iSocStatus);
            
            break;
            
        default:
        	User::Leave(0);
            break;
    }
}

RSocket& CNetworkSocket::GetSocket()
{
	return iSocket;
}

/********************************************************************
 * 								发送									*
 ********************************************************************/
CNetworkSocketSend::CNetworkSocketSend(CNetworkSocket& aSocket, SocketASync* sa) 
	: CAlibabaActive(EPriorityStandard)  // Standard priority
	, iSocket(aSocket)
{
	iSA.connCallback = sa->connCallback;
	iSA.recvCallback = sa->recvCallback;
	iSA.sendCallback = sa->sendCallback;
	iSA.reference    = sa->reference;
	iSA.iap 		 = sa->iap;
	
	iStatus = KRequestPending;
	iSendBeginSemaphore.CreateLocal(1);
	iSendEndSemaphore.CreateLocal(1);
	iSendEndSemaphore.Wait(); //denx:先消耗掉一个位置。
}

TInt CNetworkSocketSend::RunError(TInt aError)
{
	return aError;
}
CNetworkSocketSend::~CNetworkSocketSend()
{
	Cancel();
	
	iSendBeginSemaphore.Close();
	iSendEndSemaphore.Close();
}

void CNetworkSocketSend::DoCancel()
{
}

CNetworkSocketSend* CNetworkSocketSend::NewL(CNetworkSocket& aSocket, SocketASync* sa)
{
	//CNetworkSocketSend* self = new ( ELeave ) CNetworkSocketSend(aSocket, sa);
	AMNewLD(CNetworkSocketSend, self, ELeave, CNetworkSocketSend(aSocket, sa));
	
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
}

void CNetworkSocketSend::ConstructL()
{
	SymbianMainScheduler::GetInstance()->Add(this);
}

TInt CNetworkSocketSend::Send(TUint8* aBuffer, TUint32 aLength)
{
	iSendBeginSemaphore.Wait();
	RThread th;
	TThreadId currentTH = th.Id();
	TThreadId mainTH = SymbianMainScheduler::GetInstance()->GetMainThreadId();
	
	if(!IsActive())
	{
		iSendBuffer.Copy(aBuffer,aLength);
		
		Cancel();
		if(currentTH == mainTH)
		{
			iSocket.GetSocket().Send( iSendBuffer, 0, iStatus, iSendLength );
			iSocStatus=eSocketSending;
			SetActive();
		}
		else
		{
			th.Open(mainTH);
			iStatus = KRequestPending; 
			TRequestStatus* status = &iStatus;
					
			iSocStatus=eSocketWaiting;
			th.RequestComplete(status, KErrNone);
			SetActive();
			iSendEndSemaphore.Wait();
		}
		iSendBeginSemaphore.Signal();
		return 1;
	}
	else
	{
		iSendBeginSemaphore.Signal();
		return -1;
	}
}

TInt CNetworkSocketSend::SendTo(TUint8* aBuffer, TUint32 aLength, TInt aPort, TUint32 aAddr)
{
	//todo: denx: add thread support.
	User::Leave(0);
	
	if(!IsActive())
	{
	    iAddress.SetPort( aPort );
	    iAddress.SetAddress( aAddr );
		iSendBuffer.Copy(aBuffer,aLength);
		iSocket.GetSocket().SendTo( iSendBuffer, iAddress, 0, iStatus, iSendLength );
	    iSocStatus=eSocketSending;
	    SetActive();
	    return 0;
	}
	return -1;
}

void CNetworkSocketSend::RunL()
{
	switch( iSocStatus )
    {
		case eSocketInit:
			iSocStatus = eSocketNotReady;
			break;
			
        case eSocketSending:
            if ( iStatus == KErrNone )
            	iSA.sendCallback(iSA.reference, (TInt)&iSocket, eSocketSendOK);
            else
            	iSA.sendCallback(iSA.reference, (TInt)&iSocket, eSocketSendFail);
            break;
       	
        case eSocketWaiting:
        	if ( iStatus == KErrNone )
        	{
    			iSocket.GetSocket().Send( iSendBuffer, 0, iStatus, iSendLength );
    			iSocStatus=eSocketSending;
    			SetActive();	
    			iSendEndSemaphore.Signal();
        	}
        	break;
        
        default:
        	User::Leave(0);
            break;
    }
}

/********************************************************************
 * 								接收									*
 ********************************************************************/
CNetworkSocketRecv::CNetworkSocketRecv(CNetworkSocket& aSocket, SocketASync* sa) 
	:CAlibabaActive(EPriorityStandard)
	,iSocket(aSocket)
{
	iSA.connCallback = sa->connCallback;
	iSA.recvCallback = sa->recvCallback;
	iSA.sendCallback = sa->sendCallback;
	iSA.reference    = sa->reference;
	iSA.iap 		 = sa->iap;
	
	iStatus = KRequestPending;
	
	iStartRecvSemaphore.CreateLocal(1);
	iStartRecvReturnSemaphore.CreateLocal(1);
	iStartRecvReturnSemaphore.Wait(); //denx:先消耗掉一个位置。
	
	iRecvQuitSemaphore.CreateLocal(1);
	iRecvQuitSemaphore.Wait(); //denx:先消耗掉一个位置。
}

CNetworkSocketRecv::~CNetworkSocketRecv()
{
	iRecvQuitSemaphore.Wait();
	
	Cancel();
	
	iStartRecvSemaphore.Close();
	iStartRecvReturnSemaphore.Close();
	iRecvQuitSemaphore.Close();
}

void CNetworkSocketRecv::DoCancel()
{
}

TInt CNetworkSocketRecv::RunError(TInt aError)
{
	return aError;
}

void CNetworkSocketRecv::ConstructL()
{
	SymbianMainScheduler::GetInstance()->Add(this);
	StartRecv();
}

CNetworkSocketRecv* CNetworkSocketRecv::NewL(CNetworkSocket& aSocket, SocketASync* sa)
{
	//CNetworkSocketRecv* self = new ( ELeave ) CNetworkSocketRecv(aSocket, sa);
	AMNewLD(CNetworkSocketRecv, self, ELeave, CNetworkSocketRecv(aSocket, sa));
	
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
}

TInt CNetworkSocketRecv::Recv(TUint8* aBuffer, TUint32 aLength)
{
	TInt r=0;

	if(iRecvPool.Pos>=aLength)
	{
		memcpy(aBuffer, iRecvPool.Ptr, aLength);
		iRecvPool.Pos-=aLength;
		memcpy(iRecvPool.Ptr, iRecvPool.Ptr+aLength, iRecvPool.Pos);
		r=aLength;
		
		//异步通知还有数据
		if(iRecvPool.Pos>0)
			iSA.recvCallback(iSA.reference, (TInt)&iSocket, eSocketRecv);
	}
	else if(iRecvPool.Pos)
	{
		memcpy(aBuffer, iRecvPool.Ptr, iRecvPool.Pos);
		r=iRecvPool.Pos;
		iRecvPool.Pos=0;
	}
	else
	{
		//缓冲区无数据
		r = 0;
	}

    return r;
}

void CNetworkSocketRecv::StartRecv()
{
	iStartRecvSemaphore.Wait();
	RThread th;
	TThreadId currentTH = th.Id();
	TThreadId mainTH = SymbianMainScheduler::GetInstance()->GetMainThreadId();
	
	if(!IsActive())
	{
		iRevBuffer.Zero();
		
		Cancel();
		if(currentTH == mainTH)
		{
			iSocStatus=eSocketRecving;
		    iSocket.GetSocket().RecvOneOrMore( iRevBuffer, 0, iStatus, iRevLength );
		    SetActive();	
		}
		else
		{
			th.Open(mainTH);
			iStatus = KRequestPending; 
			TRequestStatus* status = &iStatus;
					
			iSocStatus=eSocketWaiting;
			th.RequestComplete(status, KErrNone);
			SetActive();
			iStartRecvReturnSemaphore.Wait();
		}
	}

	iStartRecvSemaphore.Signal();
}

TInt CNetworkSocketRecv::RecvFrom(TUint8* aBuffer, TUint32 aLength, TUint8* aPort, TUint8* aAddr)
{
	TInt r;
#if 0
	if(iRecvPool.Pos>=aLength)
	{
		memcpy(aBuffer, iRecvPool.Ptr, aLength);
		iRecvPool.Pos-=aLength;
		memcpy(iRecvPool.Ptr, iRecvPool.Ptr+aLength, iRecvPool.Pos);
		r=aLength;
	}
	else if(iRecvPool.Pos)
	{
		memcpy(aBuffer, iRecvPool.Ptr, iRecvPool.Pos);
		r=iRecvPool.Pos;
		iRecvPool.Pos=0;
	}
	else
	{
		r=-1;
	}
	aAddr[0]=(iAddress.Address()>>24)&0xff;
	aAddr[1]=(iAddress.Address()>>16)&0xff;
	aAddr[2]=(iAddress.Address()>>8)&0xff;
	aAddr[3]=(iAddress.Address())&0xff;

	aPort[0]=(iAddress.Port())&0xff;
	aPort[1]=(iAddress.Port()>>8)&0xff;
	aPort[2]=(iAddress.Port()>>16)&0xff;
	aPort[3]=(iAddress.Port()>>24)&0xff;

	if(KsOCRecvPoolSize-iRecvPool.Pos > KsOCRecvPoolSize/4 && !IsActive())
	{
		iRevBuffer.Zero();
	    iSocket.GetSocket().RecvFrom( iRevBuffer, iAddress, 0, iStatus);
	    SetActive();
	}
#endif
    return r;
}

void CNetworkSocketRecv::StartRecvFrom()
{
#if 0
	if(!IsActive())
	{
		iRevBuffer.Zero();
		iSocket.GetSocket().RecvFrom( iRevBuffer, iAddress, 0, iStatus);
	    SetActive();
	}
#endif
}

void CNetworkSocketRecv::RunL()
{
	TInt ret  = iStatus.Int();
	
    switch( iSocStatus )
    {
        case eSocketRecving:
       		SocketStatus tempSocStatus;
       		if(ret == KErrNone)
       		{
       			TInt length = iRevBuffer.Length();
       			if(length > 0)
       			{
       				while(iRecvPool.Pos + length > KsOCRecvPoolSize*2) 
       				{
       					//denx: pool溢出处理
       					iSA.sendCallback(iSA.reference, (TInt)&iSocket, eSocketOverflowWarning);
       				}
       				
       				memcpy(iRecvPool.Ptr+iRecvPool.Pos, iRevBuffer.Ptr(), iRevBuffer.Length());
       				iRecvPool.Pos += iRevBuffer.Length();
       				tempSocStatus = eSocketRecv;
       			}
       			else
       			{
       				tempSocStatus = eSocketRecvInvalid;
       			}
       		}
       		else
       		{
       			switch(ret)
       			{
       			case KErrEof:
       				tempSocStatus = eSocketErrorEof;
       				break;
       				
       			case KErrServerTerminated:
       				tempSocStatus = eSocketServerTerminated;
       				break;
       				
       			case KErrNotReady:
       				tempSocStatus = eSocketNotReady;
       				break;
       				
       			default:
       				tempSocStatus = eSocketError;
       				break;
       			}
       			
       			RDebug::Printf("[AMII	]: CNetworkSocketRecv::Recv error=%d", ret);
       		}
       		
       		iSA.recvCallback(iSA.reference, (TInt)&iSocket, tempSocStatus);
       		if(ret == KErrNone && tempSocStatus != eSocketRecvInvalid)
       			StartRecv();
       		else
       			iRecvQuitSemaphore.Signal();
       		break;
       		
        case eSocketWaiting:
			if ( iStatus == KErrNone )
			{
				iSocStatus=eSocketRecving;
				iSocket.GetSocket().RecvOneOrMore( iRevBuffer, 0, iStatus, iRevLength );
				SetActive();	
				iStartRecvReturnSemaphore.Signal();
			}
			break;
        
        default:
        	User::Leave(0);
            break;
    }
}

/********************************************************************
 * 							域名解析				        *
 ********************************************************************/
#if 0
CiavaSocHostResolver::CiavaSocHostResolver(
		RSocketServ& aSocketServ,
		RConnection& aSocketConnection) :
	CActive(EPriorityStandard),
	iSocketServ(aSocketServ),
	iConnection(aSocketConnection)
{
}

CiavaSocHostResolver::~CiavaSocHostResolver()
{
	Cancel();
	iHostResolver.Close();
	iHostMask[iHid]=0;
	iHostProcess[iHid]=NULL;
}

void CiavaSocHostResolver::DoCancel()
{
}

TInt CiavaSocHostResolver::RunError(TInt aError)
{
	return aError;
}

CiavaSocHostResolver* CiavaSocHostResolver::NewL(
		TInt aHid,
		RSocketServ& aSocketServ,
		RConnection& aSocketConnection,
		TUint8* aServerName,
		TUint8* aIpAddress)
{
	CiavaSocHostResolver* self = AMNew ( ELeave ) CiavaSocHostResolver(aSocketServ,aSocketConnection);
	CleanupStack::PushL(self);
	self->ConstructL(aHid, aServerName, aIpAddress);
	CleanupStack::Pop();
	return self;
}

void CiavaSocHostResolver::ConstructL(
		TInt aHid,
		TUint8* aServerName,
		TUint8* aIpAddress)
{
	CActiveScheduler::Add( this);
	iHostResolver.Open(iSocketServ, KAfInet, KProtocolInetUdp, iConnection);
	i_gb2unicode((unsigned char*)aServerName, (unsigned short*)iServerName.Ptr());
	iServerName.SetLength(strlen((char*)aServerName));
	iHostResolver.GetByName(iServerName, iNameEntry, iStatus);
	iIpAddress=aIpAddress;
	iHid=aHid;
	SetActive();
}

void CiavaSocHostResolver::RunL()
{
	GET_PGLOBAL;
	VmEvent ve;
	ve.event = VEVENT_SOCKET;
	iHostResolver.Close();
	if( iStatus == KErrNone )
	{
		iNameRecord=iNameEntry();
		TUint32 Address=TInetAddr::Cast(iNameRecord.iAddr).Address();
		iIpAddress[0]=(Address>>24)&0xff;
		iIpAddress[1]=(Address>>16)&0xff;
		iIpAddress[2]=(Address>>8)&0xff;
		iIpAddress[3]=(Address)&0xff;
        ve.time = IAVA_NETSTATE_GET_IP_SUCCESS;
	}
	else
	{
		ve.time = IAVA_NETSTATE_GET_IP_FAILED;
	}
	EventPut(&ve, iHostProcess[iHid]);
	IAVADELETE(iavaHostResolver[iHid])
}
#endif










