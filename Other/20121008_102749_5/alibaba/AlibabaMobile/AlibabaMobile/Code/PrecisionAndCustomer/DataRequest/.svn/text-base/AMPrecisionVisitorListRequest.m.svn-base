//
//  AMPrecisionVisitorListRequest.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionVisitorListRequest.h"
#import "AMCUDFavoriteRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation AMPrecisionVisitorListRequest

@synthesize transactionType = _transactionType;
@synthesize pageNo = _pageNo;
@synthesize pageSize = _pageSize;
@synthesize online = _online;
@synthesize siteId = _siteId;
@synthesize beginPage = _beginPage;

@synthesize request = _request;

@synthesize requestURL;

- (id) init {
    if (self = [super init]) {
        self.requestURL = OCEAN_API_URL_PRECISION_VISITOR_LIST;
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
    
    NSMutableDictionary *wrappedParams = nil;
    
    if ( (self.transactionType == (int)AMTRANSACTION_TYPE_PRECISION_VISITOR_LIST)){
        wrappedParams = [[NSMutableDictionary alloc] init];
        self.online = [NSNumber numberWithBool:NO];
        self.pageNo = self.beginPage;
        self.pageSize = [NSNumber numberWithInt:9];
        //self.siteId = @"305935211";
        [wrappedParams setObject: self.online forKey: @"online"];
        [wrappedParams setObject: self.pageNo forKey: @"pageNo"];
        [wrappedParams setObject: self.pageSize forKey: @"pageSize"];
        [wrappedParams setObject: self.siteId forKey: @"siteId"];
        
        self.request = wrappedParams;
        [wrappedParams release];
    }
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMPrecisionVisitorListRequest class]];

	[requestMapping mapKeyPath:@"request" toAttribute:@"request"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString *_data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    self.request = nil;
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:self.requestURL params:params];
    [params release];
    
    //NSLog(@"URL = %@", signedBodyString);
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_pageNo release];
    [_pageSize release];
    [_siteId release];
    
    [_request release];
    
    self.requestURL = nil;
    
    [super dealloc];
}

@end
