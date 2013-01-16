/*
* AMLog.c
*
*  Created on: 2012-03-28
*      Author: tom.lih
*/
#include "AMLog.h"
#include "AMFS.h"
#include "AMAssert.h"
#include "string.h"

#ifdef AM_LOG_ERROR_ENABLE
AMVoid  AMLogForError(const AMChar* moduleName, const AMChar* errorStr)
{

#ifdef IOS_HUADONG
	printf("Error(%s): %s\n", moduleName, errorStr);	
#endif
	
}
#endif

#ifdef AM_LOG_WARNING_ENABLE
AMVoid  AMLogForWarning(const AMChar* moduleName, const AMChar* warningStr)
{	

#ifdef IOS_HUADONG
	printf("Warning(%s): %s\n", moduleName, warningStr);		
#endif	

}
#endif

#ifdef AM_LOG_INFO_ENABLE
AMVoid  AMLogForInfo(const AMChar* moduleName, const AMChar* infoStr)
{
	
#ifdef IOS_HUADONG
	printf("Info(%s): %s\n", moduleName, infoStr);		
#endif

}
#endif

#ifdef AM_LOG_DEBUG_ENABLE
AMVoid  AMLogForDebug(const AMChar* moduleName, const AMChar* denugInfo)
{
	
#ifdef IOS_HUADONG
	printf("Debug(%s): %s\n", moduleName, denugInfo);		
#endif
	
}
#endif

