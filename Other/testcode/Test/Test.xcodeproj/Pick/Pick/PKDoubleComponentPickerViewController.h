//
//  PKDoubleComponentPickerViewController.h
//  Pick
//
//  Created by 佳 刘 on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#define kFillingComponent 0
#define kBreadComponent 1

@interface PKDoubleComponentPickerViewController : UIViewController <UIPickerViewDelegate,UIPickerViewDataSource> {
    UIPickerView *_doublePiker;
    NSArray *_fillingTypes;
    NSArray *_breadTypes;
}

@property(nonatomic, retain) IBOutlet UIPickerView *doublePicker;
@property(nonatomic, retain) NSArray *fillingTypes;
@property(nonatomic, retain) NSArray *breadTypes;

-(IBAction)buttonPressed;

@end
