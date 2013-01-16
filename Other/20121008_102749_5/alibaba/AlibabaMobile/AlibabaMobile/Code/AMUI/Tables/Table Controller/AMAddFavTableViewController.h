//
//  AMAddFavTableViewController.h
//  AlibabaMobile
//
//  Created by  on 12-7-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AMAddFavTableView.h"
#import "AMFavoriteRequest.h"
#import "AMTableViewController.h"
#import "AMAddFavTableView.h"


@interface AMAddFavTableViewController : AMTableViewController<
    AMAddFavTableViewDelegate>
{        
    AMFavoriteRequest * _addFavoriteRequset;
}

@end
