
#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_SEARCH_PRICE ([@"/news.priceMarket.getMarketPriceListV2/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMPriceListRequest : NSObject<RKRequestSerializable> {
    
    /**
     * 请求参数容器
     */
    NSDictionary * _request;
    
    NSString * _keyword;
    NSNumber * _cateId;
    NSNumber * _areaId;
    NSNumber * _page;
    NSNumber * _count;
}

@property(nonatomic, retain) NSString * keywords;
@property(nonatomic, retain) NSString * catName;
@property(nonatomic, retain) NSNumber * cateId;
@property(nonatomic, retain) NSNumber * areaId;
@property(nonatomic, retain) NSNumber * page;
@property(nonatomic, retain) NSNumber * count;

@property(nonatomic, retain) NSDictionary * request;

@end