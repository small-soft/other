#ifndef __AM_DATABASE_H__
#define __AM_DATABASE_H__

#include "AMTypes.h"
#include "AMErrno.h"

#ifdef __cplusplus
extern "C" {
#endif

#if 1
#include "sqlite3.h"
#endif

#if 0

	typedef AMVoid*  AMDatabase;
	typedef AMVoid*  AMDatabaseView;
	typedef AMVoid (*AMDatabaseCallback)(AMDatabase db, AMDatabaseView view);
	
	//���ݿ�Ĵ�����ɾ��
	AMInt32 AMDbCreate(const AMChar* pDbName);
	AMInt32 AMDbRemoveByName(const AMChar* pDbName);
	
	//���ݿ�Ĵ򿪡��ر�
	AMInt32 AMDbOpen(AMDatabase* db, const AMChar* pDbName);
	AMInt32 AMDbClose(AMDatabase db);
	
	//�����ݿ����ִ��SQL
	AMInt32 AMDbExecSQL(AMDatabase db, const AMChar* strSQL, AMDatabaseView* pView);
	AMInt32 AMDbExecSQLAsync(AMDatabase db, const AMChar* strSQL, AMDatabaseCallback cb);
	
	//�����ݿ���ͼ��ִ��SQL
	AMInt32 AMDbExecSQLV(AMDatabaseView view, const AMChar* strSQL, AMDatabaseView* pView);
	AMInt32 AMDbExecSQLVAsync(AMDatabaseView view, const AMChar* strSQL, AMDatabaseCallback cb);
	
	//�ر�View
	AMInt32 AMDbViewClose(AMDatabaseView view);
	
	//view���α����
	AMInt32 AMDbViewFirst(AMDatabaseView view);
	AMInt32 AMDbViewPrevious(AMDatabaseView view);
	AMInt32 AMDbViewNext(AMDatabaseView view);
	AMInt32 AMDbViewLast(AMDatabaseView view);
	
	//view��record����
	AMInt32 AMDbViewGetCurrentSize(AMDatabaseView view);
	AMInt32 AMDbViewGetCurrentRecord(AMDatabaseView view, AMInt8* pContent, AMInt32 size);
	
	//�õ�ĳ���ֶζ�Ӧ��View�е���
	AMInt32 AMDbViewGetColumnIndex(AMDatabaseView view, AMChar* columnName);
	AMInt32 AMDbViewGetCurrentData(AMDatabaseView view, AMInt32 nColumnIndex, AMInt8* pContent, AMInt32* size);
	
	//�õ�View�еļ�¼����
	AMInt32 AMDbViewRows(AMDatabaseView view);
	
#endif

#if 0

	typedef AMVoid*  AMDatabase;

	typedef AMInt32 (*AMDatabaseCallback)(void* unused, int Columns, char** ColumnValues, char** ColumnName);

	//���ݿ�Ĵ�����ɾ��
	AMInt32 AMDbCreate(const AMChar* pDbName);
	AMInt32 AMDbRemoveByName(const AMChar* pDbName);
	
	//���ݿ�Ĵ򿪡��ر�
	AMInt32 AMDbOpen(AMDatabase* db, const AMChar* pDbName);
	AMInt32 AMDbClose(AMDatabase db);
	
	//�����ݿ���ִ��SQL
	AMInt32 AMDbExecSQL(AMDatabase db, const AMChar* strSQL, AMDatabaseCallback cb, void* firstArg, char* errmsg);

#endif

#ifdef __cplusplus
};
#endif

#endif