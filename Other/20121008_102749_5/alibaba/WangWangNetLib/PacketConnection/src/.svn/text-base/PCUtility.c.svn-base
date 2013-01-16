#include "PCUtility.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#ifdef AMOS
#include "AMLog.h"
#else
	#ifdef WIN32
	#include "stdarg.h"
	#endif
#endif

#include "zlib.h"
#include "des_help.h"

/************************************************************************/
// declare
/************************************************************************/

/************************************************************************/
// GetSctByte
/************************************************************************/
PCRetCode GetSctByte(AMUInt8** ppbuffer, AMInt8* pleft)
{
	AMInt8 type;
	getByte((*ppbuffer), type);
	if (FT_UINT8 != type)
		return eTypeError;
	getByte((*ppbuffer), (*pleft));
	return eOK;
}

/************************************************************************/
// GetSctShort
/************************************************************************/
PCRetCode GetSctShort(AMUInt8** ppbuffer, AMInt16* pleft)
{
	AMInt8 type;
	getByte((*ppbuffer), type);
	if (FT_UINT16 != type)
		return eTypeError;

	getShort((*ppbuffer), (*pleft));
	return eOK;
}
/************************************************************************/
// GetSctInt
/************************************************************************/
PCRetCode GetSctInt(AMUInt8** ppbuffer, AMInt32* pleft)
{
	AMUInt8 type;
	getByte((*ppbuffer), type);
	if(FT_UINT32 != type && FT_INT32 != type)
		return eTypeError;
	getInt((*ppbuffer), (*pleft));
	return eOK;
}

/************************************************************************/
// GetSctLong
/************************************************************************/
PCRetCode GetSctLong(AMUInt8** ppbuffer, AMInt32* pHigher, AMInt32* pLower)
{
	AMUInt8 type;
	getByte((*ppbuffer), type);
	if (FT_INT64 != type) 
		return eTypeError;
	getInt((*ppbuffer), (*pHigher));
	getInt((*ppbuffer), (*pLower));

	return eOK;
}

/************************************************************************/
// GetSctULong
/************************************************************************/
PCRetCode GetSctULong(AMUInt8** ppbuffer, AMInt32* pHigher, AMInt32* pLower)
{
	AMUInt8 type;
	getByte((*ppbuffer), type);
	if (FT_UINT64 != type) 
		return eTypeError;
	getInt((*ppbuffer), (*pHigher));
	getInt((*ppbuffer), (*pLower));

	return eOK;
}

/************************************************************************/
// GetSctString
/************************************************************************/
PCRetCode GetSctString(AMUInt8** ppbuffer, AMInt8** ppdes, AMInt32* pLen)
{
	AMUInt8 type;

	getByte((*ppbuffer), type);
	if(FT_STRING != type)
		return eTypeError;

	return GetStringAlloc(ppbuffer, ppdes, pLen);
}

/************************************************************************/
// GetStringAlloc
/************************************************************************/
PCRetCode GetStringAlloc(AMUInt8** ppbuffer, AMInt8** ppdes, AMInt32* pLen)
{
	getInt((*ppbuffer), (*pLen));
	if(*pLen != 0)
	{    
		*ppdes = (AMInt8*)AMMalloc(*pLen+1);// +1 to make it '\0' terminated.!	yanlong.shiyl (for PM use *ppdes as a null-terminated string directly)

		if(*ppdes == NULL)
			return eMallocError;

		(*ppdes)[*pLen]=0;					//Make it \0 terminated.!

		getString((*ppbuffer), (*ppdes), (*pLen));
	}
	else
	{
		*ppdes = NULL;
	}
	return eOK;
}

/************************************************************************/
// GetVectorStructLen
/************************************************************************/
PCRetCode GetVectorStructLen(AMUInt8** ppbuffer, AMInt32* pleft)
{
	AMInt8 type;
	getByte((*ppbuffer), type);
	if (FT_VECTOR != type) 
		return eTypeError;

	getByte((*ppbuffer), type);
	if (FT_STRUCT != type) 
		return eTypeError;

	getInt((*ppbuffer), (*pleft));
	return eOK;
}

