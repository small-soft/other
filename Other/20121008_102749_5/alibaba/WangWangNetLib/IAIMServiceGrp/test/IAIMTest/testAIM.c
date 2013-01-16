#include "IAIM.h"
#include "IAIMContact.h"
#include "IAIMSession.h"
#include "IAIMGroup.h"

#include <iostream>
#include <string>
#include <AMThread.h>
#include <AMTimer.h>

#include "CallbackAdapterTest.h"

using namespace std;

AMHandle	hIM = AMNULL;

AMPVoid pvArg[2] = {AMNULL, AMNULL};

AIM_CALLBACK	testAIMCB = {
	pvArg,
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
	NULL,//OnRspSendMsg ,
	NULL,//OnRspChgPresence ,
	NULL,//
	NULL,
};

void login()
{
	cout<<"\t\t\tLogin:\n";
	string strCntID, strPwd;
	AMHandle	*pAcnt = 0;
	AMInt32		iSize = 0;
	static int presence = 1;

	if(AMNULL == hIM)
	{
		IAIM_Create((AMHandle*)&hIM);
		pvArg[1] = hIM;
		IAIM_RegisterListener((AMHandle*)hIM, &testAIMCB);
	}

	int iType;
	cout<<"Input Login Type(0 for new Id, 1 for History Account, 2 for new Token):";
	cin>>iType;
	cout<<"Input IP_CONFIG(0 for real, 1 for test):";
	int iTest;
	cin>>iTest;
	AIM_ACCOUNT_SETTING setting;
	setting.eDefaultPresence = (AIM_PRESENCE)1;
	setting.bMute = setting.bSavePwd = setting.bViberate = 1;
	if(0 == iType)
	{
		cout<<"Input account ID: ";
		cin>>strCntID;
		if(strCntID == "0")
			strCntID = "cnaliyunzq@aliyun.com";
		else if(strCntID == "1")
			strCntID = "cnaliyunpwtest001";
		else if(strCntID == "2")
			strCntID = "cnaliyunpwtest002@aliyun.com";
		else if(strCntID == "3")
			strCntID = "cnaliyunpwtest003@aliyun.com";
		else if(strCntID == "4")
			strCntID = "cnaliyunimtest1@aliyun.com";
		cout<<"Input account pwd: ";
		cin>>strPwd;
		if(strCntID == "cnaliyunzq@aliyun.com")
			strPwd = "L0SaI1UBJ23zY67ghmFOZulDT4AfntHkqExG";
		else if(strCntID == "cnaliyunpwtest001")
			strPwd = "9Fv03WEIC5xhzwA81KMyJuQTnRsifgL4qpjr";
		else if(strCntID == "cnaliyunpwtest002@aliyun.com")
			strPwd = "aKrEcbuC3qji4RIFTftgD857PkvQo0zl2JOV";
		else if(strCntID == "cnaliyunpwtest003@aliyun.com")
			strPwd = "FbIhztyf24NWQ76OcZ1CgKAPBsGLmajHEJiX";
		else if(strCntID == "cnaliyunimtest1@aliyun.com")
			strPwd = "N9LMpy1fhQrcUG7iDXo0T8PuI25gHeESzwAb";
		else if(strCntID == "cnaliyunfjqtest001")
			strPwd = "tlSmTBgcZMLE6OjWIbaY91nCzD8de0KfJ735";
		else if(strCntID == "cnaliyunpwtest007@aliyun.com")
			strPwd = "oVQpjunJI0efvm9wAdHaTqCU1x765G4MrWFy";
		IAIM_Login(hIM, strCntID.c_str(), strPwd.c_str(), AMFALSE, setting, iTest);
	}
	else if(1 == iType)
	{
		cout<<"Input account ID: ";
		cin>>strCntID;
		IAIM_Login(hIM, strCntID.c_str(), 0, AMTRUE, setting, iTest);
	}
	else
	{
		IAIM_Login(hIM, "cntaobaonikon", "79b2cc5386a3da9316bf18d50e7eed25", AMTRUE, setting, iTest);
	}
}

AMPVoid _logoutFunc(AMPVoid arg)
{
	AMHandle him  = (AMHandle)arg;
	IAIM_Logout(him);
	IAIM_Destroy(him);
	return AMNULL;
}

void logout()
{
	AMThread tid;
	cout<<"\t\t\tLogout:\t\n";
	AMThreadCreate(&tid, AMNULL, _logoutFunc, hIM);
	AMThreadDetach(tid);
	hIM = AMNULL;
}

