//
//  AMPriceGraghListResult.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-13.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@class AMPriceGraghHistotyItem;
@interface AMPriceGraghListResult : NSObject<AMObjectMappingDelegate> {
    
    /**
     * 请求成功标志
     */
    BOOL _success;
    
    /**
     * 历史价格记录
     */
    NSArray * _historyPrice;
}

@property(nonatomic, retain) NSArray * historyPrice;
@property(nonatomic, assign) BOOL success;

@end


@interface AMPriceGraghHistotyItem : NSObject <AMObjectMappingDelegate> {
    
    /**
     * 来源名字
     */
    NSString * _sourceFromName;
    
    /**
     * 主题id
     */
    NSString * _themeId;
    
    /**
     * 主题名字
     */
    NSString * _themeName;
    
    /**
     * categoryId
     */
    NSString * _categoryId;
    
    NSString * _areaId;
    
    /**
     * 价格历史表
     */
    NSArray * _priceList;
    
    
    
}

@property(nonatomic, retain) NSString * sourceFromName;
@property(nonatomic, retain) NSString * themeId;
@property(nonatomic, retain) NSString * themeName;
@property(nonatomic, retain) NSString * categoryId;
@property(nonatomic, retain) NSString * areaId;
@property(nonatomic, retain) NSArray * priceList;

@end

@interface AMPriceListItem : NSObject <AMObjectMappingDelegate> {
    
    /**
     * 来源名字
     */
    NSString * _dateWithYear;
    
    /**
     * 主题id
     */
    NSString * _price;
    
    /**
     * 主题名字
     */
    NSString * _date;
    
}

@property(nonatomic, retain) NSString * dateWithYear;
@property(nonatomic, retain) NSString * price;
@property(nonatomic, retain) NSString * date;
@end

