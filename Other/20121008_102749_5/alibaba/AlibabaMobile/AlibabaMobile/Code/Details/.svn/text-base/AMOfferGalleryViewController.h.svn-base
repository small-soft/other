//
//  OfferGalleryViewController.h
//  AlibabaMobile
//
//  Created by xiejin on 2/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HJManagedImageV.h"
#import "HJObjManager.h"
#import "AliPageControl.h"
#import "AliBackButton.h"

@class AMOfferDetail;

@interface AMOfferGalleryViewController : UIViewController<UIScrollViewDelegate>
{
    AMOfferDetail * mOfferDetail;
}

@property (nonatomic,retain) HJObjManager *objMan;

@property (nonatomic, retain) IBOutlet UIScrollView * mScrollView;
@property (nonatomic, retain) IBOutlet AliBackButton * mBackButton;
@property (nonatomic, retain) IBOutlet UILabel * mTitleLabel;
@property (nonatomic, retain) IBOutlet AliPageControl * mPageControl;



- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil offerDetail:(AMOfferDetail *)offerDetail;

- (IBAction) backButtonPressed;
- (void) initGallery;
- (void) changeIndatorState:(int)nowpage sum:(int)sum;
-(void)objManInit;


@end
