//
//  AMIMMessageModel.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-22.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface AMIMMessageModel : NSManagedObject

@property (nonatomic, retain) NSString * ownerId;
@property (nonatomic, retain) NSString * msgFrom;
@property (nonatomic, retain) NSString * msgTo;
@property (nonatomic, retain) NSString * msgContent;
@property (nonatomic, retain) NSNumber * msgType;
@property (nonatomic, retain) NSNumber * msgTime;
@property (nonatomic, retain) NSNumber * hasRead;
@property (nonatomic, retain) NSNumber * msgSequence;

@end
