#include "AIMAccountModel.h"
#include "AIMUtil.h"

#include "sqlite3.h"

#include "AMString.h"
#include "AMMemory.h"
#include "AMAssert.h"
#include "AMStdlib.h"

AMBool			IAccountModel_IsDirt(IAccountModel	*pAcntModel)
{
	AMAssert(0 != pAcntModel);
	if(0 != (pAcntModel->uiDirtFlag&0x01))
		return AMTRUE;
	return AMFALSE;
}

AMVoid			IAccountModel_ClearDirt(IAccountModel *pAcntModel)
{
	AMAssert(0 != pAcntModel);
	pAcntModel->uiDirtFlag &= ~0x01;
}

AMVoid			IAccountModel_MarkDirt(IAccountModel *pAcntModel)
{
	AMAssert(0 != pAcntModel);
	pAcntModel->uiDirtFlag |= 0x01;
}

static AMInt32 IAccountModel_OnSelAcnt(void* pvAcntor, int iCnt, char **pszValue, char**pszName)
{
	IAccountModel *pAcntModel = (IAccountModel *)pvAcntor;
	AIMAccount *pAcnt = 0;
	AMAssert(0 !=pAcntModel);

	DPRINT("IAccountModel_OnSelAcnt %s ! %s ! %s ! %s ! %s ! %s ! %s\n"
		, pszValue[0], pszValue[1], pszValue[2], pszValue[3], pszValue[4], pszValue[5], pszValue[6]);

	pAcnt = IAccount_Create();

	pAcnt->_iRid =			AMAtoi(pszValue[0]);

	if(0 != IAccount_SetID(pAcnt, pszValue[1], AMStrlen(pszValue[1])))
		return -1;

	pAcnt->uiFlag =	AMAtoi(pszValue[4]);

	if(pAcnt->uiFlag&01 && 0 != AMStrcmp("0", pszValue[2]))
	{
		IAccount_SetToken(pAcnt, pszValue[2], AMStrlen(pszValue[2]));
	}

	if(0 != AMStrcmp("0", pszValue[3]))
	{
		IAccount_SetPhoneNum(pAcnt, pszValue[3]);
	}
	pAcnt->ePresence =		AMAtoi(pszValue[5]);
	pAcnt->iGroupStamp =	AMAtoi(pszValue[6]);
	pAcnt->iContactStamp =	AMAtoi(pszValue[7]);
	pAcnt->iBlackStamp =	AMAtoi(pszValue[8]);
	pAcnt->iRevBlackStamp = AMAtoi(pszValue[9]);

	if(0 != AMStrcmp("0", pszValue[10]))
	{
		IAccount_SetSigXML(pAcnt, pszValue[10], AMStrlen(pszValue[10]));
	}
	push_front_List(&pAcntModel->listAcnt, pAcnt, sizeof(AIMAccount), DYNAMIC);

	return 0;
}

#define		SQL_CREATE_ACNT_TABLE	"CREATE TABLE IF NOT EXISTS _account(_rid		INTEGER PRIMARY KEY AUTOINCREMENT,\
																			_id			VARCHAR(125) UNIQUE,\
																			_token		VARCHAR(125),\
																			_phone		VARCHAR(20),\
																			_flag		INTEGER,\
																			_status		INTEGER,\
																			_grpstamp	INTEGER,\
																			_cntstamp	INTEGER,\
																			_blkstamp	INTEGER,\
																			_rblkstamp	INTEGER,\
																			_sigxml		TEXT);"

