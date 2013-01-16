/*
 * AMImage.cpp
 *
 *  Created on: 2010-2-7
 *      Author: Administrator
 */
#include "AMImage.h"
#include "ImageConverterEngine.h"

#define REINTERPRET( Type, NewValue, OldValue ) Type NewValue = reinterpret_cast<Type>( OldValue )

AMInt32 AMImageDestroy(AMImage image)
	{
	REINTERPRET( CFbsBitmap*, temp, image );
	delete temp;
	image = NULL;
	}

AMInt32 AMCreateImageFromFile(AMImage* image, const AMWChar* inFileName)
	{
	CImageConverterEngine* engine = CImageConverterEngine::NewL( image );
	TPtrC ptr((const TUint16*)inFileName);
	engine->StartToDecodeL( ptr );
	delete engine;
	}

AMInt32 AMGetWidth(AMImage image)
	{
	REINTERPRET( CFbsBitmap*, temp, image );
	return temp->SizeInPixels().iWidth;
	}

AMInt32 AMGetHeight(AMImage image)
	{
	REINTERPRET( CFbsBitmap*, temp, image );
	return temp->SizeInPixels().iHeight;
	}
	
AMInt32 AMCreateImage(AMImage* pImage, AMInt8* buffer, AMInt32 length)
	{
	REINTERPRET( unsigned char*, temp, buffer );
	CImageConverterEngine* engine = CImageConverterEngine::NewL( pImage );
	TPtr8 ptr(temp,length,length);
	engine->StartToDecodeL( ptr );
	delete engine;
	}

AMInt32 AMCreateImageFromRGB(AMImage* image, AMInt32 *rgb, AMInt32 width, AMInt32 height)
{
	//todo:
	return 0;
}

AMInt32 AMGetImageBuffer(AMGraphics graphics, AMImage img, 
		AMInt32 x, AMInt32 y, AMInt32 width, AMInt32 height, AMInt8* pData)
{
	//todo:
	return 0;
}
