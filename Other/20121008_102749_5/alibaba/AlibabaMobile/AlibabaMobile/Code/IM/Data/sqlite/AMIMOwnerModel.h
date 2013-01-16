//
//  AMIMOwnerModel.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-21.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface AMIMOwnerModel : NSManagedObject

@property (nonatomic, retain) NSString * uid;
@property (nonatomic, retain) NSString * passwd;
@property (nonatomic, retain) NSNumber * status;
@property (nonatomic, retain) NSNumber * autoLogin;
@property (nonatomic, retain) NSNumber * soundNotice;
@property (nonatomic, retain) NSNumber * shakeNotice;

@end