AMInt32		IAccountModel_Restore(IAccountModel *pAcntor)
{
	AMInt32 rcSqlite = 0;
	AMChar *szErrMsg = 0;
	sqlite3		*pDB = 0;

	AMAssert(AMNULL != pAcntor);

	clear(List, &pAcntor->listAcnt);
	
	rcSqlite = myADB_Open(IM_ACNT_DB, &pDB, AMFALSE);

	if(rcSqlite)
	{
		DPRINT("AMIMAcntModel: Can't open database: %s\n", sqlite3_errmsg(pDB));
		sqlite3_close(pDB);
		IAccountModel_MarkDirt(pAcntor);
		return -1;
	}

	rcSqlite = sqlite3_exec(pDB, SQL_CREATE_ACNT_TABLE, 0, 0, &szErrMsg);

	if( rcSqlite != SQLITE_OK )
	{
		DPRINT("IAccountModel_Store: Can't \"CREATE TABLE _account(...);\": %s!\n", szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);
		IAccountModel_MarkDirt(pAcntor);
		return -1;
	}

	rcSqlite = sqlite3_exec(pDB, 
							"SELECT * FROM _account;",
							IAccountModel_OnSelAcnt,
							pAcntor,
							&szErrMsg);

	if( rcSqlite != SQLITE_OK ){
		DPRINT("AMIMAcntModel: Can't SELECT * FROM _account;! for %s\n", szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);
		IAccountModel_MarkDirt(pAcntor);
		return -1;
	}

	sqlite3_close(pDB);
	
	IAccountModel_ClearDirt(pAcntor);

	DPRINT("IAccountModel_Restore.........................\n");
	return 0;
}

#define		SQL_INSERT_ACNT		"INSERT INTO _account VALUES(NULL, '%q', '%q', '%q', %d, %d, %d, %d, %d, %d, '%q');"
AMInt32		IAccountModel_Store(IAccountModel *pAcntModel)
{
	ListIter *pIter = 0;
	AIMAccount	*pAcnt = 0;

	AMInt32 rcSqlite = 0;
	AMChar *szSql = AMNULL;
	AMChar *szErrMsg = 0;
	sqlite3 *pDB = 0;

	if(AMFALSE == IAccountModel_IsDirt(pAcntModel))
		return 0;

	if(0 == pAcntModel->listAcnt.size)
		return 0;

	rcSqlite = myADB_Open(IM_ACNT_DB, &pDB, AMFALSE);

	if(rcSqlite)
	{
		DPRINT("IAccountModel_Store: Can't Open DataBase for %s\n", sqlite3_errmsg(pDB));
		sqlite3_close(pDB);
		return -1;
	}

	rcSqlite = sqlite3_exec(pDB, "BEGIN TRANSACTION;", 0, 0, &szErrMsg);
	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IAccountModel_Store:.......can not \"BEGIN TRANSACTION;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);
		return -1;
	}

	rcSqlite = sqlite3_exec(pDB, SQL_CREATE_ACNT_TABLE,	0, 0, &szErrMsg);
	if( rcSqlite != SQLITE_OK )
	{
		DPRINT("IAccountModel_Store: Can't \"CREATE TABLE _account(...);\": %s!\n", szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);
		return -1;
	}

	rcSqlite = sqlite3_exec(pDB, "DELETE FROM _account;", 0, 0, &szErrMsg);
	if( SQLITE_OK != rcSqlite)
	{
		DPRINT("IAccountModel_Store: Can't \"DELETE FROM _account;\": %s!\n", szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);
	}

	pIter = create(ListIter, &pAcntModel->listAcnt);
	tail(ListIter, pIter);
	
	do 
	{
		pAcnt = (AIMAccount *)retrieve(ListIter, pIter);
		AMAssert(AMNULL != pAcnt);

		DPRINT("IAccountModel_Store......................%s\n", pAcnt->szID?pAcnt->szID:"0");
		
		szSql = sqlite3_mprintf(SQL_INSERT_ACNT, pAcnt->szID, (pAcnt->uiFlag&0x01)?pAcnt->szToken:"0"
			, (pAcnt->szPhoneNum?pAcnt->szPhoneNum:"0"), pAcnt->uiFlag, pAcnt->ePresence
			, pAcnt->iGroupStamp, pAcnt->iContactStamp, pAcnt->iBlackStamp
			, pAcnt->iRevBlackStamp, pAcnt->szSigXML?pAcnt->szSigXML:"0");

		if(AMNULL != szSql)
		{
			rcSqlite = sqlite3_exec(pDB, szSql, 0, 0, &szErrMsg);
			sqlite3_free(szSql);
			if( rcSqlite != SQLITE_OK )
			{
				DPRINT("IAccountModel_Store..............: Can't INSERT for %s!\n", szErrMsg);
				sqlite3_free(szErrMsg);
				continue;
			}
			pAcnt->_iRid = sqlite3_last_insert_rowid(pDB);	//更新新数据的_rid			
		}
		else
		{
			sqlite3_close(pDB);
			destroy(ListIter, pIter);
			return -1;
		}
	} while (!prev(ListIter, pIter));
	destroy(ListIter, pIter);

	rcSqlite = sqlite3_exec(pDB, "COMMIT TRANSACTION;", 0, 0, &szErrMsg);
	if(SQLITE_OK != rcSqlite)
	{
		DPRINT("IAccountModel_Store:..................can not \"COMMIT TRANSACTION;\":%s\n",szErrMsg);
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);
		return -1;
	}

	sqlite3_close(pDB);

	IAccountModel_ClearDirt(pAcntModel);
	
	DPRINT("IAccountModel_Store........................Ok\n");
	return 0;
}

