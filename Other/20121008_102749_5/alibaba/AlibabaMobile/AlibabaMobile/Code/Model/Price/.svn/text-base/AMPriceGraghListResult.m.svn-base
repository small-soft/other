//
//  AMPriceGraghListResult.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-13.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMPriceGraghListResult.h"

@implementation AMPriceGraghListResult
@synthesize success = _success;
@synthesize historyPrice = _historyPrice;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPriceGraghListResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"success" toAttribute:@"success"];
            
			[sharedObjectMapping mapRelationship:@"historyPrice" withMapping:[AMPriceGraghHistotyItem sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMPriceGraghHistotyItem sharedObjectMapping] forKeyPath:@"historyPrice"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_historyPrice release];
    
    [super dealloc];
}

@end


@implementation AMPriceGraghHistotyItem
@synthesize sourceFromName = _sourceFromName;
@synthesize themeId = _themeId;
@synthesize themeName = _themeName;
@synthesize categoryId = _categoryId;
@synthesize priceList = _priceList;
@synthesize areaId = _areaId;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPriceGraghHistotyItem class]] retain];
			[sharedObjectMapping mapKeyPath:@"sourceFromName" toAttribute:@"sourceFromName"];
            [sharedObjectMapping mapKeyPath:@"themeId" toAttribute:@"themeId"];
            [sharedObjectMapping mapKeyPath:@"themeName" toAttribute:@"themeName"];
            [sharedObjectMapping mapKeyPath:@"categoryId" toAttribute:@"categoryId"];
            [sharedObjectMapping mapKeyPath:@"areaId" toAttribute:@"areaId"];
            
			[sharedObjectMapping mapRelationship:@"priceList" withMapping:[AMPriceListItem sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMPriceListItem sharedObjectMapping] forKeyPath:@"priceList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_sourceFromName release];
    [_themeId release];
    [_themeName release];
    [_categoryId release];
    [_priceList release];
    
    [super dealloc];
}

@end


@implementation AMPriceListItem
@synthesize dateWithYear = _dateWithYear;
@synthesize price = _price;
@synthesize date = _date;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPriceListItem class]] retain];
			[sharedObjectMapping mapKeyPath:@"dateWithYear" toAttribute:@"dateWithYear"];
            [sharedObjectMapping mapKeyPath:@"price" toAttribute:@"price"];
            [sharedObjectMapping mapKeyPath:@"date" toAttribute:@"date"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_dateWithYear release];
    [_price release];
    [_date release];
    
    [super dealloc];
}

@end
