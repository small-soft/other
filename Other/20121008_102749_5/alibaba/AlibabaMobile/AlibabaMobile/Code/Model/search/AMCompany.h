#import "AMObjectMappingDelegate.h"
#import "AMMemberCredit.h"
/**
 * AMCompany模型
 * 
 * @author qizhi.tangqz
 */

@class AMMemberCredit;

@interface AMCompany : NSObject <AMObjectMappingDelegate> {

  /**
   * 公司名称
 */
  NSString * _name;

  /**
   * 公司Id
 */
  NSNumber * _identifier;

  /**
   * 会员ID
 */
  NSString * _memberId;

  /**
   * 旺旺在线状态 defined by {@link DataDictConstants}
 */
  NSNumber * _aliwwStatus;

  /**
   * 首页url
 */
  NSString * _homepageUrl;

  /**
   * 法人代表
 */
  NSString * _principal;

  /**
   * 联系人
 */
  NSString * _contact;

  /**
   * 手机号码
 */
  NSString * _mobileNumber;

  /**
   * 注册年份
 */
  NSString * _establishedYear;

  /**
   * 省份
 */
  NSString * _province;

  /**
   * 城市
 */
  NSString * _city;

  /**
   * 地址
 */
  NSString * _address;

  /**
   * 注册地
 */
  NSString * _foundedPlace;

  /**
   * 主要经营地
 */
  NSString * _bizPlace;

  /**
   * 经营模式
 */
  NSString * _firstBizTypeName;

  /**
   * 诚信指数
 */
  NSNumber * _trustScore;

  /**
   * 新版诚信通标识
 */
  NSString * _packageName;

  /**
   * 电话区号
 */
  NSString * _phoneAreaCode;

  /**
   * 电话号码
 */
  NSString * _phoneNumber;

  /**
   * 主营产品
 */
  NSString * _productionService;

  /**
   * 主营产品简称
 */
  NSString * _productionServiceShort;

  /**
   * 身份标识
 */
  NSString * _trustLogo;

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
}

@property(nonatomic, retain) NSString * name;
@property(nonatomic, retain) NSString * homepageUrl;
@property(nonatomic, retain) NSString * contact;
@property(nonatomic, retain) NSString * mobileNumber;
@property(nonatomic, retain) NSString * firstBizTypeName;
@property(nonatomic, retain) NSString * packageName;
@property(nonatomic, retain) NSString * phoneAreaCode;
@property(nonatomic, retain) NSString * phoneNumber;
@property(nonatomic, retain) NSString * productionService;
@property(nonatomic, retain) NSString * productionServiceShort;
@property(nonatomic, retain) NSString * trustLogo;

@property(nonatomic, retain) AMMemberCredit * creditInfo;
@property(nonatomic, retain) NSString * memberId;
@property(nonatomic, retain) NSString * establishedYear;
@property(nonatomic, retain) NSString * address;
@property(nonatomic, retain) NSString * foundedPlace;
@property(nonatomic, retain) NSString * bizPlace;
@property(nonatomic, retain) NSNumber * trustScore;
@property(nonatomic, retain) NSString * principal;
@property(nonatomic, retain) NSString * province;
@property(nonatomic, retain) NSString * city;
@property(nonatomic, retain) NSString * longitude;
@property(nonatomic, retain) NSString * latitude;
@property(nonatomic, retain) NSNumber * aliwwStatus;
@property(nonatomic, retain) NSNumber * identifier;
@property(nonatomic, retain) NSString * regCapital;

@end
