//
//  PKCustomPickerViewController.h
//  Pick
//
//  Created by 佳 刘 on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PKCustomPickerViewController : UIViewController <UIPickerViewDelegate,UIPickerViewDataSource>

@property (nonatomic,retain) IBOutlet UIPickerView *picker;
@property (nonatomic,retain) IBOutlet UILabel *winLabel;
@property (nonatomic,retain) NSArray *col1;
@property (nonatomic,retain) NSArray *col2;
@property (nonatomic,retain) NSArray *col3;
@property (nonatomic,retain) NSArray *col4;
@property (nonatomic,retain) NSArray *col5;
@property (nonatomic,retain) IBOutlet UIButton *button;

- (IBAction)spin;

@end
