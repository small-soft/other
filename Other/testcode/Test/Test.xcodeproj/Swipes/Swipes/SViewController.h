//
//  SViewController.h
//  Swipes
//
//  Created by 佳 刘 on 12-10-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#define kMinGestureLength 25
#define kMaxVariance 5

typedef enum {
    kNoSwipe = 0,
    kHorizontalSwipe,
    kVerticalSwipe
}SwipeType;

@interface SViewController : UIViewController {
    UILabel *label;
    CGPoint gestureStartPoint;
}

@property (nonatomic,retain) IBOutlet UILabel *label;
@property CGPoint gestureStartPoint;

- (void) eraseText;

@end
