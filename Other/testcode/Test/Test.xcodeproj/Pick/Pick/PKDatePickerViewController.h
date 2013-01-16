//
//  PKDatePickerViewController.h
//  Pick
//
//  Created by 佳 刘 on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PKDatePickerViewController : UIViewController {
    UIDatePicker *_datePicker;
}

@property (nonatomic,retain) IBOutlet UIDatePicker *datePicker;

- (IBAction)buttonPressed;
@end
