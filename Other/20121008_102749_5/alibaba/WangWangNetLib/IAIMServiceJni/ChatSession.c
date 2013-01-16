#include "ChatSession.h"
#include "AIMSession.h"
#include "AIMSessionModel.h"
#include "AMString.h"
#include "IAIM.h"

AMChar *	GetTmpCszFromByteArray(JNIEnv *env, jbyteArray baray, jboolean *isCopy);
void		ReleaseTmpCszFromByteArray(JNIEnv *env, jbyteArray bary, const char *csz, jboolean *isCopy);

/*
* Class:     com_alibaba_wireless_imservice_ChatSession
* Method:    nGetContactId
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ChatSession_nGetContactId
(JNIEnv *env, jclass cls, jint handle)
{
	IASession *pSes = (IASession*)handle;
	jbyteArray	baryCntID = AMNULL;
	AMInt32 iLen = 0;

	if(0 == pSes || 0 == pSes->szContactID)
		return AMNULL;

	iLen = AMStrlen(pSes->szContactID);

	if(AMNULL == (baryCntID = (*env)->NewByteArray(env, iLen)))
		return AMNULL;
	
	(*env)->SetByteArrayRegion(env, baryCntID, 0, iLen, pSes->szContactID);
	
	return baryCntID;
}

/*
* Class:     com_alibaba_wireless_imservice_ChatSession
* Method:    nSendMsgEx
* Signature: (I[BI)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ChatSession_nSendMsgEx
(JNIEnv *env, jclass cls, jint handle, jbyteArray baryMsg, jint appendMobileImMsg)
{
	IASession *pSes = (IASession*)handle;
	AMChar	*szMsg = 0;

	if(0 == pSes || 0 == pSes->szContactID)
		return;

	AMAssert(0 != pSes->pSesModel);

	if(AMNULL == (szMsg = GetTmpCszFromByteArray(env, baryMsg, 0)))
	{
		return;
	}

	IAIMSessionModel_SendMsg(pSes->pSesModel, pSes->szContactID, szMsg, appendMobileImMsg);

	ReleaseTmpCszFromByteArray(env, baryMsg, szMsg, 0);
}

/*
* Class:     com_alibaba_wireless_imservice_ChatSession
* Method:    nSendMsg
* Signature: (I[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ChatSession_nSendMsg
(JNIEnv *env, jclass cls, jint handle, jbyteArray baryMsg)
{
	Java_com_alibaba_wireless_imservice_ChatSession_nSendMsgEx(env, cls, handle, baryMsg, 0);
}

/*
* Class:     com_alibaba_wireless_imservice_ChatSession
* Method:    nLeave
* Signature: (I)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ChatSession_nLeave
(JNIEnv *env, jclass cls, jint iSesHandle)
{
	IASession *pSes = (IASession*)iSesHandle;
	
	AMAssert(0 != pSes && 0 != pSes->pSesModel);
	if(0 == pSes || 0 == pSes->pSesModel)
	{
		return;
	}

	IAIMSessionModel_CloseSession(pSes->pSesModel, pSes);
}

/*
* Class:     com_alibaba_wireless_imservice_ChatSession
* Method:    nGetHistoryCount
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ChatSession_nGetHistoryCount
(JNIEnv *env, jclass cls, jint handle)
{
	IASession *pSes = (IASession*)handle;
	AMInt32 iCount = 0;
	if(AMNULL == pSes)
		return -1;

	if(eAIM_RESULT_OK != IAIMSession_CountMsgs(pSes, &iCount))
	{
		DPRINT("nGetHistoryCount................Error!\n");
		return -1;
	}
	return iCount;
}


/*
* Class:     com_alibaba_wireless_imservice_ChatSession
* Method:    nGetHistoryHandle
* Signature: (IJI)[I
*/
JNIEXPORT jintArray JNICALL Java_com_alibaba_wireless_imservice_ChatSession_nGetHistoryHandle
(JNIEnv *env, jclass cls, jint handle, jlong iOffset, jint iLimit)
{
	IASession *pSes = (IASession*)handle;
	jintArray	iaryMsgHandles = AMNULL;

	AMHandle	*phMsgs = AMNULL;
	AMInt32		iCount	= 0;

	AIM_RESULT	eResult;

	if(0 == pSes)
		return AMNULL;

	if(eAIM_RESULT_OK != (eResult = AIMSession_GetMsgs(pSes, (int)iOffset, iLimit, AMFALSE, &phMsgs, &iCount)))
	{
		DPRINT("nGetHistoryHandle..................Error %d!\n", eResult);
		return AMNULL;
	}

	if(0 == iCount)
		return AMNULL;

	if(AMNULL == (iaryMsgHandles = (*env)->NewIntArray(env, iCount)))
	{
		AIMSession_ReleaseMsgs(pSes, phMsgs, iCount, 0);
		return AMNULL;
	}

	(*env)->SetIntArrayRegion(env, iaryMsgHandles, 0, iCount, (const int *)phMsgs);

	AIMSession_ReleaseMsgs(pSes, phMsgs, iCount, 1);

	return iaryMsgHandles;
}

