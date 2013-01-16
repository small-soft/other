#include "AIMGroup.h"
#include "AIMContact.h"

#include "IAIM.h"	// for AIM_RESULT and AIM_PRESENCE

#include "AMString.h"
#include "AMMemory.h"
#include "AMOS.h"
#include "AIMUtil.h"

IAGroup	*	IAGroup_Create()
{
	return IAGroup_CreateProc(AMFALSE);
}

IAGroup	*	IAGroup_CreateProc(AMBool bLight)
{
	IAGroup	*pGrp = AMMalloc(sizeof(IAGroup));
	AMAssert(0 != pGrp);
	AMMemset(pGrp, 0, sizeof(IAGroup));

	if(!bLight)
	{
		construct(List, &pGrp->lChildCnt, sizeof(IAContact), NOFREE);
		set_compare(List, &pGrp->lChildCnt, IAContact_CmpPinyin);

		construct(List, &pGrp->lChildGrp, sizeof(IAGroup), NOFREE);
		set_compare(List, &pGrp->lChildGrp, IAGroup_CmpPinyin);
	}

	return pGrp;
}

AMVoid		IAGroup_Destroy(IAGroup *pGrp)
{
	AMAssert(0 != pGrp);

	destruct(List, &pGrp->lChildCnt);
	destruct(List, &pGrp->lChildGrp);

	if(pGrp->szName)
	{
		AMFree(pGrp->szName);
		pGrp->szName = 0;
	}
	if(pGrp->szPinyin)
	{
		AMFree(pGrp->szPinyin);
		pGrp->szPinyin = 0;
	}
	AMFree(pGrp);
}

AMVoid		IAGroup_SetName(IAGroup *pGrp, AMChar *szName, AMUInt32 uiLen)
{
	AMAssert(0 != pGrp && 0 != szName && 0 < uiLen);
	if(pGrp->szName)
	{
		AMFree(pGrp->szName);
		pGrp->szName = 0;
	}
	pGrp->szName = (AMChar *)AMMalloc(uiLen + 1);
	AMAssert(0 != pGrp->szName);
	AMMemcpy(pGrp->szName, szName, uiLen);
	pGrp->szName[uiLen] = 0;
}

AMVoid		IAGroup_SetPinyin(IAGroup *pGrp, AMChar *szPinyin, AMUInt32 uiLen)
{
	AMAssert(0 != pGrp && 0 != szPinyin && 0 < uiLen);
	if(pGrp->szPinyin)
	{
		AMFree(pGrp->szPinyin);
		pGrp->szPinyin = 0;
	}
	pGrp->szPinyin = (AMChar *)AMMalloc(uiLen + 1);
	AMAssert(0 != pGrp->szPinyin);
	AMMemcpy(pGrp->szPinyin, szPinyin, uiLen);
	pGrp->szPinyin[uiLen] = 0;
}

