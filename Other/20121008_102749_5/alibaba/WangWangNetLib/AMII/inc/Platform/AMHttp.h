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

//1). ����һ��AMHttpSession
//2). ����һ��AMHttpURL, 
//3). ��AMHttpSession, ����AMHttpURL�õ�һ��AMHttpConnection.
//4). ��AMHttpConnection�õ�AMHttpRequest, ����AMHttpRequest������.
//5). ��������AMHttpRequest
//6). ��AMHttpConnection�õ�AMHttpResponse. ���еõ����ؽ��.
//7). �ر�AMHttpConnection.
//8). �ر�AMHttpSession.



typedef AMPVoid     AMHttpSession;          //Http ���ӻỰ. ���Դ�����Ự����AMHttpConnection
typedef AMPVoid     AMHttpConnection;       //Http ����, ��ʾһ��Http����
typedef AMWChar*    AMHttpURL;              //����·��

//�����������Ժϳɵ�AMHttpConnection��
typedef AMPVoid AMHttpResponse;         //Http ��Ӧ��
typedef AMPVoid AMHttpRequest;          //Http ������

/*
AMHttpSession               Http ���ӻỰ    
--> AMHttpConnection        Http ����
    --> AMHttpResponse      Http ��Ӧ��
    --> AMHttpRequest       Http ������
*/

//Http�첽�¼�, 
//�����¼���ʱ���յ�ʲô����, ���ڲ��ö���, ʵ�ֵ�ʱ���ٿ��Ǽӽ�ȥ.
typedef enum
{
    AM_HTTP_CON_CREATED,            //AMHttpConnection����
    AM_HTTP_CON_CLOSING,            //AMHttpConnection���ڹر�
    AM_HTTP_CON_CLOSED,             //AMHttpConnection�ر�

    AM_HTTP_REQUEST_SENT,           //AMHttpRequest����
    AM_HTTP_REQUEST_SENTING,        //AMHttpRequest���ڷ���
    AM_HTTP_REQUEST_SENT_COMPLETE,  //AMHttpRequest���

    AM_HTTP_RESPONSE_RECEIVING,     //AMHttpResponse��ing
    AM_HTTP_RESPONSE_RECEIVED,      //AMHttpResponse�յ�
                                    //����յ�ͷ��body���¼�֪ͨ.

}AMHttpStatus;

//AMHttpResponse�п����õ�����������.
typedef enum
{
    AM_HTTP_STATUS_CODE,            //������, ����: AMUInt32, ����ֵ��鿴AMStatusCode.
    AM_HTTP_VERSION,                //AMUInt32ά��Ϊ2������, 
}AMHttpQueryCode;

//������.
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

//session��ʾ��Ӧ�ķ�����
//contextΪ���ĸ���������ı�ʶ
//statusΪ�¼�����
//dataΪ����(�����Ӧ��ʲô����, Ҫ��statusΪʲô�¼�)
//datalen���ݳ���
//pargΪAMHttpCreateSession����Ĳ���
typedef void* (*AMHttpCallback)(AMHttpSession session, AMUInt32 context, AMHttpStatus status,
                             AMUInt8* data, AMUInt32 dataLen, AMPVoid parg);

//֧�ֵĶ���
typedef enum
{
    AM_HTTP_GET,    //POST
    AM_HTTP_POST,   //GET
    AM_HTTP_HEAD,   //HEAD
}AMHttpVerb;

//�������õ�Request��ѡ��
typedef enum
{
    AM_HTTP_TIMEOUT,                //��ʱʱ��.     ����: AMTimeval,   ����: AMTimeval�ĳ���.
    AM_HTTP_FULL_URL,               //������URL.    ����: AMWChar����, \0\0����. ����: Buffer��С
    AM_HTTP_PASSWORD,               //�û���,       ����: AMUInt8����, ����: ����ĳ���
    AM_HTTP_USERNAME ,              //����,         ����: AMUInt8����, ����: ����ĳ���
}AMHttpOption;

#ifdef __cplusplus
extern "C" {
#endif
    //�����͹ر�Session, sessionName��ʾSession������, ����Ϊ��.
    //callback Ϊ�첽�ص�����. pargΪ���ݵ�callback�Ĳ���.
    AMInt32 AMHttpCreateSession(AMHttpSession* pSession, 
        const AMWChar* sessionName, AMHttpCallback callback, AMPVoid parg);
    AMInt32 AMHttpCloseSession(AMHttpSession session);

    //�򿪺͹ر�Connection
    AMInt32 AMHttpOpenConnection(AMHttpConnection* pCon, 
        AMHttpSession session, const AMHttpURL url);
    AMInt32 AMHttpCloseConnection(AMHttpConnection con);


    //��Request��Response.
    //contextΪ�����ı�ʶ, ���ڻص�������, ��ʾ�ص������Ǹ�AMHttpRequest
    //����AMHttpResponse.

    //�����Ƿ�Ҫ�ĳ�Create, ʵ�ֵ�ʱ���ٿ���. Get�ǵõ�, ��ʾAMHttpConnectionֻ��һ��AMHttpRequest
    //Create��ʾ�����ж��
    AMHttpRequest AMHttpGetRequest (AMHttpConnection con, 
        AMHttpVerb verb, AMUInt32 context);
    AMHttpResponse AMHttpGetResponse(AMHttpConnection con, AMUInt32 context);

    //�õ�����������, 
    AMInt32 AMHttpSetOption(AMHttpRequest request, AMHttpOption option, 
        AMUInt8* inBuf, AMUInt32 inBufLen); 
    AMInt32 AMHttpGetOption(AMHttpRequest request, AMHttpOption option,
        AMUInt8* outBuf, AMUInt32 inOutBufLen); 

    //context���Ϊ0, �̳�AMHttpConnection��context
    AMInt32 AMHttpSendRequest(AMHttpRequest request, AMUInt32 context);

    //�õ�AMHttpResponse��Ϣ.
    //AMHttpQueryCode��Ӧ�����ݸ�ʽ, ��鿴AMHttpQueryCode�Ķ���.
    AMInt32 AMHttpGetResponseInfo(AMHttpResponse response, AMHttpQueryCode code, 
        AMUInt8* outBuf, AMUInt32 inOutBufLen);
#ifdef __cplusplus
}
#endif
#endif

