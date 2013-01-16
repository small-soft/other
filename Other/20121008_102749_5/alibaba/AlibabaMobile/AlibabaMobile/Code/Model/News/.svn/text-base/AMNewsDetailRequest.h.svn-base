//
//  AMNewsDetailRequest.h
//  AlibabaMobile
//
//  Created by zzh on 12-1-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//



#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_NEWS_DETAIL ([@"/news.getNewsDetailV2/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMNewsDetailRequest : NSObject<RKRequestSerializable> {
    
       
    /**
     * 类目Id
     */
    NSNumber * _cateId;
    
  
}

@property(nonatomic, retain) NSNumber * cateId;
@property(nonatomic, retain) NSDictionary * request;

@end