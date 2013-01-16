#include "IMService.h"
#include "AIM.h"
#include "AIMAccountModel.h"
#include "AIMUtil.h"
#include "AliJniLog.h"

extern void ReleaseTmpCszFromByteArray(JNIEnv *env, jbyteArray bary, char *csz, jboolean *isCopy);
extern AMChar *	GetTmpCszFromByteArray(JNIEnv *env, jbyteArray baray, jboolean *isCopy);


JavaVM	* theVM = AMNULL;
//JavaVM  * LemurJavaVM = NULL;
#ifdef TARGET_VMKIT
LEMUR_JAVA_VM_DEFINE(imservice);
#endif

jclass	clsJavaConnection = AMNULL;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	JNIEnv *env;

#ifdef TARGET_VMKIT
	JNI_LOGD("IMService","JNI_OnLoad 1");
	LEMUR_JAVA_VM_REGIST(imservice, jvm);
#endif


	JNI_LOGD("IMService","JNI_OnLoad 2");

	theVM = jvm; /* cache the JavaVM pointer */
	if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_2)) {
		JNI_LOGD("IMService","JNI_OnLoad 3");
		return JNI_ERR; /* JNI version not supported */
	}

	JNI_LOGD("IMService","JNI_OnLoad 4");

	return JNI_VERSION_1_2;
}

/*
* Class:     com_alibaba_wireless_imservice_IMService
* Method:    native_SetDatabasePath
* Signature: ([B)I
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_IMService_native_1SetDatabasePath
(JNIEnv *env, jclass cls, jbyteArray path)
{
	JNI_LOGD("IMService","1SetDatabasePath");

	char *pPath = NULL;
	if(AMNULL == (pPath = GetTmpCszFromByteArray(env, path, 0)))
		return;

	IAIM_SetGlobalDatabasePath(pPath);

	ReleaseTmpCszFromByteArray(env, path, pPath, 0);
}

/*
* Class:     com_alibaba_wireless_imservice_IMService
* Method:    native_IAccountModel_Create
* Signature: ()I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_IMService_native_1IAccountModel_1Create
(JNIEnv *env, jclass cls)
{
	int iResult = 0;

	JNI_LOGD("IMService","1IAccountModel_1IAccountModel_1Create");
	iResult =  (int)IAccountModel_Create();
	return iResult;
}

/*
* Class:     com_alibaba_wireless_imservice_IMService
* Method:    native_IAccountModel_Destroy
* Signature: (I)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_IMService_native_1IAccountModel_1Destroy
(JNIEnv *env, jclass cls, jint handle)
{
	IAccountModel *pAcntModel = (IAccountModel*)handle;
	if(0 == pAcntModel)
		return;

	JNI_LOGD("IMService","1IAccountModel_1Destroy");
	IAccountModel_Destroy(pAcntModel);
}

/*
* Class:     com_alibaba_wireless_imservice_IMService
* Method:    native_IAIM_Create
* Signature: ()I
*/
JNIEXPORT jint JNICALL Java_com_alibaba_wireless_imservice_IMService_native_1IAIM_1Create
(JNIEnv *env, jclass cls)
{
	IAIM *pIM = AMNULL;

	JNI_LOGD("IMService","1IAIM_1Create");

	if(eAIM_RESULT_OK != IAIM_Create(&pIM))
	{
		DPRINT("native_1IAIM_1Create..................Error!\n");
	}

	DPRINT("native_1IAIM_1Create..........Create IAIM OK! 0x%x\n", pIM);

	return (jint)pIM;
}

/*
* Class:     com_alibaba_wireless_imservice_IMService
* Method:    native_IAIM_Destroy
* Signature: (I)V
*/
JNIEXPORT void JNICALL Java_com_alibaba_wireless_imservice_IMService_native_1IAIM_1Destroy
(JNIEnv *env, jclass cls, jint iIM)
{
	IAIM *pIM = (IAIM*)iIM;

	JNI_LOGD("IMService","1IAIM_1Destroy");
	
	DPRINT("native_1IAIM_1Destroy.................About to Destroy 0x%x\n", pIM);
	IAIM_Destroy(pIM);
	DPRINT("native_1IAIM_1Destroy.................Destroy OK 0x%x\n", pIM);
}

/*
* Class:     com_alibaba_wireless_imservice_IMService
* Method:    nGetAccountHandles
* Signature: (I)[I
*/
JNIEXPORT jintArray JNICALL Java_com_alibaba_wireless_imservice_IMService_nGetAccountHandles
(JNIEnv *env, jclass cls, jint iAcntModleHandle)
{
	IAccountModel * pAcntModel = (IAccountModel*)iAcntModleHandle;
	jintArray iaryAcntHandles = 0;
	ListIter *pIter = 0;
	int *pElem = 0, idx = 0;

	JNI_LOGD("IMService","nGetAccountHandles");
	
	DPRINT("nGetAccountHandles.......................Begin!");
	
	if(0 == pAcntModel || 0 == pAcntModel->listAcnt.size)
	{
		return AMNULL;
	}

	DPRINT("nGetAccountHandles.................Acnt num: %d!", pAcntModel->listAcnt.size);

	if(AMNULL == (iaryAcntHandles = (*env)->NewIntArray(env, pAcntModel->listAcnt.size)))
	{
		return AMNULL;
	}
	
	if(AMNULL == (pElem = (*env)->GetPrimitiveArrayCritical(env, iaryAcntHandles, 0)))
	{
		return AMNULL;
	}

	pIter = create(ListIter, &pAcntModel->listAcnt);
	head(ListIter, pIter);
	idx = 0;
	do 
	{
		pElem[idx++] = (int)retrieve(ListIter, pIter);
		DPRINT("nGetAccountHandles...............%s", ((AIMAccount*)pElem[idx-1])->szID?((AIMAccount*)pElem[idx-1])->szID:"0");
	} while (!next(ListIter, pIter));
	destroy(ListIter, pIter);

	(*env)->ReleasePrimitiveArrayCritical(env, iaryAcntHandles, pElem, 0);

	DPRINT("nGetAccountHandles.......................End!");

	return iaryAcntHandles;
}
