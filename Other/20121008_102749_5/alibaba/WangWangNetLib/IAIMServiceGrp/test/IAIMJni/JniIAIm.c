#include "JniIAIm.h"
#include "AIM.h"
#include "AMImUtil.h"

void JniIAIm_sendMsg
(JNIEnv *env, jint imHandle, jbyteArray baryCntID, jbyteArray baryMsg)
{
	char *szCntID = 0, *szInfo = 0;
	IAIM *pIM = (IAIM*)imHandle;
	AMUInt32	uiFlag = 0;

	DPRINT("JniIAIM_sendMsg..................Begin");

	if(0 == pIM)
		return;

	if(NULL == (szCntID = (*env)->GetPrimitiveArrayCritical(env, baryCntID, 0)))
		return;

	if(NULL == (szInfo = (*env)->GetPrimitiveArrayCritical(env, baryMsg, 0)))
	{
		(*env)->ReleasePrimitiveArrayCritical(env, baryCntID, szCntID, 0);
		return;
	}

	IAIM_SendMessage(pIM, szCntID, szInfo);

	(*env)->ReleasePrimitiveArrayCritical(env, baryMsg, szInfo, 0);
	(*env)->ReleasePrimitiveArrayCritical(env, baryCntID, szCntID, 0);

	DPRINT("JniIAIM_sendMsg....................... Done!");
}

jbyteArray  JniIAIm_getMsgCntId
(JNIEnv *env, jobject obj, jint iMsgHandle)		//jbyteArray JniMsg_getCntId(JNIEnv *env, jint iMsgHandle)
{
	IAIMessage *pMsg = (IAIMessage *)iMsgHandle;
	jbyteArray baryCntId = 0;
	jint	iLen = 0;

	if(0 == pMsg || 0 == pMsg->szContactID)
		return NULL;

	iLen = AMStrlen(pMsg->szContactID);

	if(NULL == (baryCntId = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, baryCntId, 0, iLen, pMsg->szContactID);

	return baryCntId;
}

jbyteArray JniIAIm_getMsgContent
(JNIEnv *env, jobject obj, jint iMsgHandle)
{
	IAIMessage *pMsg = (IAIMessage *)iMsgHandle;
	jbyteArray baryContent = 0;
	jint	iLen = 0;

	if(0 == pMsg || 0 == pMsg->szContent)
		return NULL;

	iLen = AMStrlen(pMsg->szContent);

	if(NULL == (baryContent = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, baryContent, 0, iLen, pMsg->szContent);

	return baryContent;
}

jlong JniIAIm_getMsgId
(JNIEnv *env, jobject obj, jint iMsgHandle)
{
	IAIMessage *pMsg = (IAIMessage *)iMsgHandle;

	if(0 == pMsg)
		return NULL;

	return pMsg->_iRid;
}

jint JniIAIm_getMsgType
(JNIEnv *env, jobject obj, jint iMsgHandle)
{
	IAIMessage *pMsg = (IAIMessage *)iMsgHandle;

	if(0 == pMsg)
		return NULL;

	return pMsg->eType;
}

jlong JniIAIm_getMsgTime
(JNIEnv *env, jobject obj, jint iMsgHandle)
{
	IAIMessage *pMsg = (IAIMessage *)iMsgHandle;

	if(0 == pMsg)
		return NULL;

	return pMsg->iServerTime;
}