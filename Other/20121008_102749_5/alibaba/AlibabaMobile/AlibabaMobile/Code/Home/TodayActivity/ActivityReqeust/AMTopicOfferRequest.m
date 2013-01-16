//
//  AMTopicOfferRequest.m
//  AlibabaMobile
//
//  Created by amon on 12-8-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

//http://172.22.35.80/openapi/json2/1/ali.mobile/offer.querySpecialPriceOffer/5005?_data_={industryId:%22smart%22}}

#import "AMTopicOfferRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"

@implementation AMTopicOfferRequest

@synthesize topicId = _topicId;
@synthesize pageIndex = _pageIndex;
@synthesize pageSize = _pageSize;
@synthesize requestURL = _requestURL;

-(id)init {
    [super init];
    if(self){
        self.requestURL = OCEAN_API_URL_TOPIC_OFFER_LIST;
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
    
    // Generate ocean signature string
    const char *cKey = [AMCONST_SIGNATURE_KEY cStringUsingEncoding:NSASCIIStringEncoding];
    NSMutableString *urlData = [NSMutableString stringWithString:AMCONST_OCEAN_PREFIX] ;
    [urlData appendString:self.requestURL]; 
    
    NSString *signedBodyString = nil;
    
//    NSString *_data_ = [NSString stringWithFormat: @"{topicId:%@}",self.topicId];
    NSString *_data_ = [NSString stringWithFormat: @"{request:{topicId:%@,pageInfo:{pageSize:%@,pageIndex:%@}}}",self.topicId,self.pageSize,self.pageIndex];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    
    signedBodyString = [NSString stringWithFormat: @"_data_=%@&_aop_signature=%@", _data_, [SecurityUtil signature:urlData params:params key:cKey]];
    
    [params release];
    NSLog(@"topic offer request=http://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/activity.topic.listTopicOffer/5005?%@",signedBodyString);
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

-(void) dealloc{
    
    [_topicId release];
    [_pageSize release];
    [_pageIndex release];
    [_requestURL release];
    [super dealloc];
}

@end

