//
//  BuyedOrdersTableViewCell.m
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-9-3.
//
//
//NSNumber *_orderId;//订单号
//NSNumber *_gmtModified;//下单时间
//NSString *_entryStatus;//订单状态
//NSNumber *_sumPayment;//实付款
//NSString *_buyerCompanyName;//卖家
//NSString *_productName;//标题
//NSNumber *_amout;//实付款
//NSNumber *_quantity;//条
//@property (nonatomic, retain) IBOutlet UIImageView * bkImage;
//@property (nonatomic, retain) IBOutlet HJManagedImageV *logoImage1;
#import "AMOrderBuyedMoreImagesTableViewCell.h"

@implementation AMOrderBuyedMoreImagesTableViewCell

@synthesize orderIdLabel;
@synthesize gmtModifiedLabel;
@synthesize entryStatusLabel;
@synthesize sumPaymentLabel;
@synthesize buyerCompanyNameLabel;
@synthesize bkImage;
@synthesize logoImage1;
@synthesize quantityLabel;
@synthesize logoImage2;
@synthesize logoImage3;
@synthesize logoImage4;
@synthesize orderProductCount;
@synthesize orderProductCountEnd;
@synthesize orderButton;
@synthesize logisticsButton;
@synthesize buyorsale = _buyorsale;

-(void) dealloc
{
    [orderIdLabel release];
    [gmtModifiedLabel release];
    [entryStatusLabel release];
    [sumPaymentLabel release];
    [buyerCompanyNameLabel release];
    [bkImage release];
    [logoImage1 release];
    [logoImage2 release];
    [logoImage3 release];
    [logoImage4 release];
    [quantityLabel release];
    [orderProductCount release];
    [orderProductCountEnd release];
    [orderButton release];
    [logisticsButton release];
    [_buyorsale release];
    
    [super dealloc];
}

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
    }
    return self;
}
+(id)createCell
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMOrderBuyedMoreImagesTableViewCell"
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMOrderBuyedMoreImagesTableViewCell class]])
        {
            AMOrderBuyedMoreImagesTableViewCell *obj = (AMOrderBuyedMoreImagesTableViewCell *)oneObject;
            obj.frame = CGRectMake(0.0, 0.0, 300.0, [AMOrderBuyedMoreImagesTableViewCell cellHeight]);
           
            return  obj;
        }
    }
    return nil;
}


- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
    
}

+(CGFloat)cellHeight{
    return ALI_TABLEVIEW_ORDER_MORE_IMAGE_CELL_HEIGHT;
}
+(NSString*)cellIdentifer
{
    return @"AMOrderBuyedMoreImagesTableViewCell";
}
@end
