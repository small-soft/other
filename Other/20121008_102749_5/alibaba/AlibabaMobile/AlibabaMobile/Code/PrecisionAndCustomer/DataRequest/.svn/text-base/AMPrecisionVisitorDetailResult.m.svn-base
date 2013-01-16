//
//  AMPrecisionVisitorDetailResult.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionVisitorDetailResult.h"
#import "AMPrecisionVisitorAccessLog.h"

@implementation AMPrecisionVisitorDetailResult

@synthesize showName = _showName;
@synthesize position = _position; //职位
@synthesize mainBiz = _mainBiz;    //主营行业
@synthesize mainProduct = _mainProduct; //主营产品
@synthesize mobilephone = _mobilephone;   //手机
@synthesize corpName = _corpName; //公司信息
@synthesize fixedPhone = _fixedPhone; //电话
@synthesize handShake = _handShake;
@synthesize email = _email; // 邮箱
@synthesize area = _area; //所在地区

@synthesize accessLog = _accessLog;   //
@synthesize buyDemandAreaPreferences = _buyDemandAreaPreferences; //意向地区 stringList
@synthesize buyDemandCategoryPreferences = _buyDemandCategoryPreferences;   //关注类目 stringList
@synthesize buyDemandKeywordPreferences = _buyDemandKeywordPreferences; // 搜索信息 stringList

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPrecisionVisitorDetailResult class]] retain];
            
            [sharedObjectMapping mapKeyPath:@"showName" toAttribute:@"showName"];
            [sharedObjectMapping mapKeyPath:@"position" toAttribute:@"position"];
            [sharedObjectMapping mapKeyPath:@"mainBiz" toAttribute:@"mainBiz"];
            [sharedObjectMapping mapKeyPath:@"mainProduct" toAttribute:@"mainProduct"];
            [sharedObjectMapping mapKeyPath:@"mobilephone" toAttribute:@"mobilephone"];
            [sharedObjectMapping mapKeyPath:@"corpName" toAttribute:@"corpName"];
            [sharedObjectMapping mapKeyPath:@"fixedPhone" toAttribute:@"fixedPhone"];
            [sharedObjectMapping mapKeyPath:@"handShake" toAttribute:@"handShake"];
            [sharedObjectMapping mapKeyPath:@"email" toAttribute:@"email"];
            [sharedObjectMapping mapKeyPath:@"area" toAttribute:@"area"];
            [sharedObjectMapping mapKeyPath:@"buyDemandAreaPreferences" toAttribute:@"buyDemandAreaPreferences"];
            [sharedObjectMapping mapKeyPath:@"buyDemandCategoryPreferences" toAttribute:@"buyDemandCategoryPreferences"];
            [sharedObjectMapping mapKeyPath:@"buyDemandKeywordPreferences" toAttribute:@"buyDemandKeywordPreferences"];
            
            [sharedObjectMapping mapRelationship:@"accessLog" withMapping:[AMPrecisionVisitorAccessLog sharedObjectMapping]];
            
            // Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
   			[mappingProvider setMapping:[AMPrecisionVisitorAccessLog sharedObjectMapping] forKeyPath:@"accessLog"];
        }
    }
    
    return sharedObjectMapping;
}

- (NSString *) description {
    return [NSString stringWithFormat:@"Visitor Detail: showName = %@, position = %@, mainBiz = %@, mainProduct = %@, mobilephone = %@, corpName = %@, fixedPhone = %@, handShake = %d, email = %@", _showName, _position, _mainBiz, _mainProduct, _mobilephone, _corpName, _fixedPhone, [_handShake boolValue], _email];
}

- (void) dealloc {
    [_showName release];
    
    [_position release];
    [_mainBiz release];
    [_mainProduct release];
    [_buyDemandAreaPreferences release];
    [_buyDemandCategoryPreferences release];
    [_mobilephone release];
    [_accessLog release];
    [_corpName release];
    [_fixedPhone release];
    [_handShake release];
    [_buyDemandKeywordPreferences release];
    [_email release];
    [_area release];
    [super dealloc];
}

@end
