#include "AMGDIIn.h"

void _SetFontSize(AMFontSize size, const LOGFONT* src,  LOGFONT* dst)
{
#if 0
	printf("字体大小: %d , %d\n", src->lfHeight, src->lfWidth);
	printf("字体名称: %S", src->lfFaceName);
	printf("\n");
#endif
	switch(size)
	{
	case AMFONT_SIZE_SMALL:
		//dst->lfHeight = src->lfHeight * 0.8;
		//dst->lfWidth = src->lfWidth * 0.8;
		dst->lfHeight =  10;
		dst->lfWidth =  5;
		return;
	case AMFONT_SIZE_LARGE:

		//dst->lfHeight = src->lfHeight * 1.5;
		//dst->lfWidth =  src->lfWidth * 1.5;
		dst->lfHeight =  18;
		dst->lfWidth =  9;
		return;
	default:
		//dst->lfHeight =  src->lfHeight;
		//dst->lfWidth =  src->lfWidth;
		dst->lfHeight =  12;
		dst->lfWidth =  6;
		return;
	}
}

#ifdef WINCE
int _FontCreateEnumFontFamProc(const LOGFONT* lpelf, const TEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam)
#else
int CALLBACK _FontCreateEnumFontFamProc(const LOGFONT * lpelf, const TEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam)
#endif
{
    AMFont_* f = (AMFont_*)lParam;
    if(NULL == f)
        return 0;
    if(NULL == f->hfont)
    {

        memcpy(&f->format, lpelf,  sizeof(LOGFONT));
		 _SetFontSize(f->size, lpelf, &f->format);
        f->hfont = CreateFontIndirect(&f->format);
        return 0;
    }
    return 1;
}
#ifdef WINCE
int _GetBitmapFontEnumFontFamProc(const LOGFONT* lpelf, const TEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam)
#else
int CALLBACK _GetBitmapFontEnumFontFamProc(const LOGFONT* lpelf, const TEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam)
#endif

{
    AMFont_* f = (AMFont_*)lParam;
    if(NULL == f)
        return 0;
    if(NULL == f->hfont)
    {
        memcpy(&f->format, lpelf,  sizeof(LOGFONT));
        if(wcscmp((wchar_t *)lpelf->lfFaceName, (wchar_t *)f->fontName) == 0)
        {
            f->hfont = CreateFontIndirect(&f->format);
            return 0;
        }
    }
    return 1;
}


#ifdef WINCE
int _FontCreateSystemFontEnumFontFamProc(const LOGFONT* lpelf, const TEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam)
#else
int CALLBACK _FontCreateSystemFontEnumFontFamProc(const LOGFONT* lpelf, const TEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam)
#endif
{

    AMFont_* f = (AMFont_*)lParam;
    if(NULL == f)
        return 0;
    if(NULL == f->hfont)
    {
        memcpy(&f->format, lpelf,  sizeof(LOGFONT));
        f->format.lfItalic = ((f->style & AMFONT_STYLE_ITALIC) > 0 ) ? TRUE : FALSE;
        f->format.lfWeight = ((f->style & AMFONT_STYLE_BOLD) > 0 ) ? FW_BOLD : FW_NORMAL;
        _SetFontSize(f->size, lpelf, &f->format);
        f->hfont = CreateFontIndirect(&f->format);
        return 0;
    }
    return 1;
}

HFONT _GetDcFont(HDC hdc)
{
    return (HFONT)GetCurrentObject(hdc, OBJ_FONT);
}
int   _GetDcFontInfo(HFONT hfont, int bufferLen, unsigned char* buffer)
{
    return GetObject(hfont, bufferLen, buffer);
}

int _CreateFontFromDC(AMFont* font,  HDC hdc)
{
    if(NULL == font)
        return AME_FONT_ERROR;

    HFONT hfont = _GetDcFont(hdc);
    if(NULL == hfont)
        return AME_FONT_ERROR;

    LOGFONT fontInfo; 
    if(GetObject(hfont, sizeof(LOGFONT), &fontInfo) == 0)
        return AME_FONT_ERROR;

    AMFont_* f = (AMFont_*)malloc(sizeof(AMFont_));
    memset(f, 0, sizeof(AMFont_));

    f->hfont = hfont;
    f->hdc = hdc;
    memcpy(&f->format, &fontInfo, sizeof(LOGFONT));
    *font = f;
    return AME_FONT_SUCCESS;
}

