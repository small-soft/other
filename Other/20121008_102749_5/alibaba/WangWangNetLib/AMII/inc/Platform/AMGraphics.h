/*
* AMGraphics.h
*
*  Created on: 2010-1-28
*      Author: qinghua.liqh
*/
#ifndef _AM_GRAPHICS_H_
#define _AM_GRAPHICS_H_

#include "AMGDI.h"

#ifdef __cplusplus 
extern "C" {
#endif
    //根据屏幕创建
    ADAPTER_API AMInt32 AMGraphicsCreate(AMGraphics* pGraphics);
    //通过窗口句柄创建
    ADAPTER_API AMInt32 AMCreateSystemGraphics(AMGraphics* pGraphics, AMHandle hPlatformGraphics);
    //根据AMImage创建
    ADAPTER_API AMInt32 AMCreateImageGraphics(AMGraphics* pGraphics, AMImage image);
    //销毁
    ADAPTER_API AMInt32 AMGraphicsDestroy(AMGraphics graphics);
    //宽高
    ADAPTER_API AMInt32 AMGetGraphicWidth(AMGraphics graphics);
    ADAPTER_API AMInt32 AMGetGraphicHeigth(AMGraphics graphics);

    //得到和设置当前的颜色, 目前只有一个颜色, 不分前景色和背景色. 
    ADAPTER_API AMRGB AMGetColor(AMGraphics graphics);					
    ADAPTER_API AMInt32 AMSetColor(AMGraphics graphics, AMRGB rgb);

    //分成两个函数, 分别处理前景和背景色
    ADAPTER_API AMRGB AMGetBGColor(AMGraphics graphics);
    ADAPTER_API AMInt32 AMSetBGColor(AMGraphics graphics, AMRGB rgb);
    ADAPTER_API AMRGB AMGetFGColor(AMGraphics graphics);
    ADAPTER_API AMInt32 AMSetFGColor(AMGraphics graphics, AMRGB rgb);

    //画线, 用当前颜色画
    ADAPTER_API AMInt32 AMDrawLine(AMGraphics graphics, AMPoint* p1, AMPoint* p2);

    //画长方形, 填充边框
    ADAPTER_API AMInt32 AMDrawRect(AMGraphics graphics, AMRect* rect);
    ADAPTER_API AMInt32 AMFillRect(AMGraphics graphics, AMRect* rect);

    //画圆角长方形, 填充圆角长方形,
    ADAPTER_API AMInt32 AMDrawRoundRect(AMGraphics graphics, AMRect* rect, AMInt32 arcWidth, AMInt32 arcHeight);
    ADAPTER_API AMInt32 AMFillRoundRect(AMGraphics graphics, AMRect* rect, AMInt32 arcWidth, AMInt32 arcHeight);

    //画弧, 填充弧,
    ADAPTER_API AMInt32 AMFillArc(AMGraphics graphics, AMRect* rect, AMInt32 startAngle, AMInt32 arcAngle);
    ADAPTER_API AMInt32 AMDrawArc(AMGraphics graphics, AMRect* rect, AMInt32 startAngle, AMInt32 arcAngle);

    //画多边形, 填充多边形,
    ADAPTER_API AMInt32 AMFillPolygon(AMGraphics graphics, AMPoint points[], AMInt32 nPoints) ;
    ADAPTER_API AMInt32 AMDrawPolygon(AMGraphics graphics, AMPoint points[], AMInt32 nPoints);

    //画三角形, 填充三角形,
    ADAPTER_API AMInt32 AMDrawTriangle(AMGraphics graphics, AMPoint* p1, AMPoint* p2,  AMPoint* p3);
    ADAPTER_API AMInt32 AMFillTriangle(AMGraphics graphics, AMPoint* p1, AMPoint* p2,  AMPoint* p3);

    //画字.  字符从startPos开始, 一共画len个字
    ADAPTER_API AMInt32 AMDrawText(AMGraphics graphics, const AMWChar* str, AMPoint* point, AMInt32 startPos, AMInt32 len);

    //Aplha.
    ADAPTER_API AMInt32  AMSetAlpha(AMGraphics graphics, AMUInt8 alpha);
    ADAPTER_API AMUInt8 AMGetAlpha(AMGraphics graphics);
    ADAPTER_API AMBool  AMIsAlphaSupported(AMGraphics graphics);

    //有效区域.
    ADAPTER_API AMInt32 AMGetClipX(AMGraphics graphics);					
    ADAPTER_API AMInt32 AMGetClipY(AMGraphics graphics);
    ADAPTER_API AMInt32 AMGetClipWidth(AMGraphics graphics);
    ADAPTER_API AMInt32 AMGetClipHeight(AMGraphics graphics);
    ADAPTER_API AMInt32  AMClipRect(AMGraphics graphics, AMRect* rect);
    ADAPTER_API AMInt32  AMSetClip(AMGraphics graphics, AMRect* rect);

    //字体.
    ADAPTER_API AMFont AMGetFont(AMGraphics graphics);
    ADAPTER_API AMFont AMSetFont(AMGraphics graphics, AMFont font);

    //画图片
    ADAPTER_API AMInt32 AMDrawImage(AMGraphics graphics, AMPoint* point, AMImage img, AMDrawMode drawMode);
    ADAPTER_API AMInt32 AMDrawImageArea(AMGraphics graphics, AMPoint* point, AMImage img, AMRect* rect, AMDrawMode drawMode);

    //画
    ADAPTER_API AMInt32 AMBitBlt(AMGraphics dst, AMRect* rect, AMGraphics src, AMPoint* point, AMDrawMode drawMode);
    ADAPTER_API AMInt32 AMStretchBlt(AMGraphics dst, AMRect* dstRect, AMGraphics src, AMRect* srcRect, AMDrawMode drawMode);

    //拉伸, 旋转
    ADAPTER_API AMInt32 AMScale (AMGraphics graphics, AMFloat x, AMFloat y) ;
    ADAPTER_API AMInt32 AMRotate(AMGraphics graphics, AMFloat angle);

    //区域刷新
    ADAPTER_API AMInt32 AMUpdateRect(AMGraphics graphics, AMRect* rect);

	//坐标变换
    ADAPTER_API AMInt32 AMTranslate(AMGraphics graphics, AMInt32 x, AMInt32 y);

    //通过Buffer

#ifdef __cplusplus 
}
#endif
#endif
