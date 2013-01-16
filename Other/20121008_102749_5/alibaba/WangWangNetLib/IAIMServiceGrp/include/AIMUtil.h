#ifndef __AMIMUTIL_H__
#define __AMIMUTIL_H__

#include "sqlite3.h"
#include "AMTypes.h"
#include "AIMEnum.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AIM_ANDROID_ALAN	1

#define IM_NET_RETRY_MAX	2
#define	MAX_SQL_LEN			256
#define MAX_ID_LEN				64
#define MAX_PHONE_NUMBER_LEN	32
#define MAX_INT_NUMBER_LEN		32
#define MAX_TOKEN_LEN			64

#define		MAX_SIG_COUNT		5
#define		MAX_SIG_LEN		128

	//需要处理 MAX_SQL_LEN

#define	MAX_RECENT_NUM		50
#define MAX_STRANGE_NUM		50

#define IM_ACNT_DB		"imaccountdb"


#define IAImCheckEqual(A, B, R)		do \
									{\
										if((A) != (B)) return (R);\
									} while (0)
#define IAImCheckNotEqual(A, B, R)	do \
									{\
										if((A) == (B)) return (R);\
									} while (0)


//内网测试环境
#define	MAX_IP_LEN			16
#define MAX_PORT_LEN		16

#define IP_PORT_TEST		16000
#define IP_ADDRESS_TEST     "10.250.3.153"

// 公网生产环境
#define IP_PORT_REAL		_uiIpPort
#define IP_ADDRESS_REAL		_szIpAddress


#define			SQL_INSERT_MSG		"INSERT INTO _msg VALUES(NULL,'%q',%d,%d,'%q',%d);"
#define			SQL_INSERT_CNT		"INSERT INTO _contactlist VALUES(NULL,%lld,'%q','%q','%q');"
#define			SQL_UPDATE_SIGXML	"UPDATE _account SET _sigxml='%q' WHERE _rid=%lld;"
#define			SQL_INSERT_GRP		"INSERT INTO _grouplist VALUES(NULL,%lld,%lld,'%q');"

#ifdef AMOS_DEBUG
#define DPRINT(format, ...)		AMPrintf("imapiok :"format, ## __VA_ARGS__)
#else
#define DPRINT(format, ...)
#endif

#if defined(_WIN32)        //windows and wince
#define I64FORMAT				"%I64d"
#else
#define I64FORMAT				"%lld"
#endif

	typedef	enum {
		eAIM_PRIVATE_EVENT_CNTDATA = 0,
		eAIM_PRIVATE_EVENT_ALLOT,
		eAIM_PRIVATE_EVENT_PORTRAIT,
		eAIM_PRIVATE_EVENT_SIGNATURE,
		eAIM_PRIVATE_EVENT_OPERATION_MESSAGE,
		eAIM_PRIVATE_EVENT_CAPCHA,
	}AIM_PRIVATE_EVENT_TYPE;

typedef struct {
	AMInt32	iEventType;		//0				1			2			3			5
	AMInt32 iParam1;		//eType			0			0			iCount		iAuthId
	AMInt64 i64Param2;		//hGroup		0			0			0
	AMChar *szParam3;		//hContact		NULL		szCntId		szCntIds
} AIM_PRIVATE_EVENT;


typedef struct {
	AMChar	databasePath[512];
	AMInt32 headPathLength;
}DataBasePath;

AIM_PRESENCE convert2Status(AMUInt8 basicStatus, AMUInt8 predefStatus);
AMUInt8 getBasicStatus(AIM_PRESENCE status);
AMUInt8 getPredefStatus(AIM_PRESENCE status);
/*AMInt64 AMAtoi64(const char *nptr);*/
AMInt32 myADB_Open(const AMChar *szName, sqlite3 **ppDB, AMBool bTry);
AMInt32 _AIMItoa(AMInt64 val, AMChar* buf);
AMChar * _StrDupLen(const AMChar *szStr, AMInt32 iLen);
void IAIM_SetGlobalDatabasePath(AMChar* pPath);
AMChar* _UrlGet(const AMChar *url, AMInt32 timeout);
AMChar* _UrlGetProc(const AMChar *url, AMInt32 timeout, AMInt32 *piLen);
#ifdef __cplusplus
};
#endif

#endif