IAccountModel *pSingleAcntModel = 0;

IAccountModel*	IAccountModel_Create()
{
	if(0 == pSingleAcntModel)
	{
		DPRINT("IAccountModel_Create.................AcntModle Creating\n");

		pSingleAcntModel = (IAccountModel *)AMMalloc(sizeof(IAccountModel));
		AMAssert(0 != pSingleAcntModel);
		AMMemset(pSingleAcntModel, 0, sizeof(IAccountModel));

 		construct(List, &(pSingleAcntModel->listAcnt), sizeof(AIMAccount), FREEOBJ);
 		set_compare(List, &(pSingleAcntModel->listAcnt), IAccount_cmpID);
 		set_dealloc(List, &(pSingleAcntModel->listAcnt), IAccount_Destroy);

		IAccountModel_Restore(pSingleAcntModel);

		DPRINT("IAccountModel_Create.................AcntModle Created\n");
	}
	pSingleAcntModel->iRefCount++;

	DPRINT("IAccountModel_Create.................Add Reference %d\n", pSingleAcntModel->iRefCount);
	return pSingleAcntModel;
}

AMVoid	IAccountModel_Destroy(IAccountModel *pAcntModel)
{
	AMAssert(0 != pAcntModel && pAcntModel == pSingleAcntModel);
	DPRINT("IAccountModel_Destroy................Remove Reference %d\n", pAcntModel->iRefCount);
	IAccountModel_Store(pAcntModel);
	pAcntModel->iRefCount--;
	if(0 >= pAcntModel->iRefCount)
	{
		destruct(List, &pAcntModel->listAcnt);
		AMFree(pSingleAcntModel);
		pSingleAcntModel = 0;
		DPRINT("IAccountModel_Destroy.................AcntModle Destroyed\n");
	}
}

List		*	IAccountModel_GetAccountList(IAccountModel *pAcntModel)
{
	AMAssert(0 != pAcntModel);
	return &pAcntModel->listAcnt;
}

AIMAccount	*	IAccountModel_findHistoryAcnt(IAccountModel *pAcntModel, const AMChar *szAcntID)
{
	ListIter	*pItr = 0;
	AIMAccount	*pAcnt = 0;
	AMAssert(0 != pAcntModel && 0 != szAcntID);

	if(pAcntModel->listAcnt.size <= 0)
		return 0;

	pItr = create(ListIter, &pAcntModel->listAcnt);
	head(ListIter, pItr);
	do 
	{
		pAcnt = (AIMAccount *)retrieve(ListIter, pItr);
		if(0 == AMStrcmp(pAcnt->szID, szAcntID)//帐号相等
			|| (pAcnt->szPhoneNum && 0 == AMStrcmp(pAcnt->szPhoneNum, szAcntID + ID_HEAD_LEN)))//或者传进来的电话号码相等
		{
			destroy(ListIter, pItr);
			return pAcnt;
		}
	} while (!next(ListIter, pItr));
	destroy(ListIter, pItr);

	return 0;
}

