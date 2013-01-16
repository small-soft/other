//
//  ViewController.h
//  GHUnitProject
//
//  Created by mardin partytime on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController {
    
    IBOutlet UILabel *_number;
}

@property (nonatomic,retain) UILabel *number;
- (IBAction)addOne:(UIButton *)sender;

@end
