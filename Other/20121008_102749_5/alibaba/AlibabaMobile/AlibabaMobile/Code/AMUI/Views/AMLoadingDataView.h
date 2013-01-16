//
//  AMLoadingDataView.h
//  AlibabaMobile
//
//  Created by  on 12-7-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AMLoadingDataView : UIView
{
    IBOutlet UIView * _noDataView;
    IBOutlet UIView * _loadingView;
    IBOutlet UILabel * _noDataMessageLabel;
}

-(void)showLoadingView;

-(void)endLoadingView;

-(void)showNodataMessage;
@end
