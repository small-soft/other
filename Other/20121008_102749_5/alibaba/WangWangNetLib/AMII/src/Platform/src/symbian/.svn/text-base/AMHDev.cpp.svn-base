#include <e32base.h>
#include <e32std.h>
#include <e32keys.h>
#include <hwrmvibra.h> 

#include "AMHDev.h"

AMVoid AMGuiGetSysInfo(AMInt32 keyType,AMPVoid value)
{
	TVersion version = User::Version(); 
}

#define KEY_MAP(key, code) case key: return code
AMInt32 AMGuiGetKeyCode(AMInt32 key)
{
	switch(key)
	{	
		KEY_MAP(KEY_OK, EKeyDevice3); 
		KEY_MAP(KEY_LEFT, EKeyLeftArrow); 
		KEY_MAP(KEY_RIGHT, EKeyRightArrow); 
		KEY_MAP(KEY_UP, EKeyUpArrow); 
		KEY_MAP(KEY_DOWN, EKeyDownArrow); 
	
		KEY_MAP(KEY_CLEARSK, EKeyEscape); 
		KEY_MAP(KEY_BACKSPACESK, EKeyBackspace); 
		KEY_MAP(KEY_RIGHTSK, EKeyDevice1); 
		KEY_MAP(KEY_LEFTSK, EKeyDevice0); 
		KEY_MAP(KEY_NUM0, '0'); 
		KEY_MAP(KEY_NUM1, '1'); 
		KEY_MAP(KEY_NUM2, '2'); 
		KEY_MAP(KEY_NUM3, '3'); 
		KEY_MAP(KEY_NUM4, '4'); 
		KEY_MAP(KEY_NUM5, '5'); 
		KEY_MAP(KEY_NUM6, '6'); 
		KEY_MAP(KEY_NUM7, '7'); 
		KEY_MAP(KEY_NUM8, '8'); 
		KEY_MAP(KEY_NUM9, '9'); 
		KEY_MAP(KEY_POUND,'#'); 
		KEY_MAP(KEY_STAR, '*'); 
	default:
		return 0;
	}
	return 0;
}

AMInt32 AMGuiGetKeyboardType()
{
	return KEYBOARD_VIRTUAL;
}
	
AMVoid AMGuiVibrate()
{
	CHWRMVibra* vibra = CHWRMVibra::NewLC();
	vibra->StartVibraL( 5000 );
	CleanupStack::PopAndDestroy( vibra );
}

AMVoid AMGuiFlushBackLight(AMInt32 duration)
{
	User::ResetInactivityTime();
}
