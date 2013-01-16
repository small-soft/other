#ifndef __IAIM_H__
#define	__IAIM_H__

#include "IAIMCallback.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* @brief				create an AliIM
	* @param phIM			[in/out] return the AliIM handle.
	* @return				error code.
	*/
	AIM_RESULT IAIM_Create(AMHandle *phIM);
	/**
	* @brief				destroy a AliIM
	*/
	AIM_RESULT IAIM_Destroy(AMHandle hIM);

	/**
	* @brief				Register Callback.
	*/
	AIM_RESULT IAIM_RegisterListener( AMHandle hIM, const AIM_CALLBACK *listener );

	/**
	* @brief				unregister call back
	*/
	AIM_RESULT IAIM_UnregisterListener( AMHandle hIM, const AIM_CALLBACK *listener );

	/**
	* @brief				return a array of history accounts.
	* @param ppAcntHandles	[in/out] return a array of Account Handles, which must be released by IAIM_ReleaseAccounts
	* @param piCount		[in/out] return the array length
	*/
	AIM_RESULT IAIM_GetAccounts(AMHandle hIM, AMHandle **pphAcntArray, AMInt32 *piCount);

	/**
	* @brief				release the array returned by GetHistoryAccounts
	*/
	AIM_RESULT IAIM_ReleaseAccounts( AMHandle hIM, AMHandle *phAcntArray, AMInt32 iArraySize);

	/**
	* @brief				remove an account from history accounts.
	* @param bCleanData		clear local data associated with this account.
	*/
	AIM_RESULT IAIM_RemoveAccount(AMHandle hIM, const AMChar *szAccountID, AMBool bCleanData);

	/**
	* @brief				login with account id, and password
	* @param szID			long ID
	* @param szPwd			AMNULL allowed.
	* @param bNotPlain		whether the szPwd is NOT plain.
	* @param setting		will be record as default setting of the account, if login success.
	* @more					when logining a history account whose setting.bSavePwd is AMTRUE, 
	*						one can pass AMNULL as szPwd and AMFALSE as bNotPlain.
	* @callback				OnRspLogin
	*/
	AIM_RESULT IAIM_Login(AMHandle hIM, const AMChar *szID, const AMChar *szPwd, AMBool bNotPlain, 
							AIM_ACCOUNT_SETTING setting, AMBool bTest);

	/**
	* @brief				login with account id, and password
	* @param szID			long ID
	* @param szPwd			AMNULL allowed.
	* @param bNotPlain		whether the szPwd is NOT plain.
	* @param setting		will be record as default setting of the account, if login success.
	* @more					when logining a history account whose setting.bSavePwd is AMTRUE, 
	*						one can pass AMNULL as szPwd and AMFALSE as bNotPlain.
	* @callback				OnRspLogin
	*/
	AIM_RESULT IAIM_LoginEx(AMHandle hIM, const AMChar *szID, const AMChar *szPwd, AMBool bNotPlain, 
							AIM_ACCOUNT_SETTING setting, AMBool bTest, const AMChar *latestOMVersion);

	/**
	* @brief				logout.
	*/
	AIM_RESULT IAIM_Logout(AMHandle hIM);
	/*
	 * @brief				request the hIM to force ReLogin( abort the current connection and create a new one, and ReLogin)
	 */
	AIM_RESULT IAIM_ReLogin(AMHandle hIM);

	/**
	* @brief				change presence
	* @brief				OnRspChgPresence
	*/
	AIM_RESULT IAIM_ChangePresence(AMHandle hIM, AIM_PRESENCE ePresence);

	/**
	* @brief				change verify config.
	* @param ucType			0 : do not need verify when somebody is trying to add u as a contact.
	*						1 : need verify
	*						2 : discard all add contact request.
	* @callback				OnRspChgVerify
	*/
	AIM_RESULT IAIM_ChangeVerify(AMHandle hIM, AMUChar ucType);

	/**
	* @brief				change signature.
	* @param szSignature	AMNULL to clear signature
	* @callback				OnRspChgSignature
	*/
	AIM_RESULT IAIM_ChangeSignature(AMHandle hIM, const AMChar *szSignature);

	/**
	* @brief				add contact
	* @param szContactID	long ID
	* @callback				OnRspAddContact
	*/
	AIM_RESULT IAIM_AddContact(AMHandle hIM, const AMChar *szContactID);

	/**
	* @brief				remove contact
	* @param szContactId	long ID
	* @callback				OnRemoveContact
	*/
	AIM_RESULT IAIM_RemoveContact(AMHandle hIM, const AMChar *szContactID);

	/**
	* @brief				send request verify message.
	* @param szContactID	long ID
	* @param szMsg			hello message
	*/
	AIM_RESULT IAIM_SendVerify(AMHandle hIM, const AMChar *szContactID, const AMChar *szMsg);

	/**
	* @brief				accept to be added as a contact
	* @param szContactID	long ID
	* @callback				OnRspAccept
	*/
	AIM_RESULT IAIM_AcceptAddContact(AMHandle hIM, const AMChar *szContactID);

	/**
	* @brief				reject to be added as a contact by szContactID
	* @param szContactID	long ID
	* @param szMsg			reject reason.
	*/
	AIM_RESULT IAIM_RejectAddContact(AMHandle hIM, const AMChar *szContactID, const AMChar *szMsg);

	/**
	* @brief				add black
	* @param szContactID	long ID
	* @callback				OnAddBlack
	*/
	AIM_RESULT IAIM_AddBlack(AMHandle hIM, const AMChar *szContactID);

	/**
	* @brief				remove black
	* @param szContactID	long ID
	* @callback				OnRemoveBlack
	*/
	AIM_RESULT IAIM_RemoveBlack(AMHandle hIM, const AMChar *szBlackID);

	/**
	* @brief				change E_Customer service mode.
	* @param ucStatus		0: not hung up; 1: hung up
	* @callback				OnChgSrvMode
	*/
	AIM_RESULT IAIM_ChangeSrvMode( AMHandle hIM, AMUChar ucStatus);

	/**
	* @brief				get user's verify config.
	* @param szContact		long ID
	* @callback				OnGetVerify
	*/
	AIM_RESULT IAIM_GetVerify(AMHandle hIM, const AMChar *szContact);

	/**
	* @brief				get user's detail information.
	* @param szContact		long ID
	* @callback				OnGetProfile
	*/
	AIM_RESULT IAIM_GetProfile(AMHandle hIM, const AMChar *szContact);

	/**
	* @brief				search user
	* @param szKeyWord		key word for search
	* @callback				OnSearchUser
	*/
	AIM_RESULT IAIM_SearchUser(AMHandle hIM, const AMChar *szKeyWord);

	/**
	* @brief				get user's degree
	* @param szContact		long ID
	* @callback				OnGetDegree
	*/
	AIM_RESULT IAIM_GetDegree(AMHandle hIM, const AMChar *szContact);

	/**
	* @brief				get your contact memo which marked by yourself
	* @callback				OnGetMemo
	*/
	AIM_RESULT	IAIM_GetMemo( AMHandle hIM, const AMChar *szContactID);

	/**
	* @brief				asynchronous method, get user's portrait
	* @callback				OnGetPortrait
	*/
	AIM_RESULT	IAIM_GetPortrait( AMHandle hIM, const AMChar *szContactID);

	/**
	* @brief				get user's signature.
	* @param szContactIds	multiple long IDs, with '\1' as separator
	* @param iCount			the number of IDs.
	* @callback				OnGetSignature
	*/
	AIM_RESULT IAIM_GetSignature( AMHandle hIM, const AMChar *szContactIds, AMUInt32 iCount);


	/**
	* @brief				Subscribe users' presence.
	* @param szContactIds	multiple long IDs
	* @param iCount			the number of IDs.
	* @callback				OnUpdate
	*/
	AIM_RESULT IAIM_SubscribePresence( AMHandle hIM, const AMChar **pszContactIds, AMUInt32 iCount);

	/**
	* @brief				send a message to a contact
	* @param szContactID	long ID
	* @param szMsg
	* @callback				//OnSendMsg			Not supported yet...
	*/
	AIM_RESULT IAIM_SendMessage( AMHandle hIM, const AMChar *szContactID, const AMChar *szMsg);
	AIM_RESULT IAIM_SendMessageEx( AMHandle hIM, const AMChar *szContactID, const AMChar *szMsg, AMInt32 appendMobileImMsg);

