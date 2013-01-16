/*
* AMStdlib.c
*
*  Created on: 2012-03-28
*      Author: tom.lih
*/

#include "AMOS.h"

char* itoa(int value, char* str, int radix)
{
    switch(radix)
    {
    case 16:
        AMSprintf(str, "%x", value);
        break;
    case 8:
        AMSprintf(str, "%d", value);
        break;
    case 10:
    default:
        AMSprintf(str, "%d", value);
        break;
    }
    return str;
}
