//
//  AMHomepageDressEvent1Result.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-24.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"
#import "AMHomepageDressEvent1.h"

@interface AMHomepageDressEvent1Result : NSObject<AMObjectMappingDelegate> 
{
    
}

@property(nonatomic, retain) AMHomepageDressEvent1 *event1ios;
@property(nonatomic, retain) AMHomepageDressEvent1 *event2ios;
@property(nonatomic, retain) AMHomepageDressEvent1 *event3ios;
@property(nonatomic, retain) AMHomepageDressEvent1 *price;

@end

