/*
 ============================================================================
 Name		: WebClientEngine.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CWebClientEngine implementation
 ============================================================================
 */

#include "WebClientEngine.h"

CWebClientEngine::CWebClientEngine()
	{
	// No implementation required
	}

CWebClientEngine::~CWebClientEngine()
	{
	}

CWebClientEngine* CWebClientEngine::NewLC()
	{
	CWebClientEngine* self = new (ELeave) CWebClientEngine();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CWebClientEngine* CWebClientEngine::NewL()
	{
	CWebClientEngine* self = CWebClientEngine::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CWebClientEngine::ConstructL()
	{

	}

void CWebClientEngine::MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent& aEvent)
	{
	  switch (aEvent.iStatus)
	    {
	    case THTTPEvent::EGotResponseHeaders:
	      {

	      }
	      break;

	    case THTTPEvent::EGotResponseBodyData:
	      {
	      // Part (or all) of response's body data received. Use
	      // aTransaction.Response().Body()->GetNextDataPart() to get the actual
	      // body data.

	      // Get the body data supplier
	      MHTTPDataSupplier* body = aTransaction.Response().Body();
	      TPtrC8 dataChunk;

	      // GetNextDataPart() returns ETrue, if the received part is the last
	      // one.
	      TBool isLast = body->GetNextDataPart(dataChunk);

	      // Always remember to release the body data.
	      body->ReleaseData();
	      }
	      break;

	    case THTTPEvent::EResponseComplete:
	      {

	      }
	      break;

	    case THTTPEvent::ESucceeded:
	      {

	      }
	      break;

	    case THTTPEvent::EFailed:
	      {

	      }
	      break;

	    }
	}

TInt CWebClientEngine::MHFRunError( TInt aError,
            RHTTPTransaction aTransaction,
            const THTTPEvent& aEvent)
	{
	return KErrNone;
	}
