#ifndef __AMACCOUNTMODEL_H__
#define __AMACCOUNTMODEL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "AMTypes.h"
#include "list.h"
#include "AIMAccount.h"

	typedef struct IAccountModel
	{
		List		listAcnt;
		AMUInt32	uiDirtFlag;
		AMInt32		iRefCount;
	}IAccountModel;

	IAccountModel*	IAccountModel_Create();
	AMVoid			IAccountModel_Destroy(IAccountModel *pAcntModel);

	List		*	IAccountModel_GetAccountList(IAccountModel *pAcntor);
	AIMAccount	*	IAccountModel_findHistoryAcnt(IAccountModel *pAcntor, const AMChar *szID);
	AMVoid			IAccountModel_RemoveAccount(IAccountModel *pAcntor, const AMChar *pAcnt, AMBool bDelete);
	AMInt32			IAccountModel_Store(IAccountModel *pAcntModel);

#define		ACNT_STAMP_GRP		0x01
#define		ACNT_STAMP_CNT		0x02
#define		ACNT_STAMP_BLK		0x08
#define		ACNT_STAMP_REV		0x10

	AMInt32			IAccountModel_UpdateStamp(IAccountModel *pAcntModel, AIMAccount *pAcnt, AMInt32 iStoreFlag);

	AMInt32			IAccountModel_UpdateSigXML(IAccountModel *pAcntModel, const AMChar *szID, const AMChar *szXml, AMInt32 iLen);

	AMBool			IAccountModel_IsDirt(IAccountModel	*pAcntModel);
	AMVoid			IAccountModel_ClearDirt(IAccountModel *pAcntModel);
	AMVoid			IAccountModel_MarkDirt(IAccountModel *pAcntModel);

	AMVoid			IAccountModel_LoginOK(IAccountModel *pAcntModel, AIMAccount *pAcnt);
	AMVoid			IAccountModel_ClearToken(IAccountModel	*pAcntModle, const AIMAccount *pAcnt);


	AMInt32			IAccountModel_UpdateFlag(IAccountModel *pAcntModel, AIMAccount *pAcnt);

#ifdef __cplusplus
}
#endif	
#endif	//__AMACCOUNTMODEL_H__