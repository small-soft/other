//
//  AMBuyerSellerInfoView.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "AMCompanyTabViewController.h"
#import "AMOrderDetailViewController.h"

#import "AliMemberContactView.h"
#import "AMOrderDetailResult.h"
#import "KeyValueObject.h"





@interface AMBuyerSellerInfoView : UITableView <UITableViewDelegate, UITableViewDataSource>
{
    UINavigationController * _navigationController;
}

@property (nonatomic,assign) NSObject <MemberContactDelegate> *memberContactDelegate;
//-(id) initWithData:(AMOrderDetailResult *)data withMemberId:(NSString*) memberId;

@property (nonatomic, retain) NSMutableArray * contactArray;

-(void) setNavigationController:(UINavigationController *)controller;
-(void) setData:(AMOrderDetailResult *)data withMemberId:(NSString*) memberId;

@end
