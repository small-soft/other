#include "AMGDIIn.h"
//#define _HDC_BUFFER_DEBUG_

AMInt32 AMGraphicsCreate(AMGraphics* pGraphics)
{
    CHECK_PARG_AND_RET(pGraphics);

    AMGraphics_*  g = (AMGraphics_*)malloc(sizeof(AMGraphics_));
    CHECK_PARG_AND_RETV(g, AME_MALLOC_ERROR);
    memset(g, 0 , sizeof(AMGraphics_));

    if((g->hdc = GetDC(NULL)) == NULL)
    {
        DWORD err_code = GetLastError();
        switch(err_code)
        {
        case 0:
        default:
            return AME_GRAPHICS_ERROR;
        }

        //Must Return.
        assert(0);
    }
	/*
    if(_CreateFontFromDC(&g->font, g->hdc) != AME_FONT_SUCCESS)
    {
        free(g);
        return AME_FONT_ERROR;
    }*/
	

    g->width =  GetDeviceCaps(g->hdc, HORZRES);
    g->height = GetDeviceCaps(g->hdc, VERTRES);
    g->createType = AM_FROM_DEFAULT;
    *pGraphics = (AMGraphics*)g;

	AMFont font;
	AMFontCreate(&font);
	AMSetFont(*pGraphics , font);

	AMSetClip(*pGraphics, NULL);
    return AME_GRAPHICS_SUCCESS;
}

AMInt32 AMGetGraphicWidth(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_*)graphics;
    if(NULL == graphics) 
        return AME_ARG_AINVALID;
    else
        return g->width;
}
AMInt32 AMGetGraphicHeigth(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_*)graphics;
    if(NULL == graphics) 
        return AME_ARG_AINVALID;
    else
        return  g->height;
}

AMInt32 AMCreateSystemGraphics(AMGraphics* pGraphics, AMHandle hPlatformGraphics)
{
    CHECK_PARG_AND_RET(pGraphics);
    HWND h = (HWND)hPlatformGraphics;
    CHECK_PARG_AND_RET(h);
    HDC  hdc;
    if((hdc = GetDC(h)) == NULL)
    {
        DWORD err_code = GetLastError();
        return AME_GRAPHICS_ERROR;
    }

    RECT rect;
    //if(GetWindowRect(h, &rect) == NULL)
	if(GetClientRect(h, &rect) == NULL)
    {
        DWORD err_code = GetLastError();
        return AME_GRAPHICS_ERROR;
    }

    AMGraphics_*  g = (AMGraphics_*)malloc(sizeof(AMGraphics_));
    CHECK_PARG_AND_RETV(g, AME_MALLOC_ERROR);

    g->hdc = hdc;
    g->width = rect.right - rect.left;
    g->height = rect.bottom - rect.top;
    g->createType = AM_FROM_HWND;
    g->hwnd = h;
    
	/*
    if(_CreateFontFromDC(&g->font, g->hdc) != AME_FONT_SUCCESS)
    {
        free(g);
        return AME_FONT_ERROR;
    }
	*/
    //创建双缓冲的Hdc.
    g->bufferHdc = CreateCompatibleDC(g->hdc);
    g->bufferBitmap = CreateCompatibleBitmap(g->hdc, g->width, g->height);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(g->bufferHdc, g->bufferBitmap);
    HBRUSH hBrush = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
	FillRect(g->bufferHdc, &rect, hBrush);
    //为了不修改其它函数代码, 这里吧实际要绘制的dc保存到hdc中,原始的hdc放到realHdc中
    g->realHdc = g->hdc;
    g->hdc = g->bufferHdc;
#ifdef _HDC_BUFFER_DEBUG_
	g->hdc = g->realHdc;
	g->bufferHdc = g->realHdc;
#endif // endif
    BitBlt(g->realHdc, 0, 0, g->width, g->height, g->bufferHdc, 0, 0, SRCCOPY);
    //g->hdc = g->realHdc;
    //g->bufferHdc = g->hdc;
    *pGraphics = (AMGraphics*)g;
    // modified by jiajing for setfont 
	//AMFont font;
	//AMFontCreate(&font);
	//AMSetFont(*pGraphics , font);
	AMSetClip(*pGraphics, NULL);

    
    return AME_GRAPHICS_SUCCESS;
}

