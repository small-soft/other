#include "IMnetUtility.h"
#include "PCUtility.h"
#include "IMnet.h"

#include "stdio.h"
#include "stdlib.h"

/************************************************************************/
// declare
/************************************************************************/
static void GetXMLString(AMChar* pSrc, AMChar* token, AMInt32 tokenLen, AMChar** ppDst, AMInt32* pDstLen);

/************************************************************************/
// GetLRC
/************************************************************************/
AMUInt8 GetLRC(AMUInt8* buf, AMInt32 pos, AMInt32 length) 
{
	AMInt32 i;
	AMUInt8 lrc = 0;
	for (i = 0; i < length; i++)
		lrc ^= buf[pos + i];

	return lrc;
}

/************************************************************************/
// GetCC
/************************************************************************/
AMInt16 GetCC(AMUInt8* buf, AMInt32 pos, AMInt32 length) 
{
	AMInt32 i;
	AMInt32 sum = 0;
	AMInt32 byteValue = 0;
	for (i = 0; i < length; i++) 
	{
		byteValue = buf[pos + i];
		if (byteValue < 0)
			sum += buf[pos + i] + 256;
		else
			sum += buf[pos + i];
	}

	return (AMInt16) sum;
}

/************************************************************************/
//SkipPropertyNum
/************************************************************************/
void SkipPropertyNum(AMUInt8** ppbuffer, AMInt32 n)
{
	AMInt32 i;
	AMInt32 strLen;
	AMInt8 type;
	for(i=0; i<n; i++)
	{
		getByte((*ppbuffer), type);
		switch(type)
		{
		case FT_INT8:
		case FT_UINT8:
			(*ppbuffer) += 1;
			break;

		case FT_INT16:
		case FT_UINT16:
			(*ppbuffer) += 2;
			break;

		case FT_INT32:
		case FT_UINT32:
			(*ppbuffer) += 4;
			break;

		case FT_INT64:
		case FT_UINT64:
			(*ppbuffer) += 8;
			break;

		case FT_STRING:
			getInt((*ppbuffer), strLen);
			(*ppbuffer) += strLen;
			break;

		default:
		#ifdef AMOS_DEBUG
			AMPrintf("unspported SkipPropertyNum.");
		#endif
			break;
		}
	}
}

/************************************************************************/
// XMLStringToMessageXML && GetXmlString
/************************************************************************/
void GetXMLString(AMChar* pSrc, AMChar* token, AMInt32 tokenLen, AMChar** ppDst, AMInt32* pDstLen)
{
	AMInt32 length = 0;
	AMChar* pBegin = NULL;
	AMChar* pEnd   = NULL;
	AMInt32 tokenBeginLen = tokenLen + 3;
	AMInt32 tokenEndLen   = tokenLen + 4;
	AMChar* tokenBegin = (AMChar*)AMMalloc(tokenBeginLen);
	AMChar* tokenEnd   = (AMChar*)AMMalloc(tokenEndLen);

	memset(tokenBegin, 0, tokenBeginLen);
	memset(tokenEnd, 0, tokenEndLen);
	
	//denx: sprintf这个东西可能导致异常
	//sprintf(tokenBegin, "%c%s%c", '<', token, '>');
	//sprintf(tokenEnd, "%s%s%c", "</", token, '>');
	length = strlen(token);
	memcpy(tokenBegin, "<", 1);
	memcpy(tokenBegin+1, token, length);
	memcpy(tokenBegin+1+length, ">", 1);
	memcpy(tokenEnd, "</", 2);
	memcpy(tokenEnd+2, token, length);
	memcpy(tokenEnd+2+length, ">", 1);	

	pBegin = strstr(pSrc, tokenBegin);
	pEnd   = strstr(pSrc, tokenEnd);

	if(pBegin != NULL && pEnd != NULL)
	{
		pBegin+= strlen(tokenBegin);
		*pDstLen = pEnd - pBegin;
		*ppDst = (AMChar*)AMMalloc(*pDstLen+1);  //此处申请的内存将在外面自动释放
		memset(*ppDst, 0, *pDstLen+1);
		memcpy(*ppDst, pBegin, *pDstLen);
	}

	AMFree(tokenBegin);
	AMFree(tokenEnd);
}

