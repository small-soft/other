//
//  PKDependentComponentPickerViewController.h
//  Pick
//
//  Created by 佳 刘 on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#define kStateComponent 0
#define kZipComponent 1

@interface PKDependentComponentPickerViewController : UIViewController <UIPickerViewDelegate,UIPickerViewDataSource> {
    
    UIPickerView *_picker;
    
    NSDictionary *_stateZips;
    NSArray *_states;
    NSArray *_zips;
}

@property (retain,nonatomic) IBOutlet UIPickerView *picker;
@property (retain,nonatomic) NSDictionary *stateZips;
@property (retain,nonatomic) NSArray *states;
@property (retain,nonatomic) NSArray *zips;

- (IBAction)buttonPressed;

@end
