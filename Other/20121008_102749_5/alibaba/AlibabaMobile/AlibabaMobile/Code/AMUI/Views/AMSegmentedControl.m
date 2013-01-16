
#import "AMSegmentedControl.h"



@interface AMSegmentedControl() {
    
}

-(IBAction)itemTouchDownAction:(id)sender;
- (void) customeLayoutItems;
- (UIImage *) getButtonImageWithIndex:(int)index state:(int) state;

@end

@implementation AMSegmentedControl

@synthesize mButtonArray = _mButtonArray;
@synthesize mBkImgMidNormal = _mBkImgMidNormal;
@synthesize mBkImgRightNormal = _mBkImgRightNormal;
@synthesize mBkImgLeftNormal = _mBkImgLeftNormal;
@synthesize mBkImgMidSelected = _mBkImgMidSelected;
@synthesize mBkImgRightSelected = _mBkImgRightSelected;
@synthesize mBkImgLeftSelected = _mBkImgLeftSelected;
@synthesize mImgExView = _mImgExView;
@synthesize delegate = _delegate;

- (id) initWithFrame:(CGRect)frame {
    [super initWithFrame:frame];
    if(self){
        self.mButtonArray = [[NSMutableArray alloc] init ];
        mCurrentIndex = 0;
        self.delegate = nil;
        
        self.mBkImgLeftNormal = [UIImage imageNamed:@"bg_tab"];
        self.mBkImgLeftNormal = [self.mBkImgLeftNormal stretchableImageWithLeftCapWidth:self.mBkImgLeftNormal.size.width/2 topCapHeight:self.mBkImgLeftNormal.size.height/2 ];
        
        self.mBkImgLeftSelected = [UIImage imageNamed:@"bg_tab_focus"];
        self.mBkImgLeftSelected = [self.mBkImgLeftSelected stretchableImageWithLeftCapWidth:self.mBkImgLeftSelected.size.width/2 topCapHeight:self.mBkImgLeftSelected.size.height/2 ]; 
        
        self.mBkImgMidNormal = [UIImage imageNamed:@"bg_tab"];
        self.mBkImgMidNormal = [self.mBkImgMidNormal stretchableImageWithLeftCapWidth:self.mBkImgMidNormal.size.width/2 topCapHeight:self.mBkImgMidNormal.size.height/2 ];
        
        self.mBkImgMidSelected = [UIImage imageNamed:@"bg_tab_focus"];
        self.mBkImgMidSelected = [self.mBkImgMidSelected stretchableImageWithLeftCapWidth:self.mBkImgMidSelected.size.width/2 topCapHeight:self.mBkImgMidSelected.size.height/2 ];
        
        self.mBkImgRightNormal = [UIImage imageNamed:@"bg_tab"];
        self.mBkImgRightNormal = [self.mBkImgRightNormal stretchableImageWithLeftCapWidth:self.mBkImgRightNormal.size.width/2 topCapHeight:self.mBkImgRightNormal.size.height/2 ];
        
        self.mBkImgRightSelected = [UIImage imageNamed:@"bg_tab_focus"];
        self.mBkImgRightSelected = [self.mBkImgRightSelected stretchableImageWithLeftCapWidth:self.mBkImgRightSelected.size.width/2 topCapHeight:self.mBkImgRightSelected.size.height/2 ];
    }
    return self;
}

- (void) setSelectedIndex:(int)index {
    if(index != mCurrentIndex){
        UIButton * btn = [self.mButtonArray objectAtIndex:index];
        [self itemTouchDownAction:btn];
    }
}

