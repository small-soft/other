/*
 * AMHttp.cpp
 *
 *  Created on: 2010-3-4
 *      Author: qing.chen
 */
#include <http.h>
#include <UTF.H>

#include "AMHttp.h"
#include "SymbianSocket.h"
#include "AMSocket.h"
#include "WebClientEngine.h"

#define REINTERPRET( Type, NewValue, OldValue ) Type NewValue = reinterpret_cast<Type>( OldValue )

AMInt32 SetSessionConnectionInfo(AMPVoid session);

struct HttpSessionInternal
	{
	RHTTPSession* session;
	AMHttpCallback callback;
	AMPVoid parg;
	};

struct HttpConnectionInternal
	{
	RHTTPSession* session;			// not own
	RHTTPTransaction* Transaction;
	HBufC8* url;
	CWebClientEngine* WebClientEngine;
	};

struct HttpResponseInternal
	{
	RHTTPSession* session;			// not own
	RHTTPTransaction* Transaction;
	};

AMInt32 AMHttpCreateSession(AMHttpSession* pSession, 
        const AMWChar* sessionName, AMHttpCallback callback, AMPVoid parg)
	{
	RHTTPSession* Session = new ( ELeave ) RHTTPSession;
	HttpSessionInternal* ret = new ( ELeave ) HttpSessionInternal;
	ret->session = Session;
	ret->callback = callback;
	ret->parg = parg;
	*pSession = ret;
	Session->OpenL();
	}

AMInt32 AMHttpCloseSession(AMHttpSession session)
	{
	REINTERPRET( HttpSessionInternal*, temp, session );
	delete temp->session;
	temp->session->Close();
	delete temp;
	}

AMInt32 AMHttpOpenConnection(AMHttpConnection* pCon, 
    AMHttpSession session, const AMHttpURL url)
	{
	HttpConnectionInternal* ret = new ( ELeave ) HttpConnectionInternal;
	
	RHTTPTransaction* Transaction = new ( ELeave ) RHTTPTransaction;
	
	TPtrC ptr( (const TUint16*)url );
	
	_LIT8( KHttpPrefix, "http://" );
	ret->url = HBufC8::New( ptr.Length() + KHttpPrefix().Length() );
	ret->url->Des().Copy( ptr );
	ret->url->Des().LowerCase();
	
    if(ret->url->Find(KHttpPrefix) == KErrNotFound)
      {
      // If the uri does not contain http or https,
      // use the default, "http://"
      ret->url->Des().Insert( 0, KHttpPrefix );
      }

	REINTERPRET( HttpSessionInternal*, temp, session );
	
	ret->Transaction = Transaction;
	ret->session = temp->session;
	
	*pCon = ret;
	}

AMInt32 AMHttpCloseConnection(AMHttpConnection con)
	{
	REINTERPRET( HttpConnectionInternal*, temp, con );
	delete temp->url;
	delete temp->WebClientEngine;
	delete temp;
	}

AMHttpRequest AMHttpGetRequest (AMHttpConnection con, 
    AMHttpVerb verb, AMUInt32 context)
	{
	REINTERPRET( HttpConnectionInternal*, temp, con );
	RStringF method;
	
	switch( verb )
		{
		case AM_HTTP_GET:
			{
			method = temp->session->StringPool().StringF(HTTP::EGET,
			    RHTTPSession::GetTable());
			break;
			}
		case AM_HTTP_POST:
			{
			 method = temp->session->StringPool().StringF(HTTP::EPOST,
			    RHTTPSession::GetTable());
			break;
			}
		case AM_HTTP_HEAD:
			{
			method = temp->session->StringPool().StringF(HTTP::EHEAD,
			    RHTTPSession::GetTable());
			break;
			}
		}
	
	temp->WebClientEngine = CWebClientEngine::NewL();
	
	TUriParser8 uri;
	uri.Parse(*temp->url);
	
	SetSessionConnectionInfo( temp->session );
	  
	*temp->Transaction = temp->session->OpenTransactionL(uri, *temp->WebClientEngine, method);
	return temp;
	}

