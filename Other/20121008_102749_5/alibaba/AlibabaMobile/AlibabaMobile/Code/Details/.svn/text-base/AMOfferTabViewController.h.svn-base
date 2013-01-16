//
//  AMOfferTabViewController.h
//  AlibabaMobile
//
//  Created by xiejin on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "AMOfferDetailRequest.h"
#import "HJManagedImageV.h"
#import "HJObjManager.h"
#import "AliTabViewController.h"
#import "AliTabContentViewController.h"
#import "AMFavoriteRequest.h"


@class AMOfferDetail;

extern NSString * TAB_VIEW_DATA_OFFER_DETAIL;

@interface AMOfferTabViewController : AliTabViewController <RKObjectLoaderDelegate, UIAlertViewDelegate>
{
    //数据下载相关
    AMOfferDetail *mOfferDetail;
    AMOfferDetailRequest * _request;
    NSMutableArray    * _objects;
    NSString *_offerId;
    NSNumber * _imageSizeType; 
    NSNumber * _disableLink;
    
    UIImage * btnBackImg;
    UIImage * btnBackImgPressed;
}

//other properties
@property (nonatomic, retain) NSString * mOfferId;
@property (nonatomic, retain) NSString * mOfferName;
@property (nonatomic, retain) AMFavoriteRequest *addFavoriteRequset;
@property (nonatomic, retain) AMFavoriteRequest *delFavoriteRequset;

- (id)initWithOfferId:(NSString *)offerId offerName:(NSString *)offerName preViewName:(NSString *)preViewName;
- (void) initContentViews;

@end