void XMLStringToMessageXML(AMChar* pSrc, AMInt32 srcLen, MessageXML* msgXML)
{
	AMInt32 i;
	typedef struct{
		AMChar* pToken;
		AMChar** ppValue;
		AMInt32* pLength;
	}TokenMap;

#ifdef WIN32
	TokenMap map[] = {
		{XML_PARAM_FROMUID  , &msgXML->fromUID   , &msgXML->fromUIDLen    },
		{XML_PARAM_TOUID    , &msgXML->toUID     , &msgXML->toUIDLen      },
		{XML_PARAM_MSG      , &msgXML->msg       , &msgXML->msgLen        },
		{XML_PARAM_PGID     , &msgXML->pgID      , &msgXML->pgIDLen       },
		{XML_PARAM_RESULT   , &msgXML->result    , &msgXML->resultLen     }, 
		{XML_PARAM_DISPNAME , &msgXML->dispName  , &msgXML->dispNameLen   } 
	};
#else
	TokenMap map[] = {
		{XML_PARAM_FROMUID  , 0   , 0    },
		{XML_PARAM_TOUID    , 0   , 0    },
		{XML_PARAM_MSG      , 0   , 0    },
		{XML_PARAM_PGID     , 0   , 0    },
		{XML_PARAM_RESULT   , 0   , 0    }, 
		{XML_PARAM_DISPNAME , 0   , 0    } 
	};
	map[0].ppValue = &msgXML->fromUID;
	map[0].pLength = &msgXML->fromUIDLen;
	map[1].ppValue = &msgXML->toUID;
	map[1].pLength = &msgXML->toUIDLen;
	map[2].ppValue = &msgXML->msg;
	map[2].pLength = &msgXML->msgLen;
	map[3].ppValue = &msgXML->pgID;
	map[3].pLength = &msgXML->pgIDLen;
	map[4].ppValue = &msgXML->result;
	map[4].pLength = &msgXML->resultLen;
	map[5].ppValue = &msgXML->dispName;
	map[5].pLength = &msgXML->dispNameLen;
#endif
	
	for(i=0; i<sizeof(map)/sizeof(map[0]); i++)
		GetXMLString(pSrc, map[i].pToken, strlen(map[i].pToken), map[i].ppValue, map[i].pLength);
}

void FreeMessageXml(MessageXML* pxml)
{
	if(pxml)
	{
		AMFree(pxml->dispName);
		pxml->dispName = NULL;
		AMFree(pxml->fromUID);
		pxml->fromUID = NULL;
		AMFree(pxml->msg);
		pxml->msg = NULL;
		AMFree(pxml->pgID);
		pxml->pgID = NULL;
		AMFree(pxml->result);
		pxml->result = NULL;
		AMFree(pxml->toUID);
		pxml->toUID = NULL;
	}
}

/************************************************************************/
// 
/************************************************************************/
void FreeXMLString(AMChar** ppStr)
{
	if(ppStr != NULL)
	{
		AMFree(*ppStr);
		*ppStr = NULL;
	}
}

