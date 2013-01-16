//
//  AMOrderBuyedRequest.h
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-8-30.
//
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

extern NSString *const const OCEAN_API_URL_ORDER_BUYEDORDERS;

@interface AMOrderBuyedRequest : NSObject <RKRequestSerializable>
{
    NSDictionary * _request;
    NSString *_buyerMemberId;
    NSNumber *_page;
    NSNumber *_pageSize;
    NSString * _orderStatusSet;
}
@property (nonatomic, retain) NSDictionary *request;
@property (nonatomic, retain) NSString *buyerMemberId;
@property (nonatomic, retain) NSNumber *page;
@property (nonatomic, retain) NSNumber *pageSize;
@property (nonatomic, retain) NSString *orderStatusSet;

@end