AMInt32 AMCreateImageGraphics(AMGraphics* pGraphics, AMImage img)
{
    CHECK_PARG_AND_RET(pGraphics);
    AMImage_* image = (AMImage_* )img;
    CHECK_PARG_AND_RET(image);

    HDC hdc = CreateCompatibleDC(GetDC(NULL));
	if(image->createMethod == 1)
	{
	}
	else
	{
		SelectObject(hdc, image->bitmap);
	}

    
	AMGraphics_*  g = (AMGraphics_*)malloc(sizeof(AMGraphics_));
	CHECK_PARG_AND_RETV(g, AME_MALLOC_ERROR);
	memset(g, 0 , sizeof(AMGraphics_));
	g->hdc = hdc;
	if(g->hdc == NULL)
	{
		DWORD err_code = GetLastError();
		switch(err_code)
		{
		case 0:
		default:
			return AME_GRAPHICS_ERROR;
		}

		//Must Return.
		assert(0);
	}
	g->width =  GetDeviceCaps(g->hdc, HORZRES);
	g->height = GetDeviceCaps(g->hdc, VERTRES);
	g->createType = AM_FROM_IMAGE;
	*pGraphics = (AMGraphics*)g;

	// modified by duan shaopeng
	/*AMFont font;
	AMFontCreate(&font);
	AMSetFont(*pGraphics , font);*/
	AMSetClip(*pGraphics, NULL);
    return AME_GRAPHICS_SUCCESS;
}

