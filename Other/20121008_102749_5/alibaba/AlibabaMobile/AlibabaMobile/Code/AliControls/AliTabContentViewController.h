//
//  AliTabContentViewController.h
//  AlibabaMobile
//
//  Created by xiejin on 12-2-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliTabViewController.h"

@interface AliTabContentViewController : UIViewController

@property (nonatomic, retain) NSMutableDictionary * dataDict;
@property (nonatomic, retain) UINavigationController * navigationController;

- (id)initWithData:(NSMutableDictionary *)data navigationController:(UINavigationController *) navigationController;

@end
