//
//  PKSingleComponentPickerViewController.h
//  Pick
//
//  Created by 佳 刘 on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PKSingleComponentPickerViewController : UIViewController <UIPickerViewDataSource,UIPickerViewDelegate>
@property (nonatomic,retain) IBOutlet UIPickerView *singlePicker;
@property (nonatomic,retain) NSArray *pickerData;

- (IBAction)buttonPressed;
@end
