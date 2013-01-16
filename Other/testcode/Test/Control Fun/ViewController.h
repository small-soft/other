//
//  ViewController.h
//  Control Fun
//
//  Created by 佳 刘 on 12-7-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#define kSwitchesSegmentIndex 0

@interface ViewController : UIViewController <UIActionSheetDelegate>{
    UITextField *nameField;
    UITextField *numberField;
    UILabel *sliderLabel;
    UISwitch *leftSwitch;
    UISwitch *rightSwitch;
    UIButton *doSomethingButton;
}

@property (nonatomic,retain) IBOutlet UITextField *nameField;
@property (nonatomic,retain) IBOutlet UITextField *numberField;
@property (nonatomic,retain) IBOutlet UILabel *sliderLabel;
@property (nonatomic,retain) IBOutlet UISwitch *leftSwitch;
@property (nonatomic,retain) IBOutlet UISwitch *rightSwitch;
@property (nonatomic,retain) IBOutlet UIButton *doSomethingButton;

// 输入框得done按钮
- (IBAction)textFieldDoneEditing:(id)sender;

// 背景关闭键盘
- (IBAction)backgroundTap:(id)sender;

-(IBAction)sliderChanged:(id)sender;

-(IBAction)toggleControls:(id)sender;
-(IBAction)switchChanged:(id)sender;
-(IBAction)buttonPressed;
@end
