//
//  AMAddFavTableView.h
//  AlibabaMobile
//
//  Created by  on 12-7-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AMPriceResult.h"
#import "AMOffer.h"
#import "AMCompany.h"
#import "AMFavoriteRequest.h"

@class AMAddFavTableView;

@protocol AMAddFavTableViewDelegate

@optional

/*
 * 获取手势对应行的数据
 */
-(AMPriceItem *)AMAddFavTableView:(AMAddFavTableView *)table addPriceToFav:(NSIndexPath *)indexPath;
-(AMOffer *)AMAddFavTableView:(AMAddFavTableView *)table addOfferToFav:(NSIndexPath *)indexPath;
-(AMCompany *)AMAddFavTableView:(AMAddFavTableView *)table addCompanyToFav:(NSIndexPath *)indexPath;
/*
 * 获取数据后的请求 
 */
@required
-(void)addPriceToFav:(AMPriceItem *)data;

-(void)addOfferToFav:(AMOffer *)data;

-(void)addCompanyToFav:(AMCompany *)data;

@end

@interface AMAddFavTableView : UITableView{
    UISwipeGestureRecognizer *_swipeGesture;
    NSIndexPath *_swipedIndexPath;
    NSObject <AMAddFavTableViewDelegate> * _favDelegate;
    
}


@property (nonatomic,assign) NSObject <AMAddFavTableViewDelegate> *favDelegate;
@end
