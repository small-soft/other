//
//  NMoveMeController.h
//  Nav
//
//  Created by 佳 刘 on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NSecondLevelViewController.h"

@interface NMoveMeController : NSecondLevelViewController {
    NSMutableArray *list;
}

@property (nonatomic,retain) NSMutableArray *list;

-(IBAction)toggleMove;

@end
