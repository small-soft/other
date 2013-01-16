//
//  AMHotRankOfferViewController.h
//  AlibabaMobile
//
//  Created by amon on 12-5-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliCommonDoubleSegmentTableView.h"
#import "AliTableView.h"

@interface AMHotRankOfferViewController : AliCommonDoubleSegmentTableView <AliTableViewDelegate>{
    
    BOOL upButtonState;
    BOOL hotButtonState;
    int mCurrentIndex;
    int _hotRankMode;
    int _hotOrUpMode;
}
@property (nonatomic,retain) IBOutlet UITableView *contentTable;
@property (retain,nonatomic) NSString *parentTitle;
@property (retain, nonatomic) NSString *cateTitle;
@property (nonatomic, retain) NSString *catIds;
@property (nonatomic,retain) NSString *cateId;
@property (nonatomic,retain) NSString *pageId;
@property (readwrite,nonatomic)int hotRankMode;//产品或公司
@property (readwrite,nonatomic)int hotOrUpMode;//上升榜或热销榜
@property (nonatomic, retain) UIView *headerView;
@property (nonatomic, retain) UIView *segmentLoadingView;
@property (nonatomic, retain) IBOutlet UIButton *upButton;
@property (nonatomic, retain) IBOutlet UIButton *hotButton;

@end