#define			SQL_DELETE_ACNT "DELETE FROM _account WHERE _rid=%lld;"
AMVoid			IAccountModel_RemoveAccount(IAccountModel *pAcntModel, const AMChar *szAcntId, AMBool bDelete)
{
	AIMAccount	*pAcntFind = AMNULL;
	AMInt32		rcSqlite = 0;
	sqlite3		*pDB = AMNULL;
	AMChar		*szErrMsg = AMNULL;
	AMChar	*	szSql = AMNULL;
	AMInt64		i64Rid = 0;

	AMAssert(0 != pAcntModel && AMNULL != szAcntId);

	pAcntFind = IAccountModel_findHistoryAcnt(pAcntModel, szAcntId);

	if(!pAcntFind)
		return;

	i64Rid = pAcntFind->_iRid;

	delete_List(&pAcntModel->listAcnt, pAcntFind, sizeof(AIMAccount));

	IAccountModel_MarkDirt(pAcntModel);

	szSql = sqlite3_mprintf(SQL_DELETE_ACNT, i64Rid);

	if(!szSql)
		return;	//malloc error

	rcSqlite = myADB_Open(IM_ACNT_DB, &pDB, AMFALSE);

	if(rcSqlite)
	{
		DPRINT("AMIMAcntModel: Can't open database: %s\n", sqlite3_errmsg(pDB));
		sqlite3_free(szSql);
		sqlite3_close(pDB);
		return;
	}

	rcSqlite = sqlite3_exec(pDB, szSql, 0, 0, &szErrMsg);

	sqlite3_free(szSql);

	if( rcSqlite != SQLITE_OK )
	{
		DPRINT("AMIMAcntModel: Can't DELETE!\n");
		sqlite3_free(szErrMsg);
		sqlite3_close(pDB);
		return;
	}

	sqlite3_close(pDB);

	IAccountModel_ClearDirt(pAcntModel);

	if(AMTRUE == bDelete)		//需要放到前面。 前面退出的情况，不应该影响删除数据的操作吧
	{
		//删除帐号数据库
	}
}
#define		SQL_CLEAR_TOKEN		"UPDATE _account SET _token='0' WHERE _rid=%lld;"
AMVoid		IAccountModel_ClearToken(IAccountModel	*pAcntModle, const AIMAccount *pAcnt)
{
	AIMAccount	*pAcntFind = AMNULL;
	AMChar	*szSql = AMNULL, *szErrMsg = AMNULL;
	sqlite3	*pDB = AMNULL;
	AMInt32 rcSqlite = 0;
	AMAssert(AMNULL != pAcntModle && AMNULL != pAcnt);

	pAcntFind = find_List(&pAcntModle->listAcnt, (void*)pAcnt, sizeof(AIMAccount));
	if(pAcntFind)
	{
		AMFree(pAcntFind->szToken);
		pAcntFind->szToken = AMNULL;

		IAccountModel_MarkDirt(pAcntModle);

		rcSqlite = myADB_Open(IM_ACNT_DB, &pDB, AMFALSE);

		if(rcSqlite)
		{
			DPRINT("IAccountModel_ClearToken: Can't open database: %s\n", sqlite3_errmsg(pDB));
			sqlite3_close(pDB);
			return;
		}

		rcSqlite = sqlite3_exec(pDB, SQL_CREATE_ACNT_TABLE, 0, 0, &szErrMsg);

		if( rcSqlite != SQLITE_OK )
		{
			DPRINT("IAccountModel_ClearToken: Can't \"CREATE TABLE _account(...);\": %s!\n", szErrMsg);
			sqlite3_close(pDB);
			sqlite3_free(szErrMsg);
			return;
		}

		szSql = sqlite3_mprintf(SQL_CLEAR_TOKEN, pAcnt->_iRid);

		if(AMNULL != szSql)
		{
			rcSqlite = sqlite3_exec(pDB, szSql, 0, 0, &szErrMsg);

			sqlite3_free(szSql);

			if( rcSqlite != SQLITE_OK )
			{
				DPRINT("IAccountModel_ClearToken: Can't UPDATE!\n");
				sqlite3_free(szErrMsg);
				sqlite3_close(pDB);
				return;
			}
		}

		sqlite3_close(pDB);

		IAccountModel_ClearDirt(pAcntModle);
	}
}

