//
//  AMFavSegmentedControl.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-18.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMFavSegmentedControl.h"

@implementation AMFavSegmentedControl

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

-(void) setBgImage:(NSString *)imageName WithIndex:(int) index WithState:(int) state
{
    if(state == BUTTON_STATE_NORMAL)
    {
        if(index == BUTTON_INDEX_LEFT){
            self.mBkImgLeftNormal = [UIImage imageNamed:imageName];
            self.mBkImgLeftNormal = [self.mBkImgLeftNormal stretchableImageWithLeftCapWidth:self.mBkImgLeftNormal.size.width/2 topCapHeight:self.mBkImgLeftNormal.size.height/2 ];
        }else if(index == BUTTON_INDEX_MIDDLE){
            self.mBkImgMidNormal = [UIImage imageNamed:imageName];
             self.mBkImgMidNormal = [ self.mBkImgMidNormal stretchableImageWithLeftCapWidth: self.mBkImgMidNormal.size.width/2 topCapHeight: self.mBkImgMidNormal.size.height/2 ];
        }else{
            self.mBkImgRightNormal = [UIImage imageNamed:imageName];
            self.mBkImgRightNormal = [self.mBkImgRightNormal stretchableImageWithLeftCapWidth:self.mBkImgRightNormal.size.width/2 topCapHeight:self.mBkImgRightNormal.size.height/2 ];
        }
        
    }
    else if(state == BUTTON_STATE_SELECTED)
    {
        if(index == BUTTON_INDEX_LEFT){
            self.mBkImgLeftSelected = [UIImage imageNamed:imageName];
            self.mBkImgLeftSelected = [self.mBkImgLeftSelected stretchableImageWithLeftCapWidth:self.mBkImgLeftSelected.size.width/2 topCapHeight:self.mBkImgLeftSelected.size.height/2 ]; 
        }else if(index == BUTTON_INDEX_MIDDLE){
            self.mBkImgMidSelected = [UIImage imageNamed:imageName];
            self.mBkImgMidSelected = [self.mBkImgMidSelected stretchableImageWithLeftCapWidth:self.mBkImgMidSelected.size.width/2 topCapHeight:self.mBkImgMidSelected.size.height/2 ];
        }else{
            self.mBkImgRightSelected = [UIImage imageNamed:imageName];
            self.mBkImgRightSelected = [ self.mBkImgRightSelected stretchableImageWithLeftCapWidth: self.mBkImgRightSelected.size.width/2 topCapHeight: self.mBkImgRightSelected.size.height/2 ];
        }
    }
}

- (void) addItem:(NSString *)name {
    AMButtonLableView * btnlab = [[AMButtonLableView alloc] init];
    
    [btnlab.button setTitle:name forState:UIControlStateNormal];
    btnlab.button.titleLabel.textAlignment = UITextAlignmentCenter;
    [self.mButtonArray addObject:btnlab];
    [btnlab release];
    
    [self customeLayoutItems];
}

- (void) customeLayoutItems {
    if(self.mButtonArray != nil
       && self.mButtonArray.count >0){
        int size = self.mButtonArray.count;
        
        int tempX = 0;
        int tempY = 0;
        int itemWidth = self.frame.size.width/size;
        int itemHeight = self.frame.size.height;
        
        for(int i=0; i<size;i++){
            AMButtonLableView * btn = [self.mButtonArray objectAtIndex:i];
            btn.frame = CGRectMake(tempX, tempY, itemWidth, itemHeight);
            if(mCurrentIndex != i){
                [btn.button setBackgroundImage:[self getButtonImageWithIndex:i state:BUTTON_STATE_NORMAL] forState:UIControlStateNormal];
                
            }else{
                [btn.button setBackgroundImage:[self getButtonImageWithIndex:i state:BUTTON_STATE_SELECTED] forState:UIControlStateNormal];
            }
            
            [btn.button setBackgroundImage:[self getButtonImageWithIndex:i state:BUTTON_STATE_SELECTED] forState:UIControlStateHighlighted];            
            [btn setTag:i];
            [btn addTarget:self action:@selector(itemTouchDownActionFav:) forControlEvents:UIControlEventTouchDown];
            [self addSubview:btn];
            tempX += itemWidth + 1;
        }
        
        if (nil != self.mImgExView) {
            self.mImgExView.frame = CGRectMake(2, 0, 15, 36);
            [self addSubview:self.mImgExView];
        }
        
        self.frame = CGRectMake(self.frame.origin.x + (self.frame.size.width-tempX)/2, self.frame.origin.y, tempX, self.frame.size.height);
    }
}

-(IBAction)itemTouchDownActionFav:(id)sender {
    int tag = ((UIControl *)sender).tag;
    if(tag != mCurrentIndex){
        AMButtonLableView * nowBtn = [self.mButtonArray objectAtIndex:mCurrentIndex];
        [nowBtn.button setBackgroundImage:[self getButtonImageWithIndex:mCurrentIndex state:BUTTON_STATE_NORMAL] forState:UIControlStateNormal];
        
        mCurrentIndex = tag;
        AMButtonLableView * nextBtn = [self.mButtonArray objectAtIndex:mCurrentIndex];
        [nextBtn.button setBackgroundImage:[self getButtonImageWithIndex:mCurrentIndex state:BUTTON_STATE_SELECTED] forState:UIControlStateNormal];
        
        if(self.delegate){
            [self.delegate segmentValueChanged:mCurrentIndex];
        }
    }
    
    if (mShowImgEx && nil != self.mImgExView ) {
        if (tag == 0) {
            [self.mImgExView setHidden:NO];
        } else {
            [self.mImgExView setHidden:YES];
        }
    }
}

- (void) setSelectedIndex:(int)index {
    if(index != mCurrentIndex){
        AMButtonLableView * btn = [self.mButtonArray objectAtIndex:index];
        [self itemTouchDownActionFav:btn];
    }
}

-(void) setLableTitle:(NSString *)imageName WithIndex:(int)index Visable:(BOOL)visable
{
    if(self.mButtonArray != nil
       && self.mButtonArray.count >= index) {
        AMButtonLableView * btnlab = [self.mButtonArray objectAtIndex:index];
        btnlab.lableTitle.text = imageName;
        btnlab.lableTitle.hidden = visable;
    }
    
}

- (void) dealloc {
    
    [super dealloc];
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
