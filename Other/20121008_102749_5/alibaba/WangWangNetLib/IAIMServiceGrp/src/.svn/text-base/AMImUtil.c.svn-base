#include "AIMUtil.h"
#include "IAIM.h"

#include <ctype.h>

#include "AMString.h"
#include "AMMemory.h"
#include "AMAssert.h"
#include "AMFS.h"
#include "ghttp.h"

#include <string.h>
#include <stdlib.h>

DataBasePath gDatabasePath = {{0},0};

#ifdef WIN32
#include <direct.h>
AMVoid  CreatePath(AMChar *p ) 
{
	int i = _mkdir(p);
}
#else
#include <unistd.h>
void CreatePath( char *p ) 
{
	int i,len;
	len=strlen(p);

	for( i=0; i<len; i++ )
	{
		if( p[i]=='/' )
		{
			p[i] = '\0'; //may segment fault??
			if( access(p, F_OK)!=0 )
			{
				mkdir( p, 0777 );
			}
			p[i]='/';
		}
	}
	if( len>0 && access(p, F_OK)!=0 )
	{
		mkdir( p, 0777 );
	}
}
#endif


//must like this: "/xxx/xxx/" on linux.
//or like this: "x:\\xxx\\" on winos.
void IAIM_SetGlobalDatabasePath(AMChar* pPath)
{
	AMInt32 length = 0;
	if(pPath)
	{
        DataBasePath gDatabasePathTemp = {{0},0};
        AMStrcpy(gDatabasePathTemp.databasePath, pPath);
		gDatabasePathTemp.headPathLength = strlen(pPath);
		//if dir not exist, create it.
		CreatePath(gDatabasePathTemp.databasePath);
        
        AMStrcpy(gDatabasePath.databasePath, pPath);
		gDatabasePath.headPathLength = strlen(pPath);
        
	}
}

AIM_PRESENCE convert2Status(AMUInt8 basicStatus, AMUInt8 predefStatus){
	switch (basicStatus)
	{
	case 0:
		switch (predefStatus)
		{
		case eAIM_PRESENCE_OFFLINE:
		case eAIM_PRESENCE_OFF_LOGIN:
		case eAIM_PRESENCE_UNKNOW:
		case eAIM_PRESENCE_FAKE_ONLINE:
		case eAIM_PRESENCE_NOT_USED:
		case eAIM_PRESENCE_SMS:

		case eAIM_PRESENCE_MOBILE_OFFLINE:
		case eAIM_PRESENCE_MOBILE_OFF_LOGIN:
		case eAIM_PRESENCE_MOBILE_UNKNOW:
			return predefStatus;
		default:
			return eAIM_PRESENCE_OFFLINE;
		}
	case 1:
		switch(predefStatus)
		{
		case eAIM_PRESENCE_ONLINE:
		case eAIM_PRESENCE_BUSY:			
		case eAIM_PRESENCE_AWAY:			
		case eAIM_PRESENCE_ON_PHONE:			
		case eAIM_PRESENCE_OUT2LUNCH:			
		case eAIM_PRESENCE_RIGHT_BACK:

		case eAIM_PRESENCE_MOBILE_ONLINE:
		case eAIM_PRESENCE_MOBILE_BUSY:
		case eAIM_PRESENCE_MOBILE_AWAY:
		case eAIM_PRESENCE_MOBILE_ON_PHONE:
		case eAIM_PRESENCE_MOBILE_OUT2LUNCH:
		case eAIM_PRESENCE_MOBILE_RIGHT_BACK:
			return predefStatus;

		case eAIM_PRESENCE_MOBILE:
			return eAIM_PRESENCE_MOBILE_ONLINE;

		default:
			return eAIM_PRESENCE_ONLINE;
		}
	case 2:
		switch (predefStatus)
		{
		case eAIM_PRESENCE_INVISIBLE:
		case eAIM_PRESENCE_MOBILE_INVISIBLE:
			return predefStatus;
		default:
			return eAIM_PRESENCE_INVISIBLE;
		}
	default:
		return eAIM_PRESENCE_OFFLINE;	
	}
}

