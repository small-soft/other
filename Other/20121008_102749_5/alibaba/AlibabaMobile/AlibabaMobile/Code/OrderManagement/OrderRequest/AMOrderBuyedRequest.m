//
//  BuyedOrdersRequest.m
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-8-30.
//
//NSDictionary * _request;
//NSString *_buyerMemberId;
//
//NSNumber *_page;
//NSNumber *_pageSize;

#import "AMOrderBuyedRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>


NSString * const OCEAN_API_URL_ORDER_BUYEDORDERS = @"/trade.order.listBuyedOrders/5005";

@implementation AMOrderBuyedRequest
@synthesize request = _request;
@synthesize buyerMemberId = _buyerMemberId;
@synthesize pageSize = _pageSize;
@synthesize page = _page;
@synthesize orderStatusSet = _orderStatusSet;
-(void)dealloc
{
    [_request release];
    [_buyerMemberId release];
    [_page release];
    [_pageSize release];
    [_orderStatusSet release];
    [super dealloc];
}


- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}
- (NSData*)HTTPBody
{

    self.pageSize = [NSNumber numberWithInt:6];
    
    NSString *signedBodyString = nil;
//    NSString *_data_ = [NSString stringWithFormat: @"{buyerMemberId:\"%@\",request:{buyerMemberId:\"%@\",page:%@,pageSize:%@}}",self.buyerMemberId,self.buyerMemberId,self.page,self.pageSize];
    
    
    NSString *_data_ = nil;
    if(self.orderStatusSet!=nil&self.orderStatusSet!=@""){
        _data_ = [NSString stringWithFormat: @"{buyerMemberId:\"%@\",request:{buyerMemberId:\"%@\",orderStatusSet:[\"%@\"],page:%@,pageSize:%@}}",self.buyerMemberId,self.buyerMemberId,self.orderStatusSet,self.page,self.pageSize];
    }else{
        _data_ = [NSString stringWithFormat: @"{buyerMemberId:\"%@\",request:{buyerMemberId:\"%@\",page:%@,pageSize:%@}}",self.buyerMemberId,self.buyerMemberId,self.page,self.pageSize];
    }
    
    
    
    //卖出货品的请求
//    NSString *_data_ = [NSString stringWithFormat: @"{buyerMemberId:\"%@\",request:{buyerMemberId:\"%@\",page:%@,pageSize:%@}}",self.buyerMemberId,self.buyerMemberId,self.page,self.pageSize];
    
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_ORDER_BUYEDORDERS params:params];
    NSLog(@"REQUEST=http://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/trade.order.listBuyedOrders/5005?%@",signedBodyString );
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
    
}
@end