//	AIM_RESULT IAIM_SendFile( AMHandle hIM, const AMChar *szContactID, const AMChar *szFile);
	/**
	* @brief				send a message to a session
	* @param hSession		
	* @param szMsg			
	* @callback				//OnSendSessionMsg	Not Supported yet.
	*/
	AIM_RESULT IAIM_SendSessionMsg(AMHandle hIM, AMHandle hSession, const AMChar *szMsg);	

	/**
	* @brief				get current login account
	*/
	AIM_RESULT IAIM_GetCurrentAccount(AMHandle hIM, AMHandle *phAccount);

	/**
	* @brief				get the top groups.
	* @param pphGroupArray	[in/out] return an array of group handles, which should be released using IAIM_ReleaseTopGroups
	* @param piSize			[in/out] return the array size.
	*/
	AIM_RESULT IAIM_GetTopGroups( AMHandle hIM, AMHandle **pphGroupArray, AMInt32 *piSize);

	/**
	* @brief				release the array returned by IAIM_GetTopGroups
	*/
	AIM_RESULT IAIM_ReleaseTopGroups( AMHandle hIM, AMHandle *phGroupArray, AMInt32 iArraySize );

	/**
	* @brief				get a identified group
	*/
	AIM_RESULT IAIM_GetGroupByID(AMHandle hIM, AMInt64 i64GrpID, AMHandle *phGroup);
	/**
	* @brief				get a identified contact, 
	*/
	AIM_RESULT IAIM_GetContactByID(AMHandle hIM, const AMChar *szCntID, AMHandle *phContact);

	/**
	* @brief				remove recent contact
	* @param szContactID	long ID to remove a particular recent contact
	*						AMNULL to clear all recent contacts.
	*/
	AIM_RESULT IAIM_RemoveRecent(AMHandle hIM, const AMChar *szContactID);

	/**
	* @brief				remove stranger
	* @param szContactID	long ID to remove a particular stranger
	*						AMNULL to clear all strangers.
	*/
	AIM_RESULT IAIM_RemoveStranger(AMHandle hIM, const AMChar *szContactID);

	/**
	* @brief				Open a session
	* @param szContactID	long ID: to open a contact session.
	*						SYS_SES_ID: to open a system session.
	*/	
	AIM_RESULT IAIM_OpenSession(AMHandle hIM, const AMChar *szContactID, AMHandle *phSession);
	
	/**
	* @brief				Close a Session
	*/
	AIM_RESULT IAIM_CloseSession(AMHandle hIM, AMHandle hSession);

	/**
	* @brief				Get all predefined messages
	* @param pphMsgArray	[in/out] return an array of message handles, which should be released by IAIM_ReleasePredefMsgs
	* @param piSize			[in/out] return the array size
	*/
	AIM_RESULT IAIM_GetPredefMsgs(AMHandle hIM, AMHandle **pphMsgArray, AMInt32 *piSize);
	/**
	* @brief				Release the array returned by 
	*/
	AIM_RESULT IAIM_ReleasePredefMsgs(AMHandle hIM, AMHandle *phMsgArray, AMInt32 iSize);

	/**
	* @brief				remove a predefined message
	* @param id				msg id
	*/
	AIM_RESULT IAIM_AddPredefMsg(AMHandle hIM, const AMChar *szBody, AMInt64 *pi64ID);
	/**
	* @brief				Update a predefined Msg
	* @param i64ID			msg id, 0 to remove all predefined messages
	* @param szBody			new body
	*/
	AIM_RESULT IAIM_RemovePredefMsg(AMHandle hIM, AMInt64 id);
	/**
	* @brief				Add a predefined Msg
	* @param szBody			msg body
	* @param pi64ID			[in/out] return the id of the new msg.
	*/
	AIM_RESULT IAIM_UpdatePredefMsg(AMHandle hIM, AMInt64 i64ID, const AMChar *szBody);

	/**
	* @brief				delete all message.
	*/
	AIM_RESULT IAIM_DeleteAllMsg(AMHandle hIM);

	/**
	* @brief				delete a message by id.	//use 
	*/
	AIM_RESULT IAIM_DeleteMsgById( AMHandle hIM, AMInt64 i64ID );		

	/**
	* @brief				mark a message by id.
	*/
	AIM_RESULT IAIM_MarkMsgReadById( AMHandle hIM, AMInt64 i64ID );

	/*
	 *	@brief				update the settings of currentAccount.
	 *		if pSetting==null, bBlockStranger is considered.
	 */
	AIM_RESULT IAIM_UpdateSetting(AMHandle hIM, AIM_ACCOUNT_SETTING *pSetting, AMBool bBlockStranger);

	/*
	 *	@brief				start a task to receive file
	 *	@param szContactId	the sender of the file.
	 *	@param szObjXml		the descriptor(XML) of the file.
	 *	@param szFileName	the destination file for the file.
	 *	@param piTaskId		[in/out] return an identifier for the task.
	 */
	AIM_RESULT IAIM_ReceiveFile(AMHandle hIM, const AMChar *szContactId, const AMChar *szObjXml, 
								const AMChar *szFileName, AMInt32 *piTaskId);

	/*
	 *	@brief				start a task to send file.
	 *	@param szContactId	the receiver of the file.
	 *	@param szPathName	the pathName of the file to send.	'/' is used as delimiter.
	 *	@param piTaskId		[in/out] return an identifier for the task.
	 */
	AIM_RESULT IAIM_SendFile(AMHandle hIM, const AMChar *szContactId, const AMChar *szPathName, AMInt32 *piTaskId);

	/*
	 *	@brief				cancel the download task
	 */
	AIM_RESULT IAIM_CancelTrans(AMHandle hIM, AMInt32 iTaskId);

	/*
	 *	@brief				validate the auth code.
	 */
	AIM_RESULT IAIM_CheckAuthCode(AMHandle hIM, AMInt32 iAuthId, const AMChar *szCode);

	/*
	 *	@brief				update the auth code.
	 */
	AIM_RESULT IAIM_UpdateAuthCode(AMHandle hIM, AMInt32 iAuthId);

	/*
	 *	@brief				cancel the auth code.
	 */
	AIM_RESULT IAIM_CancelAuthCode(AMHandle hIM, AMInt32 iAuthId);

	/*	by pw; 2011-7-12
	*	@brief				send 2th degree protocol message.
	*/
	AIM_RESULT IAIM_SendU2UMessage( AMHandle hIM, const AMChar *szContactID, const AMChar *szMsg, AMInt32 msgType );

	/*	by pw; 2011-7-25
	*	@brief				BindIDLogin.
	*/
	void IAIM_BindIDLogin(AMHandle hIM);


#ifdef __cplusplus
};
#endif // __cplusplus
#endif // __IAIM_H__
