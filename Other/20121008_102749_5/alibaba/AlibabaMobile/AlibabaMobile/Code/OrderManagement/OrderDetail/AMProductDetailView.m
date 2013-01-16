//
//  AMProductDetailView.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMProductDetailView.h"
#import "HJManagedImageV.h"
#import "AMSpecItem.h"
#import "UIHelp.h"

@implementation AMProductDetailView

@synthesize icon;
@synthesize noDataImg;

-(void)dealloc
{
    [icon release];
    icon = nil;
    [noDataImg release];
    noDataImg = nil;
    
    [super dealloc];
}


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
                
    }
    return self;
}

-(id) initWithEntry:(AMOrderEntryModel*) entry
{
//    [self init];
    self = [super init];
    self.frame = CGRectMake(10, 10, 300, 100);
    self.backgroundColor = [UIColor clearColor];
//    [[self layer] setBorderColor:[[UIColor blackColor] CGColor]];
//    [[self layer]setBorderWidth:1.0f];
    
    self.noDataImg = [[[UIImageView alloc ] init ] autorelease];
    self.noDataImg.image = [UIImage imageNamed:@"nodata_pic.png"];
    self.noDataImg.frame = CGRectMake(10, 10, 60, 60);
    self.noDataImg.layer.masksToBounds = YES;
    self.noDataImg.layer.cornerRadius = 10.0;
    self.noDataImg.backgroundColor = [UIColor grayColor];
    [self addSubview:self.noDataImg];
    
    
    if (entry.mainSummImageUrl!=nil && ![entry.mainSummImageUrl isEqualToString:@""])
    {
        self.noDataImg.hidden = YES;
        
        self.icon = [[[HJManagedImageV alloc ]init ]autorelease];
        self.icon.image = nil;
        self.icon.url = [NSURL URLWithString:entry.mainSummImageUrl];
        self.icon.frame = CGRectMake(10, 10, 60, 60);
        self.icon.layer.masksToBounds = YES;
        self.icon.layer.cornerRadius = 10.0;
        self.icon.backgroundColor = [UIColor grayColor];
        
        [self addSubview:icon];
        
    }

    
    int x = 80;
    int tempY = 10;
    
    UILabel * title = [[UILabel alloc] init];
    NSLog(@"productName : %@",entry.productName);
    title.text = entry.productName;
//    title.text = @"sddddddddddddddddddddddddddddddddddddddddd";
    title.font = [UIFont systemFontOfSize:12.0];
    title.textColor = [UIHelp colorWithHexString:@"0x666666"];
    title.frame = CGRectMake(x, tempY, 200, 12);
    title.backgroundColor = [UIColor clearColor];

    [self addSubview:title];
    tempY += title.frame.size.height + 5;
    [title release];
    
    int n = entry.specItems.count;
    
    for (int i = 0  ; i < n ;  i ++)
    {
        AMSpecItem * item = (AMSpecItem*) [entry.specItems objectAtIndex: i];
        UILabel * label= [[UILabel alloc]init];
        label.frame = CGRectMake(x, tempY, 100, 12);
        label.font = [UIFont  systemFontOfSize:12.0f];
        label.textColor = [UIHelp colorWithHexString:@"0x666666"];
        label.text = [NSString stringWithFormat:@"%@:%@", item.specName, item.specValue];
        label.backgroundColor = [UIColor clearColor];
        
        [self addSubview:label];
        
        tempY += label.frame.size.height + 5;
        [label release];
    }

     
    int entryCoupon = 0 ;
    if (entry.entryCouponAmount.intValue>0) {
        entryCoupon = entry.entryCouponAmount.intValue;
    }
    CGFloat pay = (entry.discountPrice.doubleValue * entry.quantity.doubleValue + entry.entryDiscount.intValue - entryCoupon)/100.00f;
        
    UILabel * label= [[UILabel alloc]init];
    label.frame = CGRectMake(x, tempY, 200, 12);
    label.font = [UIFont  systemFontOfSize:12.0f];
    label.textColor = [UIHelp colorWithHexString:@"0x666666"];
    
    
    label.text = @"实付款:";
    label.backgroundColor = [UIColor clearColor];
    
    CGSize size1= [label.text sizeWithFont:label.font constrainedToSize:CGSizeMake(MAXFLOAT, label.frame.size.height)];
    
    UILabel * label1= [[UILabel alloc]init];
    label1.frame = CGRectMake(x + size1.width , tempY, 200, 12);
    label1.font = [UIFont  systemFontOfSize:12.0f];
    label1.textColor = [UIHelp colorWithHexString:@"0xcc0000"];
    
    label1.text = [NSString stringWithFormat:@"￥%.2f", pay];
    label1.backgroundColor = [UIColor clearColor];
    
    
    CGSize size2= [label1.text sizeWithFont:label1.font constrainedToSize:CGSizeMake(MAXFLOAT, label1.frame.size.height)];
    
    UILabel * label2= [[UILabel alloc]init];
    label2.frame = CGRectMake(x + size1.width + size2.width + 10 , tempY, 200, 12);
    label2.font = [UIFont  systemFontOfSize:12.0f];
    label2.textColor = [UIHelp colorWithHexString:@"0x666666"];
    
    label2.text = @"(共";
    label2.backgroundColor = [UIColor clearColor];
    
    CGSize size3= [label2.text sizeWithFont:label2.font constrainedToSize:CGSizeMake(MAXFLOAT, label2.frame.size.height)];
    
    UILabel * label3= [[UILabel alloc]init];
    label3.frame = CGRectMake(x + size1.width + size2.width + 10 + size3.width , tempY, 200, 12);
    label3.font = [UIFont  systemFontOfSize:12.0f];
    label3.textColor = [UIHelp colorWithHexString:@"0x666666"];
    
    label3.text = [NSString stringWithFormat:@"%d", entry.quantity.intValue];
    label3.backgroundColor = [UIColor clearColor];
    
    CGSize size4= [label3.text sizeWithFont:label3.font constrainedToSize:CGSizeMake(MAXFLOAT, label3.frame.size.height)];
    
    UILabel * label4= [[UILabel alloc]init];
    label4.frame = CGRectMake(x + size1.width + size2.width + 10 + size3.width + size4.width , tempY, 200, 12);
    label4.font = [UIFont  systemFontOfSize:12.0f];
    label4.textColor = [UIHelp colorWithHexString:@"0x666666"];
    
    label4.text = [NSString stringWithFormat:@"%@)", entry.unit];
    label4.backgroundColor = [UIColor clearColor];
    
    [self addSubview:label];
    [self addSubview:label1];
    [self addSubview:label2];
    [self addSubview:label3];
    [self addSubview:label4];
    tempY += label.frame.size.height + 5;
    [label release];
    [label1 release];
    [label2 release];
    [label3 release];
    [label4 release];
    
    
    
    if (tempY < 80) {
        tempY = 80;
    }
    
        
    self.frame = CGRectMake(0, 0, 300, tempY);    
    return self;

}


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
//- (void)drawRect:(CGRect)rect
//{
//    // Drawing code
//    
//}

-(void) draw{
//    UIImageView * imageView = [[UIImageView alloc] init];
//    imageView.frame = CGRectMake(10, 10, 40, 40);
//    imageView.image = [UIImage imageNamed:@"icon_ww"];
//    
//    [self addSubview:imageView];

}


@end