- (void) addItem:(NSString *)name {
    UIButton * btn = [[UIButton alloc] init];
    
    [btn setTitle:name forState:UIControlStateNormal];
    [btn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [btn.titleLabel setFont:[UIFont boldSystemFontOfSize:DEFAULT_FONT_SIZE]];
    
    [self.mButtonArray addObject:btn];
    [btn release];
    
    [self customeLayoutItems];
}

//为解决新品类目过长显示不全临时增加次方法，控制字体大小
- (void) addItemByFontSize:(NSString *)name
{
    UIButton * btn = [[UIButton alloc] init];
    
    [btn setTitle:name forState:UIControlStateNormal];
    [btn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    float FONT_SIZE = 14.0f;
    NSLog(@"name=%@ leng=%2g",name,name.length);
    if(name!=nil){
        if(name.length<=6&&name.length>5){
            FONT_SIZE = 12.0f;
        }else if(name.length<=7&&name.length>6){
            FONT_SIZE = 10.0f;
        }else if(name.length<=8&&name.length>7){
            FONT_SIZE = 8.0f;
        }
    }
    [btn.titleLabel setFont:[UIFont boldSystemFontOfSize:FONT_SIZE]];
    
    [self.mButtonArray addObject:btn];
    [btn release];
    
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
            UIButton * btn = [self.mButtonArray objectAtIndex:i];
            btn.frame = CGRectMake(tempX, tempY, itemWidth, itemHeight);
            if(mCurrentIndex != i){
                [btn setBackgroundImage:[self getButtonImageWithIndex:i state:BUTTON_STATE_NORMAL] forState:UIControlStateNormal];
                
            }else{
                [btn setBackgroundImage:[self getButtonImageWithIndex:i state:BUTTON_STATE_SELECTED] forState:UIControlStateNormal];
            }
            
            [btn setBackgroundImage:[self getButtonImageWithIndex:i state:BUTTON_STATE_SELECTED] forState:UIControlStateHighlighted];            
            [btn setTag:i];
            [btn addTarget:self action:@selector(itemTouchDownAction:) forControlEvents:UIControlEventTouchDown];
            [self addSubview:btn];
            tempX += itemWidth;
        }
        
        if (_mImgExView != nil) {
            _mImgExView.frame = CGRectMake(2, 0, 15, 36);
            [self addSubview:_mImgExView];
        }
        
        self.frame = CGRectMake(self.frame.origin.x + (self.frame.size.width-tempX)/2, self.frame.origin.y, tempX, self.frame.size.height);
    }
}

-(IBAction)itemTouchDownAction:(id)sender {
    int tag = ((UIControl *)sender).tag;
    if(tag != mCurrentIndex){
        UIButton * nowBtn = [self.mButtonArray objectAtIndex:mCurrentIndex];
        [nowBtn setBackgroundImage:[self getButtonImageWithIndex:mCurrentIndex state:BUTTON_STATE_NORMAL] forState:UIControlStateNormal];
        
        mCurrentIndex = tag;
        UIButton * nextBtn = [self.mButtonArray objectAtIndex:mCurrentIndex];
        [nextBtn setBackgroundImage:[self getButtonImageWithIndex:mCurrentIndex state:BUTTON_STATE_SELECTED] forState:UIControlStateNormal];
        
        if(self.delegate){
            [self.delegate segmentValueChanged:mCurrentIndex];
        }
    }
    
    if (mShowImgEx && _mImgExView != nil) {
        if (tag == 0) {
            [_mImgExView setHidden:NO];
        } else {
            [_mImgExView setHidden:YES];
        }
    }
}

- (UIImage *) getButtonImageWithIndex:(int)index state:(int) state {
    if(state == BUTTON_STATE_NORMAL){
        if(index == 0){
            return self.mBkImgLeftNormal;
        }else if(index == self.mButtonArray.count - 1){
            return self.mBkImgRightNormal;
        }else{
            return self.mBkImgMidNormal;
        }
        
    }else if(state == BUTTON_STATE_SELECTED){
        if(index == 0){
            return self.mBkImgLeftSelected;
        }else if(index == self.mButtonArray.count - 1){
            return self.mBkImgRightSelected;
        }else{
            return self.mBkImgMidSelected;
        }
    }
    return nil;
}

- (void) addExImg:(NSString *)srcName {
    _mImgExView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:srcName]];
    [_mImgExView sizeToFit];
    _mImgExView.frame = CGRectMake(10, (self.frame.size.height - _mImgExView.frame.size.height)/2, _mImgExView.frame.size.width, _mImgExView.frame.size.height);
    [self addSubview:_mImgExView];
    
    [self customeLayoutItems];
}

- (void) setExImgVisable:(BOOL)visable{
    mShowImgEx = visable;
    if (_mImgExView != nil) {
        [_mImgExView setHidden:!mShowImgEx];
    }
}

- (void) dealloc {
//    [_delegate release];
    [_mButtonArray release];
    [_mBkImgLeftNormal release];
    [_mBkImgLeftSelected release];
    [_mBkImgMidNormal release];
    [_mBkImgMidSelected release];
    [_mBkImgRightNormal release];
    [_mBkImgRightSelected release];
    [_mImgExView release];
    
    [super dealloc];
}

@end