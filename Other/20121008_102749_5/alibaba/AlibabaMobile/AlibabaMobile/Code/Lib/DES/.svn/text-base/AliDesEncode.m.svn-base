//
//  AliDesEncode.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#import "AliDesEncode.h"
#import <CommonCrypto/CommonCryptor.h>
@implementation AliDesEncode

#define SIGNIN_SECRET_KEY @"bado&alcn"

#define FBENCRYPT_ALGORITHM     kCCAlgorithmDES
#define FBENCRYPT_BLOCK_SIZE    kCCBlockSizeDES
#define FBENCRYPT_KEY_SIZE      kCCKeySizeDES

+ (NSString*)encode:(NSString*)token{
    
    NSData*data = [token dataUsingEncoding:NSUTF8StringEncoding];
    NSData*key = [SIGNIN_SECRET_KEY dataUsingEncoding:NSUTF8StringEncoding];
    
    NSData* result = nil;
    
    // setup key
    unsigned char cKey[FBENCRYPT_KEY_SIZE];
	bzero(cKey, sizeof(cKey));
    [key getBytes:cKey length:FBENCRYPT_KEY_SIZE];
	
    // setup iv
    char cIv[FBENCRYPT_BLOCK_SIZE];
    bzero(cIv, FBENCRYPT_BLOCK_SIZE);
       
    // setup output buffer
	size_t bufferSize = [data length] + FBENCRYPT_BLOCK_SIZE;
	void *buffer = malloc(bufferSize);
    
    // do encrypt
	size_t encryptedSize = 0;
	CCCryptorStatus cryptStatus = CCCrypt(kCCEncrypt,
                                          FBENCRYPT_ALGORITHM,
                                          kCCOptionECBMode|kCCOptionPKCS7Padding,
                                          cKey,
                                          FBENCRYPT_KEY_SIZE,
                                          cIv,
                                          [data bytes],
                                          [data length],
                                          buffer,
                                          bufferSize,
										  &encryptedSize);
    if (cryptStatus == kCCSuccess) {
		result = [NSData dataWithBytesNoCopy:buffer length:encryptedSize];
	} else {
        free(buffer);
        NSLog(@"[ERROR] failed to encrypt|CCCryptoStatus: %d", cryptStatus);
    }
    return [result base64Encoding];
  }

@end
