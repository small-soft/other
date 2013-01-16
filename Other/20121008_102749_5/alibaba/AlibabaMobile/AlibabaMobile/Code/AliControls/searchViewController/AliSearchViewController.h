//
//  AliSearchViewController.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliSearchView.h"
#import "AliCommonTableView.h"

@interface AliSearchViewController : UIViewController <AliSearchViewDelegate>
@property (retain, nonatomic) IBOutlet AliSearchView *searchView;

@end
