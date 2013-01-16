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

typedef AMPVoid AMFont;				//������
typedef AMPVoid AMGraphics;			//�滭�����
typedef AMPVoid AMImage; 			//ͼ����
typedef AMPVoid AMHandle;  			//���ھ��

//����
typedef struct AMRectNode
{
	int x, y;
	int w, h;
}AMRect;

//��
typedef struct AMPointNode
{
	int x, y;
}AMPoint;

//��ɫ
typedef AMUInt32 AMRGB;
#define AM_SET_RGB(r, g, b, alpha) (AMUInt32)((AMUInt8)(r) | ((AMUInt8)(g) << 8) \
        | ((AMUInt8)(b << 16)) | ((AMUInt8)(alpha << 24)))

//��դ����
typedef enum AMDrawModeNode
{
	AMDM_AND = 0x1,		        //Դ��Ŀ��λ�����  D & S
	AMDM_NOTAND = 0x2,   	    //Դ�ͷ�Ŀ��λ�����  ~D & S
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
    AMDM_ALPHA = 0x2000,        // ��Դ��ALPHAֱ��д��Ŀ����, ������ɫֵ
}AMDrawMode;

//�����С
typedef enum AMFontSizeNode
{
    AMFONT_SIZE_ERROR  =  0,
    AMFONT_SIZE_SMALL  = 0x1,
    AMFONT_SIZE_MEDIUM = 0x2, 
    AMFONT_SIZE_LARGE  = 0x3,
}AMFontSize;

//������,���������
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


//������. ʵ�ֵ�ʱ�������.
#define AME_IMAGE_BASE -0x9000
enum
{
	AME_IMAGE_SCUESS     = AME_SCUESS,
    AME_IMAGE_ERROR     = AME_IMAGE_BASE,
	AME_IMAGE_INVALID_BITMAP,
	AME_IMAGE_GETRGB_ERROR,
};

//������. ʵ�ֵ�ʱ�������.
#define AME_GRAPHICS_BASE -0XA000
enum
{
	AME_GRAPHICS_SUCCESS = AME_SCUESS,
    AME_GRAPHICS_ERROR  = AME_GRAPHICS_BASE,
	AME_GRAPHICS_CLR_INVALID ,
};

//������. ʵ�ֵ�ʱ�������.
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
    //��, ֹͣ��.
    //isRepeat �Ƿ��ظ�, �������ΪAMTrue, ��dwTimeout������.
    //dwTimeout ����ʱ��, ����, -1 Ϊ����
    //AME_ERROR, AME_SCUESS, AME_UNIMPL_METHOD
    ADAPTER_API AMInt32 AMVibrate(AMBool isRepeat, AMInt32 dwTimeout);
    //����.
    //AME_ERROR, AME_SCUESS,
    ADAPTER_API AMInt32 AMVibrateStop();
#ifdef __cplusplus 
}
#endif

#endif

