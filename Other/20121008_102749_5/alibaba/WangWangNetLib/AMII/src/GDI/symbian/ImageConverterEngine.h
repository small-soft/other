/*
* ============================================================================
*  Name     : CImageConverterEngine from ImageConverterEngine.h
*  Part of  : ImageConverter
*  Created  : May 14, 2006 by Forum Nokia
*  Implementation notes:
*     Handles all ICL interaction. Implemented as a separate class/engine
*     for the sake of clarity of the example.
*  Version  : 2.0
*  Copyright: Nokia Corporation
* ============================================================================
*/

#ifndef __IMAGECONVERTER_H__
#define __IMAGECONVERTER_H__

#include <e32std.h>
#include <e32base.h>
#include <f32file.h>
#include <ImageConversion.h>
#include <BitmapTransforms.h>

#include "AMGDI.h"

class CFbsBitmap;

class CImageConverterEngine : public CActive
    {
        public: // contructors/destructors

        /*
        * NewL
        *  
        * Create a CImageConverterEngine object and return a pointer to it.
        *
        * Params: 
        *		aController Pointer to a MConverterController interface.
        *      The engine uses NotifyCompletion callback from this interface
        *      to notify the controller about completions of coding or 
        *      encoding requests.
        *		 
        * Returns:
        * 		A pointer to the created engine
        *
        */	
        static CImageConverterEngine* NewL(AMImage* image);
	
        virtual ~CImageConverterEngine();
        
        void ResetImage( AMImage* image );
        
    public: // interface methods

        /*
        * StartToDecodeL
        *  
        * Starts to decode an image from a file. When completed calls 
        * NotifyCompletion, from iController.
        *
        * Params: 
        *		aFileName Full path and filename of the image to be decoded.
        *		 
        * Returns:
        * 		Nothing
        */
        void StartToDecodeL( const TDesC& aFileName );
        
        void StartToDecodeL( const TDesC8& aFileBuffer );
        
        /*
        * StartToRotate
        *  
        * Rotates the image to the given direction.
        *
        * Params: 
        *		aDirection The direction to rotate to.
        *
        * Returns:
        * 		Nothing 
        */
        void StartToRotate( TInt aAngle );

        /*
        * StartToScale
        *  
        * Scales the image to the given percentage of the current size.
        *
        * Params: 
        *		aPercent The new size relative to the current size 
        * 		(e.g. 110 will increase the size by 10 %).
        *
        * Returns:
        * 		Nothing 
        */
        void StartToScale( TReal aX, TReal aY );

    private: // implementation of CActive
        CFbsBitmap** iBitmap; // decoded image
        RFs iFs; // for opening/saving images from/to files
        TRequestStatus iStatusUsedToWait;
        CActiveSchedulerWait iWait;
        void DoCancel();
        void RunL();
        TInt RunError(TInt aError);
        CImageConverterEngine(CFbsBitmap** image); 
        void ConstructL();	        

        union
        	{
			CImageDecoder* iImageDecoder; // decoder from ICL API
			
			CImageDecoder* iBufferDecoder;
        	} Decoder;
        
        CBitmapRotator* iRotator;
        CBitmapScaler* iScaler;
    };

#endif // #ifndef __IMAGECONVERTER_H__
