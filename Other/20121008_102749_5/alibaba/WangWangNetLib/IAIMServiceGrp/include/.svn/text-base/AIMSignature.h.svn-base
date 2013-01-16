#ifndef __AMIMSIGNATURE_H__
#define __AMIMSIGNATURE_H__

#include "AIMUtil.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

	typedef	struct  ST_AIM_SIGNATURE
	{
		AMChar 	szSignature[MAX_SIG_COUNT][MAX_SIG_LEN];
		AMInt32		iLoop, iT, iCI, iST, iRet, iFlag, iEmp;
	} AIM_SIGNATURE;

#define		XML_SIG_TEMPHEAD	"<SigOp>\
	<Sig></Sig>\
	<Loop>0</Loop>\
	<T>600</T>\
	<CI>0</CI>\
	<ST>"

#define 	XML_SIG_TEMPTAIL	"</ST>\
	<Ret>0</Ret>\
	<Flag>1</Flag>\
	<Emp>0</Emp>\
	</SigOp>"


	AMInt32		SigXML2SigStruct(const AMChar *szSigXML, AMHandle hSig);
	AMChar	*	BuildSigXML(const AMChar *szSigXML, const AMChar *szSignature);

#ifdef __cplusplus
};
#endif // __cplusplus
#endif //__AMIMSIGNATURE_H__