//
//  AMPrecisionVisitorListRequest.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"

#define OCEAN_API_URL_PRECISION_VISITOR_LIST ([@"/itrade.queryAllVisitor/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMPrecisionVisitorListRequest : NSObject <RKRequestSerializable, AMRequestDelegate> {
    NSInteger _transactionType;
    
    NSNumber *_beginPage;
    NSNumber *_pageNo;
    NSNumber *_pageSize;
    NSString *_siteId;
	NSDictionary *_request;
}

@property (nonatomic, retain) NSNumber *beginPage;

@property (nonatomic, retain) NSNumber *pageNo;
@property (nonatomic, retain) NSNumber *pageSize;
@property (nonatomic, retain) NSString *siteId;
@property (nonatomic, retain) NSDictionary  *request;

@property (nonatomic) NSInteger transactionType;
@property (nonatomic, retain) NSString *requestURL;
@property (nonatomic, retain) NSNumber *online;

@end
