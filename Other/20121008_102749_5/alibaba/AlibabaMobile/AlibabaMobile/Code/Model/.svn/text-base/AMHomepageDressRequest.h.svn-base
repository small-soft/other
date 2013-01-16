//
//  AMHomepageDressRequest.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-23.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"

#define OCEAN_API_URL_INDUSTRY_CONTENTS ([@"/industry.homepage/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMHomepageDressRequest : NSObject<RKRequestSerializable,AMRequestDelegate> {
    NSInteger     _transactionType;
    NSString     *_industryId;
    NSString     *_configName;
    NSString     *_summary; 
    NSDictionary *_request;
}

@property (nonatomic) NSInteger transactionType;
@property (nonatomic, retain) NSString *industryId;
@property (nonatomic, retain) NSString *configName;
@property (nonatomic, retain) NSString *summary;
@property (nonatomic, retain) NSDictionary * request;

@end