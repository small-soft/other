//
//  AliEnqueryCell.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliEnqueryCell.h"

@implementation AliEnqueryCell

@synthesize  label1;
@synthesize  label2;
@synthesize  label3;
@synthesize  label4;
@synthesize  label5;



-(void) dealloc{
    [label1 release];
    [label2 release];
    [label3 release];
    [label4 release];
    [label5 release];
    [super dealloc];
}
@end
