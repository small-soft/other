/*
* AMImage.h
*
*  Created on: 2010-01-29
*
*/

#ifndef _AM_IMAGE_H_
#define _AM_IMAGE_H_

#include "AMGDI.h"

#ifdef __cplusplus 
extern "C" {
#endif
    //创建和销毁
    //AMInt32 AMImageCreate(AMImage* image);
    ADAPTER_API AMInt32 AMImageDestroy(AMImage image);
    
    //从Buffer中创建Image
    ADAPTER_API AMInt32 AMCreateImage(AMImage* pImage, AMInt8* buffer, AMInt32 length);

    /* RGB不暴露出来, 在实现部分封装
    AMInt32 AMCreateImageFromRGB(AMImage* image, AMInt32 *rgb, AMInt32 width, AMInt32 height);
    AMInt32 AMGetRGB(AMImage image , AMInt32 *rgb);
    */
    ADAPTER_API AMInt32 AMCreateImageFromRGB(AMImage* image, AMInt32 *rgb, AMInt32 width, AMInt32 height);

    //文件得到
    ADAPTER_API AMInt32 AMCreateImageFromFile(AMImage* image, const AMWChar* inFileName);

    //获取高度和宽度
    ADAPTER_API AMInt32 AMGetWidth(AMImage image);
    ADAPTER_API AMInt32 AMGetHeight(AMImage image);

	ADAPTER_API AMInt32 AMGetImageBuffer(AMImage img, AMInt32 x, AMInt32 y, AMInt32 width, AMInt32 height, AMInt32* pData);
#ifdef __cplusplus 
}
#endif
#endif

