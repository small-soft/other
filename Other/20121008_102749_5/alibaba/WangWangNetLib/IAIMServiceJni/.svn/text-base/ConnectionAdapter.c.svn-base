#include "ConnectionAdapter.h"
#include "AIM.h"
#include "AIMContactModel.h"
#include "AIMSessionModel.h"
#include "AIMAccount.h"
#include "AIMUtil.h"
#include "OldMsgType.h"
#include "AMString.h"
#include "AMAssert.h"
#include "AMMemory.h"
#include <string.h>
#include "AliJniLog.h"


#include "CallbackAdapter.h"

extern JavaVM	*theVM;
extern jclass	clsJavaConnection;

JavaVMAttachArgs attachArgs = {JNI_VERSION_1_2, AMNULL, AMNULL};


void PrintContactList(jint iGrp)
{
	IAGroup *pGrp = (IAGroup*)iGrp;
	ListIter *pIter = 0;
	IAContact *pCnt = AMNULL;

	DPRINT("PrintContactList.......................Start 0x%x\n!", iGrp);
	if(!pGrp || !pGrp->lChildCnt.size)
	{
		DPRINT("PrintContactList.......................Fail 0x%x\n!", iGrp);
		return;
	}

	pIter = create(ListIter, &pGrp->lChildCnt);
	head(ListIter, pIter);
	do 
	{
		pCnt = (IAContact *)retrieve(ListIter, pIter);
		DPRINT("PrintContactList.....id: %s, bindid: %s\n!", pCnt->szID, pCnt->szBindUID ? pCnt->szBindUID : "null");
	} while (!next(ListIter, pIter));
	destroy(ListIter, pIter);

	DPRINT("PrintContactList.......................End 0x%x\n!", iGrp);
}

//--------------------------------------------------------------------------------------------------
// contact listener.
//--------------------------------------------------------------------------------------------------
#ifdef TARGET_VMKIT
JNI_KNI_CALLBACK_DEF4(imservice, AMInt32, JavaCntListener, AMVoid *, pArg, AMInt32, iType, AMInt64, i64GrpID,  const AMChar *, szCntID)
#else
AMInt32 JavaCntListener(AMVoid * pArg, AMInt32 iType, AMInt64 i64GrpID,  const AMChar * szCntID)
#endif
{
	jobject  Obj = (jobject)(((AMPVoid*)pArg)[0]);
	JNIEnv	*env = AMNULL;
	/*static*/ jmethodID mid = AMNULL;
	jbyteArray baryCntID = AMNULL;
	int		iLen = 0;

	DPRINT("JavaCntListener..........................%d, "I64FORMAT", %s", iType, i64GrpID, szCntID?szCntID:"0");

	(*theVM)->AttachCurrentThread(theVM, (void**)&env, &attachArgs);

	if(AMNULL == mid)
	{
		mid = (*env)->GetMethodID(env, clsJavaConnection, "onNativeContactListListener", "(J[BI)V");
		if(AMNULL == mid)
			return -1;
	}

	if(0 != szCntID)
	{
		iLen = AMStrlen(szCntID);
		baryCntID = (*env)->NewByteArray(env, iLen);
		if(0 == baryCntID)
			return -1;

		(*env)->SetByteArrayRegion(env, baryCntID, 0, iLen, szCntID);
	}

	(*env)->CallVoidMethod(env, Obj, mid, i64GrpID, baryCntID, iType);

	(*env)->DeleteLocalRef(env, baryCntID);

	(*theVM)->DetachCurrentThread(theVM);

	DPRINT("JavaCntListener..........................DeleteLocalRef");

	return 0;
}

//--------------------------------------------------------------------------------------------------
// Presence listener.
//--------------------------------------------------------------------------------------------------
#ifdef TARGET_VMKIT
JNI_KNI_CALLBACK_DEF3(imservice, AMInt32, JavaPreListener, AMVoid *, pvArg, const AIM_CONTACT_UPDATE_DATA*, pPresent, AMInt32, iCnt)
#else
AMInt32 JavaPreListener(AMVoid * pvArg, const AIM_CONTACT_UPDATE_DATA* pPresent, AMInt32 iCnt)
#endif
{
	jobject Obj = (jobject)(((AMPVoid*)pvArg)[0]);
	JNIEnv	*env = AMNULL;
	/*static*/ jmethodID	mid = AMNULL;
	jint	iLen = 0;
	jbyteArray	baryCntID = 0, barySignature = 0;
	jobjectArray contacts = 0;
	jobjectArray signatures = 0;
	jintArray	types = 0;
	jintArray	status = 0;
	int i = 0, *pStatus = 0, *pType = 0;
	jclass baryCls = 0;
	jint	iFlag = 0;

	DPRINT("%s >>>>>> %x, %x, %x\n", __FUNCTION__, pvArg, pPresent, iCnt);

	if(0 == iCnt)
		return 0;

	iFlag = pPresent->iFlag;

	(*theVM)->AttachCurrentThread(theVM, (void **)&env, &attachArgs);
	
	if(AMNULL == mid)
	{
		if(AMNULL == (mid = (*env)->GetMethodID(env, clsJavaConnection, "onNativePresenceListener", "([[B[I[I[[BI)V")))
		return -1;
	}

	if(0 == (baryCls = (*env)->FindClass(env, "[B")))
		return -1;

	if(AMNULL == (contacts = (*env)->NewObjectArray(env, iCnt, baryCls, 0)))
		return -1;

	if(AMNULL == (signatures = (*env)->NewObjectArray(env, iCnt, baryCls, 0)))
		return -1;

	(*env)->DeleteLocalRef(env, baryCls);		//	eliminate Reference Table Overflow

	if(AMNULL == (types = (*env)->NewIntArray(env, iCnt)))
		return -1;	
	if(0 == (pType = (int*)(*env)->GetIntArrayElements(env, types, 0)))
		return -1;

	if(AMNULL == (status = (*env)->NewIntArray(env, iCnt)))
		return -1;
	if(0 == (pStatus = (int*)(*env)->GetIntArrayElements(env, status, 0)))
	{
		(*env)->ReleaseIntArrayElements(env, types, pType, 0);
		return -1;
	}

	iLen = 0;
	for(i=0; i<iCnt; i++)
	{
		DPRINT("JavaPreListener..........................NewByteArray %s, %d, %d, %s\n", pPresent[i].szID, pPresent[i].ucStatus, pPresent[i].ucType, pPresent[i].szSignature?pPresent[i].szSignature:"0");

		pType[i] = pPresent[i].ucType;
		pStatus[i] = pPresent[i].ucStatus;

		AMAssert(0 != pPresent[i].szID);
		iLen = AMStrlen(pPresent[i].szID);

		if(AMNULL == (baryCntID = (*env)->NewByteArray(env, iLen)))
		{
			(*env)->ReleaseIntArrayElements(env, types, pType, 0);
			(*env)->ReleaseIntArrayElements(env, status, pStatus, 0);
			return -1;
		}

		(*env)->SetByteArrayRegion(env, baryCntID, 0, iLen, pPresent[i].szID);

		(*env)->SetObjectArrayElement(env, contacts, i, baryCntID);
		(*env)->DeleteLocalRef(env, baryCntID);

		if(AMNULL != pPresent[i].szSignature)
		{
			iLen = AMStrlen(pPresent[i].szSignature);
		}
		else
		{
			iLen = 0;
		}

		if(iLen > 0)
		{
			if(AMNULL == (barySignature = (*env)->NewByteArray(env, iLen)))
			{
				(*env)->ReleaseIntArrayElements(env, types, pType, 0);
				(*env)->ReleaseIntArrayElements(env, status, pStatus, 0);
				return -1;
			}

			(*env)->SetByteArrayRegion(env, barySignature, 0, iLen, pPresent[i].szSignature);

			(*env)->SetObjectArrayElement(env, signatures, i, barySignature);
			(*env)->DeleteLocalRef(env, barySignature);
		}
		else
		{
			(*env)->SetObjectArrayElement(env, signatures, i, 0);
		}
	}

	(*env)->ReleaseIntArrayElements(env, types, pType, 0);
	(*env)->ReleaseIntArrayElements(env, status, pStatus, 0);

	DPRINT("%s, %x, %x, %x, %x, %x, %x, %x, %d\n", __FUNCTION__, env, Obj, mid, contacts, status, types, signatures, iFlag);
	(*env)->CallVoidMethod(env, Obj, mid, contacts, status, types, signatures, iFlag);

	(*env)->DeleteLocalRef(env, contacts);
	(*env)->DeleteLocalRef(env, signatures);
	(*env)->DeleteLocalRef(env, status);
	(*env)->DeleteLocalRef(env, types);

	(*theVM)->DetachCurrentThread(theVM);
	DPRINT("JavaPreListener..........................Over");

	return 0;
}

