#ifndef __AMCONTACTMODEL_H__
#define	__AMCONTACTMODEL_H__

#include "hashtable.h"
#include "list.h"

#include "AIMContact.h"
#include "AIMGroup.h"
#include "IMnet.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct IAContactModel
	{
		OHTable		ohtFriends, ohtOthers, ohtTmps;	//FREEOBJ
		OHTable		ohtGroups;				//FREEOBJ

		OHTable		ohtRevBlk;				//NOFREE

		List		lTopGrp;				//NOFREE
		IAGroup		*pBindGrp,				// GrpID: BIND_ACCOUNT_GRP_ID
					*pBlkGrp,				// GrpID: BLACK_GRP_ID
					*pRecentGrp,			// GrpID: RECENT_GRP_ID
					*pStrangerGrp;			// GrpID: STRANG_GRP_ID

		AMUInt32	uiDirtFlag;				//	40		20		10		8		4		2		1
 											//	_rect	_strg	_othr	_revblk	_blk	_cnt	_grp

		struct IAIM	*	pReference;
	} IAContactModel;

	struct IAIM		*	IAContactModel_GetReference(const IAContactModel *pCntModel);//AM
	IAContact		*	IAContactModel_FindContact(const IAContactModel *pCntModel, const IAContact *pCnt);//AM

	IAContactModel	*	IAContactModel_Create(struct IAIM *pReference);
	AMVoid				IAContactModel_Destroy(IAContactModel *pCntModel);
	AMVoid				IAContactModel_ClearData(IAContactModel *pCntModle);

	AMInt32				IAContactModel_Store(IAContactModel *pCntModel, AMBool bClear);
	//bTry:����ܷ�����ݿ�
	AMInt32				IAContactModel_Restore(IAContactModel *pCntModel, AMUInt32 iDirtFlag, AMBool bTry);

	AMVoid				IAContactModel_UpdateRecent(IAContactModel *pCntModel, const AMChar *szCntID, const AMChar *szMsg, AMInt32 iLen, AMBool bDirectNotify);
	AMVoid				IAContactModel_ListenIMnet(IAContactModel *pCntModel, IMnetHandle pNetModel);
	AMVoid				IAContactModel_UnlistenIMnet(IAContactModel *pCntModel, IMnetHandle pNetModel);

	AMVoid				IAContactModel_SetAllContact(IAContactModel *pCntModel, AMBool bBindID);
	AMVoid				IAContactModel_BuildBindContactList(IAContactModel *pCntModel);
	AMVoid				IAContactModel_BuildGroupTree(IAContactModel *pCntModel);

	AMVoid				IAContactModel_DecreaseReadCnt(IAContactModel *pCntModel, const AMChar *szCntId, AMInt32 iNum);

	AMVoid				IAContactModel_ClearBindData(struct IAIM *pIM, IAContactModel *pCntModel, AMChar *szBindID);

	/**
	* @brief			�õ���������б�
	*/
	AIM_RESULT IAIMContactModel_GetGroupList(AMHandle hContactModel, const List **ppList);
	/**
	* @brief			������ID�õ���Ӧ��
	*/
	AIM_RESULT IAIMContactModel_GetGroupByID(AMHandle hContactModel, AMInt64 i64GrpID, AMHandle *phGroup);
	/**
	* @brief			������ϵ��ID�õ���Ӧ��ϵ��
	*/
	AIM_RESULT IAIMContactModel_GetContactByID(AMHandle hContactModel, const AMChar *szCntID, AMHandle *phContact);

	/**
	* @brief				�Ƴ������ϵ��
	* @param szContactID	AMNULL������������ϵ��
	*/
	AIM_RESULT IAIMContactModel_RemoveRecent(AMHandle hContactModel, const AMChar *szCntID);
	/**
	* @brief				�Ƴ�İ����
	* @param szContactID	AMNULL�������İ����
	*/
	AIM_RESULT IAIMContactModel_RemoveStranger(AMHandle hContactModel, const AMChar *szCntID);

#ifdef __cplusplus
};
#endif

#endif