// 
// 
// MailNetRetCode GetVectorSize(AMUInt8** pBufferTemp, AMInt32 *size)
// {	
// 	MailNetRetCode retCode = eOK;
// 	AMUInt8 type = 0;
// 	AMInt32 len;
// 
// 	getByte(*pBufferTemp,type);	
// 
// 	if ((type & 0xf0) != FT_VECTOR) 
// 	{
// 		return eTypeError;
// 	}
// 
// 	len  = type & 0x0f;
// 
// 	getByte(*pBufferTemp,type);
// 
// 	if (FT_STRUCT != type) {
// 		return eTypeError;
// 	}
// 
// 	switch (len) {
// 		case 0:
// 		case 4:
// 			getInt(*pBufferTemp, *size);
// 			break;
// 		case 1:
// 			getByte(*pBufferTemp, *size);
// 			break;
// 		case 2:
// 			getShort(*pBufferTemp, *size);
// 			break;
// 		default:
// 			return eTypeError;
// 	}
// 
// 	return retCode;
// }

/************************************************************************/
// GetVectorStrLen
/************************************************************************/
PCRetCode GetVectorStrLen(AMUInt8** ppbuffer, AMInt32* pleft)
{
	AMInt8 type;
	getByte((*ppbuffer), type);
	if (FT_VECTOR != type) 
		return eTypeError;

	getByte((*ppbuffer), type);
	if (FT_STRING != type)
		return eTypeError;

	getInt((*ppbuffer), (*pleft));
	return eOK;
}


void WriteData(AMUInt8	**ppbuffer, AMChar *data, AMUInt32 dataLen, AMUInt8 padding, AMUInt32 len)
{
	AMUInt32 i=0;
	AMAssert( ppbuffer && *ppbuffer);
	if(dataLen < len)
	{
		AMMemcpy(*ppbuffer, data, dataLen);
		*ppbuffer += dataLen;
		AMMemset(*ppbuffer, padding, len-dataLen);
		*ppbuffer += len-dataLen;
	}
	else
	{
		AMMemcpy(*ppbuffer, data, len);
		*ppbuffer += len;
	}
}

AMInt32 ReadData(AMUInt8	**ppbuffer, AMChar **data, AMUInt32 *dataLen, AMUInt32 len)
{
	AMAssert(ppbuffer && *ppbuffer && data);
	*data = (AMChar *)AMMalloc(len);
	if (*data == AMNULL)
		return eMallocError;

	AMMemset(*data, 0, len);
	AMMemcpy(*data, *ppbuffer, len);
	*dataLen = len;
	*ppbuffer += len;
	return eOK;
}

/************************************************************************/
// HexStringToByte
/************************************************************************/
void HexStringToByte(AMUInt8* psrc, AMInt32 srcLen, AMChar* pdst) 
{
	AMInt32 len = srcLen/2;
	AMInt32 pos = 0;
	AMInt32 i;
	AMChar hi,lw;

	for (i = 0; i < len; i++) 
	{
		pos = i * 2;
		hi = *(psrc+pos);
		lw = *(psrc+pos+1);

		if(hi>='a')
			hi = hi - 'a' + 10;
		else
			hi = hi -'0';

		if(lw>='a')
			lw = lw - 'a' + 10;
		else
			lw = lw -'0';

		pdst[i] = hi << 4 | lw;
	}
}

/************************************************************************/
// String2Long 此函数需要修改
/************************************************************************/
void String2Long(AMChar* pSrc, AMInt32* pHi, AMInt32* pLw)
{
	//上限
	//2^64-1 = 1844 6744 0737 0955 1615;
	
	//pSrc = "18446744073709551615"
	//   等价于
	//hi = FFFFFFFF, Lw = FFFFFFFE

	if(pHi != NULL && pLw != NULL)
	{	
		if(pSrc == NULL)
		{
			*pHi = 0;
			*pLw = 0;
		}
		else
		{
			*pHi = atoi(pSrc);
			*pLw = 0; 
		}
	}
}

/************************************************************************/
// Long2String 此函数需要修改
/************************************************************************/
void Long2String(AMChar* pDst, AMInt32 Hi, AMInt32 Lw)
{
#ifdef WIN32
	_ltoa(Lw, pDst, 10);	
#else
	//denx: 暂时不支持longlong. 换成itoa.
	//ltoa(Lw, pDst, 10);
	AMitoa(Lw, pDst);	
#endif
}

