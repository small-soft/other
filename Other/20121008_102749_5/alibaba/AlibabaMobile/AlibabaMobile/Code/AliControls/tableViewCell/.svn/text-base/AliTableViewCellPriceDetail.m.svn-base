//
//  AliTableViewCellPriceDetail.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewCellPriceDetail.h"

#define MARGIN (10.0)
#define SPACE (10.0)
#define PRICE_WIDTH (200.0)

@implementation AliTableViewCellPriceDetail
@synthesize title=_title;
@synthesize price = _price;
@synthesize params = _params;
@synthesize upDown = _upDown;
@synthesize date = _date;



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
    return 96.0;
}
+(NSString*)cellIdentifer
{
    return @"cellPriceDetail";
}

-(void)setupTitleView
{
    self.title.fontSize = 16.0;
    self.title.r = 0.0;
    self.title.g = 0.0;
    self.title.b = 0.0;
    self.title.frame = CGRectMake(MARGIN, MARGIN, self.frame.size.width-MARGIN-MARGIN, self.title.fontSize);
    
    
}
-(void)setupPriceView
{
    self.price.fontSize = 14.0;
    self.price.r = 0xe1;
    self.price.g = 0.0;
    self.price.b = 0.0;
    self.price.frame = CGRectMake(MARGIN, self.title.frame.origin.y+self.title.frame.size.height+8, PRICE_WIDTH, self.price.fontSize);
}
-(void)setupParamsView
{
    self.params.fontSize = 12.0;
    self.params.r = 0x66;
    self.params.g = 0x66;
    self.params.b = 0x66;
    CGFloat startY=self.price.frame.origin.y+self.price.frame.size.height+8;
    CGFloat endY=self.frame.size.height - MARGIN;
    self.params.frame = CGRectMake(MARGIN, startY, PRICE_WIDTH, endY-startY);
    self.params.numberOfLines = 2;
    
}
-(void)setupUpDownView
{
    self.upDown.fontSize = 14.0;
    self.upDown.r = 0xe1;
    self.upDown.g = 0.0;
    self.upDown.b = 0.0;
    self.upDown.frame = CGRectMake(MARGIN+PRICE_WIDTH, MARGIN+self.title.fontSize+SPACE, self.frame.size.width - MARGIN-PRICE_WIDTH-MARGIN, self.upDown.fontSize);
    self.upDown.textAlignment= UITextAlignmentRight;
}
-(void)setupDateView
{
    self.date.fontSize = 12.0;
    self.date.r = 0x66;
    self.date.g = 0x66;
    self.date.b = 0x66;
    self.date.frame = CGRectMake(MARGIN+PRICE_WIDTH, self.frame.size.height - MARGIN-self.date.fontSize, self.frame.size.width - MARGIN-PRICE_WIDTH-MARGIN, self.date.fontSize);
    self.date.textAlignment= UITextAlignmentRight;

}
-(void)setupView
{
    [self setupTitleView];
    [self setupPriceView];
    [self setupUpDownView];
    [self setupParamsView];
    [self setupDateView];
    [super setupView];
}

-(void)cellSetData:(AMPriceItem *)data
{
    self.title.text = [NSString stringWithFormat:@"%@【%@】",data.themeName,data.areaName];
    self.price.text = data.price;
    float num = [data.updown floatValue];
   
    if (num>0) {
       
        self.upDown.text=[@"↑" stringByAppendingString:data.updown];
        self.upDown.textColor = RGB(0xe1,0x00,0x00);
        self.upDown.highlightedTextColor = RGB(0xe1,0x00,0x00);
             
    }
    else if (num<0)
    {

        self.upDown.text = [@"↓" stringByAppendingString: [data.updown stringByReplacingOccurrencesOfString:@"-" withString:@""]]; 
        self.upDown.textColor = RGB(0x00,0xe1,0x00);
        self.upDown.highlightedTextColor = RGB(0x00,0xe1,0x00);
       
    }
    else
    {
        self.upDown.text=self.upDown.text=[@"→" stringByAppendingString: data.updown];
        self.upDown.textColor = RGB(0xe1,0xe1,0x00);
        self.upDown.highlightedTextColor = RGB(0xe1,0xe1,0x00);
    }
  
    //detail 
    {
        NSArray *keys=[data.attributes allKeys];
        
        int i, count;
        
        id key, value;
        
        count = [keys count];
        
        
        
        NSMutableString *text = [[NSMutableString alloc]initWithString:@""];
        
        if (count>=1) 
        {
            for (i = 0; i < count-1; i++)
            {
                key = [keys objectAtIndex: i];
                
                value = [data.attributes objectForKey: key];
                [text appendString:key];
                [text appendString:@": "];
                [text appendString:value];
                [text appendString:@" "];
                
            }
            
            key = [keys objectAtIndex: i];
            value = [data.attributes objectForKey: key];
        }
            
        CGSize labelSize = [text sizeWithFont:self.params.font];
        if (labelSize.width>self.params.frame.size.width) {
            [text appendString:key];
            [text appendString:@": "];
            [text appendString:value]; 
        }
        else {
            if (count>1) {
                [text appendString:@"\n"];
                [text appendString:key];
                [text appendString:@": "];
                [text appendString:value];   
            }
        }
        
        self.params.text = text;

        self.date.text = data.priceDate;
        
        [text release];
    }
 
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliTableViewCellPriceDetail" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliTableViewCellPriceDetail class]])
        {
            AliTableViewCellPriceDetail *obj = (AliTableViewCellPriceDetail *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 320.0, [AliTableViewCellPriceDetail cellHeight]);
            [obj setupView];
            return  obj;
        }
    }
    return nil;
}

- (void)dealloc {
    [_title release];
    [_price release];
    [_params release];
    [_upDown release];
    [_date release];
    [super dealloc];
}
@end
