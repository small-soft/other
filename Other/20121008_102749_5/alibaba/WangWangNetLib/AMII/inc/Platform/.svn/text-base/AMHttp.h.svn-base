/*
* AMHttp.h
*
*  Created on: 2010-3-1
*      Author: qinghua.liqh
*/
#ifndef _AM_HTTP_H_
#define _AM_HTTP_H_
#include "AMErrno.h"
#include "AMTypes.h"

//1). 创建一个AMHttpSession
//2). 创建一个AMHttpURL, 
//3). 从AMHttpSession, 根据AMHttpURL得到一个AMHttpConnection.
//4). 从AMHttpConnection得到AMHttpRequest, 设置AMHttpRequest的属性.
//5). 发起连接AMHttpRequest
//6). 从AMHttpConnection得到AMHttpResponse. 从中得到返回结果.
//7). 关闭AMHttpConnection.
//8). 关闭AMHttpSession.



typedef AMPVoid     AMHttpSession;          //Http 连接会话. 可以从这个会话创建AMHttpConnection
typedef AMPVoid     AMHttpConnection;       //Http 连接, 表示一次Http请求
typedef AMWChar*    AMHttpURL;              //网络路径

//下面连个可以合成到AMHttpConnection中
typedef AMPVoid AMHttpResponse;         //Http 的应答
typedef AMPVoid AMHttpRequest;          //Http 的请求

/*
AMHttpSession               Http 连接会话    
--> AMHttpConnection        Http 连接
    --> AMHttpResponse      Http 的应答
    --> AMHttpRequest       Http 的请求
*/

//Http异步事件, 
//发生事件的时候收到什么数据, 现在不好定义, 实现的时候再考虑加进去.
typedef enum
{
    AM_HTTP_CON_CREATED,            //AMHttpConnection创建
    AM_HTTP_CON_CLOSING,            //AMHttpConnection正在关闭
    AM_HTTP_CON_CLOSED,             //AMHttpConnection关闭

    AM_HTTP_REQUEST_SENT,           //AMHttpRequest发送
    AM_HTTP_REQUEST_SENTING,        //AMHttpRequest正在发送
    AM_HTTP_REQUEST_SENT_COMPLETE,  //AMHttpRequest完成

    AM_HTTP_RESPONSE_RECEIVING,     //AMHttpResponse收ing
    AM_HTTP_RESPONSE_RECEIVED,      //AMHttpResponse收到
                                    //添加收到头和body的事件通知.

}AMHttpStatus;

//AMHttpResponse中可以拿到的数据类型.
typedef enum
{
    AM_HTTP_STATUS_CODE,            //返回码, 数据: AMUInt32, 具体值请查看AMStatusCode.
    AM_HTTP_VERSION,                //AMUInt32维数为2的数组, 
}AMHttpQueryCode;

//返回码.
typedef enum
{
    AM_HTTP_STATUS_CONTINUE = 100,      // 100  OK to continue with request
    AM_HTTP_STATUS_SWITCH_PROTOCOLS,    // 101  server has switched protocols in upgrade header

    AM_HTTP_STATUS_OK = 200,             // 200 request completed
    AM_HTTP_STATUS_CREATED,              // 201 object created, reason = new URI
    AM_HTTP_STATUS_ACCEPTED,             // 202async completion (TBS)
    AM_HTTP_STATUS_PARTIAL,              // 203partial completion
    AM_HTTP_STATUS_NO_CONTENT,           // 204no info to return
    AM_HTTP_STATUS_RESET_CONTENT,        // 205request completed, but clear form
    AM_HTTP_STATUS_PARTIAL_CONTENT,      // 206partial GET furfilled

    AM_HTTP_STATUS_AMBIGUOUS = 300,      // 300server couldn't decide what to return
    AM_HTTP_STATUS_MOVED,                // 301object permanently moved
    AM_HTTP_STATUS_REDIRECT,             // 302object temporarily moved
    AM_HTTP_STATUS_REDIRECT_METHOD,      // 303redirection w/ new access method
    AM_HTTP_STATUS_NOT_MODIFIED,         // 304if-modified-since was not modified
    AM_HTTP_STATUS_USE_PROXY ,           // 305redirection to proxy, location header specifies proxy to use
    AM_HTTP_STATUS_REDIRECT_KEEP_VERB = 307,   // 307HTTP/1.1: keep same verb

    AM_HTTP_STATUS_BAD_REQUEST = 400,    // 400invalid syntax
    AM_HTTP_STATUS_DENIED,               // 401ccess denied
    AM_HTTP_STATUS_PAYMENT_REQ,          // 402payment required
    AM_HTTP_STATUS_FORBIDDEN,            // 403request forbidden
    AM_HTTP_STATUS_NOT_FOUND,            // 404object not found
    AM_HTTP_STATUS_BAD_METHOD,           // 405method is not allowed
    AM_HTTP_STATUS_NONE_ACCEPTABLE,      // 406no response acceptable to client found
    AM_HTTP_STATUS_PROXY_AUTH_REQ,       // 407proxy authentication required
    AM_HTTP_STATUS_REQUEST_TIMEOUT,      // 408server timed out waiting for request
    AM_HTTP_STATUS_CONFLICT,             // 409user should resubmit with more info
    AM_HTTP_STATUS_GONE,                 // 410the resource is no longer available
    AM_HTTP_STATUS_LENGTH_REQUIRED,      // 411the server refused to accept request w/o a length
    AM_HTTP_STATUS_PRECOND_FAILED,       // 412precondition given in request failed
    AM_HTTP_STATUS_REQUEST_TOO_LARGE,    // 413request entity was too large
    AM_HTTP_STATUS_URI_TOO_LONG,         // 414request URI too long
    AM_HTTP_STATUS_UNSUPPORTED_MEDIA,    // 415unsupported media type
    AM_HTTP_STATUS_RETRY_WITH = 449,     // 449retry after doing the appropriate action.

    AM_HTTP_STATUS_SERVER_ERROR  = 500,  // 500internal server error
    AM_HTTP_STATUS_NOT_SUPPORTED,        // 501required not supported
    AM_HTTP_STATUS_BAD_GATEWAY,          // 502error response received from gateway
    AM_HTTP_STATUS_SERVICE_UNAVAIL,      // 503temporarily overloaded
    AM_HTTP_STATUS_GATEWAY_TIMEOUT,      // 504timed out waiting for gateway
    AM_HTTP_STATUS_VERSION_NOT_SUP,      // 505HTTP version not supported
}AMStatusCode;