#if 0
#ifdef AMOS_DEBUG
#ifdef WIN32
#include "stdarg.h"
#endif
int AMPrintf(const AMChar *fmt, ...)
{
  char printf_buf[512];
  va_list args;
  int printed;

  va_start(args, fmt);
#ifdef AMOS
  printed = AMvsprintf(printf_buf, fmt, args);
#else
	#ifdef WIN32
	  printed = vsprintf(printf_buf, fmt, args);
	#else
	  printf("no support.\n");
	  return 0;
	#endif
#endif
  va_end(args);

#ifdef AMOS
  AMLogForInfo("IMnet", printf_buf); 
#else
  printf("\n[IMnet]:%s\n", printf_buf);
#endif
  
  return printed;
}
#endif
#endif

int AMitoa(int val, char* buf)
{
	const unsigned int radix = 10;
	char* p;
	unsigned int a; //every digit
	int len;
	char* b; //start of the digit char
	char temp;
	unsigned int u;

	p = buf;
	if (val < 0)
	{
		*p++ = '-';
		val = 0 - val;
	}

	u = (unsigned int)val;
	b = p;

	do
	{
		a = u % radix;
		u /= radix;
		*p++ = a + '0';
	} while (u > 0);

	len = (int)(p - buf);
	*p-- = 0;

	//swap
	do
	{
		temp = *p;
		*p = *b;
		*b = temp;
		--p;
		++b;
	} while (b < p);

	return len;
}


AMUInt8* DesEncrypt(AMUInt8* des_key, AMUInt8* des_data, EncryptType type)
{
	if(type == eDecrypt)
	{
		return des_decrypt(des_key, des_data, 8);
	}
	else
	{
		return des_encrypt(des_key, des_data, 8);
	}
}

AMInt32 ZipInflate(AMUInt8* src, AMInt32 srcLen, AMUInt8* dst, AMInt32 dstLen)
{
	uncompress (dst, (unsigned long*)&dstLen, src, (unsigned long)srcLen);
	return dstLen;
}

AMInt32	ZipDeflate(AMUInt8 *dst, AMInt32 *dstLen, AMUInt8 *src, AMInt32 srcLen)
{
	unsigned long ulDestLen = dstLen;
	compress(dst, &ulDestLen, src, srcLen);
	*dstLen = ulDestLen;
	return *dstLen;
}

PCRetCode	StrStrItem_setValue(StrStrPair *pItem, const AMChar *szValue, AMInt32 iLen);
PCRetCode	StrStrItem_setKey(StrStrPair *pItem, const AMChar *szKey, AMInt32 iLen);

PCRetCode	StrStrItem_Create(StrStrPair **ppItem, const AMChar *szKey, const AMChar *szValue)
{
	PCRetCode	retCode = 0;
	AMAssert(NULL != ppItem);
	*ppItem = AMMalloc(sizeof(StrStrPair));
	if(NULL == *ppItem)
		return eMallocError;

	AMMemset(*ppItem, 0, sizeof(StrStrPair));

	if(NULL != szKey && eOK != (retCode = StrStrItem_setKey(*ppItem, szKey, strlen(szKey))))
		return retCode;

	if(NULL != szKey && eOK!= (retCode = StrStrItem_setValue(*ppItem, szValue, strlen(szValue))))
	{
		AMFree((*ppItem)->szValue);
		(*ppItem)->szValue = NULL;

		return retCode;
	}

	return eOK;
}

PCRetCode	StrStrItem_Destroy(StrStrPair *pItem)
{
	if(NULL == pItem)
		return eInvalidParam;

	if(NULL != pItem->szKey)
	{
		AMFree(pItem->szKey);
		pItem->szKey = NULL;
	}

	if(NULL != pItem->szValue)
	{
		AMFree(pItem->szValue);
		pItem->szValue = NULL;
	}

	AMFree(pItem);

	return eOK;
}

PCRetCode	StrStrItem_setKey(StrStrPair *pItem, const AMChar *szKey, AMInt32 iLen)
{
	AMInt32 i=0;

	if(NULL == pItem)
		return eInvalidParam;

	if(NULL == szKey || iLen == 0)
		return eOK;

	pItem->szKey = AMMalloc(iLen + 1);
	if(NULL == pItem->szKey)
		return eMallocError;

	for(i=0; i<iLen; i++)
		pItem->szKey[i] = szKey[i];
	pItem->szKey[iLen] = 0;

	return eOK;
}

