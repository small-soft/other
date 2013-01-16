//
//  BrandCell.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-8-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBrandCell.h"

@implementation AMBrandCell

@synthesize box1=_box1;
@synthesize box2=_box2;
@synthesize box3=_box3;



@synthesize cellBoxViewArray=_cellBoxViewArray;
+(CGFloat)cellHeight
{
    return 90.0;
}
+(NSString*)cellIdentifer
{
    return @"brandBox";
}
+(NSUInteger)cellBoxViewArrayCount
{
    return 3;
}
-(NSMutableArray*)cellBoxViewArray
{
    if (!_cellBoxViewArray) {
        _cellBoxViewArray = [[NSMutableArray alloc]init];
    }
    [_cellBoxViewArray removeAllObjects];
    [_cellBoxViewArray addObject:self.box1];
    [_cellBoxViewArray addObject:self.box2];
    [_cellBoxViewArray addObject:self.box3];
     return _cellBoxViewArray;
}
- (void)dealloc {
    [_cellBoxViewArray release];
    [_box1 release];
    [_box2 release];
    [_box3 release];
    
    [super dealloc];
}


- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