AMUInt8 getBasicStatus(AIM_PRESENCE status){
	if((status > eAIM_PRESENCE_OFFLINE && status < eAIM_PRESENCE_INVISIBLE) 
		|| status == eAIM_PRESENCE_MOBILE
		|| status > eAIM_PRESENCE_MOBILE_OFFLINE && status < eAIM_PRESENCE_MOBILE_INVISIBLE)
	{
		return eAIM_PRESENCE_ONLINE;
	}
	else if( eAIM_PRESENCE_INVISIBLE == status
			|| eAIM_PRESENCE_MOBILE_INVISIBLE == status)
	{
		return eAIM_PRESENCE_BUSY;//ÒþÉíµÄBasicStatusÊÇ2
	}
	else if(status >= eAIM_PRESENCE_OFF_LOGIN && status <= eAIM_PRESENCE_SMS
			|| status >= eAIM_PRESENCE_MOBILE_OFF_LOGIN && status <= eAIM_PRESENCE_MOBILE_UNKNOW)
	{
		return eAIM_PRESENCE_OFFLINE;
	}
	else
	{
		return eAIM_PRESENCE_WRONG;
	}
}

AMUInt8 getPredefStatus(AIM_PRESENCE status) {
	if( eAIM_PRESENCE_OFFLINE <= status && status <=eAIM_PRESENCE_SMS 
		|| eAIM_PRESENCE_MOBILE_OFFLINE <= status && status < eAIM_PRESENCE_MOBILE_UNKNOW )
		return status;
	else if(eAIM_PRESENCE_MOBILE == status)
		return eAIM_PRESENCE_MOBILE_ONLINE;
	else
		return eAIM_PRESENCE_WRONG;
}

int _AIMItoa(AMInt64 val, char* buf)
{
	const unsigned int radix = 10;
	char* p;
	unsigned int a; //every digit
	int len = 0;
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

AMInt32 myADB_Open(const AMChar *szName, sqlite3 **ppDB, AMBool bTry)
{	
	AMInt32 index = gDatabasePath.headPathLength;
	AMInt32 iRetCode;
	DPRINT("Openning Database: %s%s\n", gDatabasePath.databasePath, szName);
	
	while(*szName)
		index += _AIMItoa(*((AMUChar *)(szName++)), gDatabasePath.databasePath+index);

	DPRINT("Openning real Database: %s\n", gDatabasePath.databasePath);

	if(AMTRUE == bTry)
	{
		iRetCode = sqlite3_open_v2(gDatabasePath.databasePath, ppDB, SQLITE_OPEN_READONLY, 0);
	}
	else
	{
		iRetCode = sqlite3_open(gDatabasePath.databasePath, ppDB);
	}

	memset(gDatabasePath.databasePath + gDatabasePath.headPathLength, 0, index);

	return iRetCode;
}

AMChar * _StrDupLen(const AMChar *szStr, AMInt32 iLen)
{
	AMChar *szRet = (AMChar *)AMMalloc(iLen+1);
	AMAssert(szRet);
	AMMemcpy(szRet, szStr, iLen);
	szRet[iLen] = 0;
	return szRet;
}

AMChar* _UrlGet(const AMChar *url, AMInt32 timeout)
{
	return _UrlGetProc(url, timeout, AMNULL);
}

AMChar* _UrlGetProc(const AMChar *url, AMInt32 timeout, AMInt32 *piLen)
{
	AMChar *p = AMNULL;
	AMChar *response = AMNULL;
	AMInt32 status, time = 0;
	AMChar *content = AMNULL;
	int len = 0;
	ghttp_request *request = AMNULL;

	if(piLen)
		*piLen = 0;

	request = ghttp_request_new();
	ghttp_set_uri(request, url);
	ghttp_set_header(request, http_hdr_Connection, "close");
	ghttp_set_sync(request, ghttp_async); 
	ghttp_set_type(request, ghttp_type_get);
	ghttp_prepare(request);

	time = 0;

	while(1){
		status = ghttp_process(request);
		DPRINT("ghttp_process.............................%d\n", status);
		if(status == ghttp_done) {
			content = ghttp_get_body(request);
			len = ghttp_get_body_len(request);
			break;
		}else if(status == ghttp_not_done){
			AMSleep(200);   //sleep for 200 millSeconds
			time += 200;
			if(time >= timeout){
				ghttp_close(request);
				break;
			}
			continue;
		}else{
			DPRINT("ghttp_process............................%s\n", ghttp_get_error(request));
			ghttp_request_destroy(request);
			return AMNULL;
		}
	}

	if(content == AMNULL)
	{
		ghttp_request_destroy(request);			
		return AMNULL;
	}

	response = (AMChar*)AMMalloc(len+1);
	AMMemcpy(response, content, len);
	response[len] = 0;
	if(piLen)
		*piLen = len;
	ghttp_request_destroy(request);
	return response;
}
