//
//  CViewController.h
//  Cells
//
//  Created by 佳 刘 on 12-9-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#define kNameValueTag 1
#define kColorValueTag 2

@interface CViewController : UIViewController <UITableViewDelegate,UITableViewDataSource>

@property (nonatomic,retain) NSArray *computers;
@end
