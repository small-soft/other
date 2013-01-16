//
//  AMGraphPickView.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-17.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol AMPickViewDataSource<NSObject>

@required
-(void)pickView:(UIView *)pickView mSelectType:(NSUInteger)selectIndex;
-(void)addSubview:(UIView *)subview;
-(void)insertSubview:(UIView *)subview aboveSubview:(UIView *)subviewAbove;
-(UIView *)superView;
@optional
-(void)tableDataSource:(UITableView *)tableview;
@end

@interface AMGraphPickView : UIView<UITableViewDelegate, UITableViewDataSource>
{
    id<AMPickViewDataSource> _dataSource;
    UITableView * _mGraphTimeTypeTableView;
    UILabel *_lableTimeType;
    UILabel *_lableTitle;
    UIButton * _mSelectTypeButtonUp;
    UIButton * _mSelectTypeButtonDown;
    UIControl * _mGraphTimeTypeSelectionView;
    NSUInteger _mGraphFilter;
    NSArray * _mGraphTimeDict;
    BOOL selectButtonType;
    
    NSInteger lastIndex;
}

@property (nonatomic, assign) id<AMPickViewDataSource> dataSource;
@property (nonatomic, retain) IBOutlet UITableView * mGraphTimeTypeTableView;
@property (nonatomic, retain) IBOutlet UILabel * lableTimeType;
@property (nonatomic, retain) IBOutlet UILabel * lableTitle;
@property (nonatomic, retain) IBOutlet UIButton * mSelectTypeButtonUp;
@property (nonatomic, retain) IBOutlet UIButton * mSelectTypeButtonDown;
@property (nonatomic, retain) IBOutlet UIControl * mGraphTimeTypeSelectionView;
@property (nonatomic, assign) NSUInteger mGraphFilter;
@property (nonatomic, retain) NSArray * mGraphTimeDict;

@property (nonatomic, assign) NSInteger lastIndex;

+(id)createView;
- (IBAction)onSelectMsgType: (id)sender;
- (void) viewWillAppear:(BOOL)animated;
- (IBAction)myActionMethod:(id)sender;
@end
