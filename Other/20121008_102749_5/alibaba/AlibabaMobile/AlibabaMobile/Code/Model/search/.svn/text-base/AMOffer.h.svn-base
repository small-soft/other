
#import "AMMoney.h"
#import "AMImage.h"
#import "AMMemberCredit.h"
#import "AMObjectMappingDelegate.h"

/**
 * Offer模型
 * 
 * @author qizhi.tangqz
 */

@interface AMOffer : NSObject <AMObjectMappingDelegate> {

  /**
   * 产品简介
 */
  NSString * _brief;

  /**
   * 省份
 */
  NSString * _province;

  /**
   * 城市
 */
  NSString * _city;

  /**
   * 公司
 */
  NSString * _company;

  /**
   * 详情页产品图片url
 */
  NSString * _detailImgUrl;

  /**
   * 详情页url
 */
  NSString * _detailUrl;

  /**
   * 列表页产品图片url
 */
  NSString * _listImgUrl;

  /**
   * 图片
 */
  AMImage * _image;

  /**
   * id
 */
  NSNumber * _offerId;

  /**
   * 公司id
 */
  NSNumber * _companyId;

  /**
   * 会员ID
 */
  NSString * _memberId;

  /**
   * 旺旺在线状态 defined by {@link DataDictConstants}
 */
  NSNumber * _aliwwStatus;

  /**
   * 价格
 */
  AMMoney * _price;

  /**
   * RMB价格
 */
  AMMoney * _rmbPrice;

  /**
   * 起订量
 */
  NSString * _quantityBegin;

  /**
   * 计量单位
 */
  NSString * _unit;

  /**
   * 标题
 */
  NSString * _subject;

  /**
   * 诚信信息
 */
  AMMemberCredit * _creditInfo;

  /**
   * 经度
 */
  NSString * _longitude;

  /**
   * 纬度
 */
  NSString * _latitude;

  /**
   * 是否使用支付宝
 */
  NSNumber * _useAlipay;

  /**
   * 是否支持混批
 */
  NSNumber * _mixWholesale;

  /**
   * 是否支持零批
 */
  NSNumber * _retailWholesale;

  /**
   * 交易笔数
 */
  NSNumber * _bookedCount;

  /**
   * 评价条数
 */
  NSNumber * _evaluateCounts;

  /**
   * 行业化特有属性(通过XTool配置)
 */
  NSDictionary * _industryAttributes;
}

@property(nonatomic, retain) NSString * brief;
@property(nonatomic, retain) NSString * province;
@property(nonatomic, retain) NSString * city;
@property(nonatomic, retain) NSString * detailImgUrl;
@property(nonatomic, retain) NSString * detailUrl;
@property(nonatomic, retain) NSString * listImgUrl;
@property(nonatomic, retain) AMImage * image;
@property(nonatomic, retain) NSNumber * offerId;
@property(nonatomic, retain) NSString * memberId;
@property(nonatomic, retain) AMMoney * price;
@property(nonatomic, retain) AMMoney * rmbPrice;
@property(nonatomic, retain) NSString * quantityBegin;
@property(nonatomic, retain) NSString * subject;
@property(nonatomic, retain) AMMemberCredit * creditInfo;
@property(nonatomic, retain) NSString * longitude;
@property(nonatomic, retain) NSString * latitude;
@property(nonatomic, retain) NSNumber * useAlipay;
@property(nonatomic, retain) NSString * company;
@property(nonatomic, retain) NSString * unit;
@property(nonatomic, retain) NSNumber * mixWholesale;
@property(nonatomic, retain) NSNumber * retailWholesale;
@property(nonatomic, retain) NSNumber * bookedCount;
@property(nonatomic, retain) NSNumber * evaluateCounts;
@property(nonatomic, retain) NSNumber * aliwwStatus;
@property(nonatomic, retain) NSDictionary * industryAttributes;
@property(nonatomic, retain) NSNumber * companyId;

@end
