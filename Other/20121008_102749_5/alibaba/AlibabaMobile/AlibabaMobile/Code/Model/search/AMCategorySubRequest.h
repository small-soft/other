//
//  AMCategorySubRequest.h
//  AlibabaMobile
//
//  Created by zzh on 12-1-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_CATEGORIES_SUB ([@"/search.category.listSubCategory/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMCategorySubRequest : NSObject<RKRequestSerializable> {
    
    NSString * _categoryId;
    /**
     * 请求参数容器
     */
    
    NSInteger _transactionType;
}
@property(nonatomic, retain) NSString * categoryId;

@property (nonatomic) NSInteger transactionType;

@end