//session表示对应的发起者
//context为有哪个函数发起的标识
//status为事件描述
//data为数据(具体对应到什么数据, 要看status为什么事件)
//datalen数据长度
//parg为AMHttpCreateSession传入的参数
typedef void* (*AMHttpCallback)(AMHttpSession session, AMUInt32 context, AMHttpStatus status,
                             AMUInt8* data, AMUInt32 dataLen, AMPVoid parg);

//支持的动作
typedef enum
{
    AM_HTTP_GET,    //POST
    AM_HTTP_POST,   //GET
    AM_HTTP_HEAD,   //HEAD
}AMHttpVerb;

//可以设置的Request的选项
typedef enum
{
    AM_HTTP_TIMEOUT,                //超时时间.     数据: AMTimeval,   长度: AMTimeval的长度.
    AM_HTTP_FULL_URL,               //完整的URL.    数据: AMWChar数组, \0\0结束. 长度: Buffer大小
    AM_HTTP_PASSWORD,               //用户名,       数据: AMUInt8数组, 长度: 数组的长度
    AM_HTTP_USERNAME ,              //密码,         数据: AMUInt8数组, 长度: 数组的长度
}AMHttpOption;

#ifdef __cplusplus
extern "C" {
#endif
    //创建和关闭Session, sessionName表示Session的名字, 可以为空.
    //callback 为异步回调函数. parg为传递到callback的参数.
    AMInt32 AMHttpCreateSession(AMHttpSession* pSession, 
        const AMWChar* sessionName, AMHttpCallback callback, AMPVoid parg);
    AMInt32 AMHttpCloseSession(AMHttpSession session);

    //打开和关闭Connection
    AMInt32 AMHttpOpenConnection(AMHttpConnection* pCon, 
        AMHttpSession session, const AMHttpURL url);
    AMInt32 AMHttpCloseConnection(AMHttpConnection con);


    //打开Request和Response.
    //context为上下文标识, 用在回调函数中, 表示回调的是那个AMHttpRequest
    //或者AMHttpResponse.

    //这里是否要改成Create, 实现的时候再考虑. Get是得到, 表示AMHttpConnection只有一个AMHttpRequest
    //Create表示可以有多个
    AMHttpRequest AMHttpGetRequest (AMHttpConnection con, 
        AMHttpVerb verb, AMUInt32 context);
    AMHttpResponse AMHttpGetResponse(AMHttpConnection con, AMUInt32 context);

    //得到和设置属性, 
    AMInt32 AMHttpSetOption(AMHttpRequest request, AMHttpOption option, 
        AMUInt8* inBuf, AMUInt32 inBufLen); 
    AMInt32 AMHttpGetOption(AMHttpRequest request, AMHttpOption option,
        AMUInt8* outBuf, AMUInt32 inOutBufLen); 

    //context如果为0, 继承AMHttpConnection的context
    AMInt32 AMHttpSendRequest(AMHttpRequest request, AMUInt32 context);

    //得到AMHttpResponse信息.
    //AMHttpQueryCode对应的数据格式, 请查看AMHttpQueryCode的定义.
    AMInt32 AMHttpGetResponseInfo(AMHttpResponse response, AMHttpQueryCode code, 
        AMUInt8* outBuf, AMUInt32 inOutBufLen);
#ifdef __cplusplus
}
#endif
#endif

