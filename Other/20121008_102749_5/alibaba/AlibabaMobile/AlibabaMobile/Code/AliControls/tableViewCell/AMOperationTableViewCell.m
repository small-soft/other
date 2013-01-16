//
//  AMOperationTableViewCell.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-23.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMOperationTableViewCell.h"

@implementation AMOperationTableViewCell
@synthesize operationView=_operationView;

-(void)setupView
{
    
}
+(CGFloat)cellHeight
{
    return 54.0;
}
+(NSString*)cellIdentifer
{
    return @"homeOperationView";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMOperationTableViewCell" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMOperationTableViewCell class]])
        {
            AMOperationTableViewCell *obj = (AMOperationTableViewCell *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AMOperationTableViewCell cellHeight]);
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
    [_operationView release];
    [super dealloc];
}
@end
