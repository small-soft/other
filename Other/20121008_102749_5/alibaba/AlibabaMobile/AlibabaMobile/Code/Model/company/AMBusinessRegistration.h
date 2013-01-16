#import "AMObjectMappingDelegate.h"
#import "AMCategory.h"

/**
 * 公司注册信息
 * @author qizhi.tangqz
 * 
 */

@interface AMBusinessRegistration : NSObject <AMObjectMappingDelegate> {

  /**
   * 公司成立年份
 */
  NSString * _establishedYear;

  /**
   * 公司注册地
 */
  NSString * _foundedPlace;

  /**
   * 法人代表(法定代表人)
 */
  NSString * _principal;

  /**
   * 企业类型描述
 */
  NSString * _companyType;

  /**
   * 注册资金
 */
  NSNumber * _regCapital;

  /**
   * 注册资金货币类型
 */
  AMCategory * _currencyType;

  /**
   * 开户银行
 */
  NSString * _bank;

  /**
   * 银行账号
 */
  NSString * _account;
}

@property(nonatomic, retain) NSString * establishedYear;
@property(nonatomic, retain) NSString * foundedPlace;
@property(nonatomic, retain) NSString * principal;
@property(nonatomic, retain) NSString * companyType;
@property(nonatomic, retain) NSNumber * regCapital;
@property(nonatomic, retain) AMCategory * currencyType;
@property(nonatomic, retain) NSString * bank;
@property(nonatomic, retain) NSString * account;

@end