AMVoid		IAccountModel_LoginOK(IAccountModel *pAcntModel, AIMAccount *pAcnt)
{
	AIMAccount *pAcntDup = 0;
	AMInt32	rcSqlite = 0;
	sqlite3	*pDB = AMNULL;
	AMChar	*szErrMsg = AMNULL;
	AMChar	*szSql = AMNULL;

	AMAssert(AMNULL != pAcntModel && AMNULL != pAcnt && AMNULL != pAcnt->szID);

	pAcntDup = IAccount_dup(pAcnt);

	IAccountModel_RemoveAccount(pAcntModel, pAcntDup->szID, AMFALSE);

	delete_List(&pAcntModel->listAcnt, pAcntDup, sizeof(AIMAccount));
	push_front_List(&pAcntModel->listAcnt, pAcntDup, sizeof(AIMAccount), DYNAMIC);

	IAccountModel_MarkDirt(pAcntModel);	
	
	rcSqlite = myADB_Open(IM_ACNT_DB, &pDB, AMFALSE);

	if(rcSqlite)
	{
		DPRINT("IAccountModel_LoginOK: Can't open database: %s\n", sqlite3_errmsg(pDB));
		sqlite3_close(pDB);
		return;
	}

	rcSqlite = sqlite3_exec(pDB, SQL_CREATE_ACNT_TABLE, 0, 0, &szErrMsg);

	if( rcSqlite != SQLITE_OK )
	{
		DPRINT("IAccountModel_Store: Can't \"CREATE TABLE _account(...);\": %s!\n", szErrMsg);
		sqlite3_close(pDB);
		sqlite3_free(szErrMsg);
		return;
	}

	szSql = sqlite3_mprintf(SQL_INSERT_ACNT, pAcntDup->szID, (pAcntDup->uiFlag&0x01)?pAcntDup->szToken:"0"
		, (pAcntDup->szPhoneNum?pAcntDup->szPhoneNum:"0"), pAcntDup->uiFlag, pAcntDup->ePresence
		, pAcntDup->iGroupStamp, pAcntDup->iContactStamp, pAcntDup->iBlackStamp, pAcntDup->iRevBlackStamp
		, pAcntDup->szSigXML?pAcntDup->szSigXML:"0");

	if(AMNULL != szSql)
	{
		rcSqlite = sqlite3_exec(pDB, "BEGIN TRANSACTION;", 0, 0, &szErrMsg);
		if(SQLITE_OK != rcSqlite)
		{
			DPRINT("IAccountModel_LoginOK.............: can not BEGIN TRANSACTION;, for: %s\n", szErrMsg);
			sqlite3_free(szErrMsg);
			sqlite3_free(szSql);
			sqlite3_close(pDB);
			return;
		}

		DPRINT("IAccountModel_LoginOK.....................%s\n", pAcntDup->szID?pAcntDup->szID:"0");

		rcSqlite = sqlite3_exec(pDB, szSql, 0, 0, &szErrMsg);
		
		sqlite3_free(szSql);

		if( rcSqlite != SQLITE_OK )
		{
			DPRINT("IAccountModel_LoginOK: Can't INSERT!\n");
			sqlite3_free(szErrMsg);
			sqlite3_close(pDB);
			return;
		}

		pAcntDup->_iRid = sqlite3_last_insert_rowid(pDB);
		pAcnt->_iRid = pAcntDup->_iRid;

		rcSqlite = sqlite3_exec(pDB, "COMMIT TRANSACTION;", 0, 0, &szErrMsg);

		if(SQLITE_OK != rcSqlite)
		{
			DPRINT("IASessionModel_StoreMsg.............: can not COMMIT TRANSACTION;, for: %s\n",szErrMsg);
			sqlite3_free(szErrMsg);
			sqlite3_close(pDB);
			return;
		}
	}

	sqlite3_close(pDB);

	IAccountModel_ClearDirt(pAcntModel);
}

