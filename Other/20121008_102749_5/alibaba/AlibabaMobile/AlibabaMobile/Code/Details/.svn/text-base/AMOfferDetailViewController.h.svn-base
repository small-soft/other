//
//  AMOfferDetailController.h
//  AlibabaMobile
//
//  Created by xiejin on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliSmallRemoteImageGallery.h"
#import "AliTabContentViewController.h"
#import "AMOfferTabViewController.h"
#import "AliMemberContactView.h"

@class AMOfferDetail;
@class AMAddress;

@interface AMOfferDetailViewController : AliTabContentViewController < MemberContactDelegate, AliGalleryDelegate>
{
    AMOfferDetail *mOfferDetail;
    BOOL isTalkAfterWwLogin;
}


@property (nonatomic, retain) IBOutlet UIScrollView * mContentScrollView;


- (IBAction) galleryClickAction;
- (void) setOfferDetail:(AMOfferDetail *)offerDetail;
-(void) setContentDataEx;
-(UILabel *) getSubjectLabel:(NSString *)subject;
- (void) setContentData;

@end
