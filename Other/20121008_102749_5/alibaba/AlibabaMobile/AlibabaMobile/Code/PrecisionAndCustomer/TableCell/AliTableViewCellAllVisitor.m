//
//  AliTableViewCellType1.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewCellAllVisitor.h"
#define MARGIN (10.0)
@implementation AliTableViewCellAllVisitor
@synthesize title=_title;
@synthesize identifyImage = _identifyImage;
@synthesize hideIdentifyIMage=_hideIdentifyIMage;
@synthesize talkBtn = _talkBtn;
//-(void)setupTalkBtnBackground
//{
//    UIImage * normalBackgroundImage = [UIImage imageNamed:@"btn_ct_nor.png"] ;
////    [normalBackgroundImage stretchableImageWithLeftCapWidth:self.talkBtn.frame.size.width/6 topCapHeight:self.talkBtn.frame.size.height/6];
//    [normalBackgroundImage stretchableImageWithLeftCapWidth:10 topCapHeight:10];
//    [self.talkBtn setBackgroundImage:normalBackgroundImage forState:UIControlStateNormal];
//    UIImage * selectBackgroundImage = [UIImage imageNamed:@"btn_ct_p.png"] ;
//    [selectBackgroundImage stretchableImageWithLeftCapWidth:10 topCapHeight:10];
//    [self.talkBtn setBackgroundImage:selectBackgroundImage forState:UIControlStateSelected];
//}


-(void)setHideIdentifyIMage:(BOOL)hideIdentifyIMage
{
    _hideIdentifyIMage = hideIdentifyIMage;
//    self.title.frame = CGRectMake(MARGIN,(self.frame.size.height-self.title.fontSize)/2, self.frame.size.width/3, self.title.fontSize);
    self.title.frame = CGRectMake(MARGIN,(self.frame.size.height-self.title.fontSize)/2, 118.0, self.title.fontSize);
//    if (hideIdentifyIMage) {
//        
//        self.title.frame = CGRectMake(MARGIN,(self.frame.size.height-self.title.fontSize)/2, self.frame.size.width-MARGIN-MARGIN, self.title.fontSize);
//        
//    }
//    else {
//        self.title.frame = CGRectMake(MARGIN, (self.frame.size.height-self.title.fontSize)/2, self.identifyImage.frame.origin.x - MARGIN, self.title.fontSize);
//    }
    self.identifyImage.hidden = hideIdentifyIMage;
    NSLog(NSStringFromCGRect(self.title.frame),nil);
}

-(void)setupIdentifyImage
{
    self.identifyImage.image = [UIImage imageNamed:@"icon_listarrow"];
    CGSize imageSize = [self.identifyImage.image size];
    //    self.identifyImage.frame = CGRectMake(self.frame.size.width - imageSize.width-MARGIN, (self.frame.size.height - imageSize.height)/2, imageSize.width, imageSize.height);
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
//    [self setupTalkBtnImage];
//    [self setupTalkBtnBackground];
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
    return 66.0;
}
+(NSString*)cellIdentifer
{
    return @"cellAllVisitors";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliTableViewCellAllVisitor" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliTableViewCellAllVisitor class]])
        {
            AliTableViewCellAllVisitor *obj = (AliTableViewCellAllVisitor *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AliTableViewCellAllVisitor cellHeight]);
            [obj setupView];
            obj.hideIdentifyIMage = NO;
            return  (AliTableViewCellAllVisitor *)oneObject;
        }
    }
    return nil;
}
- (void)dealloc {
    [_title release];
    [_identifyImage release];
    [_talkBtn release];
    [super dealloc];
}
@end
