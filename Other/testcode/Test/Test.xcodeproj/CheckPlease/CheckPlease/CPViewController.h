//
//  CPViewController.h
//  CheckPlease
//
//  Created by 佳 刘 on 12-10-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#define kMinCheckMarkAngle 50
#define kMaxCheckMarkAngle 135
#define kMinCheckMarkLength 10

@interface CPViewController : UIViewController {
    UILabel *label;
    CGPoint lastPrePoint;
    CGPoint lastCurrentPoint;
    CGFloat lineLengthSoFar;
}

@property (nonatomic,retain) IBOutlet UILabel *label;

- (void)eraseLabel;

@end
