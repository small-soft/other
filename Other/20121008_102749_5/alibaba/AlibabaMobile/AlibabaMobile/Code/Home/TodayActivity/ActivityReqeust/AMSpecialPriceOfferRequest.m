//
//  AMHotRankOfferRequest.m
//  AlibabaMobile
//
//  Created by amon on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

//http://172.22.35.80/openapi/json2/1/ali.mobile/offer.querySpecialPriceOffer/5005?_data_={industryId:%22smart%22}}

#import "AMSpecialPriceOfferRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"

@implementation AMSpecialPriceOfferRequest

@synthesize industryId = _industryId;
@synthesize requestURL = _requestURL;
@synthesize pageSize = _pageSize;
@synthesize pageIndex = _pageIndex;

-(id)init {
    [super init];
    if(self){
//        self.industryId = @"smart";
        self.requestURL = OCEAN_API_URL_SPECIAL_PRICE_OFFER_LIST;
        self.pageIndex = [NSNumber numberWithInt:1];
        self.pageSize = [NSNumber numberWithInt:10];
        
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
    
    NSString *_data_ = [NSString stringWithFormat: @"{request:{industryId:\"%@\",pageInfo:{pageSize:%@,pageIndex:%@}}}",self.industryId,self.pageSize,self.pageIndex];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    
//    signedBodyString = [NSString stringWithFormat: @"_data_=%@", _data_];
    signedBodyString = [NSString stringWithFormat: @"_data_=%@&_aop_signature=%@", _data_, [SecurityUtil signature:urlData params:params key:cKey]];
    
    [params release];

//    NSLog(@"special price request=http://172.22.35.80/openapi/json2/1/ali.mobile/offer.queryNewSpecialPriceOffer/5005?%@",signedBodyString);
    NSLog(@"special price request=http://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/offer.queryNewSpecialPriceOffer/5005?%@",signedBodyString);
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

-(void) dealloc{
    
    [_industryId release];
    [_requestURL release];
    [_pageSize release];
    [_pageIndex release];
    [super dealloc];
}

@end

