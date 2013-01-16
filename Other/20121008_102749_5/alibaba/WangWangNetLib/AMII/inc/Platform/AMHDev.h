#ifndef _AM_HDEV_H_
#define _AM_HDEV_H_
#include "AMTypes.h"
#include "AMErrno.h"
#define MICROEDITION_PLATFORM 1
#define KEYBOARD_TYPE 2

#define KEYBOARD_VIRTUAL 1
#define KEYBOARD_NUMERIC 2
#define KEYBOARD_HALF_QWERTY 3
#define KEYBOARD_QWERTY 4

#define ISTHIRDSOFTBUTTONSUPPORTED 7

//¼üÅÌÂë Begin*****************************
#define KEY_START  0
#define KEY_OK  KEY_START + 1        //Fire
#define KEY_LEFT  KEY_START +2        //Left
#define KEY_RIGHT KEY_START +3      //Right
#define KEY_UP    KEY_START +4          //Up
#define KEY_DOWN  KEY_START +5        //Down

#define KEY_CLEARSK     KEY_START +6       //Çå³ý C
#define KEY_BACKSPACESK KEY_START +7	//¹Ò»ú, ºóÍË Back
#define KEY_RIGHTSK     KEY_START +8	    //Right
#define KEY_LEFTSK      KEY_START +9        //Left

#define KEY_NUM0 KEY_START +10	 //0
#define KEY_NUM1 KEY_START +11  //1
#define KEY_NUM2 KEY_START +12
#define KEY_NUM3 KEY_START +13
#define KEY_NUM4 KEY_START +14
#define KEY_NUM5 KEY_START +15
#define KEY_NUM6 KEY_START +16
#define KEY_NUM7 KEY_START +17
#define KEY_NUM8 KEY_START +18
#define KEY_NUM9 KEY_START +19  //9
#define KEY_POUND KEY_START +20 //#
#define KEY_STAR  KEY_START +21  //*

#define KEY_END KEY_START + 22 
//¼üÅÌÂë End*******************************

#ifdef __cplusplus 
extern "C" {
#endif
	AMVoid AMGuiGetSysInfo(AMInt32 keyType,AMPVoid value);
	AMInt32 AMGuiGetKeyboardType();
	AMInt32 AMGuiGetKeyCode(AMInt32 key);
	AMVoid AMGuiVibrate();
	AMVoid AMGuiFlushBackLight(AMInt32 duration);
#ifdef __cplusplus 
}
#endif

#endif