void sendMsg()
{
	cout<<"\t\t\tsendMsg"<<endl;
	string strCnt, strContent;
	cout<<"Input Contact ID:";
	cin>>strCnt;
	cout<<"Input Msg Content:";
	cin>>strContent;
	IAIM_SendMessage(hIM, strCnt.c_str(), strContent.c_str());
}

void sendU2UMsg()
{
	cout<<"\t\t\tsendU2UMsg"<<endl;
	int type;
	string strCnt, strContent;
	cout<<"Input Contact ID:";
	cin>>strCnt;
	cout<<"Input U2U type:";
	cin>>type;
	cout<<"Input Msg Content:";
	cin>>strContent;
	IAIM_SendU2UMessage(hIM, strCnt.c_str(), strContent.c_str(), type);
}

void addContact()
{
	cout<<"\t\t\taddContact"<<endl;
	string strCnt;
	cout<<"Input Contact ID: ";
	cin>>strCnt;
	IAIM_AddContact(hIM, strCnt.c_str());
}

void addBlack()
{
	cout<<"\t\t\taddBlack"<<endl;
	string strCnt;
	cout<<"Input Contact ID: ";
	cin>>strCnt;
	IAIM_AddBlack(hIM, strCnt.c_str());
}
void removeContact()
{
	cout<<"\t\t\tremoveContact"<<endl;
	string strCnt;
	cout<<"Input Contact ID: ";
	cin>>strCnt;
	IAIM_RemoveContact(hIM, strCnt.c_str());
}
void removeBlack()
{
	cout<<"\t\t\tremoveBlack"<<endl;
	string strCnt;
	cout<<"Input Contact ID: ";
	cin>>strCnt;
	IAIM_RemoveBlack(hIM, strCnt.c_str());
}
void sendVerify()
{
	cout<<"\t\t\tsendVerify"<<endl;
	string strCnt, strDspName, strContent;
	cout<<"Input Contact ID: ";
	cin>>strCnt;
	cout<<"Input Verify Info: ";
	cin>>strContent;
	cout<<"Input Display Name: ";
	cin>>strDspName;
	IAIM_SendVerify(hIM, strCnt.c_str(), strContent.c_str());
}
void agreeAdd()
{
	cout<<"\t\t\tagreeAdd"<<endl;
	string strCnt, strContent;
	cout<<"Input Contact ID: ";
	cin>>strCnt;
	IAIM_AcceptAddContact(hIM, strCnt.c_str());
}
void rejectAdd()
{
	cout<<"\t\t\trejectAdd"<<endl;
	string strCnt, strContent;
	cout<<"Input Contact ID: ";
	cin>>strCnt;
	cout<<"Input Reject Info: ";
	cin>>strContent;
	IAIM_RejectAddContact(hIM, strCnt.c_str(), strContent.c_str());
}
void chgStatus()
{
	static int Status = 0;
	cout<<"\t\t\tchgStatus"<<endl;
	cin>>Status;

	IAIM_ChangePresence(hIM, (AIM_PRESENCE)Status);
}

void chgVerify()
{
	int iVerify = 0;
	cout<<"\t\t\tchgVerify"<<endl;
	cout<<"Input the verify type(0 for no, 1 for yes): ";
	cin>>iVerify;
	IAIM_ChangeVerify(hIM, iVerify);
}

void delMessage()
{
	cout<<"\t\t\tdelMessage"<<endl;
	cout<<"Input the contact Id: "<<endl;
	string strContact;
	cin>>strContact;
	cout<<"Input the message Id: "<<endl;
	int iID = 0;
	cin>>iID;

	AMHandle	hSes = AMNULL;

	if(eAIM_RESULT_OK != IAIM_OpenSession(hIM, strContact.c_str(), &hSes))
	{
		cout<<"OpenSession Failed............................Failed!"<<endl;
		return;
	}

	IAIMSession_RemoveMsg(hSes, iID);

	IAIM_CloseSession(hIM, hSes);
}


void modifyFastReply()
{
	cout<<"\t\t\tmodifyFastReply\n";
	int iID = 0;
	cout<<"Input the id: ";
	cin>>iID;
	string strReply;
	cout<<"Input the reply: ";
	cin>>strReply;
	IAIM_UpdatePredefMsg(hIM, iID, strReply.c_str());
}

