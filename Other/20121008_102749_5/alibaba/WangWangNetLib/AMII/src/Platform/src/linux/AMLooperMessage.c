#include "AMLooperMessage.h"
#include "AMLooperHandler.h"
#include <stdlib.h>

//创建一个消息	  
AMInt32 AMMessageInit(struct AMMessage* message, AMMessageCleanUp cleanUp)
{
    //AMLogForDebug("AMLooper", "AMMessageInit");
	if(NULL == message)
		return AME_LOOPER_MESSAGE_NULL;

	memset(message, 0, sizeof(struct AMMessage));
    message->cleanUp = cleanUp;
	return AME_LOOPER_SCUESS;
}
