#ifndef _AM_ASSERT_H_
#define _AM_ASSERT_H_
#include "AMErrno.h"
#include "AMTypes.h"
#include "AMFS.h"
#include "AMTimer.h"

//AMAssertBreak, 运行停止在出错处.
#ifdef _WIN32_WCE
    extern AMVoid __debugbreak();
    #define AMAssertBreak()  __debugbreak();
#elif (defined(_WIN32) && (!defined(__SYMBIAN32__)))
    #define AMAssertBreak()  __asm {int 3};
#else 
//要是有什么更好的方法, 可以替换.
#define AMAssertBreak()  do{AMSleep(1);}while(1);
#endif


//Assert: 在Relese下不产生代码.
//Check:  在Relese下产生代码, Debug下和Assert相同.
//AM*Equal(expression, value)	      要求expression == value, 不成立时打印信息并退出.
//AM*NotEqual(expression, value)	  要求expression != value, 不成立时打印信息并退出.
//AM*(expression)	                  expression == 0时打印信息并退出.
#ifdef AMOS_DEBUG
//要求expression == value, 不成立时打印信息并退出.
#define AMCheckEqual(expression, value)  {\
    if((expression) != (value)){\
        AMPrintf("Assert Failure([File, Line] = [%s, %d]): %s != %s \n",__FILE__,__LINE__, #expression, #value);\
        AMAssertBreak();\
    }};

//要求expression != value, 不成立时打印信息并退出.
#define AMCheckNotEqual(expression, value) {\
    if((expression) == (value)){\
        AMPrintf("Assert Failure([File, Line] = [%s, %d]): %s == %s \n",__FILE__,__LINE__, #expression, #value);\
        AMAssertBreak();\
    }};
//expression == 0时打印信息并退出.
#define AMCheck(expression)                 AMCheckNotEqual(expression, 0)


#define AMAssertEqual(expression, value)    AMCheckEqual(expression, value)
#define AMAssertNotEqual(expression, value) AMCheckNotEqual(expression, value)
#define AMAssert(expression)                AMCheck(expression)
#else
#define AMCheckEqual(expression, value)    (expression);
#define AMCheckNotEqual(expression, value) (expression);
#define AMCheck(expression)                (expression);
#define AMAssertEqual(expression, value)   
#define AMAssertNotEqual(expression, value)
#define AMAssert(expression)
#endif

/** 检查p是否为空, 如果是返回 v*/
#define CHECK_AND_RETV(p, v) if(NULL == (p))  return (v)
/** 检查参数p是否为空, 如果是返回AME_ARG_AINVALID */
#define CHECK_PARG_AND_RET(p) CHECK_AND_RETV(p, AME_ARG_AINVALID)
/** 检查p是否为空, 如果是返回 NULL (0) */
#define CHECK_AND_RET0(p) CHECK_AND_RETV(p, NULL)
/** 检查s是否等于d, 如果是返回v */
#define CHECK_EQUAL_AND_RETV(s, d, v) if( (s) == (d)) return (v)
/** 检查s是否不等于d, 如果是返回v */
#define CHECK_NOTEQUAL_AND_RETV(s, d, v) if((s) != (d)) return (v)
/** 检查p是否为空, 如果是返回 */
#define CHECK_AND_RET_NOVALUE(p) if(NULL == (p))  return
/** 检查s是否等于d, 如果是返回 */
#define CHECK_EQUAL_AND_RET_NOVALUE(s, d) if( (s) == (d)) return
/** 检查s是否不等于d, 如果是返回 */
#define CHECK_NOTEQUAL_AND_RET_NOVALUE(s, d) if((s) != (d)) return

#endif //_AM_ASSERT_H_