AMInt32 AMGraphicsDestroy(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_*)graphics;
    CHECK_PARG_AND_RET(graphics);

   /* if(g->font)
        AMFontDestroy(g->font);*/

    switch(g->createType)
    {
    case AM_FROM_DEFAULT:
        DeleteDC(g->hdc);
        
        break;
    case AM_FROM_HWND:
        ReleaseDC(g->hwnd, g->realHdc);
        DeleteObject(g->bufferBitmap);
        DeleteDC(g->bufferHdc);
        break;
    case AM_FROM_IMAGE:
		DeleteDC(g->hdc);
        break;
    }
    
    free(g);
    g = NULL;
    return AME_GRAPHICS_SUCCESS;
}
AMInt32 AMDrawLine(AMGraphics graphics, AMPoint* p1, AMPoint* p2)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(graphics);
    CHECK_PARG_AND_RET(p1);
    CHECK_PARG_AND_RET(p2);

    _AMSetForeColor(graphics);
    
    if(MoveToEx(g->hdc, p1->x, p1->y, NULL) == NULL)
        return AME_GRAPHICS_ERROR;
    if(LineTo(g->hdc, p2->x , p2->y) == NULL)
        return AME_GRAPHICS_ERROR;

    return AME_GRAPHICS_SUCCESS;
}
AMInt32 AMDrawRect(AMGraphics graphics, AMRect* rect)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(graphics);
    CHECK_PARG_AND_RET(rect);
    //_AMSetForeColor(graphics);
	int errno; 
	HGDIOBJ oldBreush = SelectObject(g->hdc,GetStockObject(NULL_BRUSH));
    if(Rectangle(g->hdc, rect->x, rect->y,  rect->x + rect->w, rect->y + rect->h) == 0)
        errno = AME_GRAPHICS_ERROR;
    else
        errno = AME_GRAPHICS_SUCCESS;
	SelectObject(g->hdc,oldBreush);
	return errno;
}
AMInt32 AMFillRect(AMGraphics graphics, AMRect* rect)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(graphics);
    CHECK_PARG_AND_RET(rect);
	
    HBRUSH hbrush = CreateSolidBrush(g->bgColor);
    RECT fillRect = {rect->x, rect->y,rect->x + rect->w,rect->y + rect->h};
    AMInt32 retValue = AME_GRAPHICS_SUCCESS ;
    if(FillRect(g->hdc, &fillRect, hbrush) == 0)
        retValue = AME_GRAPHICS_ERROR;
    DeleteObject(hbrush);
    return retValue;
}
AMInt32 AMDrawRoundRect(AMGraphics graphics, AMRect* rect, AMInt32 arcWidth, AMInt32 arcHeight)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(graphics);
    CHECK_PARG_AND_RET(rect);
    _AMSetForeColor(graphics);
    if(RoundRect(g->hdc, rect->x, rect->y,  rect->x + rect->w, rect->y + rect->h, arcWidth, arcHeight) == 0)
        return AME_GRAPHICS_ERROR;
    else
        return AME_GRAPHICS_SUCCESS;
}
AMInt32 AMFillRoundRect(AMGraphics graphics, AMRect* rect, AMInt32 arcWidth, AMInt32 arcHeight)
{
    return   AME_GRAPHICS_SUCCESS;
}
AMInt32 AMFillArc(AMGraphics graphics, AMRect* rect, AMInt32 startAngle, AMInt32 arcAngle)
{
	AMGraphics_* g = (AMGraphics_* )graphics;
	CHECK_PARG_AND_RET(graphics);
	CHECK_PARG_AND_RET(rect);

	Ellipse(g->hdc, rect->x, rect->y , rect->x + rect->w, rect->y + rect->h);
	return AME_GRAPHICS_SUCCESS;

}
AMInt32 AMDrawArc(AMGraphics graphics, AMRect* rect, AMInt32 startAngle, AMInt32 arcAngle)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(graphics);
    CHECK_PARG_AND_RET(rect);
    //创建一个Clip区域.
    //AMInt32 x = rect->x + rect->w /2;
    //AMInt32 y = rect->x + rect->w /2;
    //AMInt32 x1, y1, x2, y2;
	HGDIOBJ oldBreush = SelectObject(g->hdc,GetStockObject(NULL_BRUSH));
    Ellipse(g->hdc, rect->x, rect->y , rect->x + rect->w, rect->y + rect->h);
	SelectObject(g->hdc,oldBreush);
    return AME_GRAPHICS_SUCCESS;
}
AMInt32 AMFillPolygon(AMGraphics graphics, AMPoint points[], AMInt32 nPoints)
{
    return   AME_GRAPHICS_SUCCESS;
}
AMInt32 AMDrawPolygon(AMGraphics graphics, AMPoint points[], AMInt32 nPoints)
{
    return   AME_GRAPHICS_SUCCESS;
}
AMInt32 AMDrawTriangle(AMGraphics graphics, AMPoint* p1, AMPoint* p2,  AMPoint* p3)
{
    return   AME_GRAPHICS_SUCCESS;
}
AMInt32 AMFillTriangle(AMGraphics graphics, AMPoint* p1, AMPoint* p2,  AMPoint* p3)
{
	AMGraphics_* g = (AMGraphics_* )graphics;
	CHECK_PARG_AND_RET(graphics);
	POINT point[3];
	point[0].x = p1->x;
	point[0].y = p1->y;
	point[1].x = p2->x;
	point[1].y = p2->y;
	point[2].x = p3->x;
	point[2].y = p3->y;
	if (!Polygon(g->hdc, point, 3))
	{
		DWORD err_code = GetLastError();
		return AME_GRAPHICS_ERROR;
	}
    return   AME_GRAPHICS_SUCCESS;
}
AMInt32 AMDrawText(AMGraphics graphics, const AMWChar* str, AMPoint* point, AMInt32 startPos, AMInt32 len)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(graphics);
    CHECK_PARG_AND_RET(str);
    CHECK_PARG_AND_RET(point);

    //调整参数.
    int str_len= wcslen((wchar_t*)str);
    if(startPos < 0)
        startPos = 0;
    else if(startPos >= str_len)
        return AME_ARG_AINVALID;
    if(len <= 0)
        len = str_len - startPos;
    len = min(len, str_len - startPos);

	SetBkMode(g->hdc,TRANSPARENT);
    if(ExtTextOut(g->hdc, point->x, point->y, ETO_OPAQUE, NULL,
	            (LPCWSTR)str + startPos, len, NULL) == NULL)
    {
        DWORD err_code = GetLastError();
        return AME_GRAPHICS_ERROR;
    }

    return AME_GRAPHICS_SUCCESS;
}

AMInt32 AMBitBlt(AMGraphics dst, AMRect* rect, AMGraphics src, AMPoint* point, AMDrawMode drawMode)
{
	AMGraphics_* gdst = (AMGraphics_* )dst;
	AMGraphics_* gsrc = (AMGraphics_* )src;
	CHECK_PARG_AND_RET(gdst);
	CHECK_PARG_AND_RET(gsrc);
	CHECK_PARG_AND_RET(rect);
	CHECK_PARG_AND_RET(point);

	if(BitBlt(gdst->hdc, rect->x, rect->y, rect->w, rect->h, gsrc->hdc, 
	point->x, point->y, _ParseDrawMode(drawMode)) == NULL)
	{
		DWORD err_code = GetLastError();
		return AME_GRAPHICS_ERROR;
	}
	return AME_GRAPHICS_SUCCESS;
	//return _AMBitBltEx(dst, rect, src, point, drawMode);
}

