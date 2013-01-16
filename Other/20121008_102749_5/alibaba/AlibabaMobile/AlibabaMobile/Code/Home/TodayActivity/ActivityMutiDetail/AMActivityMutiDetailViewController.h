//
//  AMActivityDetailViewController.h
//  AlibabaMobile
//
//  Created by alimobile on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "AMSpecialPriceOfferRequest.h"
#import "AMSpecialPriceOfferResult.h"
#import "ConstDef.h"
#import "UIHelp.h"
#import "AliCommonTableView.h"

@interface AMActivityMutiDetailViewController : AliCommonTableView<UITableViewDataSource,UITableViewDelegate>{
    BOOL isLoading;
    
    AMSpecialPriceOfferRequest * _specialPriceRequest;
}

@property (nonatomic, retain) IBOutlet UITableView * mTableView;

@end
