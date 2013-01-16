//
//  AliAdvView.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "AliGallaryView.h"

@protocol AliAdvViewDelegate <NSObject>

-(UIViewController*)superController;
-(NSString*)superControllerName;
@optional
-(void) dataReload;
@end

@interface AliAdvView : UIView<RKObjectLoaderDelegate,AliGallaryViewDelegate>
@property (nonatomic,retain) NSMutableArray *bannerData;
@property (nonatomic,retain) NSObject <AliAdvViewDelegate> *delegate;
- (void)loadObjectsFromRemote;
@end
