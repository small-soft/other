/*
* AMHDev.cpp
*
*  Created on: 2010-3-3
*      Author: qinghua.liqh
*/
#include "AMHDev.h"
#include <windows.h>
/*	
// the phone keypad maps to VK_* as shown below.   
// some keys might not be present, e.g. VK_TFLIP 

sofkey1     softkey2    VK_TSOFT1, VK_TSOFT2   
    ^               VK_TUP   
<   +   >           VK_TLEFT, VK_TACTION, VK_TRIGHT   
    v               VK_TDOWN   
home        back        VK_THOME, VK_TBACK   
talk        end         VK_TTALK, VK_TEND   
1       2       3       VK_T0..VK_T9   
4       5       6       ...   
7       8       9       ...   
*       0       #       VK_TSTAR, VK_TPOUND   

// other buttons include   
VK_TRECORD   
VK_TPOWER, VK_TVOLUMEUP, VK_TVOLUMEDOWN   
VK_TFLIP  
*/

#define KEY_MAP(key, code) case key: return code
AMInt32 AMGuiGetKeyCode(AMInt32 key)
{
    switch(key)
    {	
		KEY_MAP(KEY_OK, 0x0D); 
		KEY_MAP(KEY_LEFT, 0x25); 
		KEY_MAP(KEY_RIGHT, 0x27); 
		KEY_MAP(KEY_UP, 0x26); 
		KEY_MAP(KEY_DOWN, 0x28); 

#if defined(WINCE)
        KEY_MAP(KEY_CLEARSK, VK_CLEAR); 
#elif defined(WIN32)
		KEY_MAP(KEY_CLEARSK, 46); //Delete
#endif

#if defined(WINCE)
        KEY_MAP(KEY_BACKSPACESK, VK_BACK); 
#elif defined(WIN32)
		KEY_MAP(KEY_BACKSPACESK, 27);  //Backspace
#endif

#if defined(WINCE)
		KEY_MAP(KEY_RIGHTSK, 0x71); 
#elif defined(WIN32)
		KEY_MAP(KEY_RIGHTSK, 34); //PgDn
#endif

#if defined(WINCE)
		KEY_MAP(KEY_LEFTSK, 0x70); 
#elif defined(WIN32)
		KEY_MAP(KEY_LEFTSK, 35);  //End
#endif
		KEY_MAP(KEY_NUM0, VK_NUMPAD0); 
        KEY_MAP(KEY_NUM1, VK_NUMPAD1); 
        KEY_MAP(KEY_NUM2, VK_NUMPAD2); 
        KEY_MAP(KEY_NUM3, VK_NUMPAD3); 
        KEY_MAP(KEY_NUM4, VK_NUMPAD4); 
        KEY_MAP(KEY_NUM5, VK_NUMPAD5); 
        KEY_MAP(KEY_NUM6, VK_NUMPAD6); 
        KEY_MAP(KEY_NUM7, VK_NUMPAD7); 
        KEY_MAP(KEY_NUM8, VK_NUMPAD8); 
        KEY_MAP(KEY_NUM9, VK_NUMPAD9); 
		KEY_MAP(KEY_POUND,0x78); 
		KEY_MAP(KEY_STAR, 0x77); 
    default:
        return 0;
    }
}
	AMInt32 AMGuiGetKeyboardType()
	{
		return KEYBOARD_VIRTUAL;
	}
	AMVoid AMGuiGetSysInfo(AMInt32 keyType,AMPVoid value)
	{

	}