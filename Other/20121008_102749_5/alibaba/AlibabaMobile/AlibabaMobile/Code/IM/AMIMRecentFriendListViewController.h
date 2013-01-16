//
//  AMRecentFriendListViewController.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-12.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AMIMRecentFriendListViewController : UIViewController<UITableViewDelegate, UITableViewDataSource, NSFetchedResultsControllerDelegate>

- (id)initWithNavigation:(UINavigationController *)navigation;

@end
