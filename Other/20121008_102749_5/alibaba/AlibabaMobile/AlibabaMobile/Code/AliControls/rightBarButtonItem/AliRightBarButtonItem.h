//
//  AliRightBarButtonItem.h
//  AlibabaMobile
//
//  Created by alimobile on 12-5-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
@class AliRightBarButtonItem;

@protocol AliRightBarButtonItemDelegate <NSObject>

@optional
-(void)AliRightBarButtonItem:(NSInteger)selectedButton;

@end
@interface AliRightBarButtonItem : UIBarButtonItem
+(AliRightBarButtonItem*)createView:(NSArray*)titles;
@property (nonatomic,retain)NSObject<AliRightBarButtonItemDelegate>*delegate;
@end