DWORD _ParseDrawMode(AMDrawMode drawMode)
{
    
    switch(drawMode)
    {
    case AMDM_AND: return SRCAND;
	case AMDM_NOTAND: return SRCERASE;
	case AMDM_ANDNOT:break ;
	case AMDM_XOR:return SRCINVERT;
	case AMDM_OR:return SRCPAINT;
	case AMDM_NOTOR:break;
	case AMDM_NOTXOR:break;
	case AMDM_ORNOT:break;
	case AMDM_NOTORNOT: break;
    case AMDM_NOTANDNOT:return NOTSRCERASE;
    case AMDM_NOTSCR:return NOTSRCCOPY;
    case AMDM_NOTDST:return DSTINVERT;
    case AMDM_SCR:return SRCCOPY;
    case AMDM_ALPHA:break;
    }
    

    return SRCCOPY;
}

HPEN  _CreatePen(AMRGB rgb)
{
    return CreatePen(PS_SOLID,  1, rgb);
}

AMInt32 _AMSetForeColor(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(graphics);
#if 0
    if(g->isSetForeColor == FALSE)
    {
        HPEN hPen = _CreatePen(g->color);
        HPEN oldhPen = (HPEN)SelectObject(g->hdc, hPen);
        if(g->isSetPen == FALSE)
        {
            g->pen = oldhPen;
            g->isSetPen = TRUE;
        }
        else
            DeleteObject(oldhPen);
        g->isSetForeColor = TRUE;
    }
#else
    HPEN hPen = _CreatePen(g->fgColor);
    HPEN oldhPen = (HPEN)SelectObject(g->hdc, hPen);
    if(g->isSetPen == FALSE)
    {
        g->pen = oldhPen;
        g->isSetPen = TRUE;
    }
    else
        DeleteObject(oldhPen);
#endif
    return AME_GRAPHICS_SUCCESS;
}

AMInt32 _AMSetBrushColor(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(graphics);
#if 0
    if(g->isSetBackColor == FALSE)
    {
        HBRUSH hBrush = CreateSolidBrush(g->color);
        HBRUSH oldBrush = (HBRUSH)SelectObject(g->hdc, hBrush);

         if(g->isSetPen == FALSE)
        {
            g->brush  = oldBrush;
            g->isSetBrush = TRUE;
        }
        else
            DeleteObject(oldBrush);

        g->isSetBackColor = TRUE;
    }
#else
	
    HBRUSH hBrush = CreateSolidBrush(g->bgColor);
	int errorno = GetLastError();
    HBRUSH oldBrush = (HBRUSH)SelectObject(g->hdc, hBrush);
    if(g->isSetPen == FALSE)
    {
        g->brush  = oldBrush;
        g->isSetBrush = TRUE;
    }
    else
        DeleteObject(oldBrush);
#endif
    return AME_GRAPHICS_SUCCESS;
}
AMInt32 _AMSetTextColor(AMGraphics graphics)
{
    AMGraphics_* g = (AMGraphics_* )graphics;
    CHECK_PARG_AND_RET(graphics);

#if 0
    if(g->isSetTextColor == FALSE)
    {
        SetTextColor(g->hdc, g->color);
        g->isSetTextColor = TRUE;
    }
#else
    SetTextColor(g->hdc, g->fgColor);
#endif

    return AME_GRAPHICS_SUCCESS;
}

