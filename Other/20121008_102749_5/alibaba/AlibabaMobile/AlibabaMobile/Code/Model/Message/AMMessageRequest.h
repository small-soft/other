//
//  AMMessageRequest.h
//  AlibabaMobile
//
//  Created by zzh on 11-12-29.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"

#define OCEAN_API_URL_MESSAGE_LIST ([@"/message.query/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_MESSAGE_TYPE ([@"/message.getViewCategories/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_MESSAGE_COUNT ([@"/message.getTotalMessageCount/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_MESSAGE_READ ([@"/message.readMessage/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_MESSAGE_DELETE ([@"/message.deleteMessage/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_MESSAGE_DETAIL ([@"/message.getMessage/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMMessageRequest: NSObject <RKRequestSerializable, AMRequestDelegate> {
    NSInteger _transactionType;
    
    NSString *_memberId;
    NSNumber *_pageIndex;
    NSNumber *_pageSize;
	
    NSNumber *_newMessageOnly; 
	NSNumber *_messageId;
}

@property (nonatomic, retain) NSString *memberId;
@property (nonatomic, retain) NSNumber *pageIndex;
@property (nonatomic, retain) NSNumber *pageSize;

@property (nonatomic, retain) NSNumber *newMessageOnly;
@property (nonatomic, retain) NSNumber *messageId;

@property (nonatomic) NSInteger transactionType;

@property (nonatomic, retain) NSString *requestURL;


@end