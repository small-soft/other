//
//  AMLogEntry.h
//  AlibabaMobile
//
//  Created by qizhi.tangqz on 12-3-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface AMLogEntry : NSManagedObject

@property (nonatomic, retain) NSString * content;
@property (nonatomic, retain) NSDate * createAt;
@property (nonatomic, retain) NSNumber * identifier;
@property (nonatomic, retain) NSNumber * sent;

@end
