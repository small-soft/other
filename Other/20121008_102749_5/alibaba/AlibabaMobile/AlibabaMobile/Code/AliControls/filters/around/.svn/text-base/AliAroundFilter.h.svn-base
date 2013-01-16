//
//  AliAroundFilter.h
//  AlibabaMobile
//
//  Created by alimobile on 12-5-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import "AliTableView.h"
#import "AliCommonTableView.h"
#import "AliCustomLabel.h"
@class AliAroundFilter;
@protocol AliAroundFilterDelegate
-(void)AliAroundFilter:(CLLocation*)location distance:(NSString*)distance selectedItem:(NSUInteger)selectedItem;
@end


@interface AliAroundFilter : AliCommonTableView<CLLocationManagerDelegate>
@property (retain, nonatomic) IBOutlet UIView *resultView;
@property (retain, nonatomic) IBOutlet AliCustomLabel *resultPreTitle;
@property (retain, nonatomic) IBOutlet AliCustomLabel *resultTitle;
@property (nonatomic)NSUInteger selectedItem;
@property (nonatomic,retain)NSObject<AliAroundFilterDelegate>*delegate;
@property (retain, nonatomic) IBOutlet AliTableView *contentTable;
@property (retain, nonatomic) NSString *parentTitle;
@end
