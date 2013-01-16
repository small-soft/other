//
//  AMSubpageWithMenuViewController.h
//  AlibabaMobile
//
//  Created by  on 12-8-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMSubpageCommonViewController.h"
#import "AMMenuView.h"
@interface AMSubpageWithMenuViewController :AMSubpageCommonViewController <AMMenuViewDelegate>{
    IBOutlet UILabel * _recommendOrHistoryMenuViewTitle;
    IBOutlet AMMenuView * _recommendOrHistoryMenuView;

}
@property (nonatomic, retain) NSMutableArray * recommendOrHistoryData;
@end
