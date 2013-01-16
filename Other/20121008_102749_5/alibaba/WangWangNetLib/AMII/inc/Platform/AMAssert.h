#ifndef _AM_ASSERT_H_
#define _AM_ASSERT_H_
#include "AMErrno.h"
#include "AMTypes.h"
#include "AMFS.h"
#include "AMTimer.h"

//AMAssertBreak, ����ֹͣ�ڳ���.
#ifdef _WIN32_WCE
    extern AMVoid __debugbreak();
    #define AMAssertBreak()  __debugbreak();
#elif (defined(_WIN32) && (!defined(__SYMBIAN32__)))
    #define AMAssertBreak()  __asm {int 3};
#else 
//Ҫ����ʲô���õķ���, �����滻.
#define AMAssertBreak()  do{AMSleep(1);}while(1);
#endif


//Assert: ��Relese�²���������.
//Check:  ��Relese�²�������, Debug�º�Assert��ͬ.
//AM*Equal(expression, value)	      Ҫ��expression == value, ������ʱ��ӡ��Ϣ���˳�.
//AM*NotEqual(expression, value)	  Ҫ��expression != value, ������ʱ��ӡ��Ϣ���˳�.
//AM*(expression)	                  expression == 0ʱ��ӡ��Ϣ���˳�.
#ifdef AMOS_DEBUG
//Ҫ��expression == value, ������ʱ��ӡ��Ϣ���˳�.
#define AMCheckEqual(expression, value)  {\
    if((expression) != (value)){\
        AMPrintf("Assert Failure([File, Line] = [%s, %d]): %s != %s \n",__FILE__,__LINE__, #expression, #value);\
        AMAssertBreak();\
    }};

//Ҫ��expression != value, ������ʱ��ӡ��Ϣ���˳�.
#define AMCheckNotEqual(expression, value) {\
    if((expression) == (value)){\
        AMPrintf("Assert Failure([File, Line] = [%s, %d]): %s == %s \n",__FILE__,__LINE__, #expression, #value);\
        AMAssertBreak();\
    }};
//expression == 0ʱ��ӡ��Ϣ���˳�.
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

/** ���p�Ƿ�Ϊ��, ����Ƿ��� v*/
#define CHECK_AND_RETV(p, v) if(NULL == (p))  return (v)
/** ������p�Ƿ�Ϊ��, ����Ƿ���AME_ARG_AINVALID */
#define CHECK_PARG_AND_RET(p) CHECK_AND_RETV(p, AME_ARG_AINVALID)
/** ���p�Ƿ�Ϊ��, ����Ƿ��� NULL (0) */
#define CHECK_AND_RET0(p) CHECK_AND_RETV(p, NULL)
/** ���s�Ƿ����d, ����Ƿ���v */
#define CHECK_EQUAL_AND_RETV(s, d, v) if( (s) == (d)) return (v)
/** ���s�Ƿ񲻵���d, ����Ƿ���v */
#define CHECK_NOTEQUAL_AND_RETV(s, d, v) if((s) != (d)) return (v)
/** ���p�Ƿ�Ϊ��, ����Ƿ��� */
#define CHECK_AND_RET_NOVALUE(p) if(NULL == (p))  return
/** ���s�Ƿ����d, ����Ƿ��� */
#define CHECK_EQUAL_AND_RET_NOVALUE(s, d) if( (s) == (d)) return
/** ���s�Ƿ񲻵���d, ����Ƿ��� */
#define CHECK_NOTEQUAL_AND_RET_NOVALUE(s, d) if((s) != (d)) return

#endif //_AM_ASSERT_H_
