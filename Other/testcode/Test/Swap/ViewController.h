//
//  ViewController.h
//  Swap
//
//  Created by 佳 刘 on 12-7-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#define degreesToRadians(x) (M_PI * (x) / 180.0)

@interface ViewController : UIViewController {
    UIView *landscape;
    UIView *portrait;
    
    UIButton *landscapeFooButton;
    UIButton *portraitFooButton;
    
    UIButton *landscapeBarButton;
    UIButton *portraitBarButton;
}
@property (nonatomic,retain) IBOutlet UIView *landscape;
@property (nonatomic,retain) IBOutlet UIView *portrait;
@property (nonatomic,retain) IBOutlet UIButton *landscapeFooButton;
@property (nonatomic,retain) IBOutlet UIButton *portraitFooButton;
@property (nonatomic,retain) IBOutlet UIButton *landscapeBarButton;
@property (nonatomic,retain) IBOutlet UIButton *portraitBarButton;

-(IBAction)swapButtonPressed:(id)sender;

@end