AMInt32			IAccountModel_UpdateSigXML(IAccountModel *pAcntModel, const AMChar *szID, const AMChar *szSigXml, AMInt32 iLen)
{
	AIMAccount *pAcntFind = 0;
	AMChar *szSql = AMNULL;
	AMInt32 rcSqlite = 0;
	sqlite3 *pDB = AMNULL;
	AMChar *szErrMsg = AMNULL;
	AMAssert(0 != pAcntModel && 0 != szID && 0 != szSigXml);

	pAcntFind = IAccountModel_findHistoryAcnt(pAcntModel, szID);
	if(AMNULL != pAcntFind)
	{
		IAccount_SetSigXML(pAcntFind, szSigXml, iLen);
		IAccountModel_MarkDirt(pAcntModel);

		szSql = sqlite3_mprintf(SQL_UPDATE_SIGXML, szSigXml, pAcntFind->_iRid);
		if(AMNULL != szSql)
		{
			rcSqlite = myADB_Open(IM_ACNT_DB, &pDB, AMFALSE);

			if(rcSqlite)
			{
				DPRINT("IAccountModel_UpdateStamp: Can't open database: %s\n", sqlite3_errmsg(pDB));
				sqlite3_close(pDB);
				sqlite3_free(szSql);
				return -1;
			}

			rcSqlite = sqlite3_exec(pDB, szSql, 0, 0, &szErrMsg);
			sqlite3_free(szSql);

			if( rcSqlite != SQLITE_OK )
			{
				DPRINT("IAccountModel_UpdateStamp: Can't UPDATE for %s!\n", szErrMsg);
				sqlite3_free(szErrMsg);
				sqlite3_close(pDB);
				return -1;
			}

			sqlite3_close(pDB);

			IAccountModel_ClearDirt(pAcntModel);
		}
	}

	return 0;
}

AMInt32			IAccountModel_UpdateStamp(IAccountModel *pAcntModel, AIMAccount *pAcnt, AMInt32 iDirtFlag)
{
	AIMAccount *pAcntFind = 0;
	AMAssert(0 != pAcntModel);

	pAcntFind = find_List(&pAcntModel->listAcnt, pAcnt, sizeof(AIMAccount));
	if(AMNULL != pAcntFind)
	{
		if(0 != iDirtFlag || pAcntFind->iGroupStamp != pAcntFind->iGroupStamp
			|| pAcntFind->iContactStamp != pAcnt->iContactStamp
			|| pAcntFind->iBlackStamp != pAcnt->iBlackStamp	
			|| pAcntFind->iRevBlackStamp != pAcnt->iRevBlackStamp)
		
		IAccountModel_MarkDirt(pAcntModel);

		if(0 == (iDirtFlag&0x01))
			pAcntFind->iGroupStamp = pAcnt->iGroupStamp;
		else
			pAcntFind->iGroupStamp = 0;

		if(0 == (iDirtFlag&0x02))
			pAcntFind->iContactStamp = pAcnt->iContactStamp;
		else
			pAcntFind->iContactStamp = 0;

		if(0 == (iDirtFlag&0x04))
			pAcntFind->iBlackStamp = pAcnt->iBlackStamp;
		else
			pAcntFind->iBlackStamp = 0;

		if(0 == (iDirtFlag&0x08))
			pAcntFind->iRevBlackStamp = pAcnt->iRevBlackStamp;
		else
			pAcntFind->iRevBlackStamp = 0;
	}
	else
	{
		AMAssert(0);
	}
	return 0;
}


