#ifndef __AM_SYNC_DB_H__
#define __AM_SYNC_DB_H__

/** @defgroup 可用于数据同步的数据库接口
  * @{
  */

#ifdef __cplusplus
extern "C" {
#endif

	/** @brief 数据同步的数据库句柄 */
	typedef AMVoid*  AMSyncDB;
	
	/** @brief 查询数据库回调函数 
	  * @param AMSyncDB db :  已经打开的数据库句柄
	  * @param char* data : 查询到的数据
	  * @return 返回该函数调用时候产生的错误码, >0表示正确, <=0表示错误
	  */
	typedef AMInt32 (*AMSyncDBCallback)(AMSyncDB db, char* data);

	/** @brief 创建可用于数据同步的数据库
	  * @param [IN] const AMChar* pDbName : 数据库名称
	  * @return 返回该函数调用时候产生的错误码, >0表示正确, <=0表示错误
	  */
	AMInt32 AMSyncDBCreate(const AMChar* pDbName);
	
	/** @brief 删除用可用于数据同步的数据库
	  * @param [IN] const AMChar* pDbName : 数据库名称
	  * @return 返回该函数调用时候产生的错误码, >0表示正确, <=0表示错误
	  */
	AMInt32 AMSyncDBRemoveByName(const AMChar* pDbName);

	/** @brief 打开一个可用于数据同步的数据库, 如不存在, 则自动创建一个.
	  * @param [IN/OUT] AMSyncDB* pDb : 打开后的数据库句柄
	  * @param [IN] const AMChar* pDbName : 数据库名称
	  * @return 返回该函数调用时候产生的错误码, >0表示正确, <=0表示错误
	  */
	AMInt32 AMSyncDBOpen(AMSyncDB* pDb, const AMChar* pDbName);
	
	/** @brief 关闭一个可用于数据同步的数据库
	  * @param [IN] AMSyncDB db : 已经打开并需要关闭的数据库句柄
	  * @return 返回该函数调用时候产生的错误码, >0表示正确, <=0表示错误
	  */	
	AMInt32 AMSyncDBClose(AMSyncDB db);

	/** @brief 创建一个表
	  * @param [IN] AMSyncDB db : 打开后的数据库句柄
	  * @param [IN] const AMChar* pTableName : 表名称
	  * @return 返回该函数调用时候产生的错误码, >0表示正确, <=0表示错误
	  */
	AMInt32 AMSyncDBCreateTable(AMSyncDB db, const char* pTableName);

	/** @brief 删除一个表
	  * @param [IN] AMSyncDB db : 打开后的数据库句柄
	  * @param [IN] const AMChar* pTableName : 表名称
	  * @return 返回该函数调用时候产生的错误码, >0表示正确, <=0表示错误
	  */
	AMInt32 AMSyncDBDropTable(AMSyncDB db, const AMChar* pTableName);

	/** @brief 判断一个表是否存在
	  * @param [IN] AMSyncDB db : 打开后的数据库句柄
	  * @param [IN] const AMChar* pTableName : 表名称
	  * @param [IN/OUT] AMBool* bIsExist : 返回值, true表示存在该表, false表示不存在
	  * @return 返回该函数调用时候产生的错误码, >0表示正确, <=0表示错误
	  */
	AMInt32 AMSyncDBIsTableExist(AMSyncDB db, const AMChar* pTableName, AMBool* bIsExist);
	
	/** @brief 添加一条记录
	  * @param [IN] AMSyncDB db : 打开后的数据库句柄
	  * @param [IN] const AMChar* pTableName : 表名称
	  * @param [IN] const AMChar* data : 待添加的数据(已经序列化好)
	  * @param [IN/OUT] AMUInt32* rowID : 如插入成功则返回插入的位置rowID.
	  * @return 返回该函数调用时候产生的错误码, >0表示正确, <=0表示错误
	  */
	AMInt32 AMSyncDBAddRecord(AMSyncDB db, const AMChar* pTableName, const AMChar* data, AMUInt32* rowID);
	
	/** @brief 删除一条记录
	  * @param [IN] AMSyncDB db : 打开后的数据库句柄
	  * @param [IN] const AMChar* pTableName : 表名称
	  * @param [IN] AMInt32 rowID : 待删除的记录的rowID号
	  * @return 返回该函数调用时候产生的错误码, >0表示正确, <=0表示错误
	  */	
	AMInt32 AMSyncDBDeleteRecord(AMSyncDB db, const AMChar* pTableName, AMInt32 rowID);

	/** @brief 更新一条记录
	  * @param [IN] AMSyncDB db : 打开后的数据库句柄
	  * @param [IN] const AMChar* pTableName : 表名称
	  * @param [IN] const AMChar* data : 最新的数据
	  * @param [IN] AMInt32 rowID : 待更新的记录的rowID号
	  * @return 返回该函数调用时候产生的错误码, >0表示正确, <=0表示错误
	  */
	AMInt32 AMSyncDBUpdateRecord(AMSyncDB db, const AMChar* pTableName, const AMChar* data, AMInt32 rowID);

	/** @brief 查询数据
	  * @param [IN] AMSyncDB db : 打开后的数据库句柄
	  * @param [IN] const AMChar* pTableName : 表名称
	  * @param [IN] AMSyncDBCallback cb : 查询到记录后则回调此函数
	  * @param [IN] AMInt32 rowID : 待查询的记录的rowID号
	  * @return 返回该函数调用时候产生的错误码, >0表示正确, <=0表示错误
	  */
	AMInt32 AMSyncDBQueryRecord(AMSyncDB db, const AMChar* pTableName, AMSyncDBCallback cb, AMInt32 rowID);

#ifdef __cplusplus
};
#endif

/** }@ */

#endif