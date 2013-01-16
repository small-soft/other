//
//  AliTableViewCell.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewCell.h"
#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
@implementation AliTableViewCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
    }
    return self;
}

-(void)setupView
{
 /*   
    UIImageView * cellBackBtn = [[UIImageView alloc] initWithFrame:self.frame];
    UIImage * bkImage =  [UIImage imageNamed:@"bg_listclick"];
    bkImage = [bkImage stretchableImageWithLeftCapWidth:bkImage.size.width/2 topCapHeight:bkImage.size.height/2];
    cellBackBtn.image =bkImage;
    
    self.selectedBackgroundView = cellBackBtn;
   [cellBackBtn release]; 
*/
    UIView *bg = [[UIView alloc]init];
    bg.backgroundColor = self.backgroundColor = RGB(0xe1, 0xe1, 0xe1);
    self.selectedBackgroundView = bg;
    [bg release];
}
-(void)awakeFromNib
{
    [super awakeFromNib];
    [self setupView];
}
@end
