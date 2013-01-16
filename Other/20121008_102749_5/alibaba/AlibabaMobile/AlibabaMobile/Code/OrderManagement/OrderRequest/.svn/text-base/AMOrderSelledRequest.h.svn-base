//
//  AMOrderSelledRequest.h
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-9-14.
//
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

extern NSString *const const OCEAN_API_URL_ORDER_SELLEDORDERS;

@interface AMOrderSelledRequest : NSObject <RKRequestSerializable>
{
    NSDictionary * _request;
    NSString *_sellerMemberId;
    NSNumber *_page;
    NSNumber *_pageSize;
    NSString *_orderStatusSet;
}
@property (nonatomic, retain) NSDictionary *request;
@property (nonatomic, retain) NSString *sellerMemberId;
@property (nonatomic, retain) NSNumber *page;
@property (nonatomic, retain) NSNumber *pageSize;
@property (nonatomic, retain) NSString *orderStatusSet;
@end
