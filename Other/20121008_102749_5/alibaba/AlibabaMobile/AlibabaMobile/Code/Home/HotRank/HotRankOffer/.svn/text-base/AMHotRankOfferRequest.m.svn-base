//
//  AMHotRankOfferRequest.m
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

//https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/rank.getMutiCategoryTradeRank/5005?_aop_signature=8C1D50E4A0725820A581A3E425FF3E36DB003AF8&targetId=90030&_data_={"request":{"beginPage":0,"cateIds":"10165","pageSize":9,"rankCycle":7,"rankType":"U"}}&clickId=1&clickUUID=c95fd47e-8a4d-4f11-a733-b54f5306d14b&deviceId=dea608f87dd800d7f40e688c5900433c&pageId=90020

#import "AMHotRankOfferRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"

@implementation AMHotRankOfferRequest

@synthesize beginPage = _beginPage;
@synthesize pageSize = _pageSize;
@synthesize rankCycle = _rankCycle;
@synthesize cateIds = _cateIds;
@synthesize requestURL;
@synthesize listMode = _listMode;
@synthesize transactionType = _transactionType;
-(id)init {
    [super init];
    if(self){
        self.beginPage = [NSNumber numberWithInt:1];
        self.pageSize = [NSNumber numberWithInt:9];
        self.rankCycle = [NSNumber numberWithInt:7];
        self.requestURL = OCEAN_API_URL_HOT_RANK_OFFER_LIST;
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
    
    NSString *_data_ = [NSString stringWithFormat: @"{request:{beginPage:%@,pageSize:%@,cateIds:\"%@\",rankCycle:%@,rankType:\"%@\"}}", self.beginPage, self.pageSize, self.cateIds,self.rankCycle,self.listMode];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    
    signedBodyString = [NSString stringWithFormat: @"_data_=%@&_aop_signature=%@", _data_, [SecurityUtil signature:urlData params:params key:cKey]];
    
    [params release];
    NSLog(@"hotrank offer request=https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/rank.getMutiCategoryTradeRank/5005?%@",signedBodyString);
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

-(void) dealloc{
    
    [_cateIds release];
    [_rankCycle release];
    [_listMode release];
    [_beginPage release];
    [_pageSize release];
    [requestURL release];
    [super dealloc];
}

@end

