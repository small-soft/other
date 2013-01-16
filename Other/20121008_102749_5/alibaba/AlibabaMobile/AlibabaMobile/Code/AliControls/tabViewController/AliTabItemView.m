//
//  AliTabItemView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTabItemView.h"
#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
@implementation AliTabItemView

@synthesize itemIcon=_itemIcon;
@synthesize itemTitle = _itemTitle;
@synthesize itemHighlighted=_itemHighlighted;
- (void)dealloc {
    [_itemIcon release];
    [_itemTitle release];
    [super dealloc];
}

-(void)setupView
{
    self.itemTitle.fontSize=11.0;
    self.itemTitle.r = 0xac;
    self.itemTitle.g=0xac;
    self.itemTitle.b=0xac;
    self.itemTitle.verticalAlignment  = VerticalAlignmentMiddle;
}
-(void)awakeFromNib
{
    [super awakeFromNib];
    [self setupView];
}
+(id)createView
{
    
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliTabItemView" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliTabItemView class]])
        {
            AliTabItemView*obj =  (AliTabItemView *)oneObject;
            [obj setupView];
            return  obj;
        }
    }
    return nil;
}

-(void)setItemHighlighted:(BOOL)itemHighlighted
{
    _itemHighlighted = itemHighlighted;
    if (itemHighlighted) {
        self.itemTitle.textColor =  RGB(0xff,0x73,0x00) ;
    }
    else {
         self.itemTitle.textColor =  RGB(0xac,0xac,0xac) ;
    }
}
@end