AMInt32 AMStretchBlt(AMGraphics dst, AMRect* dstRect, AMGraphics src, AMRect* srcRect, AMDrawMode drawMode)
{
    AMGraphics_* gdst = (AMGraphics_* )dst;
    AMGraphics_* gsrc = (AMGraphics_* )src;
    CHECK_PARG_AND_RET(gdst);
    CHECK_PARG_AND_RET(gsrc);
    CHECK_PARG_AND_RET(dstRect);
    CHECK_PARG_AND_RET(srcRect);
    
    if(StretchBlt(gdst->hdc, dstRect->x, dstRect->y, dstRect->w, dstRect->h, gsrc->hdc, 
        srcRect->x, srcRect->y, srcRect->w, srcRect->h, _ParseDrawMode(drawMode)) == NULL)
    {
        DWORD err_code = GetLastError();
        return AME_GRAPHICS_ERROR;
    }
    return AME_GRAPHICS_SUCCESS;
}

AMFont AMGetFont(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET0(g);

    return g->font;
}
AMFont AMSetFont(AMGraphics graphics, AMFont font)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET0(g);
    CHECK_PARG_AND_RET0(font);

    AMFont preFont = g->font;
    g->font = font;
    
    AMFont_* f = (AMFont_*)g->font;
    SelectObject(g->hdc, f->hfont);
    return preFont;
}

AMRGB AMGetColor(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET0(g);

	int alpha =  g->color >> 24 & 0xff;
	int sourceB = g->color >> 16 & 0xff;
	int sourceG = g->color >> 8 & 0xff;
	int sourceR = g->color & 0xff;
    return ((alpha << 24) & 0xff000000) | ((sourceR << 16) & 0xff0000) | ((sourceG << 8) & 0xff00) | (sourceB & 0xff);
}
AMInt32 AMSetColor(AMGraphics graphics, AMRGB rgb)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);

	int alpha =  rgb >> 24 & 0xff;
	int sourceR = rgb >> 16 & 0xff;
	int sourceG = rgb >> 8 & 0xff;
	int sourceB = rgb & 0xff;
	
	int rgbWin = ((alpha << 24) & 0xff000000) | ((sourceB << 16) & 0xff0000) | ((sourceG << 8) & 0xff00) | (sourceR & 0xff);
    if(g->color != rgbWin)
    {
        g->color = rgbWin;
        g->isSetBackColor = FALSE;
        g->isSetForeColor = FALSE;
        g->isSetTextColor = FALSE;
    }
    return AME_GRAPHICS_SUCCESS;
}

