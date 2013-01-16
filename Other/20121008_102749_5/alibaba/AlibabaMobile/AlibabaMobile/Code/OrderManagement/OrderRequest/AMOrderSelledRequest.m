//
//  AMOrderSelledRequest.m
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-9-14.

#import "AMOrderSelledRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>


NSString * const OCEAN_API_URL_ORDER_SELLEDORDERS = @"/trade.order.listSelledOrders/5005";

@implementation AMOrderSelledRequest
@synthesize request = _request;
@synthesize sellerMemberId = _sellerMemberId; 
@synthesize pageSize = _pageSize;
@synthesize page = _page;
@synthesize orderStatusSet = _orderStatusSet;
-(void)dealloc
{
    [_request release];
    [_sellerMemberId release];
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
    NSString *_data_ = nil;
//    if(self.orderStatusSet!=nil&&self.orderStatusSet!=@""){
//         _data_ = [NSString stringWithFormat: @"{sellerMemberId:\"%@\",request:{sellerMemberId:\"%@\",orderStatusSet:[\"%@\"],page:%@,pageSize:%@}}",self.sellerMemberId,self.sellerMemberId,self.orderStatusSet,self.page,self.pageSize];
//    }else{
//        _data_ = [NSString stringWithFormat: @"{sellerMemberId:\"%@\",request:{sellerMemberId:\"%@\",page:%@,pageSize:%@}}",self.sellerMemberId,self.sellerMemberId,self.page,self.pageSize];  
//    }
    if(self.orderStatusSet==nil){
        _data_ = [NSString stringWithFormat: @"{sellerMemberId:\"%@\",request:{sellerMemberId:\"%@\",orderStatusSet:[\"%@\"],page:%@,pageSize:%@}}",self.sellerMemberId,self.sellerMemberId,@"",self.page,self.pageSize];
    }else{
        _data_ = [NSString stringWithFormat: @"{sellerMemberId:\"%@\",request:{sellerMemberId:\"%@\",orderStatusSet:[\"%@\"],page:%@,pageSize:%@}}",self.sellerMemberId,self.sellerMemberId,self.orderStatusSet,self.page,self.pageSize];
    }
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_ORDER_SELLEDORDERS params:params];
    NSLog(@"REQUEST=http://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/trade.order.listSelledOrders/5005?%@",signedBodyString );
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
    
}
@end
