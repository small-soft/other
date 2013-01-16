#import "AMObjectMappingDelegate.h"

/**
 * 诚信团成员信息
 * @author qizhi.tangqz
 * 
 */

@interface AMGuaranteeGroupMember : NSObject <AMObjectMappingDelegate>{

  /**
   * 成员memberId
 */
  NSString * _memberId;

  /**
   * 成员会员类型
 */
  NSString * _memberType;

  /**
   * 公司名
 */
  NSString * _companyName;

  /**
   * 诚信通年限
 */
  NSString * _tpYear;

  /**
   * 诚信通指数
 */
  NSString * _tpScore;

  /**
   * 保障金总额
 */
  NSString * _totalCreditMoney;

  /**
   * 诚信通图标URL
 */
  NSString * _tpLogo;

  /**
   * 团头衔，团长或团成员
 */
  NSString * _memberPosition;
}

@property(nonatomic, retain) NSString * memberId;
@property(nonatomic, retain) NSString * memberType;
@property(nonatomic, retain) NSString * companyName;
@property(nonatomic, retain) NSString * tpYear;
@property(nonatomic, retain) NSString * tpScore;
@property(nonatomic, retain) NSString * totalCreditMoney;
@property(nonatomic, retain) NSString * tpLogo;
@property(nonatomic, retain) NSString * memberPosition;

@end
