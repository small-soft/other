//
//  AliTableView.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMPriceResult.h"
#import "AMOffer.h"
#import "AMCompany.h"
@class  AliTableView;
@protocol AliTableViewDelegate


@optional
-(AMPriceItem*)AliTableView:(AliTableView*)table addPriceToFav:(NSIndexPath*)indexPath;
-(AMOffer*)AliTableView:(AliTableView*)table addOfferToFav:(NSIndexPath*)indexPath;
-(AMCompany*)AliTableView:(AliTableView*)table addCompanyToFav:(NSIndexPath*)indexPath;

@end

@interface AliTableView : UITableView<RKObjectLoaderDelegate>


-(void)scrollViewDidScroll:(UIScrollView *)scrollView callback:(void(^)(void))loadNewObjects;
@property (nonatomic,assign) NSObject <AliTableViewDelegate> *favDelegate;
@end
