//
//  AliMemberContactView.h
//  AlibabaMobile
//
//  Created by xiejin on 12-2-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMMemberBrief.h"

@protocol MemberContactDelegate

@optional
-(void)wangWangDidSelected;
@end



@interface AliMemberContactView : UITableView <UITableViewDelegate, UITableViewDataSource>

@property (nonatomic,assign) NSObject <MemberContactDelegate> *memberContactDelegate;

-(void) setNavigationController:(UINavigationController *)controller;
-(void) setContactInfo:(AMMemberBrief *)brief memberId:(NSString *)memberId;
@end