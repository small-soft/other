//
//  AliTableViewCellSubTitle.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewCellSubTitle.h"
#define MARGIN (15.0)
@implementation AliTableViewCellSubTitle
@synthesize title=_title;
@synthesize subTitle=_subTitle;
@synthesize identifyImage=_identifyImage;
@synthesize hideIdentifyIMage=_hideIdentifyIMage;


-(void)setHideIdentifyIMage:(BOOL)hideIdentifyIMage
{
    _hideIdentifyIMage = hideIdentifyIMage;
    self.identifyImage.hidden = hideIdentifyIMage;
    if (hideIdentifyIMage) {
        
        self.title.frame = CGRectMake(MARGIN, 10.0, self.frame.size.width -MARGIN-MARGIN, self.title.fontSize);
        self.subTitle.frame = CGRectMake(MARGIN, self.frame.size.height - self.subTitle.fontSize - 10.0, self.frame.size.width -MARGIN-MARGIN, self.subTitle.fontSize);
           }
    else {
        self.title.frame = CGRectMake(MARGIN,10.0, self.identifyImage.frame.origin.x -MARGIN, self.title.fontSize);
        self.subTitle.frame = CGRectMake(MARGIN,(self.frame.size.height-self.subTitle.fontSize)-10.0, self.identifyImage.frame.origin.x -MARGIN-3.0, self.subTitle.fontSize);
    }
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
    self.title.r = 0x00;
    self.title.g = 0x00;
    self.title.b = 0x00;  
}
-(void)setupSubTitle
{
    self.subTitle.fontSize = 12.0;
    self.subTitle.r = 0x66;
    self.subTitle.g = 0x66;
    self.subTitle.b = 0x66;
}

-(void)setupView
{
    [self setupIdentifyImage];
    [self setupTitle];
    [self setupSubTitle];
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
    return 60.0;
}
+(NSString*)cellIdentifer
{
    return @"cellSubTitle";
}

+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliTableViewCellSubTitle" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliTableViewCellSubTitle class]])
        {
            AliTableViewCellSubTitle *obj = (AliTableViewCellSubTitle *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AliTableViewCellSubTitle cellHeight]);
            [obj setupView];
            obj.hideIdentifyIMage = NO;
            
            return  obj;
        }
    }
    return nil;
}

- (void)dealloc {
    [_title release];
    [_subTitle release];
    [_identifyImage release];
    [super dealloc];
}
@end
