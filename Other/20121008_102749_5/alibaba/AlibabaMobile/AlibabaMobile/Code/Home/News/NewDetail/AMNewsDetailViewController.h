//
//  AMNewsDetailViewController.h
//  AlibabaMobile
//
//  Created by zzh on 12-1-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliCommonTableView.h"


@interface AMNewsDetailViewController : AliCommonTableView
@property (retain, nonatomic) IBOutlet UILabel *mainTitle;
@property (retain, nonatomic) IBOutlet UILabel *subTitle;
@property (retain, nonatomic) IBOutlet UIWebView *contentView;
@property (retain, nonatomic) NSNumber*categoryId;
@property (retain, nonatomic) NSString*navigationTitle;
@property (retain, nonatomic) NSString*parentTitle;
@property (nonatomic, retain) NSMutableArray* hotNewsData;
@property (readwrite) NSUInteger hotNewsIndex;
@property (nonatomic, retain) NSMutableArray* commonNewsData;
@property (readwrite) NSUInteger commonNewsIndex;
@property (retain, nonatomic) IBOutlet UIButton *line;
@end