AMInt32 AMDrawImageArea(AMGraphics graphics, AMPoint* point, AMImage img, AMRect* rect, AMDrawMode drawMode)
{

    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);
    CHECK_PARG_AND_RET(point);
    AMImage_* image = (AMImage_* )img;
    CHECK_PARG_AND_RET(image);
	
	if(image->createMethod == 1)
	{
		#ifdef WINCE
		HDC hdc = CreateCompatibleDC(g->hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(g->hdc, image->w, image->h);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdc, hBitmap);
		/*
		pBitmapImage->LockBits(0, ImageLockModeRead, PixelFormatDontCare,pLockedBitmapData);
		memcpy(pvBuf, pLockedBitmapData->Scan0, pLockedBitmapData->Width*pLockedBitmapData->Height*2);
		pBitmapImage->UnlockBits(pLockedBitmapData);
		*/
		RECT rc;
		rc.left = point->x;
		rc.right = point->x + min(rect->w, (image->w - rect->x));
		rc.top = point->y;
		rc.bottom = point->y +  min(rect->h, (image->h - rect->y));
		
		/*
		RECT rc;
		rc.left = rect->x;
		rc.right = rect->x + rect->w;
		rc.top = rect->y;
		rc.bottom = rect->y + rect->h;

		int x1, y1, x2, y2;
		x1 = max(rect->x,   g->clipX);
		y1 = max(rect->y,   g->clipY);  
		x2 = min(rect->x + rect->w,   g->clipX + g->clipW);  
		y2 = min(rect->y + rect->h,   g->clipY + g->clipH);
	
		rc.left = x1;
		rc.right = x2;
		rc.top = y1;
		rc.bottom = y2;
		*/

		HBRUSH hBrush = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
		FillRect(hdc, &rc, hBrush);
		((IImage*)image->image)->Draw(g->hdc, &rc, NULL);
		/*
		AMRect dstRect;
		dstRect.x = point->x;
		dstRect.y = point->y;
		dstRect.w =  min(rect->w, (image->w - rect->x));
		dstRect.h =  min(rect->h, (image->h - rect->y));
		AMPoint point;
		point.x = rect->x;
		point.y = rect->y;
		_BitBltEx(g->hdc, &dstRect,hdc, &point, drawMode);
		*/
		/*
		TransparentBlt(g->hdc, point->x, point->y, min(rect->w, (image->w - rect->x)), min(rect->h, (image->h - rect->y)),
				hdc, 0, 0, min(rect->w, (image->w - rect->x)), min(rect->h, (image->h - rect->y)), RGB(0xFF, 0xFF, 0xFF));
		*/
		DeleteObject(hBrush);
		SelectObject(hdc, hOldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(hdc);
		#endif

		#if defined(WIN32) && !defined(WINCE)
		Gdiplus::Graphics graphics(g->hdc);
		graphics.DrawImage(image->image, 
			point->x, 
			point->y, 
			rect->x, 
			rect->y,
			min(rect->w, (image->w - rect->x)), 
			min(rect->h, (image->h - rect->y)),
			Gdiplus::UnitPixel);		
		#endif
	}
	else
	{
		HDC hdc = CreateCompatibleDC(g->hdc);
		HGDIOBJ  obj = SelectObject(hdc, image->bitmap);
		BitBlt(g->hdc, point->x, point->y, min(rect->w, (image->w - rect->x)), min(rect->h, (image->h - rect->y)),
			hdc, rect->x, rect->y,  _ParseDrawMode(drawMode));
		SelectObject(hdc, obj);
		DeleteDC(hdc);
	}
	
    return AME_GRAPHICS_SUCCESS;
}

AMInt32 AMDrawImage(AMGraphics graphics, AMPoint* point, AMImage img, AMDrawMode drawMode)
{
    AMImage_* image = (AMImage_* )img;
    CHECK_PARG_AND_RET(image);

    AMRect rect = {0, 0, image->w, image->h};
    return AMDrawImageArea(graphics, point, img, &rect, drawMode);
}

AMInt32 AMGetClipX(AMGraphics graphics)	
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);
    return g->clipX;
}
AMInt32 AMGetClipY(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);
    return g->clipY;
}
AMInt32 AMGetClipWidth(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);
    return g->clipW;
}
AMInt32 AMGetClipHeight(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);
    return g->clipH;
}
AMInt32 AMClipRect(AMGraphics graphics, AMRect* rect)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);
    CHECK_PARG_AND_RET(rect);

    //合并区域.
    int x1, y1, x2, y2;
    x1 = max(rect->x,   g->clipX);
    y1 = max(rect->y,   g->clipY);  
    x2 = min(rect->x + rect->w,   g->clipX + g->clipW);  
    y2 = min(rect->y + rect->h,   g->clipY + g->clipH);

    if(x1 > x2 || y1 > y2)
    {
        AMRect rect = { 0, 0 , 0, 0};
        AMSetClip(graphics, &rect);
        g->clipX = 0;
        g->clipY = 0;
        g->clipW = 0;
        g->clipH = 0;
        return AME_GRAPHICS_SUCCESS;
    }
    else
    {
        HRGN rgn = CreateRectRgn(x1, y1, x2, y2);
        SelectClipRgn(g->hdc, rgn);
        g->clipX = x1;
        g->clipY = y1;
        g->clipW = x2 - x1;
        g->clipH = y2 - y1;
        return AME_GRAPHICS_SUCCESS;
    }
}
AMInt32  AMSetClip(AMGraphics graphics, AMRect* rect)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);
    if(NULL == rect)
    {
		g->clipX = 0;
		g->clipY = 0;
		g->clipW = g->width;
		g->clipH = g->height;
        SelectClipRgn(g->hdc, NULL);
        return AME_GRAPHICS_SUCCESS;
    }

    HRGN rgn = CreateRectRgn(rect->x, rect->y, rect->x + rect->w, rect->y + rect->h);
    SelectClipRgn(g->hdc, rgn);
	g->clipX = rect->x;
	g->clipY = rect->y;
	g->clipW = rect->w;
	g->clipH = rect->h;
    return AME_GRAPHICS_SUCCESS;
}

