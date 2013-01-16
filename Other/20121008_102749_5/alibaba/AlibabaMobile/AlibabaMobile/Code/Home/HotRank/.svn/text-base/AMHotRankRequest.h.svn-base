//
//  AMHotRankRequest.h
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_HOT_RANK_CONTENTS ([@"/ops.config.findPageConfig/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMHotRankRequest : NSObject<RKRequestSerializable> {
    NSString *_name;
    NSString *_aop_responseFormat;
}

@property (nonatomic, retain) NSString *name;
@property (nonatomic, retain) NSString *aop_responseFormat;

@end
