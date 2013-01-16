/*
 * AMStdlib.h
 *
 *  Created on: 2010/07/29
 *      Author: qinghua.liqh
*/
#ifndef  _AM_STDLIB_H_
#define  _AM_STDLIB_H_
#include "AMErrno.h"
#include "AMTypes.h"

#define  AMAtoi  atoi
#ifdef _WIN32
#define  AMAtoi64 _atoi64
#define  AMI64toa _i64toa
#define  AMUI64toa _ui64toa
#else       
#define  AMAtoi64 atoll
#define  AMI64toa itoa
#define  AMUI64toa itoa
#endif
#define  AMItoa  itoa
#define  AMAtof  atof


#endif   //_AM_STDLIB_H_ 
