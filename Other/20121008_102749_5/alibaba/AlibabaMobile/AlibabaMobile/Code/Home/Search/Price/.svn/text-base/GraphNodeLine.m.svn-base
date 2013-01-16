//
//  GraphNodeLine.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-10.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "GraphNodeLine.h"

@implementation GraphNodeLine
@synthesize yVlaues;
@synthesize xVlaues;
@synthesize xVlaues_;
@synthesize xValuesFormatter;
@synthesize yValuesFormatter;
@synthesize dateWithYear;
@synthesize price;
//@synthesize date;


- (id)initWithID:(NSInteger)newID
            name:(NSString *)newName
            rect:(CGRect)frame
{
    //self = [GraphNodeLine buttonWithType:UIButtonTypeCustom];
    if (self = [super initWithID:newID name:newName rect:frame]) {
        self.lableInfo = [NSString stringWithFormat:@"information"];
        self.mybuttonType = MyUIButtonTypeRoundedRect;
    }
    
    return self;
}

- (void)btAction:(id)sender{
}

-(void) dealloc {
    [xValuesFormatter release];
    [yValuesFormatter release];
    [xVlaues release];
    [dateWithYear release];
    [price release];
    [xVlaues_ release];
    [yVlaues release];
    //[date release];
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
