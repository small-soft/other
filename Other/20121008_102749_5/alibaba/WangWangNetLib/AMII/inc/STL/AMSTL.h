#ifndef __AM_STL_H__
#define __AM_STL_H__

#if defined(WINCE) || defined(WIN32)

#include <vector>
#include <string>
#include <map>
#include <sstream> 
#include <iostream>

using namespace std;

#else

#include "ustl/ustl.h"
using namespace ustl;

#endif

#endif
