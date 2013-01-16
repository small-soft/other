/*
* AMHttp.cpp
*
*  Created on: 2010-3-2
*      Author: qinghua.liqh
*/
#include "AMHttp.h"
#include <list>
#include <windows.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")

using namespace std;

struct AMHttpSessionNode;
struct AMHttpConnectionNode;
struct AMHttpResponseNode;
struct AMHttpRequestNode;

struct AMHttpSessionNode
{
    AMWChar sessionName[128];
    AMPVoid sessionParg;
    AMHttpCallback callback;
    std::list<AMHttpConnectionNode*> cons;

    //Native.
    HINTERNET nativeSession;
};

struct  AM2RPair
{
    AMHttpResponseNode* pResponse;
    AMHttpRequestNode* pRequest;
};

struct AMHttpConnectionNode
{
    AMHttpSessionNode* pSession;
    AM2RPair rPair;

    //Native.
    HINTERNET nativeCon;
};

struct AMHttpResponseNode
{
    AMHttpConnectionNode* pCon;
    AMHttpRequestNode* pRequest;
};

struct AMHttpRequestNode
{
    AMHttpConnectionNode* pCon;
    AMHttpResponseNode* pResponse;
};



