//
//  AliTableViewCellType1.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewCellCategory.h"
#define MARGIN (15.0)
@implementation AliTableViewCellCategory
@synthesize title=_title;
@synthesize identifyImage = _identifyImage;
@synthesize hideIdentifyIMage=_hideIdentifyIMage;
-(void)setHideIdentifyIMage:(BOOL)hideIdentifyIMage
{
    _hideIdentifyIMage = hideIdentifyIMage;
 
    if (hideIdentifyIMage) {
        
        self.title.frame = CGRectMake(MARGIN,(self.frame.size.height-self.title.fontSize)/2, self.frame.size.width-MARGIN-MARGIN, self.title.fontSize);
        
    }
    else {
        self.title.frame = CGRectMake(MARGIN, (self.frame.size.height-self.title.fontSize)/2, self.identifyImage.frame.origin.x - MARGIN, self.title.fontSize);
    }
    self.identifyImage.hidden = hideIdentifyIMage;
}

-(void)setupIdentifyImage
{
    self.identifyImage.image = [UIImage imageNamed:@"icon_listarrow"];
    CGSize imageSize = [self.identifyImage.image size];
    self.identifyImage.frame = CGRectMake(self.frame.size.width - imageSize.width-MARGIN, (self.frame.size.height - imageSize.height)/2, imageSize.width, imageSize.height);

}
-(void)setupTitle
{
    self.title.fontSize = 16.0;
    self.title.r = 0x33;
    self.title.g = 0x33;
    self.title.b = 0x33;
}

-(void)setupView
{
    [self setupIdentifyImage];
    [self setupTitle];
    [super setupView];
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

+(CGFloat)cellHeight
{
    return 44.0;
}
+(NSString*)cellIdentifer
{
    return @"cellCategory";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliTableViewCellCategory" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliTableViewCellCategory class]])
        {
            AliTableViewCellCategory *obj = (AliTableViewCellCategory *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AliTableViewCellCategory cellHeight]);
            [obj setupView];
             obj.hideIdentifyIMage = NO;
            return  (AliTableViewCellCategory *)oneObject;
        }
    }
    return nil;
}
- (void)dealloc {
    [_title release];
    [_identifyImage release];
    [super dealloc];
}
@end
