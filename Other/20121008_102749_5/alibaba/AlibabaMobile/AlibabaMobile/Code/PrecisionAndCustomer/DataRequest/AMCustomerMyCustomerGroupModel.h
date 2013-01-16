//
//  AMCustomerMyCustomerGroupModel.h
//  AlibabaMobile
//
//  Created by xiaowen on 12-7-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#import "AMObjectMappingDelegate.h"

@interface AMCustomerMyCustomerGroupModel : NSObject <AMObjectMappingDelegate> {

    NSString* _identifier;
    NSNumber* _count;
    NSString* _value;
}

@property(nonatomic, retain) NSString* identifier;
@property(nonatomic, retain) NSNumber* count;
@property(nonatomic, retain) NSString* value;

@end