AMHttpResponse AMHttpGetResponse(AMHttpConnection con, AMUInt32 context)
	{
	return con;
	}

AMInt32 AMHttpSetOption(AMHttpRequest request, AMHttpOption option, 
    AMUInt8* inBuf, AMUInt32 inBufLen)
	{
	REINTERPRET( HttpConnectionInternal*, temp, request );
	RHTTPHeaders hdr = temp->Transaction->Request().GetHeaderCollection();
	
	HBufC8* buf = HBufC8::New( inBufLen );
	CleanupStack::PushL( buf );
	buf->Des().Append( inBuf, inBufLen );
	
	switch( option )
		{
		case AM_HTTP_TIMEOUT:
			{
			RStringF valStr = temp->session->StringPool().OpenFStringL( *buf );
			CleanupClosePushL(valStr);
			THTTPHdrVal val(valStr);
			hdr.SetFieldL(temp->session->StringPool().StringF(HTTP::EWspProxyConnectionTimeout,
			    RHTTPSession::GetTable()), val);
			CleanupStack::PopAndDestroy();  // valStr
			break;
			}
		}
	
	CleanupStack::PopAndDestroy( buf );
	}

AMInt32 AMHttpGetOption(AMHttpRequest request, AMHttpOption option,
    AMUInt8* outBuf, AMUInt32 inOutBufLen)
	{
	REINTERPRET( HttpConnectionInternal*, temp, request );
	RHTTPHeaders hdr = temp->Transaction->Request().GetHeaderCollection();
	
	TPtr8 ptr( outBuf, inOutBufLen );
	
	switch( option )
		{
		case AM_HTTP_TIMEOUT:
			{
			THTTPHdrVal val;
			hdr.GetField(temp->session->StringPool().StringF(HTTP::EWspProxyConnectionTimeout,
			    RHTTPSession::GetTable()), 0, val);
			ptr.Append( val.StrF().DesC() );
			break;
			}
		}
	}

AMInt32 AMHttpSendRequest(AMHttpRequest request, AMUInt32 context)
	{
	REINTERPRET( HttpConnectionInternal*, temp, request );
	temp->Transaction->SubmitL();
	}

AMInt32 AMHttpGetResponseInfo(AMHttpResponse response, AMHttpQueryCode code, 
        AMUInt8* outBuf, AMUInt32 inOutBufLen)
	{
	REINTERPRET( HttpConnectionInternal*, temp, response );
	RHTTPResponse resp = temp->Transaction->Response();
	RHTTPHeaders headers = resp.GetHeaderCollection();
	
	TPtr8 ptr( outBuf, inOutBufLen );
	
	switch( code )
		{
		case AM_HTTP_STATUS_CODE:
			{
			ptr.AppendNum( resp.StatusCode() );
			break;
			}
		case AM_HTTP_VERSION:
			{
			ptr.Append( resp.Version().Name() );
			break;
			}
		}
	}

AMInt32 SetSessionConnectionInfo(AMPVoid session)
	{
	REINTERPRET( RHTTPSession*, temp, session );
    // Set the sessions connection info...
    RStringPool strPool = temp->StringPool();
    RHTTPConnectionInfo connInfo = temp->ConnectionInfo();
    
    REINTERPRET( CNetworkAccessPoint*, NetworkAccessPoint, AMSocketIAPGet() );
    
    // ...to use our socket server and connection
    connInfo.SetPropertyL ( strPool.StringF(HTTP::EHttpSocketServ,
        RHTTPSession::GetTable() ), THTTPHdrVal (NetworkAccessPoint->GetRSocketServ().Handle()) );
    // ...to use our connection
    connInfo.SetPropertyL ( strPool.StringF(HTTP::EHttpSocketConnection,
        RHTTPSession::GetTable() ), 
        THTTPHdrVal (REINTERPRET_CAST(TInt, &(NetworkAccessPoint->GetRConnection()))) );
	}
