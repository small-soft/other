//
//  AMOrderBuyedSingleImagesTableViewCell.h
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
//NSNumber *_amount;//实付款
//NSNumber *_quantity;//条

#import <Foundation/Foundation.h>
#import "HJManagedImageV.h"
#import "AliParamButton.h"
#define ALI_TABLEVIEW_ORDER_SINGLE_IMAGE_CELL_HEIGHT 260

@interface AMOrderBuyedSingleImagesTableViewCell : UITableViewCell

@property (nonatomic, retain) IBOutlet UILabel *orderIdLabel;
@property (nonatomic, retain) IBOutlet UILabel *gmtModifiedLabel;
@property (nonatomic, retain) IBOutlet UILabel *entryStatusLabel;
@property (nonatomic, retain) IBOutlet UILabel *sumPaymentLabel;
@property (nonatomic, retain) IBOutlet UILabel *buyerCompanyNameLabel;
@property (nonatomic, retain) IBOutlet UILabel *amountLabel;
@property (nonatomic, retain) IBOutlet UILabel *quantityLabel;
@property (nonatomic, retain) IBOutlet UILabel *productNameLabel;
@property (nonatomic, retain) IBOutlet UIImageView * bkImage;
@property (nonatomic, retain) IBOutlet HJManagedImageV *logoImage1;
//@property (nonatomic, retain) IBOutlet HJManagedImageV *logoImage2;
//@property (nonatomic, retain) IBOutlet HJManagedImageV *logoImage3;
//@property (nonatomic, retain) IBOutlet HJManagedImageV *logoImage4;
@property (nonatomic, retain) IBOutlet UILabel *orderProductCount;
@property (nonatomic, retain) IBOutlet UILabel *orderProductCountEnd;

@property (nonatomic, retain) IBOutlet UILabel *buyorsale;

@property (nonatomic, retain) IBOutlet AliParamButton *orderButton;
@property (nonatomic, retain) IBOutlet AliParamButton *logisticsButton;

+(CGFloat)cellHeight;
+(NSString*)cellIdentifer;
+(id)createCell;
@end
