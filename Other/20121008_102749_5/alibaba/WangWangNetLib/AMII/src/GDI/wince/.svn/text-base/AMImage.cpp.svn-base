#include "AMGDIIn.h"
#ifdef WINCE
#include <initguid.h>
#include <imgguids.h>
#endif

#if defined(WIN32) && !defined(WINCE)
#include "GdiPlus.h"
#endif

#ifdef WINCE
IImagingFactory *gpImgFactory = NULL;
AMInt32 gpImageFactoryTotalUsed = 0;
#endif

AMInt32 AMCreateImageFromFile(AMImage* image, const AMWChar* inFileName)
{
    CHECK_PARG_AND_RET(image);
    CHECK_PARG_AND_RET(inFileName);

    AMImage_* bitmap = (AMImage_*)malloc(sizeof(AMImage_));
    CHECK_PARG_AND_RETV(bitmap, AME_MALLOC_ERROR);

	bitmap->createMethod = 0; //denx add
#ifdef WINCE
    bitmap->bitmap = SHLoadDIBitmap((wchar_t*)inFileName);
#else
	bitmap->bitmap = LoadBitmap(NULL, (wchar_t*)inFileName);
#endif
    CHECK_PARG_AND_RETV(bitmap->bitmap , (free(bitmap),AME_IMAGE_ERROR));

    BITMAP bitmapBuffer;
    CHECK_PARG_AND_RETV(GetObject(bitmap->bitmap, sizeof(BITMAP), &bitmapBuffer),
        (DeleteObject(bitmap->bitmap), free(bitmap), AME_IMAGE_ERROR));
    bitmap->w = bitmapBuffer.bmWidth;
    bitmap->h = bitmapBuffer.bmHeight;
    memcpy(&bitmap->bitmapBuffer, &bitmapBuffer, sizeof(BITMAP));
    *image = bitmap;

    return AME_IMAGE_SCUESS;
}
AMInt32 AMCreateImageFromRGB(AMImage* image, AMInt32 *rgb, AMInt32 width, AMInt32 height)
{
    CHECK_PARG_AND_RET(image);
    CHECK_PARG_AND_RET(rgb);
   
    AMImage_* bitmap = (AMImage_*)malloc(sizeof(AMImage_));
    CHECK_PARG_AND_RETV(bitmap, AME_MALLOC_ERROR);
    bitmap->createMethod = 0; //denx add

    bitmap->bitmap = CreateBitmap(width, height, 1, 32, rgb);
    CHECK_PARG_AND_RETV(bitmap->bitmap , (free(bitmap),AME_IMAGE_ERROR));

    BITMAP bitmapBuffer;
    CHECK_PARG_AND_RETV(GetObject(bitmap->bitmap, sizeof(BITMAP), &bitmapBuffer),
        (DeleteObject(bitmap->bitmap), free(bitmap), AME_IMAGE_ERROR));
    bitmap->w = bitmapBuffer.bmWidth;
    bitmap->h = bitmapBuffer.bmHeight;
    memcpy(&bitmap->bitmapBuffer, &bitmapBuffer, sizeof(BITMAP));
    *image = bitmap;

    return AME_IMAGE_SCUESS;
}

AMInt32 AMGetWidth(AMImage image)
{
    AMImage_* bitmap = (AMImage_*)image;
    CHECK_PARG_AND_RET(bitmap);

    return bitmap->w;
}
AMInt32 AMGetHeight(AMImage image)
{
    AMImage_* bitmap = (AMImage_*)image;
    CHECK_PARG_AND_RET(bitmap);

    return bitmap->h;
}
AMInt32 AMImageDestroy(AMImage image)
{
    AMImage_* bitmap = (AMImage_*)image;
    CHECK_PARG_AND_RET(bitmap);

	if(bitmap->createMethod == 1)
	{
#ifdef WINCE
		((IImage*)bitmap->image)->Release();
		if(--gpImageFactoryTotalUsed <= 0)
		{
			gpImgFactory->Release();
			CoUninitialize();
			gpImgFactory = NULL;
		}
#endif

#if defined(WIN32) && !defined(WINCE)
	GlobalFree((HGLOBAL)bitmap->globalAlloc);
#endif
	}
	else
	{
		DeleteObject(bitmap->bitmap);
	}
	
	free(bitmap);

	return AME_IMAGE_SCUESS;
}

