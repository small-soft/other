#import "AMAddress.h"
#import "AMMemberBrief.h"
#import "AMFeatureAttribute.h"
#import "AMImage.h"
#import "AMOfferStatus.h"
#import "AMPrice.h"

#import "AMObjectMappingDelegate.h"

extern NSInteger const AMREALPRICE_VALID;
extern NSInteger const AMREALPRICE_NOT_VALID;
extern NSInteger const AMREALPRICE_NOT_EXISTS;

@class AMTradeInfo, AMOfferRate;

@interface AMOfferDetail : NSObject <AMObjectMappingDelegate> {

  /**
   * offerId
 */
  NSNumber * _offerId;

  /**
   * 会员memberId
 */
  NSString * _memberId;

  /**
   * offer名称
 */
  NSString * _subject;

  /**
   * 价格区间
 */
  NSArray * _priceRange;

  /**
   * 价格单位
 */
  NSString * _priceUnit;

  /**
   * 产品单位，如克，个，公斤等
 */
  NSString * _productUnit;

  /**
   * 真实报价状态      (1：有效；2：“过期”； 3：“不存在”  )
 */
  NSNumber * _priceStatus;

  /**
   * 供货总量
 */
  NSNumber * _amount;

  /**
   * 可出售的(供货总量-下单数量)
 */
  NSNumber * _availableAmount;

  /**
   * 成交的数量（已支付）
 */
  NSNumber * _dealedAmount;
  NSNumber * _pictureAuthOffer;
  NSNumber * _priceAuthOffer;

  /**
   * 是否支持混批
 */
  NSNumber * _isMixWholeSale;

  /**
   * 交易方式
 */
  AMTradeInfo * _tradeInfo;

  /**
   * 图片列表
 */
  NSArray * _imageList;

  /**
   * 公司相关信息
 */
  AMMemberBrief * _companyBrief;

  /**
   * 发货地址
 */
  AMAddress * _sendAddress;

  /**
   * offer的各个属性值
 */
  NSArray * _featureAttributes;

  /**
   * 图文展示区
 */
  NSString * _detail;
  AMOfferRate * _rate;
  AMOfferStatus * _offerStatus;
}

@property(nonatomic, retain) NSString * detail;
@property(nonatomic, retain) NSArray * priceRange;
@property(nonatomic, retain) NSString * priceUnit;
@property(nonatomic, retain) NSNumber * mixWholeSale;
@property(nonatomic, retain) NSArray * featureAttributes;
@property(nonatomic, retain) NSString * subject;
@property(nonatomic, retain) AMTradeInfo * tradeInfo;
@property(nonatomic, retain) NSNumber * amount;
@property(nonatomic, retain) AMMemberBrief * companyBrief;
@property(nonatomic, retain) NSString * memberId;
@property(nonatomic, retain) NSArray * imageList;
@property(nonatomic, retain) AMAddress * sendAddress;
@property(nonatomic, retain) NSNumber * offerId;
@property(nonatomic, retain) NSNumber * priceStatus;
@property(nonatomic, retain) NSString * productUnit;
@property(nonatomic, retain) NSNumber * pictureAuthOffer;
@property(nonatomic, retain) NSNumber * priceAuthOffer;
@property(nonatomic, retain) NSNumber * availableAmount;
@property(nonatomic, retain) NSNumber * dealedAmount;
@property(nonatomic, retain) AMOfferRate * rate;
@property(nonatomic, retain) AMOfferStatus * offerStatus;

@end
