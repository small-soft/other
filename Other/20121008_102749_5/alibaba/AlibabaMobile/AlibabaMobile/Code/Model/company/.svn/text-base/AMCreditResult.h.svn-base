#import "AMObjectMappingDelegate.h"

/**
 * 诚信档案详细结果
 * @author qizhi.tangqz
 * 
 */

@class AMCreditSummary;
@class AMCreditGuarantee;
@class AMCreditRealAuth;

@interface AMCreditResult : NSObject <AMObjectMappingDelegate> {

  /**
   * 诚信汇总信息
 */
  AMCreditSummary * summary;

  /**
   * 诚信保障详细信息
 */
  AMCreditGuarantee * guarantee;

  /**
   * 实名认证详细信息
 */
  AMCreditRealAuth * realAuth;
}

@property(nonatomic, retain) AMCreditSummary * summary;
@property(nonatomic, retain) AMCreditGuarantee * guarantee;
@property(nonatomic, retain) AMCreditRealAuth * realAuth;



@end