void addFastReply()
{
	cout<<"\t\t\tAdd FastReply\n";
	string strReply;
	cout<<"Input the reply: ";
	cin>>strReply;
	IAIM_AddPredefMsg(hIM, strReply.c_str(), AMNULL);
}

void removeFastReply()
{
	cout<<"\t\t\tRemove FastReply\n";
	int iID = 0;
	cout<<"Input the id: ";
	cin>>iID;
	IAIM_RemovePredefMsg(hIM, iID);
}

void getFastReply()
{
	cout<<"\t\t\tGetFastReply\n";
	AMHandle	*phMsgs = AMNULL;
	AMInt32		iSize = 0;

	IAIM_GetPredefMsgs(hIM, &phMsgs, &iSize);

	if(!iSize)
		return;

	AMHandle hMsg = AMNULL;

	for(int i=0; i<iSize; i++)
	{
		hMsg = phMsgs[i];
	}

	IAIM_ReleasePredefMsgs(hIM, phMsgs, iSize);
}


void removeRecent()
{
	cout<<"\t\t\tremoveRecent:\n";
	string strRecentID;
	cout<<"Input contactID(\"all\" to clear recent_list):";
	cin>>strRecentID;
	if(strRecentID == "all")
		IAIM_RemoveRecent(hIM, AMNULL);
	else
		IAIM_RemoveRecent(hIM, strRecentID.c_str());
}

void chgSignature()
{
	cout<<"\t\t\tchgSignature:\n";
	string strSig;
	cout<<"Input new signature:";
	cin>>strSig;
	if(strSig == "clear")
		IAIM_ChangeSignature(hIM, "");
	else
		IAIM_ChangeSignature(hIM, strSig.c_str());
}

void getPeerVerifyConfig()
{
	cout<<"\t\t\tgetPeerVerifyConfig:\n";
	string strContact;
	cout<<"Input Contact ID: ";
	cin>>strContact;
	IAIM_GetVerify(hIM, strContact.c_str());
}

void getUDBProfile()
{
	cout<<"\t\t\tgetUDBProfile:\n";
	string strContact;
	cout<<"Input Contact ID: ";
	cin>>strContact;
	IAIM_GetProfile(hIM, strContact.c_str());
}

void getContactMemo()
{
	cout<<"\t\t\tgetContactMemo:\n";
	string strContact;
	cout<<"Input Contact ID: ";
	cin>>strContact;
	IAIM_GetMemo(hIM, strContact.c_str());
}

void getSignature()
{
	cout<<"\t\t\tgetSignature:\n";
	cout<<"input contact Id:";
	string strId;
	cin>>strId;
	IAIM_GetSignature(hIM, "cntaobaocmykxyzlab\1cntaobaolelosh\1cntaobaonikon", 3);
}

void getPortrait()
{
	cout<<"\t\t\tgetPortrait:\n";
	cout<<"input contact Id:";
	string strId;
	cin>>strId;
	IAIM_GetPortrait(hIM, strId.c_str());
	IAIM_GetPortrait(hIM, strId.c_str());
	IAIM_GetPortrait(hIM, strId.c_str());
	IAIM_GetPortrait(hIM, strId.c_str());
	IAIM_GetPortrait(hIM, strId.c_str());
	IAIM_GetPortrait(hIM, strId.c_str());
	IAIM_GetPortrait(hIM, strId.c_str());
	IAIM_GetPortrait(hIM, strId.c_str());
	IAIM_GetPortrait(hIM, strId.c_str());
}

static AMPVoid _destroyFunc(AMPVoid im)

{
	AMHandle hImTmp = (AMHandle)im;
	if(AMNULL == hImTmp)
		return AMNULL;

	IAIM_Destroy(hImTmp);

	return AMNULL;
}

void testDestroy()
{
	AMThread tid;
	for(int i=0; i<10; i++)
	{
		AIM_ACCOUNT_SETTING setting;
		AMSleep(150);
		AMThreadCreate(&tid, AMNULL, _destroyFunc, hIM);
		if(AME_THREAD_SCUESS != AMThreadDetach(tid))
			cout<<"\n\n\n\nDetach Error!\n\n\n";
		IAIM_Create((AMHandle*)&hIM);
		setting.eDefaultPresence = (AIM_PRESENCE)1;
		setting.bMute = setting.bSavePwd = setting.bViberate = 1;
		IAIM_Login(hIM, "abc123_ËÄ¼¾", 0, AMTRUE, setting, 0);
	}
}

