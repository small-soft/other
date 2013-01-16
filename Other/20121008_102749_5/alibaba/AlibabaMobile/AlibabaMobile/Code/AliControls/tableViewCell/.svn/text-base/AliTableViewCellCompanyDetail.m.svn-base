//
//  AliTableViewCellCompany.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewCellCompanyDetail.h"
#import "NSAttributedString+HTML.h"
#define MARGIN (10.0)
@interface AliTableViewCellCompanyDetail()
@property (nonatomic,retain)NSArray*searchBizModel;

@end
@implementation AliTableViewCellCompanyDetail
@synthesize icon=_icon;
@synthesize title = _title;
@synthesize registerTitle = _registerTitle;
@synthesize registerSubTitle = _registerSubTitle;
@synthesize orderTitle = _orderTitle;
@synthesize orderSubTitle = _orderSubTitle;
@synthesize modelTitle = _modelTitle;
@synthesize modelSubTitle = _modelSubTitle;
@synthesize addressTitle = _addressTitle;
@synthesize addressSubTitle = _addressSubTitle;
@synthesize searchBizModel=_searchBizModel;
- (void)dealloc {
    [_icon release];
    [_title release];
    [_registerTitle release];
    [_registerSubTitle release];
    [_orderTitle release];
    [_orderSubTitle release];
    [_modelTitle release];
    [_modelSubTitle release];
    [_addressTitle release];
    [_addressSubTitle release];
    [_searchBizModel release];
    [super dealloc];
}
-(NSArray*)searchBizModel
{
    if (!_searchBizModel) {
        _searchBizModel = [[NSArray alloc] initWithObjects:@"生产加工", @"经销批发",
                           @"招商代理", @"商业服务", @"其他", nil];
    }
    return _searchBizModel;
}

-(void)setupIcon
{
    self.icon.frame = CGRectMake(MARGIN, MARGIN+(16.0-12.0)/2, 13.0, 12.0);
    self.icon.mode = UIViewContentModeScaleToFill;
}
-(void)setupTitle
{
    self.title.fontSize = 16.0;
    self.title.r = 0.0;
    self.title.g = 0.0;
    self.title.b = 0.0;
    CGFloat startX= self.icon.frame.origin.x + self.icon.frame.size.width +5;
    CGFloat endX=self.frame.size.width - MARGIN;
    self.title.frame=CGRectMake(startX, MARGIN, (endX - startX), self.title.fontSize);
}
-(void)setupRegisterTitle
{
    self.registerTitle.fontSize = 14.0;
    self.registerTitle.r = 0x66;
    self.registerTitle.g = 0x66;
    self.registerTitle.b = 0x66;    
    self.registerTitle.text=@"工商注册：";
    CGSize labelSize = [self.registerTitle.text sizeWithFont:self.registerTitle.font];
    self.registerTitle.frame = CGRectMake(MARGIN, self.title.frame.origin.y + self.title.frame.size.height+10 , labelSize.width, self.registerTitle.fontSize);
}
-(void)setupRegisterSubTitle
{
    self.registerSubTitle.fontSize = 14.0;
    self.registerSubTitle.r = 0x33;
    self.registerSubTitle.g = 0x33;
    self.registerSubTitle.b = 0x33;    
    CGFloat startX= self.registerTitle.frame.origin.x + self.registerTitle.frame.size.width;
    CGFloat endX=self.frame.size.width - MARGIN;
    self.registerSubTitle.frame = CGRectMake(startX, self.title.frame.origin.y + self.title.fontSize+10 , (endX - startX), self.registerSubTitle.fontSize);
}
-(void)setupOrderTitle
{
    self.orderTitle.fontSize = 14.0;
    self.orderTitle.r = 0x66;
    self.orderTitle.g = 0x66;
    self.orderTitle.b = 0x66;    
    self.orderTitle.text=@"主营产品：";
    self.orderTitle.frame = CGRectMake(self.registerTitle.frame.origin.x, self.registerTitle.frame.origin.y + self.registerTitle.frame.size.height+10 , self.registerTitle.frame.size.width, self.orderTitle.fontSize);
}
-(void)setupOrderSubTitle
{
    self.orderSubTitle.fontSize = 14.0;
    self.orderSubTitle.r = 0x33;
    self.orderSubTitle.g = 0x33;
    self.orderSubTitle.b = 0x33;    
    self.orderSubTitle.frame = CGRectMake(self.registerSubTitle.frame.origin.x, self.registerSubTitle.frame.origin.y + self.registerSubTitle.frame.size.height+10 , self.registerSubTitle.frame.size.width, self.orderSubTitle.fontSize);
}
-(void)setupModelTitle
{
    self.modelTitle.fontSize = 14.0;
    self.modelTitle.r = 0x66;
    self.modelTitle.g = 0x66;
    self.modelTitle.b = 0x66;    
    self.modelTitle.text=@"经营模式：";
    self.modelTitle.frame = CGRectMake(self.registerTitle.frame.origin.x, self.orderTitle.frame.origin.y + self.orderTitle.frame.size.height+10 , self.registerTitle.frame.size.width, self.modelTitle.fontSize);
}
-(void)setupModelSubTitle
{
    self.modelSubTitle.fontSize = 14.0;
    self.modelSubTitle.r = 0x33;
    self.modelSubTitle.g = 0x33;
    self.modelSubTitle.b = 0x33;    
    self.modelSubTitle.frame = CGRectMake(self.registerSubTitle.frame.origin.x, self.orderSubTitle.frame.origin.y + self.orderSubTitle.frame.size.height+10 , self.registerSubTitle.frame.size.width, self.modelSubTitle.fontSize);
}

