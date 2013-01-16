//
//  SecurityUtil.h
//  ApiSecurityDemo
//
//  Created by  on 11-11-1.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonHMAC.h>

@interface SecurityUtil : NSObject

/*
 * HEX16
 */
+ (NSString*)stringWithHexBytes:(NSData *)objData;

/*
 * HEX16(HMAC-SHA1(data, key))
 */
+ (NSString *)hmacSha1ToHexStr:(NSString *)strData key:(const char *)cKey;

/*
 * 根据url，参数计算签名
 */
+ (NSString *)signature:(NSString *)pathUrl params:(NSDictionary *)params key:(const char *)cKey;

/*
* 追加AccessToken
*/
+ (void)appendAccessToken: (NSMutableDictionary *)params;

/*
 * 追加参数签名字符串
 */
+ (NSString*)generateSignedRequest:(NSString *)parentPath resourcePath:(NSString *)resourcePath params: (NSMutableDictionary *)params;

/*
 * 可选择的字符串，最后的参数表示是否追加签名。
 */
+ (NSString*)generateSignedRequest:(NSString *)parentPath resourcePath:(NSString *)resourcePath params: (NSMutableDictionary *)params isUseSignature:(BOOL)useOrNot;
@end