/*
* Class:     com_alibaba_wireless_imservice_ChatSession
* Method:    nGetUnreadCount
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ChatSession_nGetUnreadCount
(JNIEnv *env, jclass cls, jint handle)
{
	IASession *pSes = (IASession*)handle;
	AMInt32 iRet = 0;

	DPRINT("nGetUnreadCount................................Entering!\n");

	if(AMNULL == pSes)
		return -1;

	if(eAIM_RESULT_OK != IAIMSession_CountUnreadMsgs(pSes, &iRet))
	{
		DPRINT("nGetUnreadCount.....................Error!\n");
		return -1;
	}

	DPRINT("nGetUnreadCount..............................%d\n", iRet);

	return iRet;
}

/*
* Class:     com_alibaba_wireless_imservice_ChatSession
* Method:    nGetUnreadHandle
* Signature: (III)[I
*/
JNIEXPORT jintArray JNICALL Java_com_alibaba_wireless_imservice_ChatSession_nGetUnreadHandle
(JNIEnv *env, jclass cls, jint handle, jint iOffset, jint iLimit)
{
	IASession *pSes = (IASession*)handle;
	jintArray	iaryMsgHandles = AMNULL;

	AMHandle	*phMsgs = AMNULL;
	AMInt32		iCount	= 0;

	AIM_RESULT	eResult;

	if(0 == pSes)
		return AMNULL;

	if(eAIM_RESULT_OK != (eResult = AIMSession_GetMsgs(pSes, iOffset, iLimit, AMTRUE, &phMsgs, &iCount)))
	{
		DPRINT("nGetUnreadHandle..................Error %d!\n", eResult);
		return AMNULL;
	}

	if(0 == iCount)
		return AMNULL;

	if(AMNULL == (iaryMsgHandles = (*env)->NewIntArray(env, iCount)))
	{
		AIMSession_ReleaseMsgs(pSes, phMsgs, iCount, 0);
		return AMNULL;
	}

	(*env)->SetIntArrayRegion(env, iaryMsgHandles, 0, iCount, (const int *)phMsgs);

	AIMSession_ReleaseMsgs(pSes, phMsgs, iCount, 1);

	return iaryMsgHandles;
}

/*
* Class:     com_alibaba_wireless_imservice_ChatSession
* Method:    nMarkMessageRead
* Signature: (IJ)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ChatSession_nMarkMessageRead
(JNIEnv *env, jclass cls, jint handle, jlong msgId)
{
	IASession *pSes = (IASession*)handle;
	if(AMNULL == pSes)
		return;

	IAIMSession_MarkMsgRead(pSes, msgId);
}

/*
* Class:     com_alibaba_wireless_imservice_ChatSession
* Method:    nRemoveMessage
* Signature: (IJ)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ChatSession_nRemoveMessage
(JNIEnv *env, jclass cls, jint handle, jlong msgId)
{
	IASession *pSes = (IASession*)handle;
	if(AMNULL == pSes)
		return;

	DPRINT("nRemoveMessage....................Entering %lld\n", msgId);
	IAIMSession_RemoveMsg(pSes, msgId);
	DPRINT("nRemoveMessage....................Leaving %lld\n", msgId);
}

/*
* Class:     com_alibaba_wireless_imservice_ChatSession
* Method:    nReleaseMsgs
* Signature: (I[I)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ChatSession_nReleaseMsgs
(JNIEnv *env, jclass cls, jint handle, jintArray msgHandles)
{
	IASession *pSes = (IASession*)handle;
	AMHandle	*phMsgs = AMNULL;
	AMInt32		iSize = 0;
	if(AMNULL == pSes && AMNULL != msgHandles)
		return;

	iSize = (*env)->GetArrayLength(env, msgHandles);

	if(!iSize)
		return;

	if( AMNULL == (phMsgs = (*env)->GetPrimitiveArrayCritical(env, msgHandles, 0)))
		return;

	AIMSession_ReleaseMsgs(pSes, phMsgs, iSize, 2);

	(*env)->ReleasePrimitiveArrayCritical(env, msgHandles, phMsgs, 0);
}