void MakeXMLString(AMChar** ppDstStr, AMInt32* pDstStrLen, 
				   AMChar* userName, AMInt32 userNameLen,
				   AMChar* toID, AMInt32 toIDLen,
				   AMInt32 groupIDHigh, AMInt32 groupIDLow,  
				   AMChar* verifiMsg, AMInt32 verifyMsgLen,
				   AMChar* displayName, AMInt32 displayNameLen,
				   AMInt32 result)
{
	AMInt32 i;
	AMInt32 len = 0;
	AMInt32 tempLen = 0;
	typedef struct{
		AMChar*  pToken;
		AMChar*  pValue;
		AMInt32* pLength;
	}TokenMap;

	AMChar groupStr[64];
	AMInt32 groupStrLen = 0;
	AMChar resultStr[32];
	AMInt32 resultStrLen = 0;
	AMChar* pDstStrTemp = NULL;
	
#ifdef WIN32
	TokenMap map[] = {
		{XML_PARAM_FROMUID  , userName		, &userNameLen   }, //0
		{XML_PARAM_TOUID    , toID			, &toIDLen		},  //1
		{XML_PARAM_MSG      , verifiMsg		, &verifyMsgLen	},  //2
		{XML_PARAM_PGID     , groupStr		, &groupStrLen	},  //3
		{XML_PARAM_RESULT   , resultStr		, &resultStrLen  }, //4
		{XML_PARAM_DISPNAME , displayName	, &displayNameLen}  //5
	};
#else
	TokenMap map[] = {
		{XML_PARAM_FROMUID  , 0		, 0 }, //0
		{XML_PARAM_TOUID    , 0		, 0	}, //1
		{XML_PARAM_MSG      , 0		, 0	}, //2
		{XML_PARAM_PGID     , 0		, 0	}, //3
		{XML_PARAM_RESULT   , 0		, 0 }, //4
		{XML_PARAM_DISPNAME , 0		, 0	}  //5
	};
	
	map[0].pValue  = userName;
	map[0].pLength = &userNameLen;
	map[1].pValue  = toID;
	map[1].pLength = &toIDLen;
	map[2].pValue  = verifiMsg;
	map[2].pLength = &verifyMsgLen;
	map[3].pValue  = groupStr;
	map[3].pLength = &groupStrLen;
	map[4].pValue  = resultStr;
	map[4].pLength = &resultStrLen;
	map[5].pValue  = displayName;
	map[5].pLength = &displayNameLen;
#endif
	
	*pDstStrLen += 2*strlen(XML_PARAM_CNTOP);
	*pDstStrLen += 2*strlen(XML_PARAM_FROMUID);
	*pDstStrLen += 2*strlen(XML_PARAM_TOUID);
	*pDstStrLen += 2*strlen(XML_PARAM_MSG);
	*pDstStrLen += 2*strlen(XML_PARAM_PGID);
	*pDstStrLen += 2*strlen(XML_PARAM_RESULT);
	*pDstStrLen += 2*strlen(XML_PARAM_DISPNAME);
	*pDstStrLen += 5 * 7; //每个都有"<></>"

	memset(resultStr, 0, sizeof(resultStr));
	AMitoa(result, resultStr);
	resultStrLen = strlen(resultStr);

	memset(groupStr, 0, sizeof(groupStr));
	Long2String(groupStr, groupIDHigh, groupIDLow);
	groupStrLen = strlen(groupStr);

	*pDstStrLen += userNameLen;
	*pDstStrLen += toIDLen;
	*pDstStrLen += verifyMsgLen;
	*pDstStrLen += groupStrLen;
	*pDstStrLen += resultStrLen;
	*pDstStrLen += displayNameLen;

	pDstStrTemp = (AMChar*)AMMalloc(*pDstStrLen+2);
	memset(pDstStrTemp, 0, *pDstStrLen+2);
	if(pDstStrTemp != NULL)
	{
		*ppDstStr = pDstStrTemp;

		//denx: 不要使用sprintf,在某些平台可能导致内存异常
		//len = sprintf(pDstStrTemp, "%s%s%s", "<",XML_PARAM_CNTOP, ">");
		tempLen = strlen(XML_PARAM_CNTOP);
		memcpy(pDstStrTemp, "<", 1);
		memcpy(pDstStrTemp+1, XML_PARAM_CNTOP, tempLen);
		memcpy(pDstStrTemp+1+tempLen, ">", 1);
		pDstStrTemp += 1+tempLen+1;
		len = 1+tempLen+1;

		for(i=0; i<sizeof(map)/sizeof(map[0]); i++)
		{
			//denx: 不要使用sprintf,在某些平台可能导致内存异常
			//len += sprintf(pDstStrTemp + len, "%s%s%s", "<",map[i].pToken, ">");
			tempLen = strlen(map[i].pToken);
			memcpy(pDstStrTemp, "<", 1);
			memcpy(pDstStrTemp+1, map[i].pToken, tempLen);
			memcpy(pDstStrTemp+1+tempLen, ">", 1);
			pDstStrTemp += 1+tempLen+1;
			len += 1+tempLen+1;

			if(map[i].pValue != NULL && (*(map[i].pLength)) != 0)
			{
				//denx: 不要使用sprintf,在某些平台可能导致内存异常
				//len += sprintf(pDstStrTemp + len, "%s", map[i].pValue);
				//tempLen = strlen(map[i].pValue);		//	yanlong.shiyl
				tempLen = *(map[i].pLength);			//	yanlong.shiyl
				memcpy(pDstStrTemp, map[i].pValue, tempLen);
				pDstStrTemp += tempLen;
				len += tempLen;
			}

			//denx: 不要使用sprintf,在某些平台可能导致内存异常
			//len += sprintf(pDstStrTemp + len, "%s%s%s", "</",map[i].pToken, ">");
			tempLen = strlen(map[i].pToken);
			memcpy(pDstStrTemp, "</", 2);
			memcpy(pDstStrTemp+2, map[i].pToken, tempLen);
			memcpy(pDstStrTemp+2+tempLen, ">", 1);
			pDstStrTemp += 2+tempLen+1;
			len += 2+tempLen+1;
		}

		//denx: 不要使用sprintf,在某些平台可能导致内存异常
		//len += sprintf(pDstStrTemp + len, "%s%s%s", "</",XML_PARAM_CNTOP, ">");
		tempLen = strlen(XML_PARAM_CNTOP);
		memcpy(pDstStrTemp, "</", 2);
		memcpy(pDstStrTemp+2, XML_PARAM_CNTOP, tempLen);
		memcpy(pDstStrTemp+2+tempLen, ">", 1);
		pDstStrTemp += 2+tempLen+1;
		len += 2+tempLen+1;
	}

	if(len != *pDstStrLen)
	{
		*ppDstStr = NULL;
		*pDstStrLen = 0;
	
		if(pDstStrTemp)						//	yanlong.shiyl
			AMFree(pDstStrTemp);			//	yanlong.shiyl
	}
}
