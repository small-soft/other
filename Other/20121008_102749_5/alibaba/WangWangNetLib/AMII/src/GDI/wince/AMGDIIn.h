/*
* AMGDIIn.h
*
*  Created on: 2010-02-09
*
*/
#ifndef _AM_GDIIN_H_
#define _AM_GDIIN_H_

#include "AMGDI.h"
#include <windows.h>
#include <assert.h>

#ifdef WINCE
#include <imaging.h>
#endif

#if defined(WIN32) && !defined(WINCE)
#include "gdiplus.h"
#endif

#define _USER_MANAGER_FONT_  

typedef enum CreateTypeNode     //创建AMGraphics的方式
{
    AM_FROM_DEFAULT,            //默认方式创建
    AM_FROM_HWND,               //通过窗口句柄
    AM_FROM_IMAGE,              //通过图片创建
}CreateType;
typedef struct AMGraphicsNode
{
    HDC hdc;                    //DC句柄
    AMSize_t width, height;     //DC高度
    CreateType createType;      //创建方式
    HWND hwnd;                  //通过HWND创建时的HWND.
    AMFont font;                //对应的字体.
#ifdef _USER_MANAGER_FONT_
	BOOL isSelfFont;
#endif
	AMUInt8 alpha;              //当前alpha
    AMInt32 color;              //当前的颜色.
    AMRGB bgColor;
    AMRGB fgColor;
    BOOL isSetBackColor;        
    BOOL isSetForeColor;
    BOOL isSetTextColor;
    HPEN pen;                   
    BOOL isSetPen;
    HBRUSH  brush;
    BOOL isSetBrush;

    AMInt32 clipX, clipY, clipW, clipH;
	AMInt32 xTranslate,yTranslate;

    //为了不修改其它函数代码, 这里吧实际要绘制的dc保存到hdc中,原始的hdc放到realHdc中
    HDC bufferHdc;  //当createType == AM_FROM_HWND的时候的双缓冲.
    HBITMAP bufferBitmap;
    HDC realHdc;
}AMGraphics_;

typedef struct AMImageode
{
	union
	{
		HBITMAP bitmap;
#ifdef WINCE
		IImage* image;
#endif

#if defined(WIN32) && !defined(WINCE)
		Gdiplus::Image* image;
#endif
	};

	union
	{
		BITMAP  bitmapBuffer;
#ifdef WINCE
		void*	padding; //no use
#endif

#if defined(WIN32) && !defined(WINCE)
		void*  globalAlloc;
#endif
	};

    int w, h;
    int createMethod; //1表示从缓存中创建IImage,此时不用HITMAP格式,而换用IImage. 而此时bitmapBuffer为空。
}AMImage_;


typedef struct AMFontNode           //字体
{
    HFONT hfont;                    //字体句柄
    LOGFONT format;                 //创建字体对应的格式
    HDC hdc;                        //字体所在的DC
    AMWChar fontName[LF_FACESIZE];  //字体名称,如果是通过字体名称创建, 此处有值
    AMFontFace face;                
    AMFontStyle style; 
    AMFontSize size;
}AMFont_;


#ifdef WINCE
int _GetBitmapFontEnumFontFamProc(const LOGFONT* lpelf, 
                                  const TEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam);
int _FontCreateEnumFontFamProc(const LOGFONT* lpelf, 
                               const TEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam);

int _FontCreateSystemFontEnumFontFamProc(const LOGFONT* lpelf, 
                               const TEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam);
#else
int CALLBACK _GetBitmapFontEnumFontFamProc(CONST LOGFONTW *, CONST TEXTMETRICW *, DWORD, LPARAM);
int CALLBACK _FontCreateEnumFontFamProc(CONST LOGFONTW *, CONST TEXTMETRICW *, DWORD, LPARAM);
int CALLBACK  _FontCreateSystemFontEnumFontFamProc(CONST LOGFONTW *, CONST TEXTMETRICW *, DWORD, LPARAM);
#endif
//得到DC对应的字体
HFONT _GetDcFont(HDC hdc);
//得到字体的信息
int   _GetDcFontInfo(HFONT hfont, int bufferLen, unsigned char buffer);
//通过DC得到字体.
int _CreateFontFromDC(AMFont* font,  HDC hdc);
DWORD _ParseDrawMode(AMDrawMode drawMode);
HPEN  _CreatePen(AMRGB rgb);
AMInt32 _AMSetForeColor(AMGraphics graphics);
AMInt32 _AMSetTextColor(AMGraphics graphics);
AMInt32 _AMSetBrushColor(AMGraphics graphics);
AMInt32 _AMBitBltEx(AMGraphics dst, AMRect* rect, AMGraphics src, AMPoint* point, AMDrawMode drawMode);
AMInt32 _BitBltEx(HDC dst, AMRect* rect, HDC src, AMPoint* point, AMDrawMode drawMode);
#define CHECK_PARG_AND_RET(p) if(NULL == (p))  return AME_ARG_AINVALID
#define CHECK_PARG_AND_RET0(p) if(NULL == (p))  return 0
#define CHECK_PARG_AND_RETV(p, v) if(NULL == (p))  return (v)
#define CHECK_AND_RETV(s, d, v) if( (s) == (d)) return (v)
#endif //_AM_GDIIN_H_