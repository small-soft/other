//
//  AMTodayActivityBlockBoxCell.m
//  AlibabaMobile
//
//  Created by amon on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMTodayActivityBlockBoxCell.h"
@interface AMTodayActivityBlockBoxCell()
@property (retain, nonatomic) IBOutlet AMTodayActivityBoxView *blockBox1;
@property (retain, nonatomic) IBOutlet AMTodayActivityBoxView *blockBox2;

@end
@implementation AMTodayActivityBlockBoxCell
@synthesize blockBox1=_blockBox1;
@synthesize blockBox2=_blockBox2;

@synthesize cellBoxViewArray=_cellBoxViewArray;
+(CGFloat)cellHeight
{
    return 190.0;
}
+(NSString*)cellIdentifer
{
    return @"blockBox";
}
+(NSUInteger)cellBoxViewArrayCount
{
    return 2;
}
-(NSMutableArray*)cellBoxViewArray
{
       if (!_cellBoxViewArray) {
           _cellBoxViewArray = [[NSMutableArray alloc]init];
    }
    [_cellBoxViewArray removeAllObjects];
    [_cellBoxViewArray addObject:self.blockBox1];
    [_cellBoxViewArray addObject:self.blockBox2];
    return _cellBoxViewArray;
}
- (void)dealloc {
    [_cellBoxViewArray release];
    [_blockBox1 release];
    [_blockBox2 release];
    [super dealloc];
}

@end
