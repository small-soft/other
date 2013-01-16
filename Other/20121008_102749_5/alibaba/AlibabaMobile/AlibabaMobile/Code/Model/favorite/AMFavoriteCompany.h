#import "AMFavoriteBaseItem.h"
#import "AMObjectMappingDelegate.h"

@interface AMFavoriteCompany : AMFavoriteBaseItem {
  NSNumber * _companyid;

  /**
   * 公司名称
 */
  NSString * _name;

  /**
   * memberid
 */
  NSString * _memberId;

  /**
   * 公司地址
 */
  NSString * _address;

  /**
   * 经营模式
 */
  NSString * _bizType;

  /**
   * 主营
 */
  NSString * _productionService;

  /**
   * 联系人
 */
  NSString * _contact;

  /**
   * 是否诚信通会员
 */
  NSNumber * _trust;

  /**
   * 成立年份
 */
  NSString * _establishedYear;

  /**
   * 电话:区号
 */
  NSString * _phoneArea;

  /**
   * 电话:国家号码
 */
  NSString * _phoneCountry;

  /**
   * 电话:号码
 */
  NSString * _phoneNumber;

  /**
   * 诚信通logo图标链接
 */
  NSString * _tpLogo;

  /**
   * 手机号码
 */
  NSString * _mobileNumber;
    
    /**
     * 是否有效
     */
    NSNumber * _valid;
}

@property(nonatomic, retain) NSString * contact;
@property(nonatomic, retain) NSString * name;
@property(nonatomic, retain) NSString * memberId;
@property(nonatomic, retain) NSString * address;
@property(nonatomic, retain) NSString * bizType;
@property(nonatomic, retain) NSString * productionService;
@property(nonatomic, retain) NSNumber * trust;
@property(nonatomic, retain) NSString * establishedYear;
@property(nonatomic, retain) NSNumber * companyid;
@property(nonatomic, retain) NSString * phoneArea;
@property(nonatomic, retain) NSString * phoneCountry;
@property(nonatomic, retain) NSString * phoneNumber;
@property(nonatomic, retain) NSString * tpLogo;
@property(nonatomic, retain) NSString * mobileNumber;
@property(nonatomic, retain) NSNumber * valid;

@end
