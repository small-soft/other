 //
//  SecurityUtil.m
//  ApiSecurityDemo
//
//  Created by  on 11-11-1.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "SecurityUtil.h"
#import "LoginToken.h"
#import "ConstDef.h"
#import "AMLogUtils.h"
#import "AMUncaughtExceptionService.h"
@implementation SecurityUtil

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

+ (NSString*)stringWithHexBytes:(NSData *)objData {
    static const char hexdigits[] = "0123456789ABCDEF";
    const size_t numBytes = [objData length];
    const unsigned char* bytes = [objData bytes];
    char *strbuf = (char *)malloc(numBytes * 2 + 1);
    char *hex = strbuf;
    NSString *hexBytes = nil;
    
    for (int i = 0; i<numBytes; ++i) { 
        const unsigned char c = *bytes++;
        *hex++ = hexdigits[(c >> 4) & 0xF];
        *hex++ = hexdigits[(c ) & 0xF];
    }
    *hex = 0;
    hexBytes = [NSString stringWithUTF8String:strbuf];
    free(strbuf);
    return hexBytes;
}

+ (NSString *)hmacSha1ToHexStr:(NSString *)strData key:(const char *)cKey
{
    const char *cData = [strData cStringUsingEncoding:NSASCIIStringEncoding];
    
    unsigned char cHMAC[CC_SHA1_DIGEST_LENGTH];
    
    CCHmac(kCCHmacAlgSHA1, cKey, strlen(cKey), cData, strlen(cData), cHMAC);
    
    NSData *hmac = [[NSData alloc] initWithBytes:cHMAC length:sizeof(cHMAC)];
    
    NSString *hash = [SecurityUtil stringWithHexBytes:hmac];
    [hmac release];
    return [hash autorelease];
}

+ (NSString *)signature:(NSString *)pathUrl params:(NSDictionary *)paramMap key:(const char *)cKey
{
    NSMutableArray *params = [[NSMutableArray alloc] init];
    NSRange range = [pathUrl rangeOfString:@"?"];
    NSString *baseUrl;
    if(range.length > 0)
    {
        baseUrl = [pathUrl substringToIndex:range.location];
        NSArray *chunks = [[pathUrl substringFromIndex:range.location+1] componentsSeparatedByString:@"&"];
        if(chunks){
            for (NSString *chunk in chunks) {
                NSRange prange = [chunk rangeOfString:@"="];
                if(range.length > 0)
                {
                    NSMutableString *tmp = [[NSMutableString alloc] initWithString:[chunk substringToIndex:prange.location]];
                    [tmp appendString:[chunk substringFromIndex:prange.location+1]];
                    [params addObject:[tmp autorelease]];
                }
                else
                {
                    [params addObject:chunk];
                }
            }
        }
    }else{
        baseUrl = pathUrl;
    }
    for (NSString *key in [paramMap allKeys]) {
        NSMutableString *tmp = [[NSMutableString alloc] initWithString:key];
        NSString *value = [paramMap valueForKey:key];
        if(value){
            [tmp appendString:value];
        }
        [params addObject:[tmp autorelease]];
    }
    [params sortUsingSelector:@selector(compare:)];
    CCHmacContext ctx;
    unsigned char cHMAC[CC_SHA1_DIGEST_LENGTH];
    const char *cData = [baseUrl cStringUsingEncoding:NSUTF8StringEncoding];
    CCHmacInit(&ctx, kCCHmacAlgSHA1, cKey, strlen(cKey));
    CCHmacUpdate(&ctx, cData, strlen(cData));
    CCHmac(kCCHmacAlgSHA1, cKey, strlen(cKey), cData, strlen(cData), cHMAC);
    for (NSString *param in params) {
        const char *cpData = [param cStringUsingEncoding:NSUTF8StringEncoding];
        CCHmacUpdate(&ctx, cpData, strlen(cpData));
    }
    [params release];
    CCHmacFinal(&ctx, cHMAC);
    NSData *hmac = [[NSData alloc] initWithBytes:cHMAC length:sizeof(cHMAC)];
    
    NSString *hash = [SecurityUtil stringWithHexBytes:hmac];
    [hmac release];
    return hash;
}

+ (void)appendAccessToken: (NSMutableDictionary *)params {
    AMUncaughtExceptionService *service = [AMUncaughtExceptionService instance];

//    return;
//    
//    if(service.count==0){
//        return;
//    }
//    if (service.count==1) {
//        return;
//    }
    NSString *accessToken = [LoginToken getAccessToken];
    if (accessToken != nil && params != nil) {
        [params setObject:accessToken forKey:@"access_token"];
    }
}

+ (NSString*)generateSignedRequest:(NSString *)parentPath resourcePath:(NSString *)resourcePath params:(NSMutableDictionary *)params {
    // Generate ocean signature string
    const char *cKey = [AMCONST_SIGNATURE_KEY cStringUsingEncoding:NSASCIIStringEncoding];
    NSMutableString *urlData = [NSMutableString stringWithString:parentPath] ;
    [urlData appendString:resourcePath];
    
    NSString *paramsString = [NSString stringWithString:@""];
    [SecurityUtil appendAccessToken: params];
   
    [AMLogUtils appendLogTraceToHTTPRequest: params];
    
    if (params != nil && [params count] > 0) {
        for (NSString *key in [params allKeys]) {
            NSString *value = [params objectForKey: key];
            paramsString = [paramsString stringByAppendingFormat:[paramsString length] == 0 ? @"%@=%@" : @"&%@=%@", key, value];
        }
    }
    
    NSString *signature = [SecurityUtil signature:urlData params:params key:cKey];
    if (signature != nil) {
        return [paramsString stringByAppendingFormat: [paramsString length] == 0 ? @"_aop_signature=%@" : @"&_aop_signature=%@", signature];
    } else {
        return nil;
    }
}

+(NSString *)generateSignedRequest:(NSString *)parentPath resourcePath:(NSString *)resourcePath params:(NSMutableDictionary *)params isUseSignature:(BOOL)useOrNot{
    
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:parentPath resourcePath:resourcePath params:params];
    if (!useOrNot) {
        NSString *subString = @"&_aop_signature=";
        NSRange range = [signedBodyString rangeOfString:subString];
        int location = range.location;
        NSString *newSignedBodyString= [signedBodyString substringToIndex:location];
        
        return newSignedBodyString;
    }
    return signedBodyString;
}
@end
