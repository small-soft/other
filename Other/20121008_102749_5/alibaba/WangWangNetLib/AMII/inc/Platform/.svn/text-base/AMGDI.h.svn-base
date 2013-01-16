/*
* AMGDI.h
*
*  Created on: 2010-1-29
*      Author: qinghua.liqh
*/
#ifndef _AM_GDI_H_
#define _AM_GDI_H_
#include "AMErrno.h"
#include "AMTypes.h"

typedef AMPVoid AMFont;				//字体句柄
typedef AMPVoid AMGraphics;			//绘画区句柄
typedef AMPVoid AMImage; 			//图像句柄
typedef AMPVoid AMHandle;  			//窗口句柄

//区域
typedef struct AMRectNode
{
	int x, y;
	int w, h;
}AMRect;

//点
typedef struct AMPointNode
{
	int x, y;
}AMPoint;

//颜色
typedef AMUInt32 AMRGB;
#define AM_SET_RGB(r, g, b, alpha) (AMUInt32)((AMUInt8)(r) | ((AMUInt8)(g) << 8) \
        | ((AMUInt8)(b << 16)) | ((AMUInt8)(alpha << 24)))

//光栅操作
typedef enum AMDrawModeNode
{
	AMDM_AND = 0x1,		        //源和目标位与操作  D & S
	AMDM_NOTAND = 0x2,   	    //源和反目标位与操作  ~D & S
	AMDM_ANDNOT = 0x4,	        //D & ~S
	AMDM_XOR = 0x8,	            //D^ S
	AMDM_OR = 0x10,		        //D | S	
	AMDM_NOTOR = 0x20,		    //~D| S		
	AMDM_NOTXOR = 0x40,         //(~D) ^ S	
	AMDM_ORNOT= 0x80,    	    //D ^ (~S)	
	AMDM_NOTORNOT = 0x100,      //(~D) | (~S)
    AMDM_NOTANDNOT = 0x200,      //(~D) & (~S)
    AMDM_NOTSCR = 0x400,        // ~S
    AMDM_NOTDST = 0x800,        // ~D
    AMDM_SCR = 0x1000,          // S
    AMDM_ALPHA = 0x2000,        // 把源的ALPHA直接写到目标上, 忽略颜色值
}AMDrawMode;

//字体大小
typedef enum AMFontSizeNode
{
    AMFONT_SIZE_ERROR  =  0,
    AMFONT_SIZE_SMALL  = 0x1,
    AMFONT_SIZE_MEDIUM = 0x2, 
    AMFONT_SIZE_LARGE  = 0x3,
}AMFontSize;

//字体风格,可以与操作
typedef enum AMFontStyleNode
{
    AMFONT_STYLE_ERROR  =  0,
	AMFONT_STYLE_PLAIN  =  0x1,
	AMFONT_STYLE_ITALIC =  0x2,
	AMFONT_STYLE_BOLD   =  0x4,
}AMFontStyle;

typedef enum AMFontFaceNode
{
    AMFONT_FACE_ERROR         =  0,
	AMFONT_FACE_SYSTEM        =  0x1,
	AMFONT_FACE_PROPORTIONAL  =  0x2,
	AMFONT_FACE_MONOSPACE     =  0x3,
}AMFontFace;


//错误码. 实现的时候再添加.
#define AME_IMAGE_BASE -0x9000
enum
{
	AME_IMAGE_SCUESS     = AME_SCUESS,
    AME_IMAGE_ERROR     = AME_IMAGE_BASE,
	AME_IMAGE_INVALID_BITMAP,
	AME_IMAGE_GETRGB_ERROR,
};

//错误码. 实现的时候再添加.
#define AME_GRAPHICS_BASE -0XA000
enum
{
	AME_GRAPHICS_SUCCESS = AME_SCUESS,
    AME_GRAPHICS_ERROR  = AME_GRAPHICS_BASE,
	AME_GRAPHICS_CLR_INVALID ,
};

//错误码. 实现的时候再添加.
#define AME_FONT_BASE -0XB000
enum
{
	AME_FONT_SUCCESS = AME_SCUESS,
    AME_FONT_ERROR  = AME_FONT_BASE,
};


#include "AMGraphics.h"
#include "AMFont.h"
#include "AMImage.h"
#include "AMHDev.h"


#ifdef __cplusplus 
extern "C" {
#endif
    //震动, 停止震动.
    //isRepeat 是否重复, 如果设置为AMTrue, 到dwTimeout将结束.
    //dwTimeout 持续时间, 毫秒, -1 为无穷
    //AME_ERROR, AME_SCUESS, AME_UNIMPL_METHOD
    ADAPTER_API AMInt32 AMVibrate(AMBool isRepeat, AMInt32 dwTimeout);
    //结束.
    //AME_ERROR, AME_SCUESS,
    ADAPTER_API AMInt32 AMVibrateStop();
#ifdef __cplusplus 
}
#endif

#endif