//--------------------------------------------------------------------------------------------------
// Search user listener.
//--------------------------------------------------------------------------------------------------
#ifdef TARGET_VMKIT
JNI_KNI_CALLBACK_DEF3(imservice, AMInt32, JavaSearchUserListener, AMVoid *, pvArg, const AIM_RSP_SEARCH_USER *pRspSearchUser)
#else
AMInt32 JavaSearchUserListener(AMVoid *pvArg, const AIM_RSP_SEARCH_USER *pRspSearchUser)
#endif
{
	jobject Obj = (jobject)(((AMPVoid*)pvArg)[0]);
	JNIEnv	*env = AMNULL;
	/*static*/ jmethodID	mid = AMNULL;
	jint			iLen = 0;
	
	jbyteArray		baryCntId = 0;
	jbyteArray		baryNickName = 0;
	jbyteArray		baryCity = 0;
	jobjectArray	oaryCntId = 0;
	jobjectArray	oaryNickName = 0;
	jobjectArray	oaryCity = 0;
	jintArray		iaryAge = 0;
	jintArray		iaryGender = 0;
	jintArray		iaryBasicStatus = 0;

	int		*pAge = 0;
	int		*pGender = 0;
	int		*pBasicStatus = 0;

	int		i = 0;
	jclass	baryCls = 0;

	DPRINT("%s >>>>>> 0x%x, 0x%x\n", __FUNCTION__, pvArg, pRspSearchUser);

	if(AMNULL == pRspSearchUser)
	{
		return 0;
	}

	(*theVM)->AttachCurrentThread(theVM, (void **)&env, &attachArgs);
	
	if(AMNULL == mid)
	{
		if(AMNULL == (mid = (*env)->GetMethodID(env, clsJavaConnection, "onNativeSearchUserListener", "([[B[[B[I[I[[B[I)V")))
		return -1;
	}

	if(0 == (baryCls = (*env)->FindClass(env, "[B")))
	{
		return -1;
	}

	if(AMNULL == (oaryCntId = (*env)->NewObjectArray(env, pRspSearchUser->iUserCount, baryCls, 0)))
	{		
		return -1;
	}

	if(AMNULL == (oaryNickName = (*env)->NewObjectArray(env, pRspSearchUser->iUserCount, baryCls, 0)))
	{
		return -1;
	}

	
	if(AMNULL == (oaryCity = (*env)->NewObjectArray(env, pRspSearchUser->iUserCount, baryCls, 0)))
	{
		return -1;
	}

	(*env)->DeleteLocalRef(env, baryCls);		//	eliminate Reference Table Overflow

	// age
	if(AMNULL == (iaryAge = (*env)->NewIntArray(env, pRspSearchUser->iUserCount)))
	{
		return -1;	
	}
	
	if(0 == (pAge = (int*)(*env)->GetIntArrayElements(env, iaryAge, 0)))
	{
		return -1;
	}

	// gender
	if(AMNULL == (iaryGender = (*env)->NewIntArray(env, pRspSearchUser->iUserCount)))
	{
		return -1;
	}

	if(0 == (pGender = (int*)(*env)->GetIntArrayElements(env, iaryGender, 0)))
	{
		(*env)->ReleaseIntArrayElements(env, iaryAge, pAge, 0);
		return -1;
	}

	// basicStatus
	if(AMNULL == (iaryBasicStatus = (*env)->NewIntArray(env, pRspSearchUser->iUserCount)))
	{
		return -1;
	}

	if(0 == (pBasicStatus = (int*)(*env)->GetIntArrayElements(env, iaryBasicStatus, 0)))
	{
		(*env)->ReleaseIntArrayElements(env, iaryAge, pAge, 0);
		(*env)->ReleaseIntArrayElements(env, iaryGender, pGender, 0);
		return -1;
	}

	iLen = 0;
	DPRINT("pRspSearchUser->iUserCount = %d", pRspSearchUser->iUserCount);
	for(i = 0; i < pRspSearchUser->iUserCount; i++)
	{
		DPRINT("i = %d", i);
		DPRINT("pRspSearchUser->pszContactIds[i] = %s", pRspSearchUser->pszContactIds[i]);
		DPRINT("pRspSearchUser->pszNickNames[i] = %s", pRspSearchUser->pszNickNames[i]);
		DPRINT("pRspSearchUser->pszCitys[i] = %s", pRspSearchUser->pszCitys[i]);
		DPRINT("pRspSearchUser->pAges[i] = %d", pRspSearchUser->pAges[i]);
		DPRINT("pRspSearchUser->pGenders[i] = %d", pRspSearchUser->pGenders[i]);
		DPRINT("pRspSearchUser->pBasicStatus[i] = %d", pRspSearchUser->pBasicStatus[i]);				

		pAge[i] = pRspSearchUser->pAges[i];
		pGender[i] = pRspSearchUser->pGenders[i];
		pBasicStatus[i] = pRspSearchUser->pBasicStatus[i];

		AMAssert(AMNULL != pRspSearchUser->pszContactIds[i]);
		iLen = AMStrlen(pRspSearchUser->pszContactIds[i]);

		if(AMNULL == (baryCntId = (*env)->NewByteArray(env, iLen)))
		{
			(*env)->ReleaseIntArrayElements(env, iaryAge, pAge, 0);
			(*env)->ReleaseIntArrayElements(env, iaryGender, pGender, 0);
			(*env)->ReleaseIntArrayElements(env, iaryBasicStatus, pBasicStatus, 0);
			return -1;
		}

		(*env)->SetByteArrayRegion(env, baryCntId, 0, iLen, pRspSearchUser->pszContactIds[i]);

		(*env)->SetObjectArrayElement(env, oaryCntId, i, baryCntId);
		(*env)->DeleteLocalRef(env, baryCntId);

		// nickName
		if(AMNULL != pRspSearchUser->pszNickNames[i])
		{
			iLen = AMStrlen(pRspSearchUser->pszNickNames[i]);
		}
		else
		{
			iLen = 0;
		}

		if(iLen > 0)
		{
			if(AMNULL == (baryNickName = (*env)->NewByteArray(env, iLen)))
			{
				(*env)->ReleaseIntArrayElements(env, iaryAge, pAge, 0);
				(*env)->ReleaseIntArrayElements(env, iaryGender, pGender, 0);
				(*env)->ReleaseIntArrayElements(env, iaryBasicStatus, pBasicStatus, 0);
				(*env)->DeleteLocalRef(env, oaryCntId);
				return -1;
			}

			(*env)->SetByteArrayRegion(env, baryNickName, 0, iLen, pRspSearchUser->pszNickNames[i]);

			(*env)->SetObjectArrayElement(env, oaryNickName, i, baryNickName);
			(*env)->DeleteLocalRef(env, baryNickName);
		}
		else
		{
			(*env)->SetObjectArrayElement(env, oaryNickName, i, 0);
		}

		// city
		if(AMNULL != pRspSearchUser->pszCitys[i])
		{
			iLen = AMStrlen(pRspSearchUser->pszCitys[i]);
		}
		else
		{
			iLen = 0;
		}
		
		if(iLen > 0)
		{
			if(AMNULL == (baryCity = (*env)->NewByteArray(env, iLen)))
			{
				(*env)->ReleaseIntArrayElements(env, iaryAge, pAge, 0);
				(*env)->ReleaseIntArrayElements(env, iaryGender, pGender, 0);
				(*env)->ReleaseIntArrayElements(env, iaryBasicStatus, pBasicStatus, 0);
				(*env)->DeleteLocalRef(env, oaryCntId);
				(*env)->DeleteLocalRef(env, oaryNickName);
				return -1;
			}
		
			(*env)->SetByteArrayRegion(env, baryCity, 0, iLen, pRspSearchUser->pszCitys[i]);
		
			(*env)->SetObjectArrayElement(env, oaryCity, i, baryCity);
			(*env)->DeleteLocalRef(env, baryCity);
		}
		else
		{
			(*env)->SetObjectArrayElement(env, oaryCity, i, 0);
		}
	
	}

	DPRINT("%s, 0x%x, 0x%x, 0x%x", __FUNCTION__, env, Obj, mid);
	
	DPRINT("oaryCntId = 0x%x",oaryCntId);
	DPRINT("oaryNickName = 0x%x",oaryNickName);
	DPRINT("oaryCity = 0x%x",oaryCity);
	DPRINT("pAge = 0x%x",pAge);
	DPRINT("pGender = 0x%x",pGender);
	DPRINT("pBasicStatus = 0x%x",pBasicStatus);
	
	(*env)->CallVoidMethod(env, Obj, mid, oaryCntId, oaryNickName, iaryAge, iaryGender, oaryCity, iaryBasicStatus);

	(*env)->ReleaseIntArrayElements(env, iaryAge, pAge, 0);
	(*env)->ReleaseIntArrayElements(env, iaryGender, pGender, 0);
	(*env)->ReleaseIntArrayElements(env, iaryBasicStatus, pBasicStatus, 0);

	(*env)->DeleteLocalRef(env, oaryCntId);
	(*env)->DeleteLocalRef(env, oaryNickName);
	(*env)->DeleteLocalRef(env, oaryCity);
	
//	(*env)->DeleteLocalRef(env, pAge);
//	(*env)->DeleteLocalRef(env, pGender);
//	(*env)->DeleteLocalRef(env, pBasicStatus);


	(*theVM)->DetachCurrentThread(theVM);
	DPRINT("JavaSearchUserListener..........................end");

	return 0;
}


//--------------------------------------------------------------------------------------------------
// message listener.
//--------------------------------------------------------------------------------------------------
#ifdef TARGET_VMKIT
JNI_KNI_CALLBACK_DEF3(imservice, AMInt32, JavaMsgListener, AMVoid *, pvArg, IASession *, pSes, IAIMessage *, pMsg)
#else
AMInt32 JavaMsgListener(AMVoid * pvArg, IASession * pSes, IAIMessage * pMsg)
#endif
{
	jobject Obj = (jobject)(((AMPVoid*)pvArg)[0]);
	JNIEnv	*env = AMNULL;
	/*static*/ jmethodID	mid = AMNULL;

	DPRINT("JavaMsgListener..........................Begin");

	(*theVM)->AttachCurrentThread(theVM, (void **)&env, &attachArgs);

	if(AMNULL == mid)
	{
		mid = (*env)->GetMethodID(env, clsJavaConnection, "onNativeChatSessionListener", "(II)V");
		if(AMNULL == mid)
			return -1;
	}

	DPRINT("JavaMsgListener............Msg:%s, From %s", pMsg?(pMsg->szContactID?pMsg->szContactID:"0"):"0", pMsg?(pMsg->szContent?pMsg->szContent:"0"):"0");

	(*env)->CallVoidMethod(env, Obj, mid, (int)pSes, (int)pMsg);

	(*theVM)->DetachCurrentThread(theVM);
	DPRINT("JavaMsgListener..........................over");

	return 0;
}

//--------------------------------------------------------------------------------------------------
// connection listener.
//--------------------------------------------------------------------------------------------------
#ifdef TARGET_VMKIT
JNI_KNI_CALLBACK_DEF3(imservice, AMInt32, JavaConnListener, AMVoid *, pvArg, AMInt32, ucType, AMInt32, iInfo)
#else
AMInt32 JavaConnListener(AMVoid * pvArg, AMInt32 ucType, AMInt32 iInfo)
#endif
{
	jobject Obj = (jobject)(((AMPVoid*)pvArg)[0]);
	JNIEnv	*env = AMNULL;
	/*static*/ jmethodID	mid = AMNULL;

	DPRINT("JavaConnListener..........................Begin. type: %d, info: %d\n", ucType, iInfo);

	(*theVM)->AttachCurrentThread(theVM, (void **)&env, &attachArgs);

	if(AMNULL == mid)
	{
		mid = (*env)->GetMethodID(env, clsJavaConnection, "onNativeConnectionListener", "(II)V");
		if(AMNULL == mid)
			return -1;
	}

	(*env)->CallVoidMethod(env, Obj, mid, ucType, iInfo);

	(*theVM)->DetachCurrentThread(theVM);

	DPRINT("JavaConnListener..........................Over\n");

	return 0;
}

//--------------------------------------------------------------------------------------------------
// end four listener.
//--------------------------------------------------------------------------------------------------

AIM_CALLBACK		CallBack_Template = {
	0,
	OnNtfForceDisconnected,
	OnNtfCheckVersion ,
	OnNtfDataReady ,
	OnNtfNetInfo ,
	OnNtfUpdateGroup ,
	OnNtfUpdateContact ,
	OnNtfMesage ,
	OnNtfAddedBy ,
	OnNtfAcceptedBy ,
	OnNtfRejectedBy ,
	OnNtfRequestFrom ,
	OnNtfHelpLogin ,
	OnNtfUserInfo ,
	NULL ,
	OnNtfNeedAuth ,
	OnRspLogin ,
	OnRspChgVerify ,
	OnRspChgSrvMode ,
	OnRspChgSignature ,
	OnRspAddContact ,
	OnRspDelContact ,
	OnRspAccept ,
	OnRspAddBlack ,
	OnRspDelBlack ,
	OnRspGetVerify ,
	OnRspGetProfile ,
	OnRspGetDegree ,
	OnRspGetMemo ,
	OnRspGetSignature ,
	OnRspGetPortrait ,
	AMNULL,//OnRspSendMsg ,
	AMNULL,//OnRspChgPresence ,
	NULL,
	OnRspCheckCode,
	OnRspSearchUser,
};


JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nRegisterListener
(JNIEnv *env, jobject obj, jint iHandle)
{
	IAIM	*pIM = (IAIM *)iHandle;
	jclass	localClass = AMNULL;
	jobject	GlobalObj = AMNULL;
	AIM_CALLBACK *pCallBack = AMNULL;
	AMPVoid *ppVargs = AMNULL;

	if(0 == pIM)
		return -1;

	DPRINT("nRegisterListener........................Begin");

	if(clsJavaConnection == AMNULL)
	{
		if(AMNULL == (localClass = (*env)->GetObjectClass(env, obj)))
			return -1;
		
		if(AMNULL == (clsJavaConnection = (*env)->NewGlobalRef(env, localClass)))
		{
			(*env)->DeleteLocalRef(env, localClass);
			return -1;
		}	
		(*env)->DeleteLocalRef(env, localClass);
	}

	if(AMNULL == (GlobalObj = (*env)->NewGlobalRef(env,obj)))
		return -1;

	pCallBack = (AIM_CALLBACK *)AMMalloc(sizeof(AIM_CALLBACK));
	AMMemcpy(pCallBack, &CallBack_Template, sizeof(AIM_CALLBACK));

	ppVargs = (AMPVoid*)AMMalloc(sizeof(AMPVoid)*2);
	ppVargs[0] = (AMPVoid)GlobalObj;
	ppVargs[1] = pIM;

	pCallBack->pvArg = ppVargs;
	IAIM_RegisterListener(pIM, pCallBack);

	DPRINT("nRegisterListener........................End");
	return 0;
}

JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nUnregisterListener
(JNIEnv *env, jobject obj, jint iHandle)
{
	IAIM	*pIM = (IAIM *)iHandle;
	AIM_CALLBACK *pCallBack = AMNULL;

	if(0 == pIM)
		return -1;

	DPRINT("nUnRegisterListener........................Begin");

	pCallBack = (AIM_CALLBACK *)pIM->callback;
	IAIM_UnregisterListener(pIM, pCallBack);

	(*env)->DeleteGlobalRef(env, (jobject)(((AMPVoid*)pCallBack->pvArg)[0]));
	AMFree(pCallBack->pvArg);
	AMFree(pCallBack);

	DPRINT("nUnRegisterListener........................End");

	return 0;
}

AMChar *	GetTmpCszFromByteArray(JNIEnv *env, jbyteArray baray, jboolean *isCopy)
{
	AMChar *szRet = 0, *szTmp =0;
 	AMInt32	iLen = (*env)->GetArrayLength(env, baray);

	if(AMNULL == (szTmp = (*env)->GetPrimitiveArrayCritical(env, baray, isCopy)))
	{
		return 0;
	}

	if(0 == (szRet = (AMChar*)AMMalloc(iLen+1)))
		return 0;

	AMMemcpy(szRet, szTmp, iLen);
	szRet[iLen] = 0;

	(*env)->ReleasePrimitiveArrayCritical(env, baray, szTmp, (isCopy?(*isCopy):0));

	return szRet;
}

