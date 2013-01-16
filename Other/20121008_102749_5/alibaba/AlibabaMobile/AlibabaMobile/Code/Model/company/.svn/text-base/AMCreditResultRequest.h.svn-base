//
//  AMCreditResultRequest.h
//  AlibabaMobile
//
//  Created by  on 12-2-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_CREDIT_RESULT ([@"/company.getCreditDetail/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMCreditResultRequest : NSObject<RKRequestSerializable>
{
    NSString * _memberId;
    NSDictionary * _request;
}


@property (nonatomic, retain) NSString * memberId;
@property(nonatomic, retain) NSDictionary * request;

@end