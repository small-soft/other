//
//  NCheckListViewController.h
//  Nav
//
//  Created by 佳 刘 on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NSecondLevelViewController.h"

@interface NCheckListViewController : NSecondLevelViewController {
    NSArray *list;
    NSIndexPath *lastIndexPath;
}

@property (nonatomic,retain) NSArray *list;
@property (nonatomic,retain) NSIndexPath *lastIndexPath;

@end
