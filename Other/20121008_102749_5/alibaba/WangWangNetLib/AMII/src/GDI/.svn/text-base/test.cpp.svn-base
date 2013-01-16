#include "AMGDI.h"
#include "string.h"
#include "windows.h"

#define AMWStrlen(str) _tcslen(str)

int wmain()
{
    /*
    AMGraphics pGraphics;
    AMGraphicsCreate(&pGraphics);
    int width = AMGetGraphicWidth(pGraphics);
    int height = AMGetGraphicHeigth(pGraphics);

    AMPoint p1 = {30, 30};
    AMPoint p2 = {200, 200};
    AMDrawLine(pGraphics, &p1, &p2);
    AMDrawText(pGraphics, (AMWChar*)L"Hello World", &p1, 0, wcslen(L"Hello World"));
    AMRect rect = { 30, 30, 100, 200};
    AMBitBlt(pGraphics, &rect, pGraphics, &p2, AMDM_SCR);
    AMDrawRoundRect(pGraphics, &rect, 10, 15);
    
    AMImage image;
    AMCreateImageFromFile(&image, (AMWChar*)L"\\Program Files\\GDI\\test.bmp");
    AMDrawImage(pGraphics, &p1, image, AMDM_SCR);
    AMGraphicsDestroy(pGraphics);
    AMFont font;
    AMGetBitmapFont(&font, (AMWChar*)L"宋体");
    */

    /*
    AMGraphics pGraphics;
    AMImage image;
    AMCreateImageFromFile(&image, (AMWChar*)L"\\Program Files\\GDI\\test.bmp");
    AMCreateImageGraphics(&pGraphics, image);
    */

    AMGraphics pGraphics;
    AMGraphicsCreate(&pGraphics);
    AMInt32 width = AMGetGraphicWidth(pGraphics);
    AMInt32 height = AMGetGraphicHeigth(pGraphics);

    //1. draw a while background.
    AMRect backGround = {0, 0, width, height};
    AMRGB backGroundColors = 0xFFFFFF;
    AMSetBGColor(pGraphics, backGroundColors);
    AMFillRect(pGraphics, &backGround);
	
	// TEST IMAGE PAINT
	AMImage image = NULL;
	int* pRGB = new int[width*height];
	memset(pRGB, 0, width*height*sizeof(int));
	AMCreateImageFromRGB(&image, pRGB, width, height);
	delete[] pRGB;
	
	AMGraphics graphics = NULL;
	AMCreateImageGraphics(&graphics, image);
	backGroundColors = 0;
	AMSetBGColor(graphics, backGroundColors);
	AMFillRect(graphics, &backGround);
	

	AMPoint point = {0, 0};
	AMBitBlt(pGraphics,&backGround,graphics,&point,AMDM_SCR);
	AMUpdateRect(pGraphics, &backGround);
	//AMDrawImage(pGraphics, &point, image, AMDM_SCR);
#if 0		
    //2. Draw a Black rect.
    AMRect rectRect = {10, 10, 100, 50};
    AMRGB foreGroundColors = 0xFF000000;
    AMSetFGColor(pGraphics, foreGroundColors);
	AMSetBGColor(pGraphics, 0x00000000);
    AMDrawRect(pGraphics, &rectRect);


    //3. Draw a blue 
    AMRGB blueForeGroundColors = RGB(0, 0, 0x00);
    AMPoint textOutPoint = {10, 80};
    AMSetFGColor(pGraphics, blueForeGroundColors);
	AMSetBGColor(pGraphics, 0x00000000);
    AMDrawText(pGraphics, (AMWChar*)L"Hello 阿里云", &textOutPoint, 0, -1);

    //4 Draw a line.
    AMRGB redForeGroundColors = RGB(0xff, 0, 0xff);
    AMPoint linePoint1 = {10, 100};
    AMPoint linePoint2 = { 10, 300};
    AMPoint linePoint3 = { 230, 300};
    AMPoint linePoint4 = { 230, 100};
    AMSetFGColor(pGraphics, redForeGroundColors);
    AMDrawLine(pGraphics, &linePoint1, &linePoint2);
    AMDrawLine(pGraphics, &linePoint3, &linePoint4);
    AMSetFGColor(pGraphics, blueForeGroundColors);
    AMDrawLine(pGraphics, &linePoint2, &linePoint3);
    AMDrawLine(pGraphics, &linePoint4, &linePoint1);
	
    //5. Draw a Image
    AMImage image;
    AMCreateImageFromFile(&image, (AMWChar*)L"\\Program Files\\GDI\\test.bmp");
    AMPoint imagePoint = { 20, 110};
    AMRect imageRect  = {28, 28, 200, 180};
    AMDrawImageArea(pGraphics, &imagePoint, image, &imageRect, AMDM_SCR);
	
    //6. Draw a Blue Rect. and Fill Red color
	
    AMRect rectRect2 = {120, 10, 100, 50};
	AMSetBGColor(pGraphics, redForeGroundColors);
    AMSetFGColor(pGraphics, blueForeGroundColors);
    AMFillRect(pGraphics, &rectRect2);

    //7. 震动
    //AMVibrate(AMFALSE, 1000);

    //8. 字体
    AMFont pFont;
    //AMFontCreate(&pFont,AMFONT_FACE_SYSTEM,AMFONT_STYLE_ERROR,AMFONT_SIZE_MEDIUM);
    AMInt32 fontHeight = AMCharHeight(pFont);
    AMInt32 fontWeight0 = AMCharsWidth(pFont, (AMWChar*)L"l", AMWStrlen(L"l"));
    fontWeight0 = AMCharsWidth(pFont, (AMWChar*)L"w", AMWStrlen(L"w"));
    fontWeight0 = AMCharsWidth(pFont, (AMWChar*)L"q", AMWStrlen(L"q"));
    fontWeight0 = AMCharsWidth(pFont, (AMWChar*)L"阿", AMWStrlen(L"阿"));
    fontWeight0 = AMCharsWidth(pFont, (AMWChar*)L"阿里", AMWStrlen(L"阿里"));
    fontWeight0 = AMCharsWidth(pFont, (AMWChar*)L"w阿里", AMWStrlen(L"w阿里"));
    AMInt32 fontWeight1 = AMCharsWidth(pFont, (AMWChar*)L"lll", AMWStrlen(L"lll"));
    AMInt32 fontWeight2 = AMCharsWidth(pFont, (AMWChar*)L"lll.........", AMWStrlen(L"lll........."));
    AMInt32 fontWeight3 = AMCharsWidth(pFont, (AMWChar*)L"阿里云", AMWStrlen(L"阿里云"));
    AMInt32 fontWeight4 = AMCharsWidth(pFont, (AMWChar*)L"lll阿里云", AMWStrlen(L"lll阿里云"));
    AMInt32 fontWeight5 = AMCharsWidth(pFont, (AMWChar*)L"lll阿里云..............", AMWStrlen(L"lll阿里云.............."));

    //8. 大小字体
    AMFont pFontBig;
    AMCreateSystemFont(&pFontBig, AMFONT_FACE_SYSTEM, AMFONT_STYLE_BOLD, AMFONT_SIZE_LARGE);
    AMPoint textOutPointFontBig = {10, 120};
	AMSetFGColor(pGraphics, 0x00000000);
    AMSetFGColor(pGraphics, blueForeGroundColors);
    AMSetFont(pGraphics, pFontBig);
    AMDrawText(pGraphics, (AMWChar*)L"Hello 阿里云", &textOutPointFontBig, 0, -1);
#endif
	/*
    AMFont pFontSmall;
    AMCreateSystemFont(&pFontSmall, AMFONT_FACE_SYSTEM, AMFONT_STYLE_ITALIC, AMFONT_SIZE_SMALL);
    AMPoint textOutPointFontSmall = {10, 160};
    AMSetColor(pGraphics, blueForeGroundColors);
    AMSetFont(pGraphics, pFontSmall);
    AMDrawText(pGraphics, (AMWChar*)L"Hello 阿里云", &textOutPointFontSmall, 0, -1);
	*/

}

