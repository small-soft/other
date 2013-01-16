//
//  AMHomeViewController.h
//  AlibabaMobile
//
//  Created by zzh on 11-12-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "AliPageControl.h"
#import "AliSearchView.h"
#import "AliTableView.h"
#import "AliAdvView.h"
#import "AliChannel.h"
@interface AMHomeViewController : UIViewController <UITableViewDataSource,UITableViewDelegate,UIScrollViewDelegate,AliSearchViewDelegate,AliChannelDelegate,AliAdvViewDelegate> {
    RKReachabilityObserver *_observer;
}


@property (nonatomic, retain) RKReachabilityObserver *observer;
@property (retain, nonatomic) IBOutlet AliSearchView *searchView;
@property (retain, nonatomic) IBOutlet AliTableView * funcListTable;
@end
