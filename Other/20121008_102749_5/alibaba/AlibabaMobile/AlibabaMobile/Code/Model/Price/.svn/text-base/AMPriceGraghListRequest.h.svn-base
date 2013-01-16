//
//  AMPriceGraghListRequest.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-13.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_SEARCH_PRICE_GRAGH ([@"/news.priceMarket.getHistoryPrice/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMPriceGraghListRequest : NSObject<RKRequestSerializable> {
    
    /**
     * 请求参数容器
     */
    NSDictionary * _request;
    
    NSNumber * _themeId;
    NSNumber * _areaId;
    NSNumber * sourceFormId;

}



@property(nonatomic, retain) NSNumber * themeId;
@property(nonatomic, retain) NSNumber * areaId;
@property(nonatomic, retain) NSNumber * sourceFormId;
@property(nonatomic, retain) NSDictionary * request;


@end
