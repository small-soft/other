//
//  AMFavoriteRequest.m
//  AlibabaMobile
//
//  Created by qizhi.tangqz on 11-12-29.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import "AMFavoriteRequest.h"
#import "AMCUDFavoriteRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation AMFavoriteRequest

@synthesize transactionType = _transactionType;

@synthesize memberid = _memberid;
@synthesize beginPage = _beginPage;
@synthesize pageSize = _pageSize;

@synthesize offerids = _offerids;
@synthesize offerid = _offerid;
@synthesize companyids = _companyids;
@synthesize companyid = _companyid;

@synthesize themeId = _themeId;
@synthesize area = _area;
@synthesize sourceFromId = _sourceFromId;
@synthesize memberId = _memberId;

@synthesize request = _request;

@synthesize requestURL;

- (id) init {
    if (self = [super init]) {
        self.requestURL = OCEAN_API_URL_OFFER_FAV;
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

    if ( (self.transactionType == (int)AMTRANSACTION_TYPE_FAVORITE_PRICE_ADD) 
          ||(self.transactionType == (int)AMTRANSACTION_TYPE_FAVORITE_PRICE_DELETE) ){
        wrappedParams = [[NSMutableDictionary alloc] init];
        [wrappedParams setObject: self.themeId forKey: @"themeId"];
        [wrappedParams setObject: self.memberId forKey: @"memberId"];
        [wrappedParams setObject: self.area forKey: @"area"];
        [wrappedParams setObject: self.sourceFromId forKey: @"sourceFromId"];
        
        self.request = wrappedParams;
        //修改人 孟希羲
        //NSLog(@"request :%d",[self.request retainCount]);
        [wrappedParams release];
        //NSLog(@"request :%d",[self.request retainCount]);
    }
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMFavoriteRequest class]];
    [requestMapping mapKeyPath:@"beginPage" toAttribute:@"beginPage"];
    [requestMapping mapKeyPath:@"pageSize" toAttribute:@"pageSize"];
    
    if (!( (self.transactionType == (int)AMTRANSACTION_TYPE_FAVORITE_PRICE_ADD) 
        ||(self.transactionType == (int)AMTRANSACTION_TYPE_FAVORITE_PRICE_DELETE) )){
        [requestMapping mapKeyPath:@"memberid" toAttribute:@"memberid"];
    } 
    
	[requestMapping mapKeyPath:@"offerid" toAttribute:@"offerid"];
	[requestMapping mapKeyPath:@"offerids" toAttribute:@"offerids"];
    [requestMapping mapKeyPath:@"companyids" toAttribute:@"companyids"];
    [requestMapping mapKeyPath:@"companyid" toAttribute:@"companyid"];
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
    NSLog(@"signedBodyString : %@",signedBodyString);
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_memberid release];
    [_pageSize release];
    [_offerids release];
    [_offerid release];
    [_companyids release];
    [_beginPage release];
    [_companyid release];
    [_request release];
    [_themeId release];
    [_area release];
    [_sourceFromId release];
    [_memberId release];
    
    self.requestURL = nil;
    
    [super dealloc];
}

@end
