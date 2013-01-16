//
//  AMGroupCell.h
//  NAMenu
//
//  Created by  on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AMMenuView.h"
#import "HJManagedImageV.h"
typedef enum {
    AMGroupCellStyleLeftButton,
    AMGroupCellStyleRightArrowButton
}AMGroupCellStyle;

@class AMGroupTableViewController;

@interface AMGroupCell:UITableViewCell<AMMenuViewDelegate>{
    IBOutlet UIButton *_expandBtn;
    IBOutlet HJManagedImageV * _expandImage;
    IBOutlet AMMenuView * _menuView;
    int _subItemsCount;
    IBOutlet UILabel *_itemText;
    AMGroupTableViewController * _parentTableController;
    IBOutlet UILabel *_itemDescribeText;
    IBOutlet UIView *_bottomLine;
}

@property (nonatomic,retain)  AMMenuView *menuView;
@property (nonatomic,assign) int subItemsCount;
@property (nonatomic,retain) UILabel *itemText;
@property (nonatomic, assign) AMGroupTableViewController * parentTableController;
@property (nonatomic,retain) HJManagedImageV *expandImage;
@property (nonatomic,retain) UIButton * expandBtn;
@property (nonatomic,retain) UILabel * itemDescribeText;
@property (nonatomic,retain) UIView *bottomLine;
//@property (nonatomic,assign) BOOL isLoaded;
-(id)initWithStyle:(AMGroupCellStyle)style;
-(void) rotateExpandBtn:(BOOL)isExpand;
@end
