//
//  NDisclosureButtonController.m
//  Nav
//
//  Created by 佳 刘 on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NDisclosureDetailController.h"

@implementation NDisclosureDetailController

@synthesize label;
@synthesize message;

#pragma - mark
#pragma mark vc lifecycle
- (void)viewWillAppear:(BOOL)animated {
    label.text = message;
    [super viewWillAppear:animated];
}

- (void)viewDidUnload {
    self.label = nil;
    self.message = nil;
    [super viewDidUnload];
}

- (void)dealloc {
    [label release];
    [message release];
    [super dealloc];
}

@end
