#ifndef __PC_UTILITY_H__
#define __PC_UTILITY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hashtable.h"
#include "PacketConnection.h"

	/************************************************************************/
	// prototype size
	/************************************************************************/
#define FT_PACK		0
#define FT_INT8		1
#define FT_UINT8	2
#define FT_INT16	3
#define FT_UINT16	4
#define FT_INT32	5
#define FT_UINT32	6
#define FT_INT64	7
#define FT_UINT64	8
#define FT_STRUCT	9
#define FT_MAP		10
#define FT_STRING	0x40
#define FT_VECTOR	0x50

	/************************************************************************/
	// prototype put.
	/************************************************************************/
#define putShort(b, val)							\
	*((b)++) = (AMUInt8) ((val) >> (8));		    \
	*((b)++) = (AMUInt8) ((val) >> (0));		

#define putInt(b, val)								\
	*((b)++) = (AMUInt8) ((val) >> (24));		    \
	*((b)++) = (AMUInt8) ((val) >> (16));		    \
	*((b)++) = (AMUInt8) ((val) >> (8));		    \
	*((b)++) = (AMUInt8) ((val) >> (0));		

#define putByte(b, val)								\
	*((b)++) = (val);								

#define putString(b, val, len)						\
	putInt((b),(len));	        					\
	if(len != 0) {									\
	memcpy((b), (val), (len));                      \
	(b)+=(len);	};

#define putLong(b, up, lw)							\
	putInt((b), (up));								\
	putInt((b), (lw));								

	/************************************************************************/
	// struct put
	/************************************************************************/
#define putSctByte(b, val)							\
	putByte((b), FT_UINT8);							\
	putByte((b), (val));							

#define putSctShort(b, val)							\
	putByte((b), FT_UINT16);						\
	putShort((b), (val));

#define putSctInt(b, val)							\
	putByte((b), FT_UINT32);						\
	putInt((b), val);

#define putSctLong(b, up, lw)						\
	putByte((b), FT_INT64);							\
	putLong(b, up, lw);

#define putSctULong(b, up, lw)						\
	putByte((b), FT_UINT64);						\
	putLong(b, up, lw);

#define putSctString(b, val, len)					\
	putByte((b), FT_STRING);						\
	putString((b), val, len);							

#define putStrByte(b, val, len)						\
	putByte((b), FT_STRING);						\
	putInt((b), len);								\
	memcpy((b), val, len);							\
	(b)+=len;

#define putVectorInt(b, vectInt, length)			\
	putByte((b), FT_VECTOR);						\
	putByte((b), FT_UINT32);						\
	putInt((b), length);							\
	for (i = 0; i < length; i++){					\
	putInt((b), vectInt[i]);						\
	}

#define putVectorStr(b, vectStr, length)			\
	putByte((b), FT_VECTOR);						\
	putByte((b), FT_STRING);						\
	putInt((b), length);							\
	for(i = 0; i < length; i++){					\
	putString((b),(vectStr[i]),strlen(vectStr[i])); \
	}

	/************************************************************************/
	// prototype get
	/************************************************************************/
#define getProtocolBodyLength(len)					\
	(0==(len) ? 0 : ((len) / 8 + 1) * 8)		
	/*
	#define getLongValue(b, off)					\
	( ((b[off + 7] & 0xFFL) << 0) +					\
	((b[off + 6] & 0xFFL) << 8) +					\
	((b[off + 5] & 0xFFL) << 16) +					\
	((b[off + 4] & 0xFFL) << 24) +					\
	((b[off + 3] & 0xFFL) << 32) +					\
	((b[off + 2] & 0xFFL) << 40) +					\
	((b[off + 1] & 0xFFL) << 48) +					\
	((b[off + 0] & 0xFFL) << 56) )
	*/	

#define getIntValue(b, off)							\
	( ((b[off + 3] & 0xFF) << 0)  +					\
	((b[off + 2] & 0xFF) << 8)  +					\
	((b[off + 1] & 0xFF) << 16) +					\
	((b[off + 0] & 0xFF) << 24) )

#define getShortValue(b, off)						\
	( ((b[off + 1] & 0xFF) << 0) +					\
	((b[off + 0] & 0xFF) << 8) )

#define getByte(b, left)							\
	(left) = *((b)++);	

#define getLeftBytes(bt, bd, len)					\
	memcpy((bd), (bt), (len));						\
	(bt)+=(len);

#define getInt(b, left)								\
	(left) = getIntValue((b), 0);					\
	(b)+=4;

#define getLong(b, up, lw)							\
	getInt((b), (up));								\
	getInt((b), (lw));

#define getShort(b, left)							\
	(left) = getShortValue((b), 0);					\
	(b)+=2;

#define getString(b, left, len)						\
	memcpy((left), (b), len);						\
	(b)+=len;

typedef enum {
	eDecrypt,
	eEncrypt
}EncryptType;	

	PCRetCode GetSctByte(AMUInt8** ppbuffer, AMInt8* pleft);
	PCRetCode GetSctLong(AMUInt8** ppbuffer, AMInt32* pHigher, AMInt32* pLower);
	PCRetCode GetSctULong(AMUInt8** ppbuffer, AMInt32* pHigher, AMInt32* pLower);
	PCRetCode GetSctInt(AMUInt8** ppbuffer, AMInt32* pleft);
	PCRetCode GetSctShort(AMUInt8** ppbuffer, AMInt16* pleft);
	PCRetCode GetSctString(AMUInt8** ppbuffer, AMInt8** ppdes, AMInt32* pLen);
	PCRetCode GetStringAlloc(AMUInt8** ppbuffer, AMInt8** ppdes, AMInt32* pLen);
	PCRetCode GetVectorStructLen(AMUInt8** ppbuffer, AMInt32* pleft);
	PCRetCode GetVectorStrLen(AMUInt8** ppbuffer, AMInt32* pleft);

	
	void WriteData(AMUInt8	**ppbuffer, AMChar *data, AMUInt32 dataLen, AMUInt8 padding, AMUInt32 len);
	AMInt32 ReadData(AMUInt8	**ppbuffer, AMChar **data, AMUInt32 *dataLen, AMUInt32 len);


	void HexStringToByte(AMUInt8* psrc, AMInt32 srcLen, AMChar* pdst);
	void String2Long(AMChar* pSrc, AMInt32* pUp, AMInt32* pLw);
	void Long2String(AMChar* pDst, AMInt32 Hi, AMInt32 Lw);
	int AMitoa(int val, char* buf);

	PCRetCode GetSctStrStrMap(AMUInt8 **ppBuffer, OHTable **ppOhtable, AMInt32 *piLen);

	AMUInt8* DesEncrypt(AMUInt8* des_key, AMUInt8* des_data, EncryptType type);
	AMInt32 ZipInflate(AMUInt8* src, AMInt32 srcLen, AMUInt8* dst, AMInt32 dstLen);
	AMInt32	ZipDeflate(AMUInt8 *dst, AMInt32 *dstLen, AMUInt8 *src, AMInt32 srcLen);

#ifdef __cplusplus
}
#endif


#endif
