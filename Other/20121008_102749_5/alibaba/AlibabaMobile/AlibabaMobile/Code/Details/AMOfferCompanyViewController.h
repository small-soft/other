//
//  AMOfferCompanyViewController.h
//  AlibabaMobile
//
//  Created by xiejin on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AMOfferTabViewController.h"
#import "AliTabContentViewController.h"

@class AMOfferDetail;

@interface AMOfferCompanyViewController : AliTabContentViewController{
    
    AMOfferDetail * mOfferDetail;
    
    int buttonX;
    int tempY;
    int buttonWidth;
    int buttonHeight;
    
    int nameLabelWidth;
    int nameLabelHeight;
    int valueLabelWidth;
    int valueLabelHeight;
    int imageLabelWidth;
    int imageLabelHeight;
    
    float fontSize;
    
    int nameLabelX;
    int valueLabelX;
    int rightImgX;
}

@property (nonatomic, retain) IBOutlet UIScrollView * mMainScrollView;

//- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil offerDetail:(AMOfferDetail *)offerDetail;
//-(void) initPositionValue;
//-(UIButton *) getItemButtonWithTitle:(NSString *)title value:(NSString *)value;
//
//- (IBAction) makeCallWithNumber:(id)sender;

@end
