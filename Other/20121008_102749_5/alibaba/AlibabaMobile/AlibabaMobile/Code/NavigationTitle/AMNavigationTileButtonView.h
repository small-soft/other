//
//  AMNavigationTileButtonView.h
//  AlibabaMobile
//
//  Created by zzh on 12-1-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AMNavigationTileButtonView : UIView

@property (nonatomic,retain) IBOutlet UIButton *titleButton;
@property (retain, nonatomic) IBOutlet UIButton *arrowButton;

- (void) setTitle:(NSString *)title;

@end
