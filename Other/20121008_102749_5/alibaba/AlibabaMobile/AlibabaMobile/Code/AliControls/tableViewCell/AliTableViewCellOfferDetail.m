//
//  AliTableViewCellOfferDetail.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewCellOfferDetail.h"
#import "NSAttributedString+HTML.h"
#define MARGIN (10.0)
@implementation AliTableViewCellOfferDetail
@synthesize nodataImage=_nodataImage;
@synthesize icon=_icon;
@synthesize title=_title;
@synthesize address=_address;
@synthesize price=_price;
@synthesize orderStart=_orderStart;
@synthesize preTrade=_preTrade;
@synthesize trade=_trade;
@synthesize sufTrade=_sufTrade;
@synthesize line = _line;

- (void)dealloc {
    [_nodataImage release];
    [_icon release];
    [_title release];
    [_address release];
    [_price release];
    [_orderStart release];
    [_preTrade release];
    [_trade release];
    [_sufTrade release];
    [_line release];
    [super dealloc];
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
-(void)setupNodataImage
{

    self.nodataImage.image = [UIImage imageNamed:@"nodata_pic"];
    self.nodataImage.frame = CGRectMake(MARGIN, (self.frame.size.height - 75.0)/2, 75.0, 75.0);

}
-(void)setupIcon
{
    self.icon.frame = self.nodataImage.frame;
}
-(void)setupTitle
{
    self.title.fontSize = 16.0;
    self.title.r = 0.0;
    self.title.g = 0.0;
    self.title.b = 0.0;
    self.title.numberOfLines = 2;
    
    CGFloat startX= MARGIN+self.nodataImage.frame.size.width+MARGIN;
    CGFloat endX=self.frame.size.width - MARGIN;
    self.title.frame=CGRectMake(startX, MARGIN, (endX - startX), (self.title.fontSize*2+5));
    
}
-(void)setupAddress
{
    self.address.fontSize = 12.0;
    self.address.r = 0x66;
    self.address.g = 0x66;
    self.address.b = 0x66;
    self.address.frame = CGRectMake(self.title.frame.origin.x, self.title.frame.origin.y+self.title.frame.size.height+5, self.title.frame.size.width, self.address.fontSize);

}
-(void)setupPrice
{
    self.price.fontSize = 14.0;
    self.price.r = 0xcc;
    self.price.g = 0x00;
    self.price.b = 0x00;
}
-(void)setupLine
{
    self.line.fontSize = 12.0;
    self.line.r = 0xe0;
    self.line.g = 0xe0;
    self.line.b = 0xe0;    
}

-(void)setupOrderStart
{
    self.orderStart.fontSize = 12.0;
    self.orderStart.r = 0x66;
    self.orderStart.g = 0x66;
    self.orderStart.b = 0x66;    
}
-(void)setupPreTrade
{
    self.preTrade.fontSize = 12.0;
    self.preTrade.r = 0x66;
    self.preTrade.g = 0x66;
    self.preTrade.b = 0x66;
}
-(void)setupTrade
{
    self.trade.fontSize = 12.0;
    self.trade.r = 0xff;
    self.trade.g = 0x73;
    self.trade.b = 0x00;
}
-(void)setupSufTrade
{
    self.sufTrade.fontSize = 12.0;
    self.sufTrade.r = 0x66;
    self.sufTrade.g = 0x66;
    self.sufTrade.b = 0x66;
}

-(void)setupView
{
    [self setupNodataImage];
    [self setupIcon];
    [self setupTitle];
    [self setupAddress];
    [self setupPrice];
    [self setupLine];
    [self setupOrderStart];
    [self setupPreTrade];
    [self setupTrade];
    [self setupSufTrade];

    
    [super setupView];
}

-(void)cellSetData:(AliTableViewCellOfferDetail*)cell favOffer:(AMFavoriteOffer *)data
{
    self.nodataImage.layer.masksToBounds = YES;
    self.nodataImage.layer.cornerRadius= 2.0;
    self.nodataImage.frame = CGRectMake(MARGIN, (self.frame.size.height - 75.0)/2, 75.0, 75.0);

    self.icon.image = nil;
    self.icon.url = [NSURL URLWithString:data.firstImage];
    self.icon.layer.masksToBounds = YES;
    self.icon.layer.cornerRadius= 10.0;
    self.icon.frame = self.nodataImage.frame;
    
    NSAttributedString *attributedText = [[NSAttributedString alloc] initWithHTML:[data.title dataUsingEncoding:NSUTF8StringEncoding]documentAttributes:NULL];
    self.title.text=attributedText.plainTextString;
    // [attributedText release];
    
    self.address.text = data.sendAddress;
    
    if (data.price.cent&&[data.price.cent doubleValue]>0) {
        
        self.price.text =  [NSString stringWithFormat:@"￥%.2f ",[data.price.cent doubleValue]/100]; 
    }
    else {
        self.price.text = nil;
    }
    if (self.price.text) {
        
        CGSize labelSize = [self.price.text sizeWithFont:self.price.font];
        self.price.frame = CGRectMake(self.title.frame.origin.x, self.address.frame.origin.y+self.address.frame.size.height+7, labelSize.width, self.price.fontSize);
    }
    else
    {
        self.price.frame = CGRectMake(self.title.frame.origin.x, self.address.frame.origin.y+self.address.frame.size.height+7, 0, 0);
    }
    if ([[data.quantityBegin stringValue] isEqualToString:@"0"]) {
        self.orderStart.text = nil;
        self.line.text=nil;
    }
    else {
        self.line.text=@"┃";
        self.orderStart.text = [NSString stringWithFormat:@"%@%@起",data.quantityBegin,data.unit];
    }
    if (self.orderStart.text) {
        CGSize labelSize = [self.line.text sizeWithFont:self.line.font];
        
        self.line.frame = CGRectMake(self.price.frame.origin.x+self.price.frame.size.width,self.price.frame.origin.y+(self.price.fontSize - self.orderStart.fontSize),labelSize.width,self.line.fontSize);
        
        CGFloat startX = self.line.frame.origin.x+self.line.frame.size.width;
        CGFloat endX = self.title.frame.origin.x+self.title.frame.size.width;
        
        self.orderStart.frame = CGRectMake(startX,self.price.frame.origin.y+(self.price.fontSize - self.orderStart.fontSize),(endX - startX),self.orderStart.fontSize);
        
    }

    /*
    {
        self.preTrade.text=@"成交";
        CGSize labelSize = [self.preTrade.text sizeWithFont:self.preTrade.font];
        self.preTrade.frame = CGRectMake(self.title.frame.origin.x, self.price.frame.origin.y + self.price.fontSize+7 , labelSize.width, self.preTrade.fontSize);
    }
    {
        self.trade.text= [data.bookedCount stringValue];
        CGSize labelSize = [self.trade.text sizeWithFont:self.trade.font];
        self.trade.frame = CGRectMake(self.preTrade.frame.origin.x+self.preTrade.frame.size.width, self.preTrade.frame.origin.y, labelSize.width, self.trade.fontSize);
    }
    
    {
        self.sufTrade.text= @"笔";
        CGSize labelSize = [self.sufTrade.text sizeWithFont:self.sufTrade.font];
        self.sufTrade.frame = CGRectMake(self.trade.frame.origin.x+self.trade.frame.size.width, self.preTrade.frame.origin.y, labelSize.width, self.sufTrade.fontSize);
        
    }*/
}

-(void)cellSetData:(AliTableViewCellOfferDetail*)cell amOffer:(AMOffer *)data
{
    self.nodataImage.layer.masksToBounds = YES;
    self.nodataImage.layer.cornerRadius= 2.0;
    self.icon.image = nil;
    [self.icon clear];
    self.icon.url = [NSURL URLWithString:data.listImgUrl];
    self.icon.layer.masksToBounds = YES;
    self.icon.layer.cornerRadius= 10.0;
  
    
    NSAttributedString *attributedText = [[NSAttributedString alloc] initWithHTML:[data.subject dataUsingEncoding:NSUTF8StringEncoding]documentAttributes:NULL];
    self.title.text=attributedText.plainTextString;
    // [attributedText release];
    
    if (data.province!=nil) {
        self.address.text = [NSString stringWithFormat:@"%@ %@",data.province,data.city];
    }
    else
    {
        
        self.address.text = data.city;       
    }
  if (data.rmbPrice.amount&&[data.rmbPrice.amount doubleValue]>0) {
      
        self.price.text =  [NSString stringWithFormat:@"￥%.2f",[data.rmbPrice.amount doubleValue]]; 
    }
    else {
        self.price.text = nil;
    }
    if (self.price.text) {
        
        CGSize labelSize = [self.price.text sizeWithFont:self.price.font];
        self.price.frame = CGRectMake(self.title.frame.origin.x, self.address.frame.origin.y+self.address.frame.size.height+7, labelSize.width, self.price.fontSize);
    }
    else
    {
        self.price.frame = CGRectMake(self.title.frame.origin.x, self.address.frame.origin.y+self.address.frame.size.height+7, 0, 0);
    }
    if ([data.quantityBegin isEqualToString:@"0"]) {
        self.orderStart.text = nil;
        self.line.text=nil;
    }
    else {
        self.line.text=@"┃";
        self.orderStart.text = [NSString stringWithFormat:@"%@%@起",data.quantityBegin,data.unit];
    }
    if (self.orderStart.text) {
        CGSize labelSize = [self.line.text sizeWithFont:self.line.font];
        
         self.line.frame = CGRectMake(self.price.frame.origin.x+self.price.frame.size.width+4,self.price.frame.origin.y+(self.price.fontSize - self.orderStart.fontSize),labelSize.width,self.line.fontSize);
        
        CGFloat startX = self.line.frame.origin.x+self.line.frame.size.width+4;
        CGFloat endX = self.title.frame.origin.x+self.title.frame.size.width;
       
        self.orderStart.frame = CGRectMake(startX,self.price.frame.origin.y+(self.price.fontSize - self.orderStart.fontSize),(endX - startX),self.orderStart.fontSize);

    }
    
    //为0则隐藏成交xx笔
    if([data.bookedCount intValue]==0){
        self.preTrade.hidden = YES;
        self.trade.hidden = YES;
        self.sufTrade.hidden = YES;
    }else{
        {
            self.preTrade.text=@"成交";
            CGSize labelSize = [self.preTrade.text sizeWithFont:self.preTrade.font];
            self.preTrade.frame = CGRectMake(self.title.frame.origin.x, self.price.frame.origin.y + self.price.fontSize+7 , labelSize.width, self.preTrade.fontSize);
        }
        {
            self.trade.text= [data.bookedCount stringValue];
            CGSize labelSize = [self.trade.text sizeWithFont:self.trade.font];
            self.trade.frame = CGRectMake(self.preTrade.frame.origin.x+self.preTrade.frame.size.width, self.preTrade.frame.origin.y, labelSize.width, self.trade.fontSize);
        }
        {
            self.sufTrade.text= @"笔";
            CGSize labelSize = [self.sufTrade.text sizeWithFont:self.sufTrade.font];
            self.sufTrade.frame = CGRectMake(self.trade.frame.origin.x+self.trade.frame.size.width, self.preTrade.frame.origin.y, labelSize.width, self.sufTrade.fontSize);
        }
    }
    
}
+(CGFloat)cellHeight
{
    return 114.0;
}
+(NSString*)cellIdentifer
{
    return @"cellOfferDetail";
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliTableViewCellOfferDetail" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliTableViewCellOfferDetail class]])
        {
            AliTableViewCellOfferDetail *obj = (AliTableViewCellOfferDetail *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AliTableViewCellOfferDetail cellHeight]);
            [obj setupView];
            return  obj;
        }
    }
    return nil;
}

@end
