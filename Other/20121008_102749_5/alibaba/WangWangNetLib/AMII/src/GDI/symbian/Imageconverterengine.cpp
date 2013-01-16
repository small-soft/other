/*
* ============================================================================
*  Name     : CImageConverterEngine from ImageConverterEngine.cpp
*  Part of  : ImageConverter
*  Created  : May 14, 2006 by Forum Nokia
*  Implementation notes:
*     Handles all ICL interaction. Implemented as a separate class/engine
*     for the sake of clarity of the example.
*  Version  : 2.0
*  Copyright: Nokia Corporation
* ============================================================================
*/

#include <fbs.h>
#include <ImageConversion.h>
#include <BitmapTransforms.h>
#include <EIKENV.H>
#include "ImageConverterEngine.h"

#define CAST( Type, Value ) reinterpret_cast<Type>( Value )

CImageConverterEngine* CImageConverterEngine::NewL(AMImage* image)
    {
    
    CFbsBitmap** Image = CAST( CFbsBitmap**, image );
    
    CImageConverterEngine* self = 
        new(ELeave) CImageConverterEngine( Image );
    CleanupStack::PushL( self );
	
    self->ConstructL();

    CleanupStack::Pop(self);
    return self; 
    }

CImageConverterEngine::CImageConverterEngine(CFbsBitmap** image) : 
    CActive( EPriorityStandard ), iBitmap( image )
    {
    }

void CImageConverterEngine::ConstructL()
    {
    User::LeaveIfError( iFs.Connect() );
    CActiveScheduler::Add( this );
    }

CImageConverterEngine::~CImageConverterEngine()
    {
    Cancel();
    delete Decoder.iImageDecoder; 
    delete Decoder.iBufferDecoder;
    delete iRotator;
    delete iScaler;
    iFs.Close();          //   related RFs is closed, 
    }

void CImageConverterEngine::ResetImage( AMImage* image )
	{
	CFbsBitmap** Image = CAST( CFbsBitmap**, image );
	delete iBitmap;
	iBitmap = Image;
	}

void CImageConverterEngine::StartToDecodeL( const TDesC& aFileName )
    {
    
    Cancel();
    
    delete Decoder.iImageDecoder; Decoder.iImageDecoder = NULL;
    
    // create the decoder
    Decoder.iImageDecoder = CImageDecoder::FileNewL( iFs, aFileName );

    // create the destination bitmap
    CFbsBitmap* Bitmap = new (ELeave) CFbsBitmap();
    Bitmap->Create( Decoder.iImageDecoder->FrameInfo().iOverallSizeInPixels, Decoder.iImageDecoder->FrameInfo().iFrameDisplayMode );
    
    
    *iBitmap = Bitmap;

    // start conversion to bitmap

    Decoder.iImageDecoder->Convert( &iStatus, *Bitmap );

    SetActive();
    iWait.Start();
    }

void CImageConverterEngine::StartToDecodeL( const TDesC8& aFileBuffer )
	{
    Cancel();
    
    delete Decoder.iBufferDecoder; Decoder.iBufferDecoder = NULL;

    Decoder.iBufferDecoder = CImageDecoder::DataNewL( iFs, aFileBuffer);
    // create the destination bitmap
    CFbsBitmap* Bitmap = new (ELeave) CFbsBitmap();
    Bitmap->Create( Decoder.iBufferDecoder->FrameInfo().iOverallSizeInPixels, Decoder.iBufferDecoder->FrameInfo().iFrameDisplayMode );
    
    
    *iBitmap = Bitmap;

    // start conversion to bitmap

    Decoder.iBufferDecoder->Convert( &iStatus, *Bitmap );

    SetActive();
    iWait.Start();
	}

void CImageConverterEngine::StartToRotate( TInt aAngle )
    {
    Cancel();
    
    delete iRotator; iRotator = NULL;
    
    iRotator = CBitmapRotator::NewL();
    
    if( aAngle < 0 )
    	{
    	while( aAngle < 0 )
    		{
    		aAngle += 360;
    		}
    	}
		
    if( aAngle <= 90 ) 
        {
        iRotator->Rotate( &iStatus, **iBitmap, 
            CBitmapRotator::ERotation90DegreesClockwise );	
        }
    else if( aAngle <= 180 )
        { 
        iRotator->Rotate( &iStatus, **iBitmap, 
            CBitmapRotator::ERotation180DegreesClockwise );	
        }
    else
    	{
        // 270 clockwise == 90 anticlockwise
        iRotator->Rotate( &iStatus, **iBitmap, 
            CBitmapRotator::ERotation270DegreesClockwise );	
    	}

    SetActive();
    iWait.Start();
    }

void CImageConverterEngine::StartToScale( TReal aX, TReal aY )
    {
    Cancel();
    
    delete iScaler; iScaler = NULL;
    
    iScaler = CBitmapScaler::NewL();

    TInt newWidth = (TInt)((*iBitmap)->SizeInPixels().iWidth * aX);
    TInt newHeight = (TInt)((*iBitmap)->SizeInPixels().iHeight * aY);
		
    // the maintain aspect ratio is by default set to true
    iScaler->Scale( &iStatus, **iBitmap, TSize(newWidth,newHeight) );

    SetActive();
    iWait.Start();
    }

void CImageConverterEngine::DoCancel()
    {

    delete *iBitmap;

    if( Decoder.iImageDecoder )
    	{
    	Decoder.iImageDecoder->Cancel();
    	}
    if( Decoder.iBufferDecoder )
    	{
    	Decoder.iBufferDecoder->Cancel();
    	}    
    if( iRotator )
    	{
    	iRotator->Cancel();
    	}
    if( iScaler )
    	{
    	iScaler->Cancel();
    	}
    }
	

void CImageConverterEngine::RunL()
    {
    iBitmap = NULL;
    iWait.AsyncStop();
    }

TInt CImageConverterEngine::RunError(TInt /*aError*/)   
    {
    return KErrNone;
    }

