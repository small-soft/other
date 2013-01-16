#import "AMObjectMappingDelegate.h"

/**
 * 诚信保障信息
 * @author qizhi.tangqz
 * 
 */

@class AMGuaranteeGroup;

@interface AMCreditGuarantee : NSObject <AMObjectMappingDelegate>{

  /**
   * 诚保会员角色<br>
   * <ol>
   * <li>SUPER：超级圈成员
   * <li>MASTER：普通圈主,只有团长资格未创建团，也是此状态。
   * <li>MEMBER：普通圈成员
   * <li>GUANRANTEE：普通诚保
   * <li>NON_GUARANTEE：非诚保
   * <ol>
 */
  NSString * position;

  /**
   * 保障金总额
 */
  NSString * totalCreditMoney;

  /**
   * 使用中的保障金总额
 */
  NSString * totalFreezeMoney;

  /**
   * 可用的保障金总额
 */
  NSString * totalBalanceMoney;

  /**
   * 冻结记录的总数
 */
  NSNumber * freezeRecordsNum;

  /**
   * 已关闭的记录总数
 */
  NSNumber * unFreezeRecordsNum;

  /**
   * 团本身基本信息和团列表
 */
  AMGuaranteeGroup * guaranteeGroup;
}

@property(nonatomic, retain) NSString * position;
@property(nonatomic, retain) NSString * totalCreditMoney;
@property(nonatomic, retain) NSString * totalFreezeMoney;
@property(nonatomic, retain) NSString * totalBalanceMoney;
@property(nonatomic, retain) NSNumber * freezeRecordsNum;
@property(nonatomic, retain) NSNumber * unFreezeRecordsNum;
@property(nonatomic, retain) AMGuaranteeGroup * guaranteeGroup;

@end