PCRetCode	StrStrItem_setValue(StrStrPair *pItem, const AMChar *szValue, AMInt32 iLen)
{
	AMInt32 i=0;

	if(NULL == pItem)
		return eInvalidParam;

	if(NULL == szValue || iLen == 0)
		return eOK;

	pItem->szValue = AMMalloc(iLen + 1);
	if(NULL == pItem->szValue)
		return eMallocError;

	for(i=0; i<iLen; i++)
		pItem->szValue[i] = szValue[i];
	pItem->szValue[iLen] = 0;

	return eOK;
}
AMInt32	StrStrItem_CmpKey(const AMVoid *pItemA, const AMVoid *pItemB, AMUInt32 uiSize)
{
	StrStrPair *pA = (StrStrPair*)pItemA,
				*pB = (StrStrPair*)pItemB;
	AMAssert(NULL != pA && NULL != pB);
	AMAssert(NULL != pA->szKey && NULL != pB->szKey);

	return strcmp(pA->szKey, pB->szKey);
}

AMUInt32 StrStrItem_Hash( const AMVoid *pItem, AMUInt32 uiSize)
{
	AMUInt32 uiRet = 0;
	AMChar *str = ((StrStrPair *)pItem)->szKey;
	AMAssert(0 != str);
	while(*str != 0)
		uiRet = (uiRet << 5) + (*str++);

	return uiRet;
}

PCRetCode GetSctStrStrMap(AMUInt8 **ppBuffer, OHTable **ppOhtable, AMInt32 *piLen)
{
	PCRetCode retCode = eOK;
	StrStrPair* pItem = NULL;
	AMUInt8 type = 0;
	AMUInt8 keyType = 0;
	AMUInt8 valueType = 0;
	AMUInt8 size = 0;
	AMInt32	iTotalStringLen = 0;

	getByte((*ppBuffer), type);
	if (FT_MAP != type)
		return eTypeError;

	getByte((*ppBuffer), type);
	if (FT_STRING != type)
		return eTypeError;

	getByte((*ppBuffer), type);
	if (FT_STRING != type)
		return eTypeError;

	getByte((*ppBuffer), size);
	if(0 == size)
		return eOK;

	AMAssert(NULL == *ppOhtable);

	*ppOhtable = (OHTable*)AMMalloc(sizeof(OHTable));
	AMAssert(NULL != *ppOhtable);
	AMMemset(*ppOhtable, 0, sizeof(OHTable));
	construct(OHTable, *ppOhtable, sizeof(StrStrPair), FREEOBJ);
	set_compare(OHTable, (*ppOhtable), StrStrItem_CmpKey);
	set_dealloc(OHTable, (*ppOhtable), StrStrItem_Destroy);
	set_hash_OHTable(*ppOhtable, StrStrItem_Hash);

	iTotalStringLen = 0;
	while(size --)
	{   
		retCode = StrStrItem_Create(&pItem, NULL, NULL);

		if(retCode != eOK)
		{
			destruct(OHTable, *ppOhtable);
			AMFree(*ppOhtable);
			return retCode;
		}

		retCode = GetStringAlloc(ppBuffer, &pItem->szKey, &pItem->iKeyLen);
		if(retCode != eOK)
		{
			StrStrItem_Destroy(pItem);
			destruct(OHTable, *ppOhtable);
			AMFree(*ppOhtable);
			return	retCode;
		}

		iTotalStringLen += pItem->iKeyLen;

		retCode = GetStringAlloc(ppBuffer, &pItem->szValue, &pItem->iValueLen);
		if(retCode != eOK)
		{
			StrStrItem_Destroy(pItem);
			destruct(OHTable, *ppOhtable);
			AMFree(*ppOhtable);
			return retCode;
		}

		iTotalStringLen += pItem->iValueLen;

		insert_OHTable(*ppOhtable, pItem, sizeof(StrStrPair), DYNAMIC);
	}

	if(piLen)
		*piLen = iTotalStringLen;

	return eOK;
}
