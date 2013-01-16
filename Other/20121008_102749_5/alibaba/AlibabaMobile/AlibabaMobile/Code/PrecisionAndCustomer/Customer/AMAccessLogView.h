//
//  AMAccessLogView.h
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>



@interface AMAccessLogView : UITableView <UITableViewDelegate, UITableViewDataSource>
{
    NSMutableArray * _accessArray;
    NSNumber *  _accessCount;
    UINavigationController * _navigationController;
    
}

@property (nonatomic, retain) NSMutableArray * accessArray;
@property (nonatomic, retain) NSNumber * accessCount;


-(void) setNavigationController:(UINavigationController *)controller;
//-(void) setEnqueryInfo:(NSArray *)logs ;
-(void) calculateHeight;

@end
