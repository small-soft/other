//
//  NDisclosureButtonControllerViewController.h
//  Nav
//
//  Created by 佳 刘 on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NSecondLevelViewController.h"
#import "NDisclosureDetailController.h"

@interface NDisclosureButtonController : NSecondLevelViewController {
    NDisclosureDetailController *childController;
}

@property (nonatomic,retain) NSArray *list;

@end
