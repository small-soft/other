//
//  AMIndustySelectHomeView.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-4.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
@protocol AMSelectPickViewDelegate<NSObject>
@required
-(void)showTableView;
@end

@interface AMIndustySelectHomeView : UIControl<UITableViewDelegate, UITableViewDataSource>
{
}
@property (nonatomic, assign) id <AMSelectPickViewDelegate> delegate;
@property (retain, nonatomic) IBOutlet UIView          *headerView;
@property (retain, nonatomic) IBOutlet UITableView     *tableView;

+(id)createView;

@end