AIM_RESULT IAIMGroup_GetID( const AMHandle hGroup, AMInt64 *pId )
{
	const IAGroup * pGroup = (const IAGroup *)hGroup;
	AMAssert(0 != pGroup && AMNULL != pId);

	*pId = pGroup->iGroupID;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMGroup_GetName( const AMHandle hGroup, const AMChar **pszName )
{
	const IAGroup * pGroup = (const IAGroup *)hGroup;
	AMAssert(0 != pGroup && AMNULL != pszName);

	*pszName = pGroup->szName;

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMGroup_CountContacts( const AMHandle hGroup, AMBool bRecursive, AMInt32 *pNum )
{
	const IAGroup * pGroup = (const IAGroup *)hGroup;
	AMAssert(0 != pGroup && NULL != pNum);

	*pNum = IAGroup_GetCntNum(pGroup, bRecursive);

	return eAIM_RESULT_OK;
}

AMInt32		IAGroup_GetCntNum(const IAGroup *pGrp, AMBool bRecursive)
{
	AMInt32 iCount = 0;
	ListIter *pItr = 0;
	IAGroup	*pChildGrp = 0;
	iCount = pGrp->lChildCnt.size;
	if(AMTRUE == bRecursive && pGrp->lChildGrp.size > 0)
	{
		pItr = create(ListIter, (List*)&pGrp->lChildGrp);
		head(ListIter, pItr);
		do 
		{
			pChildGrp = (IAGroup *)retrieve(ListIter, pItr);
			iCount += IAGroup_GetCntNum(pChildGrp, bRecursive);
		} while (!next(ListIter, pItr));
	}
	return iCount;
}

AIM_RESULT IAIMGroup_CountOnlines( const AMHandle hGroup, AMBool bRecursive, AMInt32 *pNum )
{
	const IAGroup * pGroup = (const IAGroup *)hGroup;
	AMAssert(0 != pGroup && AMNULL != pNum);

	*pNum = IAGroup_GetOnlineCntNum(pGroup, bRecursive);

	return eAIM_RESULT_OK;
}

AMInt32		IAGroup_GetOnlineCntNum(const IAGroup *pGrp, AMBool bRecursive)
{
	AMInt32 iCount = 0;
	ListIter *pGrpItr = 0, *pCntItr;
	IAGroup	*pChildGrp = 0;
	IAContact *pChildCnt = 0;
	AMBool	bTmp = AMFALSE;

	if(pGrp->lChildCnt.size > 0)
	{
		pCntItr = create(ListIter, (List*)&pGrp->lChildCnt);
		head(ListIter, pCntItr);
		do 
		{
			pChildCnt = (IAContact *)retrieve(ListIter, pCntItr);

			IAIMContact_IsOnline(pChildCnt, &bTmp);
			if(AMTRUE == bTmp)
			{
				iCount++;
			}
		} while (!next(ListIter, pCntItr));
		destroy(ListIter, pCntItr);
	}

	if(AMTRUE == bRecursive && pGrp->lChildGrp.size > 0)
	{
		pGrpItr = create(ListIter, (List*)&pGrp->lChildGrp);
		head(ListIter, pGrpItr);
		do 
		{
			pChildGrp = (IAGroup *)retrieve(ListIter, pGrpItr);
			iCount += IAGroup_GetOnlineCntNum(pChildGrp, bRecursive);
		} while (!next(ListIter, pGrpItr));
	}

	return iCount;
}


AIM_RESULT IAGroup_CountUnreadMsgs( const AMHandle hGroup, AMBool bRecursive, AMInt32 *pCount )
{
	const IAGroup * pGroup = (const IAGroup *)hGroup;
	AMAssert(0 != pGroup && AMNULL != pCount);

	if(bRecursive)
		return eAIM_RESULT_NOT_SUPPORT;

	*pCount = pGroup->iUnreadMsgCnt;

	return eAIM_RESULT_OK;
}

const IAGroup	*IAGroup_GetParentGrp(const IAGroup *pGrp)
{
	AMAssert(0 != pGrp);
	return pGrp->pParentGrp;
}

static AIM_RESULT AIMGroup_GetHandles( AMHandle hGroup, AMBool bRecursive, AMBool bCnt, AMHandle **pphHandleArray, AMInt32 *piSize)
{
	const IAGroup * pGroup = (const IAGroup *)hGroup;
	AMInt32 i = 0;
	ListIter *pIter = AMNULL;
	AMAssert(0 != pGroup && AMNULL != pphHandleArray && AMNULL != piSize );

	*piSize = 0;

	if(bRecursive)
		return eAIM_RESULT_NOT_SUPPORT;

	if(bCnt)
		*piSize = pGroup->lChildCnt.size;
	else
		*piSize = pGroup->lChildGrp.size;

	if(!(*piSize))
		return eAIM_RESULT_OK;

	*pphHandleArray = (AMHandle *)AMMalloc(sizeof(AMHandle) * (*piSize));
	if(!(*pphHandleArray))
		return eAIM_RESULT_MALLOC_ERROR;

	if(bCnt)
		pIter = create(ListIter, &pGroup->lChildCnt);
	else
		pIter = create(ListIter, &pGroup->lChildGrp);

	head(ListIter, pIter);
	do 
	{
		(*pphHandleArray)[i++] = (AMHandle) retrieve(ListIter, pIter);
	} while (!next(ListIter, pIter));
	destroy(ListIter, pIter);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMGroup_ReleaseHandles( AMHandle hGroup, AMBool bCnt, AMHandle *phHandleArray, AMInt32 iArraySize)
{
	const IAGroup * pGroup = (const IAGroup *)hGroup;
	AMAssert(0 != pGroup );

	if(iArraySize>0)
		AMFree(phHandleArray);

	return eAIM_RESULT_OK;
}

AIM_RESULT IAIMGroup_GetContacts( AMHandle hGroup, AMBool bRecursive, AMHandle **pphContactArray, AMInt32 *piSize)
{
	return AIMGroup_GetHandles( hGroup, bRecursive, AMTRUE, pphContactArray, piSize);
}

AIM_RESULT IAIMGroup_GetGroups( AMHandle hGroup, AMBool bRecursive, AMHandle **pphGroupArray, AMInt32 *piSize)
{
	return AIMGroup_GetHandles( hGroup, bRecursive, AMFALSE, pphGroupArray, piSize);
}

AIM_RESULT IAIMGroup_ReleaseContacts( AMHandle hGroup, AMHandle *phContactArray, AMInt32 iArraySize)
{
	return IAIMGroup_ReleaseHandles( hGroup, AMTRUE, phContactArray, iArraySize);
}

AIM_RESULT IAIMGroup_ReleaseGroups( AMHandle hGroup, AMHandle *phGroupArray, AMInt32 iArraySize)
{
	return IAIMGroup_ReleaseHandles( hGroup, AMFALSE, phGroupArray, iArraySize);
}

AMInt32 IAGroup_CmpID(const AMVoid *pG1,const AMVoid *pG2, size_t t)
{
	IAGroup *pGA = (IAGroup*)pG1,
		*pGB = (IAGroup*)pG2;

	if(pGA->iGroupID > pGB->iGroupID)
		return 1;
	else if(pGA->iGroupID < pGB->iGroupID)
		return -1;
	else 
		return 0;
}

AMInt32 IAGroup_CmpPinyin(const AMVoid *pG1,const AMVoid *pG2, size_t t)
{
	IAGroup *pGA = (IAGroup*)pG1,
		*pGB = (IAGroup*)pG2;
	AMAssert(0 != pGA && 0 != pGB);
	AMAssert(0 != pGA->szPinyin && 0 != pGB->szPinyin);
	return AMStrcmp(pGA->szPinyin, pGB->szPinyin);
}

AMUInt32 IAGroup_Hash(AMVoid *pG, size_t t)
{
	AMUInt32 *puiTmp = 0;
	IAGroup	*pGrp = (IAGroup *)pG;
	AMAssert(0 != pGrp);
	puiTmp = (AMUInt32 *)&pGrp->iGroupID;
	DPRINT("IAGroup_Hash..................%x, %x\n", puiTmp[0], puiTmp[1]);
	return puiTmp[0] + puiTmp[1];
}

