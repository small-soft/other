#import "AMObjectMappingDelegate.h"

/**
 * 诚信档案基本信息
 * @author qizhi.tangqz
 * 
 */

@interface AMCreditBase : NSObject <AMObjectMappingDelegate> {

  /**
   * 诚信通版本:参照DataDictHelper.getTpVersions
 */
  NSString * _tpVersion;

  /**
   * 诚信通logo图标链接
 */
  NSString * _tpLogo;

  /**
   * 诚信通年限
 */
  NSNumber * _tpYear;

  /**
   * 诚信通指数
 */
  NSNumber * _tpScore;

  /**
   * 诚保类型：参照DataDictHelper.getGuaranteeTypes
 */
  NSString * _guaranteeType;

  /**
   * 诚保金额
 */
  NSString * _totalBalanceMoney;

  /**
   * 会员编号
 */
  NSString * _memberId;

  /**
   * 是否支持7天赔付
 */
  NSNumber * _fastpay;
    
    /**
     *是否支持实地人证
     */
    NSNumber * _ovAuth;
    
    /**
     *是否如实报价
     */
    NSNumber * _realPrice;
}

@property(nonatomic, retain) NSString * tpVersion;
@property(nonatomic, retain) NSNumber * tpYear;
@property(nonatomic, retain) NSNumber * tpScore;
@property(nonatomic, retain) NSString * guaranteeType;
@property(nonatomic, retain) NSString * totalBalanceMoney;
@property(nonatomic, retain) NSString * memberId;
@property(nonatomic, retain) NSString * tpLogo;
@property(nonatomic, retain) NSNumber * fastpay;

@property (nonatomic, retain) NSNumber * ovAuth;
@property (nonatomic, retain) NSNumber * realPrice;

@end
