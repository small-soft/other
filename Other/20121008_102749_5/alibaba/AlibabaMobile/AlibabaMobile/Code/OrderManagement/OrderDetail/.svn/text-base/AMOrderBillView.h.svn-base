//
//  AMOrderBillView.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AMOrderInvoiceModel.h"
#import "AMOrderDetailResult.h"
#import "KeyValueObject.h"

@interface AMOrderBillView : UITableView <UITableViewDelegate, UITableViewDataSource>
{
    UINavigationController * _navigationController;
}

//@property (nonatomic,assign) NSObject <MemberContactDelegate> *memberContactDelegate;
//-(id) initWithData:(AMOrderDetailResult *)data withMemberId:(NSString*) memberId;

@property (nonatomic, retain) NSMutableArray * contactArray;

-(void) setNavigationController:(UINavigationController *)controller;
-(void) setData:(AMOrderDetailResult *)data withMemberId:(NSString*) memberId;

@end
