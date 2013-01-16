#import "AMObjectMappingDelegate.h"

@interface AMPrice : NSObject <AMObjectMappingDelegate> {

  /**
   * 供货量区间开始值
 */
  NSNumber * _beginAmount;

  /**
   * 供货量区间截止值
 */
  NSNumber * _endAmount;

  /**
   * 价格
 */
  NSNumber * _price;
}

@property(nonatomic, retain) NSNumber * beginAmount;
@property(nonatomic, retain) NSNumber * price;
@property(nonatomic, retain) NSNumber * endAmount;

@end