void fastLogin()
{
	cout<<"\t\t\tFastLogin cmykxyzlab\t\t\n";
	if(AMNULL == hIM)
	{
		IAIM_Create((AMHandle*)&hIM);
		pvArg[1] = hIM;
		IAIM_RegisterListener((AMHandle*)hIM, &testAIMCB);
	}
	AIM_ACCOUNT_SETTING setting;
	setting.eDefaultPresence = (AIM_PRESENCE)1;
	setting.bMute = setting.bSavePwd = setting.bViberate = 1;
	IAIM_Login(hIM, "cntaobaolelosh", "1234qwer", AMFALSE, setting, 0);
}

void chgSrvMode()
{
	cout<<"\t\t\tChange Server Mode: \t\t\n";
	int status;
	cout<<"Input status(0 or 1): ";
	cin>>status;
	IAIM_ChangeSrvMode(hIM, status);
}

void subscribe()
{
	cout<<"\t\t\tSubscribe contact Status: \t\t\n";
	string strContacts;
	cout<<"Input contactId:";
	cin>>strContacts;
	unsigned int uiCount;
	cout<<"Input the number of contactIds:";
	cin>>uiCount;
	const char * pTmp = strContacts.c_str();
	IAIM_SubscribePresence(hIM, &pTmp, 1);
}

void removeMsg()
{
	cout<<"\t\t\tremoveMsg:\t\t\n";
	int iMsgId;
	cout<<"Input message Id: ";
	cin>>iMsgId;
	AMHandle hSes = AMNULL;
	IAIM_OpenSession(hIM, "systemSes", &hSes);
	IAIMSession_RemoveMsg(hSes, iMsgId);
}

void chgFlag()
{
	cout<<"\t\t\tchgFlag:\t\t\n";
	cout<<"Input  mute, viberate, save, presence:";
	int iVib, iMute, iSave, iPresence;
	cin>>iMute>>iVib>>iSave>>iPresence;
	AIM_ACCOUNT_SETTING setting = {(AIM_PRESENCE)iPresence, iSave, iMute, iVib};
	IAIM_UpdateSetting(hIM, &setting, 0);
}

void sendFile()
{
	cout<<"\t\t\tsendFile:\t\t\n";
	string strContact;
	cout<<"Input ContactId: ";
	cin>>strContact;
	string strFileName;
	cout<<"Input file name:";
	cin>>strFileName;
	IAIM_SendFile(hIM, strContact.c_str(), strFileName.c_str(), 0);
}

void recvFile()
{
	cout<<"\t\t\trecvFile:\n";
	string strContact;
	cout<<"Input ContactId: ";
	cin>>strContact;
	string strFileXml;
	cout<<"Input file XML: ";
	cin>>strFileXml;
	cout<<"Input file name to save:";
	string strFileName;
	cin>>strFileName;
	IAIM_ReceiveFile(hIM, strContact.c_str(), strFileXml.c_str(), strFileName.c_str(), 0);
}

void updateAuth()
{
	cout<<"\t\t\t updateAuth:\n";
	cout<<"Input authId: ";
	int iAuthId = 0;
	cin>>iAuthId;
	IAIM_UpdateAuthCode(hIM, iAuthId);
}

void cancelAuth()
{
	cout<<"\t\t\t cancelAuth:\n";
	cout<<"Input authId: ";
	int iAuthId = 0;
	cin>>iAuthId;
	IAIM_CancelAuthCode(hIM, iAuthId);
}

void checkAuth()
{
	cout<<"\t\t\t checkAuth:\n";
	cout<<"Input authId: ";
	int iAuthId = 0;
	cin>>iAuthId;
	cout<<"Input Code: ";
	string strCode;
	cin>>strCode;
	IAIM_CheckAuthCode(hIM, iAuthId, strCode.c_str());
}

void blockStranger()
{
	cout<<"\t\t\t blockStranger: ";
	AMInt32 iBlock;
	cout<<"Block stranger (0: no, 1:yes):";
	cin>>iBlock;
	IAIM_UpdateSetting(hIM, NULL, iBlock);
}

