/*
* AMGDI.cpp
*
*  Created on: 2010-02-22
*
*/
#include "AMGDIIn.h"

#ifdef WINCE
#ifdef TPC
#include "vibrate.h"        //PPC不支持，是SmartPhone用
#else
#include <Nled.h>
#endif
#endif
//震动, 停止震动.
//isRepeat 是否重复, 如果设置为AMTrue, 到dwTimeout将结束.
//dwTimeout 持续时间, 毫秒, -1 为无穷
//AME_ERROR, AME_SCUESS, AME_UNIMPL_METHOD
AMInt32 AMVibrate(AMBool isRepeat, AMInt32 dwTimeout)
{
#ifdef WINCE
#ifdef TPC
     HRESULT  hr = Vibrate(0, NULL, isRepeat, dwTimeout);
     CHECK_AND_RETV(hr, E_FAIL, AME_ERROR);
     CHECK_AND_RETV(hr, E_NOTIMPL, AME_UNIMPL_METHOD);
     
#else
    NLED_COUNT_INFO nci;
    int nIndex = 1;
    /*
    if(NLedGetDeviceInfo(NLED_COUNT_INFO_ID, (PVOID) &nci))
        nIndex = (int)nci.cLeds - 1;
    else
        return AME_ERROR;
    */
    NLED_SETTINGS_INFO settings ; 
    memset(&settings,0,sizeof(NLED_SETTINGS_INFO));
    settings.LedNum= nIndex; 
    settings.OffOnBlink= 1;
    BOOL v = NLedSetDevice(NLED_SETTINGS_INFO_ID, &settings);
    CHECK_AND_RETV(v, FALSE, AME_ERROR);
#endif
#endif
	return AME_SCUESS;
}
//结束.
//AME_ERROR, AME_SCUESS,
AMInt32 AMVibrateStop()
{
#ifdef WINCE
#ifdef TPC
    HRESULT  hr = VibrateStop();
    CHECK_AND_RETV(hr, E_FAIL, AME_ERROR);

#else
    NLED_COUNT_INFO nci;
    int nIndex = 1;
    /*
    if(NLedGetDeviceInfo(NLED_COUNT_INFO_ID, (PVOID) &nci))
        nIndex = (int)nci.cLeds - 1;
    else
        return AME_ERROR;
    */
    NLED_SETTINGS_INFO settings ; 
    memset(&settings,0,sizeof(NLED_SETTINGS_INFO));
    settings.LedNum= nIndex; 
    settings.OffOnBlink= 0;
    BOOL v = NLedSetDevice(NLED_SETTINGS_INFO_ID, &settings);
    CHECK_AND_RETV(v, FALSE, AME_ERROR);

#endif
#endif
	return AME_SCUESS;
}
