//
//  AliOperationTableViewCell.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliOperationTableViewCell.h"

@implementation AliOperationTableViewCell
@synthesize operation1=_operation1;
@synthesize operation2=_operation2;

-(void)setupView
{
    
}
+(CGFloat)cellHeight
{
    return 90.0;
}
+(NSString*)cellIdentifer
{
    return @"homeOperation";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliOperationTableViewCell" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliOperationTableViewCell class]])
        {
            AliOperationTableViewCell *obj = (AliOperationTableViewCell *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AliOperationTableViewCell cellHeight]);
            [obj setupView];
            return  obj;
        }
    }
    return nil;
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

- (void)dealloc {
    [_operation1 release];
    [_operation2 release];
    [super dealloc];
}
@end
