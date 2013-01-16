//
//  AMHotRankRequest.m
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-4-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


//
//https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/news.getImgMagazineCategories/5005?_aop_signature=6FC8841E28384A93FA2C8A7B37CCD6A92FD9C4C3&access_token=61c10f41-4a7a-468f-a1ef-5bcfbbfadf17&targetId=15&_data_={}&clickId=13&clickUUID=4bb550b5-fda2-4a16-857f-6bfc138e0650&deviceId=dea608f87dd800d7f40e688c5900433c&pageId=106
//

//https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/news.getImgMagazineList/5005?_aop_signature=AB6F2A6856FC365F89D3FA174D78E1A71ECEDFEC&access_token=61c10f41-4a7a-468f-a1ef-5bcfbbfadf17&targetId=15&_data_={"request":{"categoryid":"1","count":40,"page":1}}&clickId=2&clickUUID=ce065c61-2cc5-4488-a499-5f59ef0b4b55&deviceId=dea608f87dd800d7f40e688c5900433c&pageId=15
////
//热销排行
//
//https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/rank.getMutiCategoryTradeRank/5005?_aop_signature=2CCEE4AB032BD2D73D15260E6E59CD70F7B1C558&access_token=61c10f41-4a7a-468f-a1ef-5bcfbbfadf17&targetId=90030&_data_={"request":{"beginPage":0,"cateIds":"1043324","pageSize":9,"rankCycle":7,"rankType":"H"}}&clickId=1&clickUUID=6c69fd01-934a-4f95-baa7-4592b8cf7e86&deviceId=dea608f87dd800d7f40e688c5900433c&pageId=90020

#import "AMHotRankCompanyRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"

@implementation AMHotRankCompanyRequest

@synthesize page = _page;
@synthesize count = _count;
@synthesize rankCycle = _rankCycle;
@synthesize requestURL;
@synthesize cateId = _cateId;
@synthesize listMode = _listMode;
@synthesize transactionType = _transactionType;


-(id)init {
    [super init];
    if(self){
        self.page = [NSNumber numberWithInt:1];
        self.count = [NSNumber numberWithInt:9];
        self.rankCycle = [NSNumber numberWithInt:7];
        self.requestURL = OCEAN_API_URL_HOT_RANK_COMPANY_LIST;
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

		NSString *_data_ = [NSString stringWithFormat: @"{request:{beginPage:%@,pageSize:%@,cateId:\"%@\",rankCycle:%@,rankType:\"%@\"}}", self.page, self.count, self.cateId,self.rankCycle,self.listMode];
        
		// Create NSDictionary object and setObject to it
		NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
		[params setObject: _data_ forKey: @"_data_"];
        
		signedBodyString = [NSString stringWithFormat: @"_data_=%@&_aop_signature=%@", _data_, [SecurityUtil signature:urlData params:params key:cKey]];
        
    [params release];
	 NSLog(@"hotrank request=https://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/rank.getMutiCategoryTradeRank/5005?%@",signedBodyString);
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc{
    [_page release];
    [_count release];
    [_rankCycle release];
    [_listMode release];
    [_cateId release];
    [requestURL release];
    [super dealloc];
}

@end