AMInt32 AMCreateImage(AMImage* pImage, AMInt8* buffer, AMInt32 length)
{
#ifdef WINCE
	if(gpImgFactory == NULL)
	{
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		if(!SUCCEEDED(CoCreateInstance(CLSID_ImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IImagingFactory, (void **)&gpImgFactory)))
		{
			CoUninitialize();
			return 0;
		}
	}

	//Image对象很重要
	IImage* pIImage = NULL;
	if(SUCCEEDED(gpImgFactory->CreateImageFromBuffer(buffer, length, DISPOSAL_GLOBALFREE,&pIImage)))
	{ 
		gpImageFactoryTotalUsed++;

		//获取图片的信息
		ImageInfo stImageInfo;
		pIImage->GetImageInfo(&stImageInfo);

		AMImage_* bitmap = (AMImage_*)malloc(sizeof(AMImage_));
		CHECK_PARG_AND_RETV(bitmap, AME_MALLOC_ERROR);

		memset(bitmap, 0, sizeof(AMImage_));
		bitmap->createMethod = 1;
		bitmap->image = pIImage;
		//memcpy(bitmap->buffer, buffer, length * sizeof(AMInt8));
		bitmap->w = stImageInfo.Width;
		bitmap->h = stImageInfo.Height;

		*pImage = (AMImage*)bitmap;
		return 1;
	}
	else
	{
		AMInt32 i = GetLastError();
		pImage = NULL;
		return -1;
	}
#endif 
#if defined(WIN32) && !defined(WINCE)
	
	HGLOBAL hMem = GlobalAlloc(GMEM_FIXED, length);
	BYTE* pmem = (BYTE*)GlobalLock(hMem);
	memcpy(pmem,buffer,length);
	GlobalUnlock(hMem);

	IStream* pstm;
	CreateStreamOnHGlobal(hMem,FALSE,&pstm);      
	
	Gdiplus::Image* gdiImage = Gdiplus::Image::FromStream(pstm);

	AMImage_* bitmap = (AMImage_*)malloc(sizeof(AMImage_));
	CHECK_PARG_AND_RETV(bitmap, AME_MALLOC_ERROR);

	memset(bitmap, 0, sizeof(AMImage_));
	bitmap->image = gdiImage;
	bitmap->createMethod = 1;
	bitmap->h = gdiImage->GetHeight();
	bitmap->w = gdiImage->GetWidth();
	bitmap->globalAlloc = hMem;

	*pImage = (AMImage*)bitmap;

	return 1;
#endif
}

AMInt32 AMGetImageBuffer(AMImage img, AMInt32 x, AMInt32 y, AMInt32 width, AMInt32 height, AMInt32* pData)
{

	AMImage_* image = (AMImage_* )img;
	CHECK_PARG_AND_RET(image);

#ifdef WINCE
	if(image->createMethod == 1)
	{
		HDC	hdc = CreateCompatibleDC(GetDC(NULL));
		HBITMAP hBitmap = CreateCompatibleBitmap(GetDC(NULL), image->w, image->h);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdc, hBitmap);
		RECT rc;
		rc.left = 0;
		rc.right = image->w;
		rc.top = 0;
		rc.bottom = image->h;
		HBRUSH hBrush = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
		FillRect(hdc, &rc, hBrush);
		HRESULT hr = ((IImage*)image->image)->Draw(hdc, &rc, NULL);
		if (hr != S_OK)
		{
			//to-do
		}

		for(int i=0; i<height; i++)
		{
			for(int j=0; j<width; j++)
			{
				AMInt32 rgb = GetPixel(hdc, j + x, i + y);
				int alpha =  rgb >> 24 & 0xff;
				int sourceB = rgb >> 16 & 0xff;
				int sourceG = rgb >> 8 & 0xff;
				int sourceR = rgb & 0xff;
				*pData = ((alpha << 24) & 0xff000000) | ((sourceR << 16) & 0xff0000) | ((sourceG << 8) & 0xff00) | (sourceB & 0xff);
				pData ++;
			}
		}
		DeleteObject(hBrush);
		SelectObject(hdc, hOldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(hdc);
	}
  	else
  	{
  		BITMAP* bitmap = &(image->bitmapBuffer);
  		for(int i=0; i<height; i++)
  		{
  			memcpy(pData, ((int*)(bitmap->bmBits))+bitmap->bmWidthBytes*(y+i)+x, width*bitmap->bmBitsPixel);
  			pData += width*bitmap->bmBitsPixel;
  		}
  	}
#endif

#if defined(WIN32) && !defined(WINCE)
	if(image->createMethod = 1)
	{
		Gdiplus::Image* gdiImage = image->image;

		HDC	hdc = CreateCompatibleDC(GetDC(NULL));
		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(gdiImage, 0, 0);

		for(int i=0; i<height; i++)
		{
			for(int j=0; j<width; j++)
			{
				AMInt32 rgb = GetPixel(hdc, j + x, i + y);
				int alpha =  rgb >> 24 & 0xff;
				int sourceB = rgb >> 16 & 0xff;
				int sourceG = rgb >> 8 & 0xff;
				int sourceR = rgb & 0xff;
				*pData = ((alpha << 24) & 0xff000000) | ((sourceR << 16) & 0xff0000) | ((sourceG << 8) & 0xff00) | (sourceB & 0xff);
				pData ++;
			}
		}

		DeleteDC(hdc);
	}
	else
	{
		BITMAP* bitmap = &(image->bitmapBuffer);
		for(int i=0; i<height; i++)
		{
			memcpy(pData, ((int*)(bitmap->bmBits))+bitmap->bmWidthBytes*(y+i)+x, width*bitmap->bmBitsPixel);
			pData += width*bitmap->bmBitsPixel;
		}
	}

#endif

	return AME_GRAPHICS_SUCCESS;
}