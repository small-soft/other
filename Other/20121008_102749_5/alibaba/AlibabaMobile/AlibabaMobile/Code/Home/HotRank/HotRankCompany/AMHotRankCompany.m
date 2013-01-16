//
//  AMHotRankCompany.m
//  AlibabaMobile
//
//  Created by amon on 12-4-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMHotRankCompany.h"

@implementation AMHotRankCompany
@synthesize cityName = _cityName;
@synthesize companyName = _companyName;
@synthesize companyPaymentGMV = _companyPaymentGMV;
@synthesize rankRiseNum = _rankRiseNum;
@synthesize satisfiedRate = _satisfiedRate;
@synthesize offerPicUrl = _offerPicUrl;
@synthesize sellerCompanyId = _sellerCompanyId;
@synthesize sellerMemberId = _sellerMemberId;
+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
//sellerCompanyId: 26300887,
//streetAddr: "南洋路服装城纺织机械市场1A栋二层",
//cityName: "石狮市",
//provinceName: "福建",
//companyName: "石狮市谷翼崎服饰有限公司",
//companyPaymentGMV: 214145,
//backBuyerCnt: 17,
//satisfiedRate: 99.14,
//rankRiseNum: 0,
//buyerMemberCnt: 104,
//offerPicUrl: [
//              "http://img.china.alibaba.com/img/ibank/2012/346/909/491909643_1243285864.64x64.jpg",
//              "http://img.china.alibaba.com/img/ibank/2012/368/009/483900863_1243285864.64x64.jpg",
//              "http://img.china.alibaba.com/img/ibank/2012/027/739/491937720_1243285864.64x64.jpg",
//              "http://img.china.alibaba.com/img/ibank/2012/035/265/492562530_1243285864.64x64.jpg"
//              ],
//sellerMemberId: "chinagueqi",
//companyTradeCnt: 141
    
//    
//    NSNumber *_satisfiedRate;//商品满意度
//    NSString *companyName;//公司
//    NSNumber *_companyPaymentGMV;//交易额
//    NSString *_cityName;//城市
//    NSNumber *_rankRiseNum;//上升排名
    
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHotRankCompany class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"satisfiedRate" toAttribute:@"satisfiedRate"];
            [sharedObjectMapping mapKeyPath:@"rankRiseNum" toAttribute:@"rankRiseNum"];
            [sharedObjectMapping mapKeyPath:@"companyName" toAttribute:@"companyName"];
            [sharedObjectMapping mapKeyPath:@"companyPaymentGMV" toAttribute:@"companyPaymentGMV"];
            [sharedObjectMapping mapKeyPath:@"cityName" toAttribute:@"cityName"];
            [sharedObjectMapping mapKeyPath:@"offerPicUrl" toAttribute:@"offerPicUrl"];
            [sharedObjectMapping mapKeyPath:@"sellerCompanyId" toAttribute:@"sellerCompanyId"];
            [sharedObjectMapping mapKeyPath:@"sellerMemberId" toAttribute:@"sellerMemberId"];

        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc{
    [_companyName release];
    [_cityName release];
    [_satisfiedRate release];
    [_companyPaymentGMV release];
    [_rankRiseNum release];
    [_offerPicUrl release];
    [_sellerCompanyId release];
    [_sellerMemberId release];
    [super dealloc];
}
@end
