//
//  AMFeedbackRequest.h
//  AlibabaMobile
//
//  Created by lih on 12-2-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_FEEDBACK ([@"/feedback.commitSuggestion/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMFeedbackRequest : NSObject <RKRequestSerializable> {
    
    NSString * _content;
    NSString * _type; 
    NSString * _source;
    NSString *_memberId;
    NSDictionary  *_suggestion;
}

@property (nonatomic, retain) NSString *content;
@property (nonatomic, retain) NSString *type;
@property (nonatomic, retain) NSString *source;
@property (nonatomic, retain) NSString *memberId;
@property (nonatomic, retain) NSDictionary  *suggestion;

@property (nonatomic, retain) NSString *requestURL;

@end