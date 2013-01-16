//
//  AMIndustrySubpageRequest.h
//  AlibabaMobile
//
//  Created by  on 12-8-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"
#define OCEAN_API_URL_INDUSTRY_SUBPAGE ([@"/industry.subpage/" stringByAppendingString:AMCONST_APP_KEY])

//@interface AMDataRequests : NSObject{
//    
//}
//@property (nonatomic,copy) NSString * configName;
//@property (nonatomic,copy) NSString * summary;
//@end

@interface AMSubpageRequest : NSObject<RKRequestSerializable,AMRequestDelegate>{
    NSString     *_industryId;
    NSString     *_categoryId;
    NSArray      *_dataRequests;
    NSDictionary *_request;
    NSString     *_loginId;
    NSString     *_terminalId;
    NSInteger    _transactionType;
}

@property (nonatomic, copy) NSString *industryId;
@property (nonatomic, copy) NSString *categoryId;
//dataRequest 是一个每个元素为dictionary的array 该dictionary只有两个key 一个是configName 一个是summary
@property (nonatomic, retain) NSArray *dataRequests;
@property (nonatomic, retain) NSDictionary * request;
@property (nonatomic) NSInteger transactionType; 
@property (nonatomic, copy) NSString *loginId;
@property (nonatomic, copy) NSString *terminalId;


@end
