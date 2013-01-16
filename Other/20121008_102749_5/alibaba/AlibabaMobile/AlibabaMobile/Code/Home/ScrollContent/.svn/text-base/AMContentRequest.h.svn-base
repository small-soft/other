//
//  AMContentRequest.h
//  AlibabaMobile
//
//  Created by zzh on 11-12-29.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_CONTENTS ([@"/ops.config.findPageConfig/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMContentRequest : NSObject<RKRequestSerializable> {
    NSString *_name;
    NSString *_aop_responseFormat;
}

@property (nonatomic, retain) NSString *name;
@property (nonatomic, retain) NSString *aop_responseFormat;   

@end