#include "AMGui.h"
#include "AMOS.h"
#include <time.h>
#include <windows.h>
__GUI_BEGIN_NAMESPACE
System::System(void)
{
}

System::~System(void)
{
}

long System::currentTimeMillis()
{ 
	/*long ret;
	struct AMTimeval tp;
	AMGetUTCTimeEx(&tp);
	ret = tp.tv_sec * 1000 + tp.tv_usec/1000;*/
	return GetTickCount();

}
String System::getString (int n )
{	

	String str  = L"";
	int mod;
	int div;
	while(true){
		mod = n % 10;
		div = n /10;
		if(div == 0 && mod == 0 )
			break;
		
		switch(mod){
			case 0:
				str =  L"0" + str;
				break;
			case 1:
				str = L"1" + str;
				break;
			case 2:
				str = L"2" + str;
				break;
			case 3:
				str = L"3" + str;
				break;
			case 4:
				str = L"4" + str;
				break;
			case 5:
				str = L"5" + str;
				break;
			case 6:
				str = L"6" + str;
				break;
			case 7:
				str = L"7" + str;
				break;
			case 8:
				str = L"8" + str;
				break;
			case 9:
				str = L"9" + str;
				break;
			default:
				str = L"0" + str;
		}
		n = div;
		mod = 0;
	}
	
	return str;
}
__GUI_END_NAMESPACE
