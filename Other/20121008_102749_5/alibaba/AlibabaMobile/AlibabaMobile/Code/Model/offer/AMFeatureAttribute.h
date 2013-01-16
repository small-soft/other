#import "AMObjectMappingDelegate.h"

@interface AMFeatureAttribute : NSObject <AMObjectMappingDelegate> {

  /**
   * 属性ID，也是属性的唯一标识
 */
  NSNumber * _fid;

  /**
   * 属性名，相当于页面上面的label
 */
  NSString * _name;

  /**
   * 属性Flag，例如交易属性的一些flag：price、unit、amount等等
 */
  NSString * _flag;

  /**
   * 属性值
 */
  NSArray * _values;
}

@property(nonatomic, retain) NSNumber * fid;
@property(nonatomic, retain) NSString * name;
@property(nonatomic, retain) NSString * flag;
@property(nonatomic, retain) NSArray * values;

@end