AMInt32  AMSetAlpha(AMGraphics graphics, AMUInt8 alpha)
{	
	AMGraphics_* g = (AMGraphics_* )graphics;
	CHECK_PARG_AND_RET0(g);
	
	g->alpha = alpha;
   
	return 0;
}

AMUInt8 AMGetAlpha(AMGraphics graphics)
{	
	AMGraphics_* g = (AMGraphics_* )graphics;
	CHECK_PARG_AND_RET0(g);

	return g->alpha;
 
}
AMBool  AMIsAlphaSupported(AMGraphics graphics)
{
    return 0;
}

ADAPTER_API AMInt32 AMUpdateRect(AMGraphics graphics, AMRect* rect)
{
	//static int index = 0;
	//printf("index = %d\n", index++);
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);
    if(g->createType != AM_FROM_HWND)
        return AME_GRAPHICS_SUCCESS;

    if(rect == NULL)
    {
        BitBlt(g->realHdc, 0, 0, g->width, g->height, g->bufferHdc, 0, 0,_ParseDrawMode(AMDM_SCR));
        return AME_GRAPHICS_SUCCESS;
    }
    else
    {
        BitBlt(g->realHdc, rect->x, rect->y, rect->w, rect->h, g->bufferHdc, rect->x, rect->y, _ParseDrawMode(AMDM_SCR));
        return AME_GRAPHICS_SUCCESS;
    }
}
AMRGB AMGetBGColor(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);
	
	int alpha =  g->bgColor >> 24 & 0xff;
	int sourceB = g->bgColor >> 16 & 0xff;
	int sourceG = g->bgColor >> 8 & 0xff;
	int sourceR = g->bgColor & 0xff;
	return ((alpha << 24) & 0xff000000) | ((sourceR << 16) & 0xff0000) | ((sourceG << 8) & 0xff00) | (sourceB & 0xff);
}
AMInt32 AMSetBGColor(AMGraphics graphics, AMRGB rgb)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);

	int alpha =  rgb >> 24 & 0xff;
	int sourceR = rgb >> 16 & 0xff;
	int sourceG = rgb >> 8 & 0xff;
	int sourceB = rgb & 0xff;

	int rgbWin = ((alpha << 24) & 0xff000000) | ((sourceB << 16) & 0xff0000) | ((sourceG << 8) & 0xff00) | (sourceR & 0xff);

    g->bgColor = rgbWin;
    _AMSetBrushColor(graphics);
    return   AME_GRAPHICS_SUCCESS;
}
AMRGB AMGetFGColor(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);

	int alpha =  g->fgColor >> 24 & 0xff;
	int sourceB = g->fgColor >> 16 & 0xff;
	int sourceG = g->fgColor >> 8 & 0xff;
	int sourceR = g->fgColor & 0xff;
	return ((alpha << 24) & 0xff000000) | ((sourceR << 16) & 0xff0000) | ((sourceG << 8) & 0xff00) | (sourceB & 0xff);
}
AMInt32 AMSetFGColor(AMGraphics graphics, AMRGB rgb)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(g);

	int alpha =  rgb >> 24 & 0xff;
	int sourceR = rgb >> 16 & 0xff;
	int sourceG = rgb >> 8 & 0xff;
	int sourceB = rgb & 0xff;
	int rgbWin = ((alpha << 24) & 0xff000000) | ((sourceB << 16) & 0xff0000) | ((sourceG << 8) & 0xff00) | (sourceR & 0xff);

    g->fgColor = rgbWin;
    _AMSetForeColor(graphics);
    _AMSetTextColor(graphics);
    return   AME_GRAPHICS_SUCCESS;
}

AMInt32 AMTranslate(AMGraphics graphics, AMInt32 x, AMInt32 y)
{
	AMGraphics_* g = (AMGraphics_* )graphics;
	CHECK_PARG_AND_RET(g);
	SetViewportOrgEx(g->hdc, x, y, NULL); 
	return  AME_GRAPHICS_SUCCESS;
}