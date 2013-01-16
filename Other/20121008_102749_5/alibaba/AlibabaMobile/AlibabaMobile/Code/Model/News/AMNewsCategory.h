#import "AMObjectMappingDelegate.h"

@interface AMNewsCategory : NSObject <AMObjectMappingDelegate> {

  /**
   * 类目Id
 */
  NSNumber * _identifier;

  /**
   * 类目名称
 */
  NSString * _name;
}

@property(nonatomic, retain) NSNumber * identifier;
@property(nonatomic, retain) NSString * name;

@end
