//
//  searchBarCancelView.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliUIButton.h"
@interface searchBarCancelView : UIView

@property (retain, nonatomic) IBOutlet AliUIButton *cancelButton;
+(id)createView;
@end
