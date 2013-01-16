//
//  NRowControllsController.h
//  Nav
//
//  Created by 佳 刘 on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NSecondLevelViewController.h"

@interface NRowControllsController : NSecondLevelViewController {
    NSArray *list;
}

@property (nonatomic,retain) NSArray *list;
-(IBAction)buttonTapped:(id)sender;

@end
