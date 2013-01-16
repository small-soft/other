#ifndef __AMIMGROUP_H__
#define __AMIMGROUP_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "IAIMGroup.h"
#include "list.h"

	typedef struct IAGroup
	{
		AMInt64			_iRid;
		AMInt64			iGroupID;
		AMChar		*	szName;
		AMChar		*	szPinyin;
		AMInt64			iParentGid;

		AMInt32			iUnreadMsgCnt;

		struct IAGroup * pParentGrp;
		List			lChildGrp;
		List			lChildCnt;
	}IAGroup;

	IAGroup	*	IAGroup_Create();
	IAGroup	*	IAGroup_CreateProc(AMBool bLight);
	AMVoid		IAGroup_Destroy(IAGroup *pGrp);
	AMInt32		IAGroup_CmpID(const AMVoid *pG1,const AMVoid *pG2, size_t t);
	AMInt32		IAGroup_CmpPinyin(const AMVoid *pG1,const AMVoid *pG2, size_t t);
	AMUInt32	IAGroup_Hash(AMVoid *pG, size_t t);
	AMVoid		IAGroup_SetName(IAGroup *pGrp, AMChar *szName, AMUInt32 uiLen);
	AMVoid		IAGroup_SetPinyin(IAGroup *pGrp, AMChar *szPinyin, AMUInt32 uiLen);

	/**
	* @brief				得到组中联系人的个数
	* @param bRecursive	表示是否递归计算联系人的个数（当组有子组的时候有效），一般为AMFALSE
	*/
	AMInt32			IAGroup_GetCntNum(const IAGroup *pGrp, AMBool bRecursive);
	/**
	* @brief				得到组中在线好友的数目
	* @param pGrp
	* @param bRecursive	表示是否递归计算在线联系人的个数（当组有子组的时候有效），一般为AMFALSE
	*/
	AMInt32			IAGroup_GetOnlineCntNum(const IAGroup *pGrp, AMBool bRecursive);
	
	/**
	* @brief				得到该组的父组（当组为嵌套组时有效）
	* @return				返回父组的指针，当无父亲组时返回AMNULL
	*/
	const IAGroup*	IAGroup_GetParentGrp(const IAGroup *pGrp);

	/**
	* @brief				得到组的子组列表
	*/
	const List	*	IAGroup_GetChildGrpList(const IAGroup *pGrp);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif