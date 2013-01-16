//
//  AMUncaughtExceptionRequest.h
//  AlibabaMobile
//
//  Created by  on 12-7-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_SEND_EXCEPTION_LOGS ([@"/ops.appclick.createAppErrorLogs/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMUncaughtExceptionRequest : NSObject<RKRequestSerializable>{
    
    NSInteger _transactionType;
    
    NSDictionary * _request;
    
    NSDictionary * _header;
    
    NSArray * _logs;
    
}

@property (nonatomic) NSInteger transactionType;

@property(nonatomic, retain) NSDictionary * header;
@property(nonatomic, retain) NSArray * logs;

@property(nonatomic, retain) NSDictionary * request;
@property (nonatomic, retain) NSString *accessToken;

@end

