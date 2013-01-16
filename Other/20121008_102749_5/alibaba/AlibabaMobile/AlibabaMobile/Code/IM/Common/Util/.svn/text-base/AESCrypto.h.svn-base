//
//  AESCrypto.h
//  BencaogangmuPreLoad
//
//  Created by Chen John on 10-2-27.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>
#import <CommonCrypto/CommonCryptor.h>

@interface AESCrypto : NSObject {

}

-(NSData *)encryptText:(NSString *)text;
-(NSString *)decryptText:(NSData *)encryptedData;
	
-(NSData *)encrypt:(NSData *)plainText key:(NSData *)aSymmetricKey padding:(CCOptions *)pkcs7;
-(NSData *)decrypt:(NSData *)plainText key:(NSData *)aSymmetricKey padding:(CCOptions *)pkcs7;

- (NSData *)doCipher:(NSData *)plainText key:(NSData *)aSymmetricKey
			 context:(CCOperation)encryptOrDecrypt padding:(CCOptions *)pkcs7;
@end
