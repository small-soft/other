// IAIMTest.cpp : 定义控制台应用程序的入口点。
//
/*
#include "stdafx.h"
#include <vld.h>
#include "AMMemory.h"
#include <iostream>
using namespace std;


extern void test_IM(void);
extern void test_CGL();

int _tmain(int argc, _TCHAR* argv[])
{
	test_IM();

	//test_CGL();
	PrintfLeakMemory();
	return 0;
}

*/
#include "stdafx.h"
#include "AIMUtil.h"
#include "AMOS.h"
//#include <vld.h>
#include <string.h>


extern void test_IM(void);

#define XML_TRANS_SIZE		"<dwImageSize>"
#define XML_TRANS_SIZE_END	"</dwImageSize>"
#define	XML_TRANS_MD5BGN	"<strImageHash>"
#define	XML_TRANS_MD5END	"</strImageHash>"
#define	XML_TRANS_ID		"<llSID>"
#define XML_TRANS_ID_END	"</llSID>"
#define XML_TRANS_EXTBGN	"<strImageExtend>"
#define XML_TRANS_EXTEND	"</strImageExtend>"

void test()
{
	char szXML[256]={0}, *szTmp = szXML;
	AMInt32 iPos = 0;

	strcat(szXML, "<xparam>" XML_TRANS_SIZE);
	szTmp +=  sizeof("<xparam>" XML_TRANS_SIZE) - 1;
	iPos = _AIMItoa(256, szTmp);
	szTmp += iPos;
	strcat(szTmp, XML_TRANS_SIZE_END XML_TRANS_MD5BGN);
	szTmp += sizeof(XML_TRANS_SIZE_END XML_TRANS_MD5BGN) - 1;
	strcat(szTmp, "12345678901234567890123456789012");
	szTmp += 32;
	strcat(szTmp, XML_TRANS_MD5END XML_TRANS_EXTBGN);
	szTmp += sizeof(XML_TRANS_MD5END XML_TRANS_EXTBGN) - 1;
	if(".jpg")
	{
		strcat(szTmp, ".jpg");
		szTmp += strlen(".jpg");
	}
	strcat(szTmp, XML_TRANS_EXTEND "</xparam>");

}

int test2()
{
	char *szXML = "<xparam><dwImageSize>1500</dwImageSize><strImageHash>0bc864dcf35f50dbf337dc6c4db61e1f</strImageHash><llSID>237954110580587332</llSID><strImageExtend>.jpg</strImageExtend></xparam>";
		char *szObjId = AMNULL, *szSize = AMNULL, *szMd5Bgn = AMNULL, 
		*szMd5End = AMNULL, *szExtendBgn = AMNULL, *szExtendEnd = AMNULL;
	char *szDigest = AMNULL, *szFileName = AMNULL;

	if(szSize = AMStrstr(szXML, XML_TRANS_SIZE))
		if(szMd5Bgn = AMStrstr(szSize + 2*sizeof(XML_TRANS_SIZE)-2, XML_TRANS_MD5BGN)) 
			if(szMd5End = AMStrstr(szMd5Bgn + sizeof(XML_TRANS_MD5BGN)-1, XML_TRANS_MD5END))
				if(szObjId = AMStrstr(szMd5End + sizeof(XML_TRANS_MD5END)-1, XML_TRANS_ID))
					if(szExtendBgn = AMStrstr(szObjId + 2*sizeof(XML_TRANS_ID)-2, XML_TRANS_EXTBGN))
						if(szExtendEnd = AMStrstr(szExtendBgn + sizeof(XML_TRANS_EXTBGN)-1, XML_TRANS_EXTEND))
							return 0;
	return -1;
}

void test3()
{
	char databasePath[120] = {0};
	char databasePath2[120] = {0};
	char *szName = "cnalichnyuxinhe02";
	int index = 0;
	while(*szName)
		index += _AIMItoa(*((AMUChar *)(szName++)), &(databasePath[index]));

	szName = "cnalichnyuxinhe12";
	index = 0;
	while(*szName)
		index += _AIMItoa(*((AMUChar *)(szName++)), &(databasePath2[index]));

}

int _tmain(int argc, _TCHAR* argv[])
{
//	test3();
	test_IM();
	//test2();
	return 0;
}