#define ARGB_GETALPHA(rgb)      (AMUInt8)((rgb) >> 24)
#define ARGB_GETRED(rgb)        (AMUInt8)(((rgb)) & 0xff)
#define ARGB_GETGREEN(rgb)      (AMUInt8)(((rgb) >> 8) & 0xff)
#define ARGB_GETBLUE(rgb)       (AMUInt8)(((rgb) >> 16) & 0xff)
AMInt32 _AMBitBltEx(AMGraphics dst, AMRect* rect, AMGraphics src, AMPoint* point, AMDrawMode drawMode)
{
	AMGraphics_* gdst = (AMGraphics_* )dst;
	AMGraphics_* gsrc = (AMGraphics_* )src;
	CHECK_PARG_AND_RET(gdst);
	CHECK_PARG_AND_RET(gsrc);
	CHECK_PARG_AND_RET(rect);
	CHECK_PARG_AND_RET(point);

	/*
	if(BitBlt(gdst->hdc, rect->x, rect->y, rect->w, rect->h, gsrc->hdc, 
	point->x, point->y, _ParseDrawMode(drawMode)) == NULL)
	{
	DWORD err_code = GetLastError();
	return AME_GRAPHICS_ERROR;
	}
	*/
	for(int x = 0; x < rect->w; x++)
	{
		for(int y = 0; y < rect->h; y++)
		{
			COLORREF  corSrc = GetPixel(gsrc->hdc, point->x + x, point->y + y);
			COLORREF  corDst = GetPixel(gdst->hdc, rect->x + x, rect->y + y);

			AMUInt8 alphaSrc = ARGB_GETALPHA(corSrc);
			AMUInt8 alphadst = ARGB_GETALPHA(corDst);
			AMUInt8 rS = ARGB_GETRED(corSrc);
			AMUInt8 gS = ARGB_GETGREEN(corSrc);
			AMUInt8 bS = ARGB_GETBLUE(corSrc);   

			AMUInt8 rd= ARGB_GETRED(corDst);
			AMUInt8 gd = ARGB_GETGREEN(corDst);
			AMUInt8 bd = ARGB_GETBLUE(corDst);

			AMUInt8 r = (AMUInt8)(((rS * alphaSrc) + (rd * (255-alphaSrc)))/255);
			AMUInt8 g = (AMUInt8)(((gS * alphaSrc) + (gd * (255-alphaSrc)))/255);
			AMUInt8 b = (AMUInt8)(((bS * alphaSrc) + (bd * (255-alphaSrc)))/255);

			COLORREF uiNewColor = alphadst << 24 |b <<16| g<<8 | r ;

			SetPixel(gsrc->hdc, rect->x + x, rect->y + y, uiNewColor);
		}
	}

	if(BitBlt(gdst->hdc, rect->x, rect->y, rect->w, rect->h, gsrc->hdc, 
		point->x, point->y, _ParseDrawMode(drawMode)) == NULL)
	{
		DWORD err_code = GetLastError();
		return AME_GRAPHICS_ERROR;
	}

	return AME_GRAPHICS_SUCCESS;
}

AMInt32 _BitBltEx(HDC dst, AMRect* rect, HDC src, AMPoint* point, AMDrawMode drawMode)
{
	CHECK_PARG_AND_RET(rect);
	CHECK_PARG_AND_RET(point);

	/*
	if(BitBlt(gdst->hdc, rect->x, rect->y, rect->w, rect->h, gsrc->hdc, 
	point->x, point->y, _ParseDrawMode(drawMode)) == NULL)
	{
	DWORD err_code = GetLastError();
	return AME_GRAPHICS_ERROR;
	}
	*/
	for(int x = 0; x < rect->w; x++)
	{
		for(int y = 0; y < rect->h; y++)
		{
			COLORREF  corSrc = GetPixel(src, point->x + x, point->y + y);
			COLORREF  corDst = GetPixel(dst, rect->x + x, rect->y + y);

			//if((corSrc & 0xff000000) != 0)
			//	return 0;

			AMUInt8 alphaSrc = ARGB_GETALPHA(corSrc);
			AMUInt8 alphadst = ARGB_GETALPHA(corDst);
			AMUInt8 rS = ARGB_GETRED(corSrc);
			AMUInt8 gS = ARGB_GETGREEN(corSrc);
			AMUInt8 bS = ARGB_GETBLUE(corSrc);   

			AMUInt8 rd= ARGB_GETRED(corDst);
			AMUInt8 gd = ARGB_GETGREEN(corDst);
			AMUInt8 bd = ARGB_GETBLUE(corDst);

			AMUInt8 r = (AMUInt8)(((rS * alphaSrc) + (rd * (255-alphaSrc)))/255);
			AMUInt8 g = (AMUInt8)(((gS * alphaSrc) + (gd * (255-alphaSrc)))/255);
			AMUInt8 b = (AMUInt8)(((bS * alphaSrc) + (bd * (255-alphaSrc)))/255);

			COLORREF uiNewColor = alphadst << 24 |b <<16| g<<8 | r ;

			SetPixel(src, rect->x + x, rect->y + y, uiNewColor);
		}
	}

	if(BitBlt(dst, rect->x, rect->y, rect->w, rect->h, src, 
		point->x, point->y, _ParseDrawMode(drawMode)) == NULL)
	{
		DWORD err_code = GetLastError();
		return AME_GRAPHICS_ERROR;
	}

	return AME_GRAPHICS_SUCCESS;
}