//
//  AMIndustrySelectPickView.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-29.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol AMIndustrySelectPickViewDelegate<NSObject>
@optional
-(void)industrySelectPickViewEvent;
@end

@interface AMIndustrySelectPickView : UIControl
@property (nonatomic, assign) id <AMIndustrySelectPickViewDelegate> delegate;
@property (nonatomic, retain) IBOutlet UILabel * lableTitle;
@property (nonatomic, retain) IBOutlet UIButton * mSelectTypeButtonUp;
@property (nonatomic, retain) IBOutlet UIButton * mSelectTypeButtonDown;
@property (nonatomic, assign) BOOL isButtonUp;

-(IBAction)selectTypeButtonUp:(UIButton *)sender;
-(IBAction)selectTypeButtonDown:(UIButton *)sender;
-(IBAction)selectTypeButtonUpOutside:(UIButton *)sender;
+(id)createView;
@end
