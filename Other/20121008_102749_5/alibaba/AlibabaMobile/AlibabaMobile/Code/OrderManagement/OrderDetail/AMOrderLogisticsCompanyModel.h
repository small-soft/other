//
//  AMOrderLogisticsCompanyModel.h
//  AlibabaMobile
//
//  Created by alimobile on 12-9-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"
#import "AMOrderLogisticsCompanyModel.h"

@interface AMOrderLogisticsCompanyModel : NSObject<AMObjectMappingDelegate>
{
    NSString * _companyName;
    NSString * _companyNo;
}


@property (nonatomic,retain) NSString * companyName;
@property (nonatomic,retain) NSString * companyNo;


@end
