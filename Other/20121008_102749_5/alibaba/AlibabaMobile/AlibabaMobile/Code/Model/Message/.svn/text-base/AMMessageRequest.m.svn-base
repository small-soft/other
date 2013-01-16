//
//  AMMessageRequest.m
//  AlibabaMobile
//
//  Created by qizhi.tangqz on 11-12-29.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import "AMMessageRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation AMMessageRequest

@synthesize transactionType = _transactionType;

@synthesize memberId = _memberId;
@synthesize pageIndex = _pageIndex;
@synthesize pageSize = _pageSize;
@synthesize newMessageOnly = _newMessageOnly;
@synthesize messageId = _messageId;

@synthesize requestURL;

- (id) init {
    if (self = [super init]) {
    }
    
    return self;
}

// Impliment RKRequestSerializable delegate methods here

/**
 * The value of the Content-Type header for the HTTP Body representation of the serialization
 */
- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}

/**
 * An NSData representing the HTTP Body serialization of the object implementing the protocol
 */
- (NSData*)HTTPBody {

    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMMessageRequest class]];
    [requestMapping mapKeyPath:@"pageIndex" toAttribute:@"pageIndex"];
    [requestMapping mapKeyPath:@"pageSize" toAttribute:@"pageSize"];
	[requestMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
	[requestMapping mapKeyPath:@"newMessageOnly" toAttribute:@"newMessageOnly"];
	[requestMapping mapKeyPath:@"messageId" toAttribute:@"messageId"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString *_data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];

    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    
    NSString *signedBodyString = nil;
    
    if (self.transactionType == AMTRANSACTION_TYPE_MESSAGE_TYPE) {
        signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:self.requestURL params:nil];
    }else {
        [params setObject: _data_ forKey: @"_data_"];
        signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:self.requestURL params:params];
    }

    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_memberId release];
    [_pageIndex release];
	[_pageSize release];
    [_newMessageOnly release];
	[_messageId release];
    
    self.requestURL = nil;
    
    [super dealloc];
}

@end