#define		SQL_UPDATE_ACNT_FLAG	"UPDATE _account SET _flag=%d, _status=%d WHERE _rid=%lld;"
#define		SQL_UPDATE_ACNT_PWD		"UPDATE _account SET _pwd='%q' WHERE _rid=%lld;"
AMInt32			IAccountModel_UpdateFlag(IAccountModel *pAcntModel, AIMAccount *pAcnt)
{
	AIMAccount *pAcntFind = 0;
	AMChar *szSql = AMNULL;
	AMInt32 rcSqlite = 0;
	sqlite3 *pDB = AMNULL;
	AMChar *szErrMsg = AMNULL;
	AMAssert(0 != pAcntModel && 0 != pAcnt);

	pAcntFind = IAccountModel_findHistoryAcnt(pAcntModel, pAcnt->szID);
	if(AMNULL != pAcntFind
		&& ( pAcntFind->uiFlag != pAcnt->uiFlag 
			|| pAcntFind->ePresence != pAcnt->ePresence) )
	{
		AMBool bPwdSaveChanged = pAcnt->uiFlag&0x01 - pAcntFind->uiFlag&0x01;

		pAcntFind->uiFlag = pAcnt->uiFlag;
		pAcntFind->ePresence = pAcnt->ePresence;
		IAccountModel_MarkDirt(pAcntModel);

		DPRINT("%s >>>>>> acnt:%x, flag: %d, presence: %d, row_id = "I64FORMAT"\n",
			__FUNCTION__, pAcntFind, pAcntFind->uiFlag, pAcntFind->ePresence, pAcntFind->_iRid);

		szSql = sqlite3_mprintf(SQL_UPDATE_ACNT_FLAG, pAcnt->uiFlag, pAcnt->ePresence, pAcntFind->_iRid);
		if(AMNULL != szSql)
		{
			rcSqlite = myADB_Open(IM_ACNT_DB, &pDB, AMFALSE);

			if(rcSqlite)
			{
				DPRINT("IAccountModel_UpdateFlag: Can't open database: %s\n", sqlite3_errmsg(pDB));
				sqlite3_close(pDB);
				sqlite3_free(szSql);
				return -1;
			}

			rcSqlite = sqlite3_exec(pDB, szSql, 0, 0, &szErrMsg);
			sqlite3_free(szSql);

			if( rcSqlite != SQLITE_OK )
			{
				DPRINT("IAccountModel_UpdateFlag: Can't UPDATE for %s!\n", szErrMsg);
				sqlite3_free(szErrMsg);
				sqlite3_close(pDB);
				return -1;
			}

			if(bPwdSaveChanged)
			{
				if(!(pAcntFind->uiFlag & 0x01))
					szSql = sqlite3_mprintf(SQL_UPDATE_ACNT_PWD, pAcntFind->szPwd, pAcntFind->_iRid);
				else
					szSql = sqlite3_mprintf(SQL_UPDATE_ACNT_PWD, "", pAcntFind->_iRid);

				if(szSql)
				{
					rcSqlite = sqlite3_exec(pDB, szSql, 0, 0, &szErrMsg);
					sqlite3_free(szSql);

					if( rcSqlite != SQLITE_OK )
					{
						DPRINT("IAccountModel_UpdateFlag: Can't UPDATE for %s!\n", szErrMsg);
						sqlite3_free(szErrMsg);
						sqlite3_close(pDB);
						return -1;
					}
				}
			}
			
			sqlite3_close(pDB);

			IAccountModel_ClearDirt(pAcntModel);
		}
	}

	return 0;
}