-(void)setupAddressTitle
{
    self.addressTitle.fontSize = 14.0;
    self.addressTitle.r = 0x66;
    self.addressTitle.g = 0x66;
    self.addressTitle.b = 0x66;    
    self.addressTitle.text=@"公司地址：";
    self.addressTitle.frame = CGRectMake(self.registerTitle.frame.origin.x, self.modelTitle.frame.origin.y + self.modelTitle.frame.size.height+10 , self.registerTitle.frame.size.width, self.addressTitle.fontSize);
    NSLog(@"%f---%f",self.addressTitle.frame.origin.y,self.addressTitle.frame.size.height);
}
-(void)setupAddressSubTitle
{
    self.addressSubTitle.fontSize = 14.0;
    self.addressSubTitle.r = 0x33;
    self.addressSubTitle.g = 0x33;
    self.addressSubTitle.b = 0x33;    
    self.addressSubTitle.frame = CGRectMake(self.registerSubTitle.frame.origin.x, self.modelSubTitle.frame.origin.y + self.modelSubTitle.frame.size.height+10 , self.registerSubTitle.frame.size.width, self.addressSubTitle.fontSize);
}

-(void)setupView
{
    [self setupIcon];
    [self setupTitle];
    [self setupRegisterTitle];
    [self setupRegisterSubTitle];
    [self setupOrderTitle];
    [self setupOrderSubTitle];
    [self setupModelTitle];
    [self setupModelSubTitle];
    [self setupAddressTitle];
    [self setupAddressSubTitle];
    [super setupView];
}
-(void)cellSetData:(AliTableViewCellCompanyDetail*)cell amFavCompany:(AMFavoriteCompany *)data
{
    //trust
    self.icon.url = [NSURL URLWithString:data.tpLogo];
    NSAttributedString *attributedText =  [[NSAttributedString alloc] initWithHTML:[data.name dataUsingEncoding:NSUTF8StringEncoding] documentAttributes:NULL];
    cell.title.text=attributedText.plainTextString;
    //set bold font
    if ([data.establishedYear isEqualToString:@"0"]) {
        self.registerSubTitle.text = [NSString stringWithFormat:@"--年"];
        
    }
    else {
        self.registerSubTitle.text = [NSString stringWithFormat:@"%@年", data.establishedYear];
        
    }
    NSAttributedString* attributedText1 = [[NSAttributedString alloc] initWithHTML:[data.productionService dataUsingEncoding:NSUTF8StringEncoding] documentAttributes:NULL];
    cell.orderSubTitle.text=attributedText1.plainTextString;
    
    int index = [data.bizType intValue]-1;
    if (index>=[self.searchBizModel count]) {
        index = [self.searchBizModel count]-1;
    }
    self.modelSubTitle.text = [self.searchBizModel objectAtIndex:index ];
    
    self.addressSubTitle.text = data.address;

}
-(void)cellSetData:(AliTableViewCellCompanyDetail*)cell amCompany:(AMCompany *)data
{
    [self.icon clear];
    self.icon.url = [NSURL URLWithString:data.creditInfo.trustLogoSmall];

    NSAttributedString *attributedText = [[NSAttributedString alloc] initWithHTML:[data.name dataUsingEncoding:NSUTF8StringEncoding] documentAttributes:NULL];
    
    self.title.text=attributedText.plainTextString;
    
    //set bold font
    
    
    if([data.regCapital isEqualToString:@"0"]||!data.regCapital)
    {
        if ([data.establishedYear isEqualToString:@"0"]) {
            self.registerSubTitle.text = [NSString stringWithFormat:@"---年(无需验资)"];
        }
        else {
            self.registerSubTitle.text = [NSString stringWithFormat:@"%@年(无需验资)", data.establishedYear];
        }
        
    }
    else {
        if ([data.establishedYear isEqualToString:@"0"]) {
            self.registerSubTitle.text = [NSString stringWithFormat:@"--年(人民币%@万)",data.regCapital];
        }
        else {
            self.registerSubTitle.text = [NSString stringWithFormat:@"%@年(人民币%@万)", data.establishedYear,data.regCapital];
        }
        
    }
    NSAttributedString *attributedText1 = [[NSAttributedString alloc] initWithHTML:[data.productionService dataUsingEncoding:NSUTF8StringEncoding] documentAttributes:NULL];
    self.orderSubTitle.text = attributedText1.plainTextString;
    int index = [data.firstBizTypeName intValue]-1;
    if (index>=[self.searchBizModel count]) {
        index = [self.searchBizModel count]-1;
    }
    self.modelSubTitle.text = [self.searchBizModel objectAtIndex:index ];
    if (data.province!=nil) {
        self.addressSubTitle.text = [NSString stringWithFormat:@"%@ %@ %@",data.province,data.city,data.address];
    }
    else if (data.city!=nil)
    {
        self.addressSubTitle.text = [NSString stringWithFormat:@"%@ %@",data.city,data.address];
        
    }
    else {
        self.addressSubTitle.text = data.address;
    }

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
    return 132.0;
}
+(NSString*)cellIdentifer
{
    return @"cellCompanyDetail";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliTableViewCellCompanyDetail" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliTableViewCellCompanyDetail class]])
        {
            AliTableViewCellCompanyDetail *obj = (AliTableViewCellCompanyDetail *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AliTableViewCellCompanyDetail cellHeight]);
            [obj setupView];
            return  obj;
        }
    }
    return nil;
}

@end
