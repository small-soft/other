//
//  AliSegmentedControl.h
//  AlibabaMobile
//
//  Created by xiejin on 12-2-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol AliSegmentedDelegate <NSObject>

- (void) segmentValueChanged:(int)nowIndex;

@end

@interface AliSegmentedControl : UIView
{
        NSMutableArray * _mButtonArray;
        UIImage * _mBkImgLeftNormal;
        UIImage * _mBkImgLeftSelected;
        UIImage * _mBkImgMidNormal;
        UIImage * _mBkImgMidSelected;
        UIImage * _mBkImgRightNormal;
        UIImage * _mBkImgRightSelected;
        UIImageView * _mImgExView;
        id<AliSegmentedDelegate> _delegate;
        
    int mCurrentIndex;
    BOOL mShowImgEx;
}

@property (nonatomic, retain) NSMutableArray * mButtonArray;
@property (nonatomic, retain) UIImage * mBkImgLeftNormal;
@property (nonatomic, retain) UIImage * mBkImgLeftSelected;
@property (nonatomic, retain) UIImage * mBkImgMidNormal;
@property (nonatomic, retain) UIImage * mBkImgMidSelected;
@property (nonatomic, retain) UIImage * mBkImgRightNormal;
@property (nonatomic, retain) UIImage * mBkImgRightSelected;
@property (nonatomic, retain) UIImageView * mImgExView;

@property (nonatomic, retain) id<AliSegmentedDelegate> delegate;

- (void) addItem:(NSString *)name;
- (void) setSelectedIndex:(int)index;
- (UIImage *) getButtonImageWithIndex:(int)index state:(int) state;

//为解决新品类目过长显示不全临时增加次方法，控制字体大小
- (void) addItemByFontSize:(NSString *)name;

- (void) addExImg:(NSString *)srcName;
- (void) setExImgVisable:(BOOL)visable;

@end
