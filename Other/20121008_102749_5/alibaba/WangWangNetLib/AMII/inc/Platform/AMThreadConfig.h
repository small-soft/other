/*
 * AMThreadConfig.h
 *
 *  Created on: 2009-11-17
 *      Author: qinghua.liqh
 */

#ifndef _AM_THREAD_CONFIG_H_
#define _AM_THREAD_CONFIG_H_
/*
 * @defgroup 线程配置模块
 * @{
 */
#include "AMErrno.h"
#include "AMTypes.h"

#define AMTHREAD_MUTEX_SUPPORT_PROCESS_SHARED	 0	 /**< Mutex是否支持进程间共享 */
#define AMTHREAD_MUTEX_SUPPORT_TRY_LOCK			 1   /**< Mutex是否支持trylock */
#define AMTHREAD_COND_SUPPORT_PROCESS_SHARED     0   /**< 条件变量是否支持进程间共享 */
#define AMTHREAD_COND_SUPPORT_TIMEWAIT			 1   /**< 条件变量是否支持time wait */

#define AMTHREAD_DLL_EXPORT ADAPTER_API				 
/** @} */
#endif /* _AM_THREAD_CONFIG_H_ */


