#include "AIMSignature.h"

#include "AMString.h"
#include "AMStdlib.h"
#include "AMMemory.h"
#include "AMAssert.h"

#define		XML_TAG_SIGOP	"SigOp"
#define		XML_TAG_SIG		"Sig"

#define		XML_TAG_LOOP	"Loop"
#define		XML_TAG_T		"T"
#define		XML_TAG_CI		"CI"
#define		XML_TAG_ST		"ST"
#define		XML_TAG_RET		"Ret"
#define		XML_TAG_FLAG	"Flag"
#define		XML_TAG_EMP		"Emp"

#define		HeadTag(tag)		"<"tag">"
#define		TailTag(tag)		"</"tag">"

AMInt32		SigXML2SigStruct(const AMChar *szSigXML, AMHandle hSig)
{
	int i = 0;
	AMChar *szBegin = AMNULL, *szEnd = AMNULL;
	AIM_SIGNATURE *pSig = (AIM_SIGNATURE*)hSig;
	AMAssert(0 != szSigXML && AMNULL != pSig);

	AMMemset(pSig, 0, sizeof(AIM_SIGNATURE));

	szBegin = AMStrstr(szSigXML, HeadTag(XML_TAG_SIG));
	i=0;
	while(AMNULL != szBegin && i<MAX_SIG_COUNT)
	{
		szBegin += sizeof(HeadTag(XML_TAG_SIG)) -1;
		szEnd = AMStrstr(szBegin, TailTag(XML_TAG_SIG));

		if(AMNULL != szEnd)	
		{
			if(szEnd-szBegin < MAX_SIG_LEN)
			{
				AMMemcpy(pSig->szSignature[i], szBegin, szEnd-szBegin);
			}
			szBegin = AMStrstr(szEnd, HeadTag(XML_TAG_SIG));		
		}
		else
			break;

		i++;
	}

	if(AMNULL == szEnd)
		szEnd = szSigXML;

	szBegin = AMStrstr(szEnd, HeadTag(XML_TAG_LOOP));
	if(AMNULL != szBegin)
		pSig->iLoop = AMAtoi(szBegin + sizeof(HeadTag(XML_TAG_LOOP))-1);
	else
		szBegin = szSigXML;

	szBegin = AMStrstr(szBegin, HeadTag(XML_TAG_T));
	if(AMNULL != szBegin)
		pSig->iT = AMAtoi(szBegin + sizeof(HeadTag(XML_TAG_T))-1);
	else
		szBegin = szSigXML;
	
	szBegin = AMStrstr(szBegin, HeadTag(XML_TAG_CI));
	if(AMNULL != szBegin)
		pSig->iCI = AMAtoi(szBegin + sizeof(HeadTag(XML_TAG_CI))-1);
	else
		szBegin = szSigXML;

	szBegin = AMStrstr(szBegin, HeadTag(XML_TAG_ST));
	if(AMNULL != szBegin)
		pSig->iST = AMAtoi(szBegin + sizeof(HeadTag(XML_TAG_ST))-1);
	else
		szBegin = szSigXML;

	szBegin = AMStrstr(szBegin, HeadTag(XML_TAG_RET));
	if(AMNULL != szBegin)
		pSig->iRet = AMAtoi(szBegin + sizeof(HeadTag(XML_TAG_RET))-1);
	else
		szBegin = szSigXML;

	szBegin = AMStrstr(szBegin, HeadTag(XML_TAG_FLAG));
	if(AMNULL != szBegin)
		pSig->iFlag	 = AMAtoi(szBegin + sizeof(HeadTag(XML_TAG_FLAG))-1);
	else
		szBegin = szSigXML;

	szBegin = AMStrstr(szBegin, HeadTag(XML_TAG_EMP));
	if(AMNULL != szBegin)
		pSig->iEmp = AMAtoi(szBegin + sizeof(HeadTag(XML_TAG_EMP))-1);
	
	return 0;
}

AMChar	*	BuildSigXMLFromStruct(AIM_SIGNATURE *pSigStruct, const AMChar *szSig)//只是把5个sig造好，没有追加后面的loop/st/ci等设置
{
	AMChar	*	szResultXML = AMNULL;
	AMInt32		iLen = 0, iPos = 0, i=0;
	AMAssert(pSigStruct);
	iLen = sizeof(XML_SIG_TEMPHEAD) + sizeof(XML_SIG_TEMPTAIL) + 3*MAX_INT_NUMBER_LEN;

	iLen += szSig?AMStrlen(szSig):0 + 11;

	for(i=0; i< MAX_SIG_COUNT-1; i++)
		iLen += pSigStruct->szSignature[i]?AMStrlen(pSigStruct->szSignature[i]):0 + 11;//11 for "<Sig></Sig>"

	szResultXML = (AMChar*)AMMalloc(iLen);
	if(!szResultXML)
		return AMNULL;

	AMMemset(szResultXML, 0, iLen);

	AMMemcpy(szResultXML, HeadTag(XML_TAG_SIGOP), sizeof(HeadTag(XML_TAG_SIGOP))-1);

	AMStrcat(szResultXML, HeadTag(XML_TAG_SIG));
	if(szSig)
		AMStrcat(szResultXML, szSig);
	AMStrcat(szResultXML, TailTag(XML_TAG_SIG));
	
	for(i=0; i< MAX_SIG_COUNT-1; i++)
	{
		AMStrcat(szResultXML, HeadTag(XML_TAG_SIG));
		AMStrcat(szResultXML, pSigStruct->szSignature[i]);
		AMStrcat(szResultXML, TailTag(XML_TAG_SIG));
	}

	return szResultXML;
}

AMChar	*	BuildSigXML(const AMChar *szSigXML, const AMChar *szSignature)
{
	AIM_SIGNATURE	sigStruct;
	AMChar *szRetXML = AMNULL, *szLeft = AMNULL;

	AMAssert(szSigXML);

	if(0 != SigXML2SigStruct(szSigXML, &sigStruct))
		return AMNULL;

	if(AMNULL == (szRetXML = BuildSigXMLFromStruct(&sigStruct, szSignature)))
		return AMNULL;

	AMStrcat(szRetXML, XML_SIG_TEMPHEAD + sizeof(HeadTag(XML_TAG_SIGOP)) + sizeof(HeadTag(XML_TAG_SIG)) + sizeof(TailTag(XML_TAG_SIG)) -1);
	AMStrcat(szRetXML, "0");
	AMStrcat(szRetXML, XML_SIG_TEMPTAIL);

	if(!szSignature || !*szSignature)
	{
		szLeft = AMStrstr(szRetXML, HeadTag(XML_TAG_EMP));
		AMAssert(szLeft);
		szLeft[sizeof(HeadTag(XML_TAG_EMP))-1]='1';
	}

	return szRetXML;
}