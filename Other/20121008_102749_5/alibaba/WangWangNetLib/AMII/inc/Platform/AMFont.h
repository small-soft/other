/*
* AMFont.h
*
*  Created on:  2010-1-29
*      Author: qinghua.liqh
*/
#ifndef _AM_FONT_H_
#define _AM_FONT_H_

#include "AMGDI.h"
#ifdef __cplusplus 
extern "C" {
#endif
    //构造和销毁
    ADAPTER_API AMInt32 AMFontCreate(AMFont* pFont);		//创建默认字体
    ADAPTER_API AMInt32 AMFontDestroy(AMFont font);

    //根据字体名称得到字体
    ADAPTER_API AMInt32 AMGetBitmapFont(AMFont* pFont, const AMWChar* fontName);
    //创建系统字体
    ADAPTER_API AMInt32 AMCreateSystemFont(AMFont* pFont, AMFontFace face, AMFontStyle style, AMFontSize size);

    //矢量字体
    ADAPTER_API AMBool  AMIsTrueTypeFileSupported();
    ADAPTER_API AMInt32 AMCreateTrueTypeFont(AMFont* pFont, const AMChar* fileName);

    //字体宽高
    ADAPTER_API AMInt32 AMCharsWidth(AMFont font, const AMWChar* text, AMInt32 length);
    ADAPTER_API AMInt32 AMCharHeight(AMFont font);

    //字体属性
    ADAPTER_API AMFontFace AMGetFace(AMFont font);
    ADAPTER_API AMFontSize AMGetSize(AMFont font);
    ADAPTER_API AMFontStyle AMGetStyle(AMFont font);
#ifdef __cplusplus 
}
#endif
#endif

