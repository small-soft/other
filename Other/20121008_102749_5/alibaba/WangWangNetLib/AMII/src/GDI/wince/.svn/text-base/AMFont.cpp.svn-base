#include "AMGDIIn.h"
AMInt32 AMFontCreate(AMFont* pFont)
{
    CHECK_PARG_AND_RET(pFont);

    AMFont_* f = (AMFont_*)malloc(sizeof(AMFont_));
    CHECK_PARG_AND_RETV(f, AME_MALLOC_ERROR);
    memset(f, 0 , sizeof(AMFont_));
    f->style = AMFONT_STYLE_ERROR;
    f->size = AMFONT_SIZE_MEDIUM;
    f->face = AMFONT_FACE_SYSTEM;
    f->hdc = GetDC(NULL);
    EnumFontFamilies(f->hdc, NULL, _FontCreateEnumFontFamProc, (LPARAM)f);

    if(NULL == f->hfont)
    {
        free(f);
        return AME_FONT_ERROR;
    }

    *pFont = f;
    return AME_FONT_SUCCESS;
}

AMInt32 AMFontDestroy(AMFont font)
{
    AMFont_* pfont = (AMFont_*)font;
    CHECK_PARG_AND_RET(pfont);

    free(pfont);
    pfont = NULL;
    return AME_FONT_SUCCESS;
}
AMInt32 AMGetBitmapFont(AMFont* pFont, const AMWChar* fontName)
{
    if(NULL == pFont) 
        return AME_ARG_AINVALID;

    if(NULL == fontName)
        return AMFontCreate(pFont);

    AMFont_* f = (AMFont_*)malloc(sizeof(AMFont_));
    if(NULL == f)
        return AME_MALLOC_ERROR;
    memset(f, 0 , sizeof(AMFont_));
    wcscpy((wchar_t *)f->fontName, (wchar_t *)fontName);
    f->style = AMFONT_STYLE_ERROR;
    f->size = AMFONT_SIZE_MEDIUM;
    f->face = AMFONT_FACE_SYSTEM;
    f->hdc = GetDC(NULL);
    EnumFontFamilies(f->hdc, NULL, _GetBitmapFontEnumFontFamProc, (LPARAM)f);

    if(NULL == f->hfont)
    {
        free(f);
        return AME_FONT_ERROR;
    }

    *pFont = f;
    return AME_FONT_SUCCESS;
}

AMInt32 AMCreateSystemFont(AMFont* pFont, AMFontFace face, AMFontStyle style, AMFontSize size)
{
    CHECK_PARG_AND_RET(pFont);

    AMFont_* f = (AMFont_*)malloc(sizeof(AMFont_));
    CHECK_PARG_AND_RETV(f, AME_MALLOC_ERROR);
    memset(f, 0 , sizeof(AMFont_));
    f->hdc = GetDC(NULL);
    f->size = size;
    f->style = style;
    f->face = face;

    EnumFontFamilies(f->hdc, NULL, _FontCreateSystemFontEnumFontFamProc, (LPARAM)f);
    if(NULL == f->hfont)
    {
        free(f);
        return AME_FONT_ERROR;
    }
    *pFont = f;
    return AME_FONT_SUCCESS;
}

AMBool  AMIsTrueTypeFileSupported()
{
    return AMFALSE;
}
AMInt32 AMCreateTrueTypeFont(AMFont* pFont, const AMWChar* fileName)
{
    return AME_UNIMPL_METHOD;
}

AMInt32 AMCharsWidth(AMFont font, const AMWChar* text, AMInt32 length)
{
    AMFont_* pfont = (AMFont_*)font;
    CHECK_PARG_AND_RET(pfont);
    SIZE size = { 0};
    if(GetTextExtentPoint(pfont->hdc, (WCHAR*)text, length, &size) == 0)
	{
	   int errorCode = GetLastError();
       return AME_FONT_ERROR;
	}
#if 0
	if(wcscmp(text, L"UI Demo")==0)
	{
		length = length;
	}
	printf("×ÖÌå¿í¶È: \"%S", text);
	printf("\" = [%d, %d]\n", size.cx, size.cy);
#endif
    return size.cx;
}
AMInt32 AMCharHeight(AMFont font)
{
    AMFont_* pfont = (AMFont_*)font;
    CHECK_PARG_AND_RET(pfont);

    TEXTMETRIC textMetric;
    GetTextMetrics(pfont->hdc, &textMetric);
    return textMetric.tmHeight;
}

AMFontFace AMGetFace(AMFont font)
{    
    AMFont_* pfont = (AMFont_*)font;
    if(NULL == pfont) 
        return AMFONT_FACE_ERROR;

    return pfont->face;
}
AMFontSize AMGetSize(AMFont font)
{
    AMFont_* pfont = (AMFont_*)font;
    if(NULL == pfont) 
        return AMFONT_SIZE_ERROR;

    return pfont->size;
}
AMFontStyle AMGetStyle(AMFont font)
{
    AMFont_* pfont = (AMFont_*)font;
    if(NULL == pfont) 
        return AMFONT_STYLE_ERROR;

    return pfont->style;
}