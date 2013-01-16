#include "stdio.h"
#include "string.h"
#include "memory.h"
#ifdef AMOS
#include "AMOs.h"
#else
#ifdef WIN32
#include "windows.h"
#endif
#endif
#include "IMnet.h"

IMnetHandle ghHandle = NULL;
/************************************************************************/
//test
/************************************************************************/
IMnetRetCode OnNetworkConfig(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	PcEventNetworkConfig* pConfirm = (PcEventNetworkConfig*)pEventContent;

	if(pConfirm->result > 0)
	{
		printf(".... 网络连接成功 \t\t....\n");
		//cntaobaoabc123_四季 2048
		//cntaobao小果果
		printf(".... 登录用户:%s \t....\n", "cntaobaosymbiane66");
		return IMnetLogin(hIMnetHandle, "cntaobaosymbiane66", "system1", 0, 0, 0, 0, 0);
		//return IMnetLogin(hIMnetHandle, "cntaobaoabc123_四季", "system", 0, 0, 0, 0);
	}
	else
		return eNotReady;
}

IMnetRetCode OnLogin(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	return IMnetPostLogin(hIMnetHandle, 1,1);
}

IMnetRetCode OnCheckVersion2(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	return eOK;
}

IMnetRetCode OnCheckVersion3(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	return eOK;
}

void onHelp(IMnetHandle hHandle)
{
	printf("-------------------------------------------------\n");
	printf(" help:			type \"help\" and \"?\" to show this.\n");
	printf(" create:		create IMnet module.\n");
	printf(" exit:			exit IMnet module.\n");
	printf(" connect: 		connect to server.\n");
	printf(" login:			login.\n");
	printf(" sendmsg:		send message to somebody.\n");
	printf(" relogin:		reLogin again.\n");
	printf(" logoff:		logoff.\n");
	printf(" postlogin:		postLogin.\n");
	printf(" addblack:		add somebody to black.\n");
	printf(" delblack:		delete black.\n");
	printf(" addcontact:		add somebody to contact.\n");
	printf(" delcontact:		delete contact.\n");
	printf(" changestatus:		change status.\n");
	printf(" delofflinemsg:		delete offline messages.\n");
	printf(" subscribe:		subscribe contact info.\n");
	printf("-------------------------------------------------\n");
}

void onConnect(IMnetHandle hHandle)
{
	char ip[5];

choice:
	memset(ip, 0, sizeof(ip));
	printf("connect to: \n 1:生产环境:110.75.161.60:16000\n 2:测试环境:121.0.29.29:16000\nYou choice[1 or 2]:");
	scanf("%s",ip);

	//生产环境
#define IP_ADDRESS1 "110.75.161.60"
	//测试环境
#define IP_ADDRESS2 "121.0.29.29"
#define IP_PORT		16000

	if(strcmp(ip, "1") == 0)
	{
		printf(".... 连接到%s:%d \t....\n", IP_ADDRESS1, IP_PORT);
		IMnetNetworkConfig(hHandle, IP_ADDRESS1, IP_PORT, 0);
	}
	else if(strcmp(ip, "2") == 0)
	{
		printf(".... 连接到%s:%d \t....\n", IP_ADDRESS2, IP_PORT);
		IMnetNetworkConfig(hHandle, IP_ADDRESS1, IP_PORT, 0);
	}
	else
	{
		printf("You choose error. Choose again!\n");
		goto choice;
	}
}

void onCreate(IMnetHandle hHandle)
{
	IMnetRetCode retCode;
	printf(".... IMnet模块创建 ....");
	retCode = IMnetMainCreate(&ghHandle, NULL);
	if(retCode == eOK)
		printf("\t创建成功\n");
	else
		printf("\t创建失败\n");

	printf(".... 注册消息回调 ....\t注册成功\n");
}

void onExit(IMnetHandle hHandle)
{
	printf(".... Destroy IMnet ....\n");
	IMnetMainDestory(hHandle);
	printf(".... 销毁成功 ....\n");
}

void onLogin(IMnetHandle hHandle)
{
	char name[50];
	char password[50];
	memset(name, 0, sizeof(name));
	memset(password, 0, sizeof(password));

login:
	printf("Login: 1.cntaobaosymbian66 2.cntaobaoabc123_四季\nYou choice[1 or 2]:");
	scanf("%s",name);

	//cntaobaoabc123_四季 2048
	//cntaobao小果果
	if(strcmp(name, "1") == 0)
		IMnetLogin(hHandle, "cntaobaosymbiane66", "system1", 0, 0, 0, 0, 0);
	else if(strcmp(name, "2") == 0)
		IMnetLogin(hHandle, "cntaobaoabc123_四季", "system", 0, 0, 0, 0, 0);
	else
		goto login;
}

void onPostLogin(IMnetHandle hHandle)
{
	IMnetPostLogin(hHandle, 1,1);
}

IMnetRetCode onAddContactRsp(IMnetHandle hIMnetHandle, EventContent* pEventContent)
{
	int i;
	ImEventAddContact* p = (ImEventAddContact*)pEventContent;

	if(p->retCode == 1)
		IMnetSendVerifyInfo(hIMnetHandle, "cntaobao专业色郎", "xx", "test");
	else if(p->retCode == 2)
	{
		i++;
		//; waiting for auth.
	}
	else if(p->retCode == 0)
	{
		i++;
		//; ok
	}
	else if(p->retCode == -1)
	{
		if(p->info == eIMADDCONTACTRESULT_NEEDAUTH)
			IMnetSendVerifyInfo(hIMnetHandle, "cntaobao专业色郎", "xx", "test");
	}
	else
	{
		i++;
	}

	return eOK;
}

void onAddContact(IMnetHandle hHandle)
{
	IMnetMainRegister(hHandle, IM_EVENT_ADDCONTACT, onAddContactRsp);
	IMnetAddContact(hHandle, "cntaobao专业色郎", 0, 0, 0);
}

#ifdef AMOS
	int wmain(void)
#else
	#ifdef WIN32
	int main(void)
	#endif
#endif
{
	char cmd[100];
	int i;

	typedef void (*Function)(IMnetHandle hHandle);

	typedef struct {
		char*		pCmd;
		Function	pFunc;
	}CmdMap;

	CmdMap map[] = {
		{"help"		,	onHelp		},
		{"?"		,	onHelp		},
		{"connect"	,	onConnect	},
		{"exit"		,	onExit		},
		{"create"	,	onCreate	},
		{"login"	,	onLogin		},
		{"postlogin",	onPostLogin },
		{"addcontact",  onAddContact},
	};

	while(1)
	{
		memset(cmd, 0, sizeof(cmd));
		printf("# ");
		scanf("%s",cmd);

		for(i=0; i<sizeof(map)/sizeof(map[0]); i++)
		{
			if(strcmp(map[i].pCmd, cmd)==0)
			{
				map[i].pFunc(ghHandle);
				break;
			}
		}
		
		if(i==sizeof(map)/sizeof(map[0]))
			printf("unknow cmd.\n");
		printf("\n");
	}
}

