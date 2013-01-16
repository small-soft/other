/*
 ============================================================================
 Name		: WebClientEngine.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CWebClientEngine declaration
 ============================================================================
 */

#ifndef WEBCLIENTENGINE_H
#define WEBCLIENTENGINE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <http.h>

// CLASS DECLARATION

/**
 *  CWebClientEngine
 * 
 */
class CWebClientEngine : public CBase, public MHTTPTransactionCallback
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CWebClientEngine();

	/**
	 * Two-phased constructor.
	 */
	static CWebClientEngine* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CWebClientEngine* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CWebClientEngine();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
	void MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent& aEvent);
	
	TInt MHFRunError( TInt aError,
	            RHTTPTransaction aTransaction,
	            const THTTPEvent& aEvent);

	};

#endif // WEBCLIENTENGINE_H