void ReleaseTmpCszFromByteArray(JNIEnv *env, jbyteArray bary, char *csz, jboolean *isCopy)
{
	AMFree(csz);
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCurrentAccount
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCurrentAccount
(JNIEnv *env, jobject obj, jint iIm)
{
	jint iRet = 0;
	IAIM_GetCurrentAccount((IAIM*)iIm, (AMHandle*)&iRet);
	
	return iRet;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nLogin
* Signature: (I[B[BZIZZZZ)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nLogin
(JNIEnv *env, jobject obj, jint iHandle, jbyteArray baryAcntID, jbyteArray baryPwd, jboolean isToken, jint iStatus, jboolean bSave, jboolean bMute, jboolean bViberate, jboolean bTest)
{
	Java_com_alibaba_wireless_imservice_ConnectionAdapter_nLoginEx
		(env, obj, iHandle, baryAcntID, baryPwd, isToken, iStatus, bSave, bMute, bViberate, bTest, 0);
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nLoginEx
* Signature: (I[B[BZIZZZZ[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nLoginEx
(JNIEnv *env, jobject obj, jint iHandle, jbyteArray baryAcntID, jbyteArray baryPwd, jboolean isToken, jint iStatus, jboolean bSave, jboolean bMute, jboolean bViberate, jboolean bTest, jbyteArray latestOMVersion)
{
	char *szAcntID = 0, *szPwd = 0, *szLatestOMVersion = 0;
	IAIM *pIM = (IAIM*)iHandle;
	AIM_ACCOUNT_SETTING setting;

	DPRINT("imservice jni About to IAIM_Login!");

	if(0 == pIM)
		return;

	if(AMNULL == (szAcntID = GetTmpCszFromByteArray(env, baryAcntID, 0)))
		return;

	if(AMNULL != baryPwd)
	{
		if(AMNULL == (szPwd = GetTmpCszFromByteArray(env, baryPwd, 0)))
		{
			ReleaseTmpCszFromByteArray(env, baryAcntID, szAcntID, 0);
			return;
		}
	}

	if(AMNULL != latestOMVersion)
	{
		if(AMNULL == (szLatestOMVersion = GetTmpCszFromByteArray(env, latestOMVersion, 0)))
		{
			ReleaseTmpCszFromByteArray(env, baryAcntID, szAcntID, 0);
			if(AMNULL != szPwd)
			{
				ReleaseTmpCszFromByteArray(env, baryPwd, szPwd, 0);
			}
			return;
		}
	}

	DPRINT("imservice jni, nLogin %s, %s", szAcntID, szPwd);
	
	setting.eDefaultPresence = iStatus;
	setting.bSavePwd = bSave;
	setting.bMute = bMute;
	setting.bViberate = bViberate;

	IAIM_LoginEx(pIM, szAcntID, szPwd, isToken, setting, bTest, szLatestOMVersion);

	DPRINT("imservice jni, nLogin %s, %s", szAcntID, szPwd);

	if(AMNULL != szLatestOMVersion)
	{
		ReleaseTmpCszFromByteArray(env, latestOMVersion, szLatestOMVersion, 0);
	}
	if(AMNULL != szPwd)
	{
		ReleaseTmpCszFromByteArray(env, baryPwd, szPwd, 0);
	}
	ReleaseTmpCszFromByteArray(env, baryAcntID, szAcntID, 0);

	DPRINT("imservice jni IAIM_Login Done!");
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nLogout
* Signature: (I)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nLogout
(JNIEnv *env, jobject obj, jint handle)
{
	DPRINT("imservice jni About to IAIM_Logout!");

	IAIM_Logout((IAIM*)handle);

	DPRINT("imservice jni IAIM_Logout Done!");
}
/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nRemoveBlack
* Signature: (I[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nRemoveBlack
(JNIEnv *env, jobject obj, jint iHandle, jbyteArray jbryBlkID)
{
	AMChar *szBlkID = 0;
	IAIM *pIM = (IAIM*)iHandle;

	DPRINT("imservice jni About to nRemoveBlack!");

	if(0 == pIM || 0 == pIM->pCntModel)
		return;

	if(AMNULL == (szBlkID = GetTmpCszFromByteArray(env, jbryBlkID, 0)))
		return;
	
	IAIM_RemoveBlack(pIM, szBlkID);

	ReleaseTmpCszFromByteArray(env, jbryBlkID, szBlkID, 0);

	DPRINT("imservice jni nRemoveBlack Done!");
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nAddBlack
* Signature: (I[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nAddBlack
(JNIEnv *env, jobject obj, jint iHandle, jbyteArray baryCntID)
{
	AMChar *szBlkID = 0;
	IAIM *pIM = (IAIM*)iHandle;

	DPRINT("imservice jni About to nAddBlack!");

	if(0 == pIM)
		return;

	if(AMNULL == (szBlkID = GetTmpCszFromByteArray(env, baryCntID, 0)))
		return;

	IAIM_AddBlack(pIM, szBlkID);

	ReleaseTmpCszFromByteArray(env, baryCntID, szBlkID, 0);

	DPRINT("imservice jni nAddBlack Done!");
}
/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nAddContact
* Signature: (I[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nAddContact
(JNIEnv *env, jobject obj, jint iHandle, jbyteArray baryCntID)
{
	AMChar *szCntID = AMNULL;
	IAIM *pIM = (IAIM*)iHandle;

	DPRINT("imservice jni About to nAddContact!");

	if(!pIM || !(szCntID = GetTmpCszFromByteArray(env, baryCntID, 0)))
		return ;

	IAIM_AddContact(pIM, szCntID);

	ReleaseTmpCszFromByteArray(env, baryCntID, szCntID, 0);

	DPRINT("imservice jni nAddContact Done!");
	return;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nRemoveContact
* Signature: (I[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nRemoveContact
(JNIEnv *env, jobject obj, jint iHandle, jbyteArray jaryCntID)
{
	IAIM *pIM = (IAIM*)iHandle;
	AMChar *szCntID = 0;

	DPRINT("imservice jni About to nRemoveContact!");

	if(0 == pIM)
		return;

	if(0 == (szCntID = GetTmpCszFromByteArray(env, jaryCntID, 0)))
		return;	

	IAIM_RemoveContact(pIM, szCntID);

	ReleaseTmpCszFromByteArray(env, jaryCntID, szCntID, 0);

	DPRINT("imservice jni nRemoveContact Done!");
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nChangeStatus
* Signature: (II)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nChangeStatus
(JNIEnv *env, jobject obj, jint iIM, jint status)
{
	DPRINT("imservice jni About to nChangeStatus.............%d!\n", status);

	IAIM_ChangePresence((IAIM*)iIM, (AMUChar)status);

	DPRINT("imservice jni nChangeStatus Done!");
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nChangeVerifyType
* Signature: (II)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nChangeVerifyType
(JNIEnv *env, jobject o, jint iIM, jint bVerify)
{
	IAIM *pIM = (IAIM*)iIM;

	DPRINT("imservice jni About to nChangeVerifyType!");

	if(0 == pIM)
		return;

	IAIM_ChangeVerify(pIM, (AMUChar)bVerify);

	DPRINT("imservice jni nChangeVerifyType End!");

	return;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nAcceptAddContact
* Signature: (I[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nAcceptAddContact
(JNIEnv *env, jobject o, jint iHandle, jbyteArray jaryCntID)
{
	IAIM *pIM = (IAIM*)iHandle;
	AMChar *szCntID = 0;

	DPRINT("imservice jni About to nAcceptAddContact!");

	if(0 == pIM)
		return;	

	if(0 == (szCntID = GetTmpCszFromByteArray(env, jaryCntID, 0)))
		return;
	
	IAIM_AcceptAddContact(pIM, szCntID);
	
	ReleaseTmpCszFromByteArray(env, jaryCntID, szCntID, 0);

	DPRINT("imservice jni nAcceptAddContact Done!");
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nRejectAddContact
* Signature: (I[B[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nRejectAddContact
(JNIEnv *env, jobject o, jint iHandle, jbyteArray baryCntID, jbyteArray baryInfo)
{
	char *szCntID = 0, *szInfo = 0;
	IAIM *pIM = (IAIM*)iHandle;

	DPRINT("imservice jni About to nRejectAddContact!");

	if(0 == pIM)
		return;

	if((szCntID = GetTmpCszFromByteArray(env, baryCntID, 0))
		&& (szInfo = GetTmpCszFromByteArray(env, baryInfo, 0)) )
	{
		DPRINT("nRejectAddContact....................%s, %s\n", szCntID, szInfo);
		IAIM_RejectAddContact(pIM, szCntID, szInfo);
	}

	if(szInfo)
		ReleaseTmpCszFromByteArray(env, baryInfo, szInfo, 0);
	if(szCntID)
		ReleaseTmpCszFromByteArray(env, baryCntID, szCntID, 0);

	DPRINT("imservice jni nRejectAddContact Done!");
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nSendMessage
* Signature: (I[B[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nSendMessage
(JNIEnv *env, jobject o, jint iHandle, jbyteArray baryCntID, jbyteArray baryInfo)
{
	Java_com_alibaba_wireless_imservice_ConnectionAdapter_nSendMessageEx
		(env, o, iHandle, baryCntID, baryInfo, 0);
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nSendMessageEx
* Signature: (I[B[BI)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nSendMessageEx
(JNIEnv *env, jobject o, jint iHandle, jbyteArray baryCntID, jbyteArray baryInfo, jint iAppend)
{
	char *szCntID = 0, *szInfo = 0;
	IAIM *pIM = (IAIM*)iHandle;

	DPRINT("nSendMessage................Begin!\n");

	if(0 == pIM)
		return;

	if((szCntID = GetTmpCszFromByteArray(env, baryCntID, 0))
		&& (szInfo = GetTmpCszFromByteArray(env, baryInfo, 0)))
	{
		DPRINT("nSendMessageEx...................%s, %s\n", szCntID, szInfo);
		IAIM_SendMessageEx(pIM, szCntID, szInfo, iAppend);
	}

	if(szInfo)
		ReleaseTmpCszFromByteArray(env, baryInfo, szInfo, 0);
	if(szCntID)
		ReleaseTmpCszFromByteArray(env, baryCntID, szCntID, 0);

	DPRINT("imservice jni nSendMessage Done!");
}


/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nSendU2UMessage
* Signature: (I[B[BI)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nSendU2UMessage
(JNIEnv *env, jobject o, jint iHandle, jbyteArray baryCntID, jbyteArray baryInfo, jint iType)
{
	char *szCntID = 0, *szInfo = 0;
	IAIM *pIM = (IAIM*)iHandle;

	DPRINT("nSendU2UMessage................Begin!\n");

	if(0 == pIM)
		return;

	if((szCntID = GetTmpCszFromByteArray(env, baryCntID, 0))
		&& (szInfo = GetTmpCszFromByteArray(env, baryInfo, 0)))
	{
		DPRINT("nSendMessageEx...................%s, %s\n", szCntID, szInfo);
		IAIM_SendU2UMessage(pIM, szCntID, szInfo, iType);
	}

	if(szInfo)
		ReleaseTmpCszFromByteArray(env, baryInfo, szInfo, 0);
	if(szCntID)
		ReleaseTmpCszFromByteArray(env, baryCntID, szCntID, 0);

	DPRINT("imservice jni nSendMessage Done!");
}


/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nSendVerifyInfo
* Signature: (I[B[B[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nSendVerifyInfo
(JNIEnv *env, jobject o, jint iHandle, jbyteArray baryCntID, jbyteArray baryDspName, jbyteArray baryInfo)
{
	char *szCntID = 0, *szInfo = 0;
	IAIM *pIM = (IAIM*)iHandle;

	DPRINT("imservice jni About to nSendVerifyInfo!");

	if(0 == pIM)
		return;

	if((szCntID = GetTmpCszFromByteArray(env, baryCntID, 0))
		&& (szInfo = GetTmpCszFromByteArray(env, baryInfo, 0)))
	{
		DPRINT("nSendVerifyInfo..................%s, %s\n", szCntID, szInfo);
		IAIM_SendVerify(pIM, szCntID, szInfo);
	}
	if(szInfo)
		ReleaseTmpCszFromByteArray(env, baryInfo, szInfo, 0);
	if(szCntID)
		ReleaseTmpCszFromByteArray(env, baryCntID, szCntID, 0);

	DPRINT("imservice jni nSendVerifyInfo Done!");
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetAccounts
* Signature: (I)[I
*/
JNIEXPORT jintArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetAccounts
(JNIEnv *env, jobject o, jint iHandle)
{
	IAIM *pIM = (IAIM*)iHandle;
	AMHandle	*phAccount = AMNULL;
	AMInt32		iCount = 0;
	jintArray	iaryAccount = AMNULL;

	DPRINT("imservice jni About to nGetAccounts!");

	if(0 == pIM)
		return AMNULL;

	IAIM_GetAccounts(pIM, &phAccount, &iCount);

	if(!iCount)
		return AMNULL;

	if(AMNULL == (iaryAccount = (*env)->NewIntArray(env, iCount)))
		return AMNULL;

	(*env)->SetIntArrayRegion(env, iaryAccount, 0, iCount, (const int *)phAccount);

	IAIM_ReleaseAccounts(pIM, phAccount, iCount);

	return iaryAccount;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetBlackList
* Signature: (I)[I
*/
JNIEXPORT jintArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetBlackList
(JNIEnv *env, jobject o, jint iHandle)
{
	IAIM *pIM = (IAIM*)iHandle;
	const List * pBlkList = 0;
	ListIter	*pIter = 0;
	jintArray	ret = 0;
	AMInt32		*pElem = 0;
	int			i=0;

	DPRINT("imservice jni About to nGetBlackList!");

	if(0 == pIM || 0 == pIM->pCntModel || 0 == pIM->pCntModel->pBlkGrp)
		return AMNULL;

	pBlkList = &pIM->pCntModel->pBlkGrp->lChildCnt;
	if(0 == pBlkList->size)
		return AMNULL;

	ret = (*env)->NewIntArray(env, pBlkList->size);
	if(AMNULL == ret)
		return AMNULL;

	pElem = (*env)->GetPrimitiveArrayCritical(env, ret, 0);
	if(0 == pElem)
		return AMNULL;

	pIter = create(ListIter, (List*)pBlkList);
	head(ListIter, pIter);
	i=0;
	do 
	{
		pElem[i++] = (int)retrieve(ListIter, pIter);
	} while (!next(ListIter, pIter));
	destroy(ListIter, pIter);

	(*env)->ReleasePrimitiveArrayCritical(env, ret, pElem, 0);

	DPRINT("imservice jni nGetBlackList Done!");

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetRecentList
* Signature: (I)[I
*/
JNIEXPORT jintArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetRecentList
(JNIEnv *env, jobject o, jint iIM)
{
	IAIM *pIM = (IAIM*)iIM;
	const List * pRctList = 0;
	ListIter	*pIter = 0;
	jintArray	ret = 0;
	AMInt32		*pElem = 0;
	int			i=0;

	DPRINT("imservice jni About to nGetRecentList!");

	if(0 == pIM || 0 == pIM->pCntModel || 0 == pIM->pCntModel->pRecentGrp)
		return AMNULL;

	pRctList = &pIM->pCntModel->pRecentGrp->lChildCnt;
	if(0 == pRctList->size)
		return AMNULL;

	ret = (*env)->NewIntArray(env, pRctList->size);
	if(AMNULL == ret)
		return AMNULL;

	pElem = (*env)->GetPrimitiveArrayCritical(env, ret, 0);
	if(0 == pElem)
		return AMNULL;

	pIter = create(ListIter, (List*)pRctList);
	head(ListIter, pIter);
	i=0;
	do 
	{
		pElem[i++] = (int)retrieve(ListIter, pIter);
	} while (!next(ListIter, pIter));
	destroy(ListIter, pIter);

	(*env)->ReleasePrimitiveArrayCritical(env, ret, pElem, 0);

	DPRINT("imservice jni nGetRecentList Done!");

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetChatSession
* Signature: (I[BZ)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetChatSession
(JNIEnv * env, jobject obj, jint iIM, jbyteArray baryCntID, jboolean bCreate)
{
	IAIM *pIM = (IAIM*)iIM;
	const char *szCntID = 0;
	jint		iRet = 0;

	DPRINT("imservice jni About to nGetChatSession!");

	if(0 == pIM || 0 == pIM->pSesModel)
		return 0;

	if(AMNULL == (szCntID = GetTmpCszFromByteArray(env, baryCntID, 0)))
		return 0;

	if(eAIM_RESULT_OK != IAIMSessionModel_OpenSession(pIM->pSesModel, szCntID, (AMHandle*)&iRet))
	{
		DPRINT("nGetChatSession...................Error!\n");
		ReleaseTmpCszFromByteArray(env, baryCntID, (char *)szCntID, 0);
		return 0;
	}

	ReleaseTmpCszFromByteArray(env, baryCntID, (char*)szCntID, 0);

	DPRINT("imservice jni nGetChatSession Done!");

	return iRet;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nAddFastReply
* Signature: (I[B)J
*/
JNIEXPORT jlong JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nAddFastReply
(JNIEnv *env, jobject obj, jint iIM, jbyteArray jbaryReply)
{
	IAIM *pIm = (IAIM*)iIM;
	AMChar	*szReply = 0;
	AMInt64	iRet = -1;

	if(0 == pIm)
		return -1;

	if(AMNULL == (szReply = GetTmpCszFromByteArray(env, jbaryReply, 0)))
		return -1;
	
	if(eAIM_RESULT_OK != IAIM_AddPredefMsg(pIm, szReply, &iRet))
	{
		DPRINT("nAddFastReply..................Error!\n");
		ReleaseTmpCszFromByteArray(env, jbaryReply, szReply, 0);
		return -1;
	}

	ReleaseTmpCszFromByteArray(env, jbaryReply, szReply, 0);

	return iRet;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetFastReplyList
* Signature: (I)[I
*/
JNIEXPORT jintArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetFastReplyList
(JNIEnv *env, jobject obj, jint iIM)
{
	IAIM *pIm = (IAIM*)iIM;
	jintArray	iaryMsgHandles = AMNULL;

	AMHandle	*phMsgs = AMNULL;
	AMInt32		iCount	= 0;

	if(0 == pIm)
		return AMNULL;

	if(eAIM_RESULT_OK != IAIM_GetPredefMsgs(pIm, &phMsgs, &iCount))
	{
		DPRINT("nGetFastReplyList..................Error!\n");
		return AMNULL;
	}

	if(0 == iCount)
		return AMNULL;

	if(AMNULL == (iaryMsgHandles = (*env)->NewIntArray(env, iCount)))
	{
		AIM_ReleasePredefMsgs(pIm, phMsgs, iCount, 0);
		return AMNULL;
	}

	(*env)->SetIntArrayRegion(env, iaryMsgHandles, 0, iCount, (const int *)phMsgs);

	AIM_ReleasePredefMsgs(pIm, phMsgs, iCount, 1);

	return iaryMsgHandles;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetFastReplyList
* Signature: (I)[I
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nReleaseFastReplyList
(JNIEnv *env, jobject obj, jint iIM, jintArray msgHandles)
{
	IAIM *pIM = (IAIM*)iIM;
	AMHandle	*phMsgs = AMNULL;
	AMInt32		iSize = 0;

	if(AMNULL == pIM && AMNULL != msgHandles)
		return;

	iSize = (*env)->GetArrayLength(env, msgHandles);

	if(!iSize)
		return;

	if( AMNULL == (phMsgs = (*env)->GetPrimitiveArrayCritical(env, msgHandles, 0)))
		return;

	AIMSession_ReleaseMsgs(pIM, phMsgs, iSize, 2);

	(*env)->ReleasePrimitiveArrayCritical(env, msgHandles, phMsgs, 0);
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nModifyFastReply
* Signature: (II[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nModifyFastReply
(JNIEnv *env, jobject obj, jint iIm, jlong id, jbyteArray jbaryReply)
{
	IAIM *pIm = (IAIM*)iIm;
	AMChar	*szReply = 0;

	if(0 == pIm)
		return ;

	if(AMNULL == (szReply = GetTmpCszFromByteArray(env, jbaryReply, 0)))
		return;

	IAIM_UpdatePredefMsg(pIm, id, szReply);

	ReleaseTmpCszFromByteArray(env, jbaryReply, szReply, 0);

}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nRemoveFastReply
* Signature: (II)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nRemoveFastReply
(JNIEnv *env, jobject obj, jint iIm, jlong id)
{
	IAIM *pIm = (IAIM*)iIm;

	if(0 == pIm)
		return ;

	IAIM_RemovePredefMsg(pIm, id);
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nChgServerMode
* Signature: (IZ)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nChgServerMode
(JNIEnv *env, jobject obj, jint iIM, jboolean status)
{
	DPRINT("imservice jni About to nChgServerMode.............%d!\n", status);

	IAIM_ChangeSrvMode((IAIM*)iIM, (AMUChar)status);

	DPRINT("imservice jni nChgServerMode Done!");
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nRemoveRecentContact
* Signature: (I[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nRemoveRecentContact
(JNIEnv *env, jobject obj, jint iIm, jbyteArray jbaryCntId)
{
	IAIM *pIm = (IAIM*)iIm;
	AMChar *szCntId = AMNULL;

	DPRINT("nRemoveRecentContact........................Begin\n");

	if(0 == pIm || 0 == pIm->pCntModel)
	{
		DPRINT("nRemoveRecentContact...........Im Handle is not valid\n");
		return ;
	}

	if(AMNULL != jbaryCntId)
	{
		if(AMNULL == (szCntId = GetTmpCszFromByteArray(env, jbaryCntId, 0)))
			return;
	}

	DPRINT("nRemoveRecentContact........................%s\n", szCntId);
	IAIMContactModel_RemoveRecent(pIm->pCntModel, szCntId);
	
	if(szCntId)
		ReleaseTmpCszFromByteArray(env, jbaryCntId, szCntId, 0);

	DPRINT("nRemoveRecentContact.......................OK!\n");
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nRemoveStrangerContact
* Signature: (I[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nRemoveStrangerContact
(JNIEnv *env, jobject obj, jint iIm, jbyteArray jbaryCntId)
{
	IAIM *pIm = (IAIM*)iIm;
	AMChar *szCntId = AMNULL;

	DPRINT("nRemoveStrangerContact.......................Entering!\n");


	if(0 == pIm || 0 == pIm->pCntModel)
	{
		DPRINT("nRemoveStrangerContact...........Im Handle is not valid\n");
		return ;
	}

	if(AMNULL != jbaryCntId)
	{
		if(AMNULL == (szCntId = GetTmpCszFromByteArray(env, jbaryCntId, 0)))
			return;
	}

	DPRINT("nRemoveStrangerContact........................%s\n", szCntId);
	IAIMContactModel_RemoveStranger(pIm->pCntModel, szCntId);

	if(szCntId)
		ReleaseTmpCszFromByteArray(env, jbaryCntId, szCntId, 0);

	DPRINT("nRemoveStrangerContact.......................OK!\n");
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nRemoveAllMessage
* Signature: (I[B)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nRemoveAllMessage
(JNIEnv *env, jobject obj, jint iIM)
{
	IAIM *pIm = (IAIM *)iIM;
	if(0 == pIm)
		return -1;
	IAIM_DeleteAllMsg(pIm);
	return 0;
}

// /*
// * Class:     com_alibaba_wireless_imservice_ConnectionAdapter
// * Method:    nRemoveMessage
// * Signature: (IJ)I
// */
// JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nRemoveMessage
// (JNIEnv *env, jobject obj, jint iIM, jlong i64MsgId)
// {
// 	IAIM *pIm = (IAIM *)iIM;
// 	if(0 == pIm)
// 		return -1;
// 	IAIM_DeleteMsgByID(pIm, i64MsgId);
// 	return 0;
// }

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetTopGroupHandles
* Signature: (I)[I
*/
JNIEXPORT jintArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetTopGroupHandles
(JNIEnv *env, jobject obj, jint iIM)
{
	IAIM	*pIm = (IAIM*)iIM;
	IAContactModel *pCntModel = 0;
	jintArray ret = 0; 
	int		*pElem = 0, i=0;
	ListIter *pIter = 0;

	pCntModel = pIm->pCntModel;
	if(0 == pIm || 0 == pCntModel)
		return AMNULL;

	if(0 == pCntModel->lTopGrp.size)
		return AMNULL;

	if(AMNULL == (ret = (*env)->NewIntArray(env, pCntModel->lTopGrp.size)))
		return AMNULL;

	pElem = (*env)->GetPrimitiveArrayCritical(env, ret, 0);
	if(0 == pElem)
		return AMNULL;

	pIter = create(ListIter, &pCntModel->lTopGrp);
	head(ListIter, pIter);
	i=0;
	do 
	{
		pElem[i++] = (int)retrieve(ListIter, pIter);
	} while (!next(ListIter, pIter));
	destroy(ListIter, pIter);

	(*env)->ReleasePrimitiveArrayCritical(env, ret, pElem, 0);

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nCancel
* Signature: (I)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nCancel
(JNIEnv *env, jobject obj, jint handle)
{
	IAIM	*pIm = (IAIM*)handle;
	if(0 == pIm)
		return;

	IAIM_Logout(pIm);
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetImStatus
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetImStatus
(JNIEnv *env, jobject obj, jint handle)
{
	IAIM	*pIm = (IAIM*)handle;
	AMUChar	ucRet = 0;
	if(0 == pIm)
		return -1;

	AIM_GetIMStatus(pIm, &ucRet);

	return ucRet;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCurrentToken
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCurrentToken
(JNIEnv *env, jobject obj, jint handle)
{
	IAIM	*pIm = (IAIM*)handle;
	jbyteArray	baryToken = AMNULL;
	const char	*szToken = AMNULL;
	AMUInt32	uiLen = 0;
	
	if(AMNULL == pIm)
	{
		return AMNULL;
	}

	if(eAIM_RESULT_OK != AIM_GetCurrentToken(pIm, &szToken, &uiLen))
	{
		return AMNULL;
	}

	if(AMNULL == szToken)
	{
		return AMNULL;
	}

	baryToken = (*env)->NewByteArray(env, uiLen);

	(*env)->SetByteArrayRegion(env, baryToken, 0, uiLen, szToken);

	return baryToken;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCurrentWebMD5
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCurrentWebMD5
(JNIEnv *env, jobject obj, jint handle)
{
	IAIM	*pIm = (IAIM*)handle;
	jbyteArray	baryToken = AMNULL;
	const char	*szToken = AMNULL;
	AMUInt32	uiLen = 0;

	if(AMNULL == pIm)
	{
		return AMNULL;
	}

	if(eAIM_RESULT_OK != AIM_GetCurrentWebMD5(pIm, &szToken, &uiLen))
	{
		return AMNULL;
	}

	if(AMNULL == szToken)
	{
		return AMNULL;
	}

	baryToken = (*env)->NewByteArray(env, uiLen);

	(*env)->SetByteArrayRegion(env, baryToken, 0, uiLen, szToken);

	return baryToken;
}


/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetContactVerify
* Signature: (I)[B
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetContactVerify
(JNIEnv *env, jobject obj, jint iIm, jbyteArray jbaryCntId, jint iClientID)
{
	IAIM *pIm = (IAIM*)iIm;
	AMChar *szCntId = AMNULL;

	if(0 == pIm || 0 == pIm->pCntModel)
	{
		DPRINT("nGetContactVerify...........Im Handle is not valid\n");
		return ;
	}

	if(AMNULL != jbaryCntId)
	{
		if(AMNULL == (szCntId = GetTmpCszFromByteArray(env, jbaryCntId, 0)))
			return;
	}

	IAIM_GetVerify(pIm, szCntId);
	
	if(szCntId)
		ReleaseTmpCszFromByteArray(env, jbaryCntId, szCntId, 0);
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetContactUDBProfile
* Signature: (I)[B
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetContactUDBProfile
(JNIEnv *env, jobject obj, jint iIm, jbyteArray jbaryCntId)
{
	IAIM *pIm = (IAIM*)iIm;
	AMChar *szCntId = AMNULL;

	if(0 == pIm || 0 == pIm->pCntModel)
	{
		DPRINT("nGetContactUDBProfile...........Im Handle is not valid\n");
		return ;
	}

	if(AMNULL != jbaryCntId)
	{
		if(AMNULL == (szCntId = GetTmpCszFromByteArray(env, jbaryCntId, 0)))
			return;
	}

	IAIM_GetProfile(pIm, szCntId);

	if(szCntId)
		ReleaseTmpCszFromByteArray(env, jbaryCntId, szCntId, 0);
}


JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nSearchUser
(JNIEnv *env, jobject obj, jint iIm, jbyteArray jbKeyword)
{
	DPRINT("JNI nSearchUser()");

	IAIM *pIm = (IAIM*)iIm;
	AMChar *szKeyWord = AMNULL;

	if(0 == pIm || 0 == pIm->pCntModel)
	{
		DPRINT("nSearchUser.........Im Handle is not valid\n");
		return ;
	}

	if(AMNULL != jbKeyword)
	{
		if(AMNULL == (szKeyWord = GetTmpCszFromByteArray(env, jbKeyword, 0)))
		{
			return;
		}
	}

	IAIM_SearchUser(pIm, szKeyWord);

	if(szKeyWord)
	{
		ReleaseTmpCszFromByteArray(env, jbKeyword, szKeyWord, 0);
	}

	
}


/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetContactPortrait
* Signature: (I)[B
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetContactPortrait
(JNIEnv *env, jobject obj, jint iIm, jbyteArray jbaryCntId)
{
	IAIM *pIm = (IAIM*)iIm;
	AMChar *szCntId = AMNULL;

	if(0 == pIm || 0 == pIm->pCntModel)
	{
		DPRINT("nGetContactPortrait...........Im Handle is not valid\n");
		return ;
	}

	if(AMNULL != jbaryCntId)
	{
		if(AMNULL == (szCntId = GetTmpCszFromByteArray(env, jbaryCntId, 0)))
			return;
	}

	IAIM_GetPortrait(pIm, szCntId);

	if(szCntId)
		ReleaseTmpCszFromByteArray(env, jbaryCntId, szCntId, 0);
}


/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nChangeSignature
* Signature: (II)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nChangeSignature
(JNIEnv *env, jobject obj, jint iIm, jbyteArray jbarySignature)
{
	IAIM *pIm = (IAIM*)iIm;
	AMChar *szSignature = AMNULL;

	if(0 == pIm || 0 == pIm->pCntModel)
	{
		DPRINT("nChangeSignature...........Im Handle is not valid\n");
		return ;
	}

	if(AMNULL != jbarySignature)
	{
		if(AMNULL == (szSignature = GetTmpCszFromByteArray(env, jbarySignature, 0)))
			return;
	}

	IAIM_ChangeSignature(pIm, szSignature);

	if(szSignature)
		ReleaseTmpCszFromByteArray(env, jbarySignature, szSignature, 0);
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetContactSignature
* Signature: (II)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetContactSignature
(JNIEnv *env, jobject obj, jint iIm, jbyteArray baryContacts, jint iCount)
{
	IAIM *pIm = (IAIM*)iIm;
	AMChar *szContacts = AMNULL;

	if(0 == pIm || 0 == pIm->pCntModel)
	{
		DPRINT("nGetContactSignature...........Im Handle is not valid\n");
		return ;
	}

	if(AMNULL != baryContacts)
	{
		if(AMNULL == (szContacts = GetTmpCszFromByteArray(env, baryContacts, 0)))
			return;
	}

	IAIM_GetSignature(pIm, szContacts, iCount);

	if(szContacts)
		ReleaseTmpCszFromByteArray(env, baryContacts, szContacts, 0);
}


/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetAcntHandle
* Signature: (I[B)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetAcntHandle
(JNIEnv *env, jclass cls, jint iAcntModel, jbyteArray aryAcntID)
{
	IAccountModel	*pAcntModel = (IAccountModel*)iAcntModel;
	char	*	szAcntID = 0;
	const AIMAccount	*pAcnt = 0;

	if(0 == pAcntModel)
		return 0;

	if(NULL == (szAcntID = GetTmpCszFromByteArray(env, aryAcntID, 0)))
		return 0;

	pAcnt = IAccountModel_findHistoryAcnt(pAcntModel, szAcntID);

	ReleaseTmpCszFromByteArray(env, aryAcntID, szAcntID, 0);

	return (int)pAcnt;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetAcntID
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetAcntID
(JNIEnv *env, jclass cls, jint iAcnt)
{
	AIMAccount *pAcnt = (AIMAccount*)iAcnt;
	int iLen = 0;
	jbyteArray ret = 0; 

	//DPRINT("About to nGetAcntID for Acnt %x, %s\n", pAcnt, pAcnt->szID?pAcnt->szID:"0");

	if(0 == pAcnt || 0 == pAcnt->szID)
		return NULL;

	iLen = AMStrlen(pAcnt->szID);
	if(0 == iLen)
		return NULL;

	if(NULL == (ret = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, ret, 0, iLen, pAcnt->szID);

	DPRINT("nGetAcntID for Acnt %d end!\n", iAcnt);

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetAcntName
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetAcntName
(JNIEnv *env, jclass cls, jint iAcnt)
{
	AIMAccount *pAcnt = (AIMAccount*)iAcnt;
	int iLen = 0;
	jbyteArray ret = 0; 

	if(0 == pAcnt || 0 == pAcnt->szName)
		return NULL;

	iLen = AMStrlen(pAcnt->szName);
	if(0 == iLen)
		return NULL;

	if(NULL == (ret = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, ret, 0, iLen, pAcnt->szName);

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetAcntType
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetAcntType
(JNIEnv *env, jclass cls, jint iAcnt)
{
	AIMAccount *pAcnt = (AIMAccount*)iAcnt;

	if(0 == pAcnt)
		return -1;

	return pAcnt->eType;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetAcntStatus
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetAcntStatus
(JNIEnv *env, jclass cls, jint iAcnt)
{
	AIMAccount *pAcnt = (AIMAccount*)iAcnt;

	if(0 == pAcnt)
		return -1;

	DPRINT("nGetAcntStatus.........................%d\n", pAcnt->ePresence);
	return pAcnt->ePresence;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetAcntFlag
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetAcntFlag
(JNIEnv *env, jclass cls, jint iAcnt)
{
	AIMAccount *pAcnt = (AIMAccount*)iAcnt;

	if(0 == pAcnt)
		return -1;

	return pAcnt->uiFlag;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetAcntPhone
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetAcntPhone
(JNIEnv *env, jclass cls, jint iAcnt)
{
	AIMAccount *pAcnt = (AIMAccount*)iAcnt;
	int iLen = 0;
	jbyteArray ret = 0; 

	if(0 == pAcnt || 0 == pAcnt->szPhoneNum)
		return NULL;

	iLen = AMStrlen(pAcnt->szPhoneNum);
	if(0 == iLen)
		return NULL;

	if(NULL == (ret = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, ret, 0, iLen, pAcnt->szPhoneNum);

	return ret;
}
/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nIsPwdNull
* Signature: (I)Z
*/
JNIEXPORT jboolean JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nIsPwdNull
(JNIEnv *env, jclass cls, jint iAcnt)
{
	AIMAccount *pAcnt = (AIMAccount*)iAcnt;
	jboolean ret = 0; 

	if(eAIM_RESULT_OK != AIMAccount_IsPwdNull(pAcnt, &ret))
		return AMTRUE;

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetGrpHandle
* Signature: (IJ)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetGrpHandle
(JNIEnv *env, jclass cls, jint iIM, jlong iGrpID)
{
	IAIM	*pIM = (IAIM*)iIM;
	const IAGroup	*pGrp = 0;

	DPRINT("nGetGrpHandle.......................Begin! gid: %lld\n", iGrpID);

	if(0 == pIM || 0 == pIM->pCntModel)
		return 0;	

	if(eAIM_RESULT_OK != IAIMContactModel_GetGroupByID(pIM->pCntModel, iGrpID, (AMHandle*)&pGrp))
	{
		DPRINT("nGetGrpHandle.........................Error!\n");
		return 0;
	}

	DPRINT("nGetGrpHandle........................Done! gid: %lld\n", iGrpID);
	return (int)pGrp;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetGrpID
* Signature: (I)J
*/
JNIEXPORT jlong JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetGrpID
(JNIEnv *env, jclass cls, jint iGrp)
{
	IAGroup *pGrp = (IAGroup*)iGrp;

	if(0 == pGrp)
		return -1;

	return pGrp->iGroupID;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetGrpName
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetGrpName
(JNIEnv *env, jclass cls, jint iGrp)
{
	IAGroup *pGrp = (IAGroup*)iGrp;
	int iLen = 0;
	jbyteArray ret = 0; 

	if(0 == pGrp || 0 == pGrp->szName)
		return NULL;

	iLen = AMStrlen(pGrp->szName);
	if(0 == iLen)
		return NULL;

	if(NULL == (ret = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, ret, 0, iLen, pGrp->szName);

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCntList
* Signature: (I)[I
*/
JNIEXPORT jintArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCntList
(JNIEnv *env, jclass cls, jint iGrp)
{
	IAGroup *pGrp = (IAGroup*)iGrp;
	jintArray ret = 0; 
	int		*pElem = 0, i=0;
	ListIter *pIter = 0;

	if(!pGrp || !pGrp->lChildCnt.size)
	{
		DPRINT("nGetCntList.......................Fail 0x%x\n!", iGrp);
		return NULL;
	}

	if(NULL == (ret = (*env)->NewIntArray(env, pGrp->lChildCnt.size)))
		return NULL;

	pElem = (*env)->GetPrimitiveArrayCritical(env, ret, 0);
	if(0 == pElem)
		return NULL;

	pIter = create(ListIter, &pGrp->lChildCnt);
	head(ListIter, pIter);
	i=0;
	do 
	{
		pElem[i++] = (int)retrieve(ListIter, pIter);
	} while (!next(ListIter, pIter));
	destroy(ListIter, pIter);

	PrintContactList(iGrp);

	(*env)->ReleasePrimitiveArrayCritical(env, ret, pElem, 0);

	DPRINT("nGetCntList.......................End 0x%x\n!", iGrp);

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetGrpList
* Signature: (I)[I
*/
JNIEXPORT jintArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetGrpList
(JNIEnv *env, jclass cls, jint iGrp)
{
	IAGroup *pGrp = (IAGroup*)iGrp;
	jintArray ret = 0; 
	int		*pElem = 0, i=0;
	ListIter *pIter = 0;

	if(!pGrp || !pGrp->lChildGrp.size)
		return NULL;

	if(NULL == (ret = (*env)->NewIntArray(env, pGrp->lChildGrp.size)))
		return NULL;

	pElem = (*env)->GetPrimitiveArrayCritical(env, ret, 0);
	if(0 == pElem)
		return NULL;

	pIter = create(ListIter, &pGrp->lChildGrp);
	head(ListIter, pIter);
	i=0;
	do 
	{
		pElem[i++] = (int)retrieve(ListIter, pIter);
	} while (!next(ListIter, pIter));
	destroy(ListIter, pIter);

	(*env)->ReleasePrimitiveArrayCritical(env, ret, pElem, 0);

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCntNum
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCntNum
(JNIEnv *env, jclass cls, jint iGrp)
{
	IAGroup *pGrp = (IAGroup*)iGrp;
	AMInt32	iRet = -1;

	if(0 == pGrp)
		return -1;

	if(eAIM_RESULT_OK != IAIMGroup_CountContacts(pGrp, AMFALSE, &iRet))
	{
		AMAssert(0);
	}
	return iRet;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetOnlineNum
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetOnlineNum
(JNIEnv *env, jclass cls, jint grpHandle)
{
	IAGroup *pGrp = (IAGroup*)grpHandle;
	AMInt32	iNum = -1;

	DPRINT("nGetOnlineNum.......................Begin 0x%x\n!", grpHandle);

	if(0 == pGrp)
		return -1;

	if(eAIM_RESULT_OK != IAIMGroup_CountOnlines(pGrp, AMFALSE, &iNum))
	{
		AMAssert(0);
	}

	DPRINT("nGetOnlineNum.......................End 0x%x\n!", grpHandle);

	return iNum;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetParentGrp
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetParentGrp
(JNIEnv *env, jclass cls, jint grpHandle)
{
	IAGroup *pGrp = (IAGroup*)grpHandle;
	if(0 == pGrp)
		return -1;

	return (int)pGrp->pParentGrp;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetUnreadMsgCnt
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetUnreadMsgCnt
(JNIEnv *env, jclass cls, jint grpHandle)
{
	IAGroup *pGrp = (IAGroup*)grpHandle;
	if(0 == pGrp)
		return -1;

	DPRINT("nGetUnreadMsgCnt.........................%d, %d\n", grpHandle, pGrp->iUnreadMsgCnt);
	return (int)pGrp->iUnreadMsgCnt;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCntHandle
* Signature: (I[B)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCntHandle
(JNIEnv *env, jclass cls, jint iIM, jbyteArray aryCntID)
{
	IAIM	*pIM = (IAIM*)iIM;
	char	*	szCntID = 0;
	const IAContact	*pCnt = 0;

	if(0 == pIM || 0 == pIM->pCntModel)
		return 0;

	if(NULL == (szCntID = GetTmpCszFromByteArray(env, aryCntID, 0)))
		return 0;

	IAIMContactModel_GetContactByID(pIM->pCntModel, szCntID, (AMHandle*)&pCnt);

	ReleaseTmpCszFromByteArray(env, aryCntID, szCntID, 0);

	return (int)pCnt;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    ngetCntGrpID
* Signature: (I)J
*/
JNIEXPORT jlong JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_ngetCntGrpID
(JNIEnv *env, jclass cls, jint iHandle)
{
	IAContact *pCnt = (IAContact*)iHandle;

	if(0 == pCnt)
		return -1;

	return pCnt->iParentGid;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCntID
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCntID
(JNIEnv *env, jclass cls, jint iCnt)
{
	IAContact *pCnt = (IAContact*)iCnt;
	int iLen = 0;
	jbyteArray ret = 0; 

	if(0 == pCnt || 0 == pCnt->szID)
		return NULL;

	iLen = AMStrlen(pCnt->szID);
	if(0 == iLen)
		return NULL;

	if(NULL == (ret = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, ret, 0, iLen, pCnt->szID);

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCntType
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCntType
(JNIEnv *env, jclass cls, jint iCnt)
{
	IAContact *pCnt = (IAContact*)iCnt;

	if(0 == pCnt)
		return -1;

	return pCnt->eType;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCntNick
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCntNick
(JNIEnv *env, jclass cls, jint iCnt)
{
	IAContact *pCnt = (IAContact*)iCnt;
	int iLen = 0;
	jbyteArray ret = 0; 

	if(0 == pCnt || 0 == pCnt->szName)
		return NULL;

	iLen = AMStrlen(pCnt->szName);
	if(0 == iLen)
		return NULL;

	if(NULL == (ret = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, ret, 0, iLen, pCnt->szName);

	return ret;
}
/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCntPinyin
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCntPinyin
(JNIEnv *env, jclass cls, jint iCnt)
{
	IAContact *pCnt = (IAContact*)iCnt;
	int iLen = 0;
	jbyteArray ret = 0; 

	if(0 == pCnt || 0 == pCnt->szPinyin)
		return NULL;

	iLen = AMStrlen(pCnt->szPinyin);
	if(0 == iLen)
		return NULL;

	if(NULL == (ret = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, ret, 0, iLen, pCnt->szPinyin);

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCntLastMsg
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCntLastMsg
(JNIEnv *env, jclass cls, jint iCnt)
{
	IAContact *pCnt = (IAContact*)iCnt;
	int iLen = 0;
	jbyteArray ret = 0; 

	if(0 == pCnt || 0 == pCnt->szLastMsg)
		return NULL;

	iLen = AMStrlen(pCnt->szLastMsg);
	if(0 == iLen)
		return NULL;

	if(NULL == (ret = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, ret, 0, iLen, pCnt->szLastMsg);

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCntStatus
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCntStatus
(JNIEnv *env, jclass cls, jint iCnt)
{
	IAContact *pCnt = (IAContact*)iCnt;

	if(0 == pCnt)
		return -1;

	return pCnt->ePresence;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCntParentGrp
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCntParentGrp
(JNIEnv *env, jclass cls, jint iCnt)
{
	IAContact *pCnt = (IAContact*)iCnt;

	if(0 == pCnt)
		return -1;

	return (int)pCnt->pParentGrp;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCntFlag
* Signature: (I)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCntFlag
(JNIEnv *env, jclass cls, jint iCnt)
{
	IAContact *pCnt = (IAContact*)iCnt;

	if(0 == pCnt)
		return -1;

	return pCnt->uiFlag;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetSignature
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetSignature
(JNIEnv *env, jclass cls, jint iCnt)
{
	IAContact *pCnt = (IAContact*)iCnt;
	int iLen = 0;
	jbyteArray ret = 0; 

	if(0 == pCnt || 0 == pCnt->szSignature)
		return NULL;

	iLen = AMStrlen(pCnt->szSignature);
	if(0 == iLen)
		return NULL;

	if(NULL == (ret = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, ret, 0, iLen, pCnt->szSignature);

	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetPhoneNum
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetPhoneNum
(JNIEnv *env, jclass cls, jint iCnt)
{
	IAContact *pCnt = (IAContact*)iCnt;
	int iLen = 0;
	jbyteArray ret = 0; 

	if(0 == pCnt || 0 == pCnt->szPhone)
		return NULL;

	iLen = AMStrlen(pCnt->szPhone);
	if(0 == iLen)
		return NULL;

	if(NULL == (ret = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, ret, 0, iLen, pCnt->szPhone);

	return ret;
}

JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nMsgGetCntId
  (JNIEnv *env, jclass clz, jint iMsgHandle)
{
	IAIMessage *pMsg = (IAIMessage *)iMsgHandle;
	jbyteArray baryCntId = 0;
	jint	iLen = 0;

	if(0 == pMsg || 0 == pMsg->szContactID)
		return AMNULL;

	iLen = AMStrlen(pMsg->szContactID);

	if(AMNULL == (baryCntId = (*env)->NewByteArray(env, iLen)))
		return AMNULL;

	(*env)->SetByteArrayRegion(env, baryCntId, 0, iLen, pMsg->szContactID);

	return baryCntId;
}

/*
 * Class:     com_alibaba_wireless_imservice_ConnectionAdapter
 * Method:    nMsgGetBody
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nMsgGetBody
(JNIEnv *env, jclass clz, jint iMsgHandle)
{
	IAIMessage *pMsg = (IAIMessage *)iMsgHandle;
	jbyteArray baryContent = 0;
	jint	iLen = 0;

	if(0 == pMsg || 0 == pMsg->szContent)
		return AMNULL;

	iLen = AMStrlen(pMsg->szContent);

	if(AMNULL == (baryContent = (*env)->NewByteArray(env, iLen)))
		return AMNULL;

	(*env)->SetByteArrayRegion(env, baryContent, 0, iLen, pMsg->szContent);

	JNI_LOGE("ConnectionAdapter", "nMsgGetBody");
	return baryContent;
}

/*
 * Class:     com_alibaba_wireless_imservice_ConnectionAdapter
 * Method:    nMsgGetId
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nMsgGetId
(JNIEnv *env, jclass clz, jint iMsgHandle)
{
	IAIMessage *pMsg = (IAIMessage *)iMsgHandle;

	if(0 == pMsg)
		return -1;

	return pMsg->_iRid;
}

static AIM_MSG_TYPE_OLD _MsgTypeTranlator(AIM_MSG_TYPE eType)
{
	switch (eType)
	{
	case eMSG_TYPE_CHAT_SEND:
		return CNT_MESSAGE_SENT;
	case eMSG_TYPE_CHAT_RECV:
		return CNT_MESSAGE_RECEIVED;
	case eMSG_TYPE_CHAT_AUTO:
		return AUTO_REPLAY_CNT_MESSAGE;

	case eMSG_TYPE_SMS_SEND:
	case eMSG_TYPE_SMS_RECV:
	case eMSG_TYPE_TRIBE://需要其他字段，目前不支持
	case eMSG_TYPE_MULTY://需要其他字段，目前不支持
	case eMSG_TYPE_OFFLINE://现在所有离线消息，IMService收到的时候是CHAT_RECV...
	case eMSG_TYPE_FILE: //需要其他字段，目前不支持
	case eMSG_TYPE_EVIDENCE:
		break;

	case eMSG_TYPE_SYSTEM:
		return SYSTEM_MESSAGE;
	case eMSG_TYPE_CONTACT_ADD_OK:
		return ADD_CNT_SUCCESS;
	case eMSG_TYPE_CONTACT_ADD_FAIL:
		return ADD_CNT_FAILED;
	case eMSG_TYPE_CONTACT_NEED_REQ:
		return ADD_CNT_NEED_REQ;
	case eMSG_TYPE_CONTACT_WAIT_VERIFY:
		return ADD_CNT_WAIT_VERIFY;
	case eMSG_TYPE_CONTACT_ADDED_BY:
		return ADDED_BY_PEER;
	case eMSG_TYPE_CONTACT_REQ_FROM:
		return REQ_FROM_PEER;
	case eMSG_TYPE_CONTACT_REJECTED_BY:
		return DECLINED_BY_PEER;
	case eMSG_TYPE_CONTACT_ACCEPTED_BY:
		return ACCEPTED_BY_PEER;

	case eMSG_TYPE_SUBSCRIBE:
		return SUBSCRIBE_MESSAGE;
	case eMSG_TYPE_OPERATION:
		return AUTO_OPERATION_TIP;
	}
	return (AIM_MSG_TYPE_OLD)eType;
	DPRINT("_MsgTypeTranlator................Unknown Type: %d\n", eType);
}

JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nMsgGetType
(JNIEnv *env, jclass clz, jint iMsgHandle)
{
	IAIMessage *pMsg = (IAIMessage *)iMsgHandle;

	if(0 == pMsg)
		return -1;

	return _MsgTypeTranlator(pMsg->eType);
}

JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nMsgGetU2UType
(JNIEnv *env, jclass clz, jint iMsgHandle)
{
	IAIMessage *pMsg = (IAIMessage *)iMsgHandle;

	if(0 == pMsg)
		return -1;

	return _MsgTypeTranlator(pMsg->u2uType);
}

/*
 * Class:     com_alibaba_wireless_imservice_ConnectionAdapter
 * Method:    nMsgGetTime
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nMsgGetTime
(JNIEnv *env, jclass clz, jint iMsgHandle)
{
	IAIMessage *pMsg = (IAIMessage *)iMsgHandle;

	if(0 == pMsg)
		return -1;

	return pMsg->iServerTime;
}

/*
 * Class:     com_alibaba_wireless_imservice_ConnectionAdapter
 * Method:    nMsgGetUnread
 * Signature: (I)B
 */
JNIEXPORT jbyte JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nMsgGetUnread
(JNIEnv *env, jclass clz, jint msgHandle)
{
	IAIMessage *pMsg = (IAIMessage *)msgHandle;

	if(0 == pMsg)
		return -1;

	return pMsg->bUnread;
}


/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nSetMobileImMessage
* Signature: ([B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nSetMobileImMessage
(JNIEnv *env, jclass cls, jbyteArray msg)
{
	AMChar* mobileImMsg = AMNULL;
	mobileImMsg = GetTmpCszFromByteArray(env, msg, 0);
	if(AMNULL == mobileImMsg)
	{
		return;
	}

	IASessionModel_SetMobileImMessage(mobileImMsg);

	ReleaseTmpCszFromByteArray(env, msg, mobileImMsg, 0);
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nSetTtid
* Signature: ([B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nSetTtid
	(JNIEnv *env, jclass cls, jbyteArray jttid)
{
	AMChar* ttid = AMNULL;
	ttid = GetTmpCszFromByteArray(env, jttid, 0);
	if(AMNULL == ttid)
	{
		return;
	}

	IAIM_SetTtid(ttid);

	ReleaseTmpCszFromByteArray(env, jttid, ttid, 0);
}


/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetOperationMessage
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetOperationMessage
	(JNIEnv *env, jclass cls, jint iIM)
{
	AMChar* message = IAIM_GetOperationMessage();
	jbyteArray jmessage = NULL;

	if(message != AMNULL)
	{
		int length = AMStrlen(message);
		jmessage = (*env)->NewByteArray(env, length);
		(*env)->SetByteArrayRegion(env, jmessage, 0, length, message);
	}

	IAIM_FreeOperationMessage();

	return jmessage;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetCurSigXML
* Signature: (I)[B
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCurSigXML
(JNIEnv *env, jobject obj, jint handle)
{
	IAIM	*pIm = (IAIM*)handle;
	jbyteArray	baryToken = AMNULL;
	const char	*szToken = AMNULL;
	AMUInt32	uiLen = 0;

	if(AMNULL == pIm)
	{
		return AMNULL;
	}

	if(eAIM_RESULT_OK != AIM_GetCurSigXML(pIm, &szToken, &uiLen))
	{
		return AMNULL;
	}

	if(AMNULL == szToken)
	{
		return AMNULL;
	}

	baryToken = (*env)->NewByteArray(env, uiLen);

	(*env)->SetByteArrayRegion(env, baryToken, 0, uiLen, szToken);

	return baryToken;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nUpdateSetting
* Signature: (IIZZZ)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nUpdateSetting
(JNIEnv *env, jobject obj, jint iHandle, jint iStatus, jboolean bSave, jboolean bMute, jboolean bViberate)
{
	IAIM *pIM = (IAIM*)iHandle;
	AIM_ACCOUNT_SETTING setting = {0,0,0,0};

	DPRINT("imservice jni About to nUpdateSetting...%x, %d, %c, %c, %c\n", pIM, iStatus, bSave, bMute, bViberate);

	if(0 == pIM)
		return -1;

	setting.eDefaultPresence = iStatus;
	setting.bSavePwd = bSave;
	setting.bMute = bMute;
	setting.bViberate = bViberate;

	return IAIM_UpdateSetting(pIM, &setting, 0);
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nBlockStranger
* Signature: (IIZ)I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nBlockStranger
(JNIEnv *env, jobject obj, jint iHandle, jboolean bBlockStranger)
{
	IAIM *pIM = (IAIM*)iHandle;
	

	DPRINT("imservice jni About to nUpdateSetting...%x, %d\n", pIM, bBlockStranger);

	if(0 == pIM)
		return -1;

	return IAIM_UpdateSetting(pIM, NULL, bBlockStranger);
}

JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nSendFile
(JNIEnv *env, jobject obj, jint iHandle, jbyteArray contantID, jbyteArray filePath)
{
	AMInt32 iTaskId = 0, iRetCode = 0;
	AMChar *szContantID = 0, *szFilePath = 0;
	IAIM *pIM = (IAIM *)iHandle;

	DPRINT("imservice jni => nSendFile...%x.\n", pIM);

	if(0 == pIM)
		return -1;

	if(AMNULL == (szContantID = GetTmpCszFromByteArray(env, contantID, 0)))
		return -1;

	if(AMNULL == (szFilePath = GetTmpCszFromByteArray(env, filePath, 0)))
	{
		ReleaseTmpCszFromByteArray(env, contantID, szContantID, 0);
		return -1;
	}

	iRetCode = IAIM_SendFile(pIM, szContantID, szFilePath, &iTaskId);
	DPRINT("imservice jni  ==> nSendFile ret: %d.\n!", iRetCode);

	ReleaseTmpCszFromByteArray(env, contantID, szContantID, 0);
	ReleaseTmpCszFromByteArray(env, filePath, szFilePath, 0);

	DPRINT("imservice jni  ==> nSendFile Done!");

	if (iRetCode == eAIM_RESULT_OK)
		return iTaskId;
	else
	{
		AMAssert(iRetCode < 0);
		return iRetCode;
	}
}

JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nReceiveFile
(JNIEnv *env, jobject obj, jint iHandle, jbyteArray contantID, jbyteArray objXml, jbyteArray filePath)
{
	AMInt32 iTaskId = 0, iRetCode = 0;
	AMChar *szContantID = 0, *szFilePath = 0, *szObjXml = 0;
	IAIM *pIM = (IAIM *)iHandle;

	DPRINT("imservice jni => nReceiveFile...%x.\n", pIM);

	if(0 == pIM)
		return -1;

	if(AMNULL == (szContantID = GetTmpCszFromByteArray(env, contantID, 0)))
		return -1;

	if(AMNULL == (szObjXml = GetTmpCszFromByteArray(env, objXml, 0)))
	{
		ReleaseTmpCszFromByteArray(env, contantID, szContantID, 0);
		return -1;
	}

	if(AMNULL == (szFilePath = GetTmpCszFromByteArray(env, filePath, 0)))
	{
		ReleaseTmpCszFromByteArray(env, objXml, szObjXml, 0);
		ReleaseTmpCszFromByteArray(env, contantID, szContantID, 0);
		return -1;
	}

	iRetCode = IAIM_ReceiveFile(pIM, szContantID, szObjXml, szFilePath, &iTaskId);
	DPRINT("imservice jni  ==> nReceiveFile ret: %d, taskID: %d.\n!", iRetCode, iTaskId);

	ReleaseTmpCszFromByteArray(env, contantID, szContantID, 0);
	ReleaseTmpCszFromByteArray(env, objXml, szObjXml, 0);
	ReleaseTmpCszFromByteArray(env, filePath, szFilePath, 0);

	DPRINT("imservice jni  ==> nReceiveFile Done!");

	if (iRetCode == eAIM_RESULT_OK)
		return iTaskId;
	else
	{
		AMAssert(iRetCode < 0);
		return iRetCode;
	}
}

JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nCancelTrans
(JNIEnv *env, jobject obj, jint iHandle, jint iTaskId)
{
	IAIM *pIM = (IAIM *)iHandle;
	if (pIM == 0)
		return -1;
	return IAIM_CancelTrans(pIM, iTaskId);
}

JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nCheckAuth
	(JNIEnv *env, jobject obj, jint iHandle, jint iAuthId, jbyteArray jbCode)
{
	IAIM *pIM = (IAIM *)iHandle;
	const AMChar *szCode = AMNULL;
	AMInt32 iRetCode = eAIM_RESULT_OK;
	
	DPRINT("%s >>>>>> Entering with Handle: 0x%x, AuthId: %d, jbCode: 0x%x\n", __FUNCTION__, iHandle, iAuthId, jbCode);

	if (!pIM || !iAuthId || !jbCode)
		return eAIM_RESULT_PARAM_ERROR;

	if(!(szCode = GetTmpCszFromByteArray(env, jbCode, 0)))
		return eAIM_RESULT_PARAM_ERROR;

	iRetCode = IAIM_CheckAuthCode(pIM, iAuthId, szCode);

	ReleaseTmpCszFromByteArray(env, jbCode, szCode, 0);

	return iRetCode;
}

JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nUpdateAuth
(JNIEnv *env, jobject obj, jint iHandle, jint iAuthId)
{
	IAIM *pIM = (IAIM *)iHandle;
	if (pIM == 0)
		return -1;
	return IAIM_UpdateAuthCode(pIM, iAuthId);
}

JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nCancelAuth
(JNIEnv *env, jobject obj, jint iHandle, jint iAuthId)
{
	IAIM *pIM = (IAIM *)iHandle;
	if (pIM == 0)
		return -1;
	return IAIM_CancelAuthCode(pIM, iAuthId);
}

JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nReLogin
(JNIEnv *env, jobject obj, jint iHandle)
{
	IAIM *pIM = (IAIM *)iHandle;
	if (pIM == 0)
		return -1;
	return IAIM_ReLogin(pIM);
}


JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetRemarkMsg
(JNIEnv *env, jobject obj, jint iHandle) {
	IAIM *pIM = (IAIM *)iHandle;
	jbyteArray baResult = AMNULL;
	AMInt32 iLen = 0;

	if (pIM == 0)
		return -1;
	if(!pIM->szRemarkMsg)
		return NULL;

	iLen = AMStrlen(pIM->szRemarkMsg);

	if(!iLen)
		return NULL;

	baResult = (*env)->NewByteArray(env, iLen);
	
	if(baResult) {
		(*env)->SetByteArrayRegion(env, baResult, 0, iLen, pIM->szRemarkMsg);
		(*env)->DeleteLocalRef(env, baResult);
	}

	return baResult;
}

JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetWebSession
(JNIEnv *env, jobject obj, jint iHandle) {
	IAIM *pIM = (IAIM *)iHandle;
	jbyteArray baResult = AMNULL;
	AMInt32 iLen = 0;

	if (pIM == 0)
		return -1;
	if(!pIM->szWebSession)
		return NULL;

	iLen = AMStrlen(pIM->szWebSession);

	if(!iLen)
		return NULL;

	baResult = (*env)->NewByteArray(env, iLen);

	if(baResult) {
		(*env)->SetByteArrayRegion(env, baResult, 0, iLen, pIM->szWebSession);
		(*env)->DeleteLocalRef(env, baResult);
	}

	return baResult;
}


JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetCurrentPhoneNum
(JNIEnv *env, jobject obj, jint iHandle) {
	IAIM *pIM = (IAIM *)iHandle;
	jbyteArray baResult = AMNULL;
	AMInt32 iLen = 0;

	if (pIM == 0)
		return -1;

	DPRINT("nGetCurrentPhoneNum-----------------phone status:%d, retcode:%d ", pIM->phoneNumStatus, pIM->phoneNumRetCode);

	if(!pIM->szPhoneNum)
	{
		DPRINT("nGetCurrentPhoneNum-----------------phone is null");
		return NULL;
	}

	iLen = AMStrlen(pIM->szPhoneNum);

	if(!iLen)
		return NULL;

	baResult = (*env)->NewByteArray(env, iLen);

	if(baResult) {
		(*env)->SetByteArrayRegion(env, baResult, 0, iLen, pIM->szPhoneNum);
		(*env)->DeleteLocalRef(env, baResult);
	}

	return baResult;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetWWBindStatus
* Signature: (I)I
*/
JNIEXPORT jlong JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetWWBindStatus
(JNIEnv *env, jobject obj, jint handle)
{
	IAIM	*pIm = (IAIM*)handle;
	AMInt64	nRet = 0;
	if(0 == pIm || 0 == pIm->pAcnt)
		return -1;

	nRet = pIm->pAcnt->eBindStatus;
	nRet = (nRet << 32) + pIm->pAcnt->uiBindIDLoginRetCode;
	DPRINT("nGetWWBindStatus: %ull",nRet);

	DPRINT("PrintContactList: bind group");
	PrintContactList((jint)pIm->pCntModel->pBindGrp);
	DPRINT("PrintContactList: black group");
	PrintContactList((jint)pIm->pCntModel->pBlkGrp);
	DPRINT("PrintContactList: strange group");
	PrintContactList((jint)pIm->pCntModel->pStrangerGrp);

	return nRet;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nGetWWBindID
* Signature: (I)I
*/
JNIEXPORT jbyteArray JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nGetWWBindID
(JNIEnv *env, jobject obj, jint handle)
{
	IAIM	*pIm = (IAIM*)handle;
	int iLen = 0;
	jbyteArray ret = 0; 

	if(0 == pIm)
		return NULL;

	iLen = AMStrlen(pIm->pAcnt->szBindID);
	if(0 == iLen)
		return NULL;

	if(NULL == (ret = (*env)->NewByteArray(env, iLen)))
		return NULL;

	(*env)->SetByteArrayRegion(env, ret, 0, iLen, pIm->pAcnt->szBindID);

	DPRINT("imservice jni nGetWWBindID Done!");
	return ret;
}

/*
* Class:     com_alibaba_wireless_imservice_ConnectionAdapter
* Method:    nWWBindIDLogin
* Signature: (I[B)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_ConnectionAdapter_nWWBindIDLogin
(JNIEnv *env, jobject obj, jint iHandle)
{
	AMChar *szBlkID = 0;
	IAIM *pIM = (IAIM*)iHandle;

	DPRINT("imservice jni About to nAddBlack!");

	if(0 == pIM)
		return;

	IAIM_BindIDLogin(pIM);

	DPRINT("imservice jni nWWBindIDLogin Done!");
}
