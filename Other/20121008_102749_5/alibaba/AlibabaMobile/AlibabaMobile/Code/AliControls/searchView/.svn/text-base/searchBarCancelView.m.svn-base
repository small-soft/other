//
//  searchBarCancelView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "searchBarCancelView.h"
#import "UIHelp.h"

@implementation searchBarCancelView
@synthesize cancelButton;

+(id)createView
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"searchBarCancelView" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[searchBarCancelView class]])
        {
            searchBarCancelView *obj = (searchBarCancelView *)oneObject;
            [obj setupView];
            return  obj;
            
        }
    }
    return nil;
}

-(void)setupView
{
//    self.cancelButton.backgroundColor = [UIColor colorWithRed:255/255.0f green:115/255.0f blue:0/255.0f alpha:1.0f];
//    [self.cancelButton setBackgroundColor:[UIColor colorWithRed:255/255.0f green:115/255.0f blue:0/255.0f alpha:1.0f]];
//    [self.cancelButton.layer setCornerRadius:3.0];
    UIImage *buttonImage = [UIImage imageNamed:@"btn_tb_normal"];
    UIImage *btnBackImgPressed = [UIImage imageNamed:@"btn_tb_normal_tap"];
    
    
    self.cancelButton.titleLabel.textAlignment = UITextAlignmentCenter;
    self.cancelButton.titleLabel.shadowColor = [UIColor colorWithRed:100/255.0 green:26/255.0 blue:4/255.0 alpha:0.52];
    self.cancelButton.titleLabel.shadowOffset = CGSizeMake(-0.5, -0.5);
    [self.cancelButton setBackgroundImage:buttonImage forState:UIControlStateNormal];
    [self.cancelButton setBackgroundImage:btnBackImgPressed forState:UIControlStateHighlighted];
    [self.cancelButton setBackgroundImage:btnBackImgPressed forState:UIControlStateSelected];
    
    self.cancelButton.titleLabel.frame = CGRectMake(self.cancelButton.titleLabel.frame.origin.x + 1, self.cancelButton.titleLabel.frame.origin.y, self.cancelButton.titleLabel.frame.size.width, self.cancelButton.titleLabel.frame.size.height);
}


- (void)dealloc {
    [cancelButton release];
    [super dealloc];
}
@end
