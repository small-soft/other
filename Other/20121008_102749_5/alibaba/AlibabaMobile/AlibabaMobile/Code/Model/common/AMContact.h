#import "AMObjectMappingDelegate.h"

/**
 * 联系信息
 * @author qizhi.tangqz
 * 
 */

@interface AMContact : NSObject <AMObjectMappingDelegate> {

  /**
   * 电话列表
 */
  NSArray * _phone;

  /**
   * 手机
 */
  NSArray * _mobile;

  /**
   * 传真
 */
  NSString * _fax;

  /**
   * 公司首页
 */
  NSArray * _homepage;
}

@property(nonatomic, retain) NSArray * phone;
@property(nonatomic, retain) NSArray * mobile;
@property(nonatomic, retain) NSString * fax;
@property(nonatomic, retain) NSArray * homepage;

@end