void printGrps()
{
	cout<<"\t\t\t printGrps: ";
	AMHandle *pGrps = AMNULL;
	AMInt32 iCount = 0;
	AMInt64 iGrpId = 0;
	const AMChar	*szGrpName = AMNULL;
	IAIM_GetTopGroups(hIM, &pGrps, &iCount);
	for(int i=0; i<iCount; i++)
	{
		IAIMGroup_GetID(pGrps[i], &iGrpId);
		IAIMGroup_GetName(pGrps[i], &szGrpName);
		cout<<"\n"<<i<<"\t grpName: "<<szGrpName<<"\t id: "<<iGrpId;
	}
	IAIM_ReleaseTopGroups(hIM, pGrps, iCount);
	cout<<endl;
}

void printCnts()
{
	cout<<"\t\t\t printCnts: ";
	cout<<"\nInput GroupId";
	AMInt64 iGrpId = 0;
	cin>>iGrpId;
	AMHandle hGrps = AMNULL;
	IAIM_GetGroupByID(hIM, iGrpId, &hGrps);
	if(hGrps)
	{
		AMHandle *phCnts = AMNULL;
		AMInt32 iCount = 0;
		const AMChar	*szCntName = AMNULL;
		IAIMGroup_GetContacts(hGrps, AMFALSE, &phCnts, &iCount);
		for(int i=0; i<iCount; i++)
		{
			IAIMContact_GetID(phCnts[i], &szCntName);
			cout<<"\n"<<i<<"\t cntID: "<<szCntName;
		}
		cout<<endl;
	}
}

void testAuth()
{
	IAIM_AddContact(hIM, "cntaobaoachi");
	IAIM_SendVerify(hIM, "cntaobaoachi", "info");
}

void testRelogin()
{
	IAIM_ReLogin(hIM);
}

void loginWWBindID()
{
	IAIM_BindIDLogin(hIM);
}

void getWWBindStatus()
{
	//IAIM	*pIm = (IAIM*)hIM;
	AMInt64	nRet = 0;
	//nRet = pIm->pAcnt->eBindStatus;
	//nRet = nRet << 32 + pIm->pAcnt->uiBindIDLoginRetCode;
	cout << "status: " << nRet <<endl;
}

void getWWBindID()
{
	//IAIM	*pIm = (IAIM*)hIM;
	//cout << "BindID: " << pIm->pAcnt->szBindID <<endl;
	cout << "BindID: " <<endl;
}

string info[] = { "printinfo", "login", "subscribe", "logout"
, "printGrps", "printCnts", "sendMsg", "sendU2UMsg", "addContact", "removeContact"
, "addBlack", "removeBlack", "removeRecent", "sendVerify", "rejectAdd"
, "agreeAdd", "chgStatus", "chgVerify", "chgSignature", "delMessage"
, "getFastReply", "removeFastReply", "addFastReply", "modifyFastReply"
, "getPeerVerifyConfig", "getUDBProfile", "getSignature", "testDestroy"
, "fastLogin", "chgSrvMode", "getContactMemo", "getPortrait", "removeMsg"
, "chgFlag", "sendFile", "recvFile", "updateAuth", "cancelAuth"
, "checkAuth", "blockStranger", "testAuth", "testRelogin", "loginWWBindID", "getWWBindStatus", "getWWBindID"};

void printinfo()
{
	for(int i=0; i<sizeof(info)/sizeof(info[0]); i++)
	{
		cout<<i<<": "<<info[i]<<"\t\t";
		if(i%2 == 1)
			cout<<endl;
	}
}

void (*command[])(void) = { printinfo, login, subscribe, logout
, printGrps, printCnts, sendMsg, sendU2UMsg, addContact, removeContact
, addBlack, removeBlack, removeRecent, sendVerify, rejectAdd
, agreeAdd, chgStatus,chgVerify, chgSignature, delMessage
, getFastReply, removeFastReply, addFastReply, modifyFastReply
, getPeerVerifyConfig, getUDBProfile, getSignature, testDestroy
, fastLogin, chgSrvMode, getContactMemo, getPortrait, removeMsg
, chgFlag, sendFile, recvFile, updateAuth, cancelAuth
, checkAuth, blockStranger, testAuth, testRelogin, loginWWBindID, getWWBindStatus, getWWBindID};

void test_IM()
{
	int i = -1;
	printinfo();
	cout<<"Input the Command ID:";
	cin>>i;
	while(i>=0 && i<sizeof(command)/sizeof(command[0]))
	{
		command[i]();
		cout<<"Input the Command ID:";
		cin>>i;
	}
	if(hIM)
		IAIM_Destroy(hIM);
}