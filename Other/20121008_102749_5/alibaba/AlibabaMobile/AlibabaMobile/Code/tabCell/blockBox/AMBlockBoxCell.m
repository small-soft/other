//
//  AMBlockBoxCell.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBlockBoxCell.h"
@interface AMBlockBoxCell()
@property (retain, nonatomic) IBOutlet AMBoxView *blockBox1;
@property (retain, nonatomic) IBOutlet AMBoxView *blockBox2;
@property (retain, nonatomic) IBOutlet AMBoxView *blockBox3;
@property (retain, nonatomic) IBOutlet AMBoxView *blockBox4;

@end
@implementation AMBlockBoxCell
@synthesize blockBox1=_blockBox1;
@synthesize blockBox2=_blockBox2;
@synthesize blockBox3=_blockBox3;
@synthesize blockBox4=_blockBox4;
@synthesize cellBoxViewArray=_cellBoxViewArray;
+(CGFloat)cellHeight
{
    return 87.0;
}
+(NSString*)cellIdentifer
{
    return @"blockBox";
}
+(NSUInteger)cellBoxViewArrayCount
{
    return 4;
}
-(NSMutableArray*)cellBoxViewArray
{
       if (!_cellBoxViewArray) {
           _cellBoxViewArray = [[NSMutableArray alloc]init];
    }
    [_cellBoxViewArray removeAllObjects];
    [_cellBoxViewArray addObject:self.blockBox1];
    [_cellBoxViewArray addObject:self.blockBox2];
    [_cellBoxViewArray addObject:self.blockBox3];
    [_cellBoxViewArray addObject:self.blockBox4];
    return _cellBoxViewArray;
}
- (void)dealloc {
    [_cellBoxViewArray release];
    [_blockBox1 release];
    [_blockBox2 release];
    [_blockBox3 release];
    [_blockBox4 release];
    [super dealloc];
}

@end
