//
//  GraphNodeList.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-10.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UIKit/UIcolor.h>
#import <RestKit/RestKit.h>
#import "S7GraphView.h"




@interface GraphNodeList : UIView
{
     id<S7GraphViewDataSource> dataSource;
    
    
    NSFormatter *_xValuesFormatter;
	NSFormatter *_yValuesFormatter;
	
	BOOL _drawAxisX;
	BOOL _drawAxisY;
	BOOL _drawGridX;
	BOOL _drawGridY;
	
	UIColor *_xValuesColor;
	UIColor *_yValuesColor;
	
	UIColor *_gridXColor;
	UIColor *_gridYColor;
	
	BOOL _drawInfo;
	NSString *_info;
	UIColor *_infoColor;
   
    
    UILabel *lableInfo;       //弹出窗口中显示的描述文字（某节点的时间、数据信息）
    UIView *popView;          //弹出窗口
    NSUInteger numberOfPlots; //画几条折线
    NSUInteger indexofButtons;//存储用户在节点列表中按下的节点位置
    UIImage *imageButton;     //存储按钮图片
    UIImage *imageButtonBackground;     //存储按钮图片
    NSUInteger imagePopViewOrigent;
    NSUInteger imagePopViewUpOrigent;
    UIImageView *imagePopView;    //存储弹出窗口图片
    UIImageView *imagePopViewUp;    //存储弹出窗口图片
    
    NSArray *lists;


}
+ (GraphNodeList *)loadGraphInfoList:(CGRect)frame;
+ (UIColor *)colorByIndex:(NSInteger)index;
- (void)btAction:(id)sender;
- (void)reloadData;
@property (nonatomic, assign) IBOutlet id<S7GraphViewDataSource> dataSource;
@property (nonatomic, retain) IBOutlet NSFormatter *xValuesFormatter;
@property (nonatomic, retain) IBOutlet NSFormatter *yValuesFormatter;

@property (nonatomic, retain) IBOutlet UILabel *lableInfo;
@property (nonatomic, assign) BOOL drawAxisX;
@property (nonatomic, assign) BOOL drawAxisY;
@property (nonatomic, assign) BOOL drawGridX;
@property (nonatomic, assign) BOOL drawGridY;

@property (nonatomic, retain) UIColor *xValuesColor;
@property (nonatomic, retain) UIColor *yValuesColor;

@property (nonatomic, retain) UIColor *gridXColor;
@property (nonatomic, retain) UIColor *gridYColor;

@property (nonatomic, assign) BOOL drawInfo;
@property (nonatomic, copy) NSString *info;
@property (nonatomic, retain) UIColor *infoColor;
@property (nonatomic, assign) NSUInteger numberOfPlots;
@property (nonatomic, assign) NSUInteger indexofButtons;
@property (nonatomic, retain) UIImage *imageButton;
@property (nonatomic, retain) UIImage *imageButtonBackground;

@property (nonatomic, retain) UIImageView *imagePopView;
@property (nonatomic, retain) UIImageView *imagePopViewUp;

@property (nonatomic, retain) NSArray *lists;



@end
