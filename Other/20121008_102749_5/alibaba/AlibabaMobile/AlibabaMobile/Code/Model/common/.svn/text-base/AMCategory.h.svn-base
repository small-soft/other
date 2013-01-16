#import "AMObjectMappingDelegate.h"

/**
 * 类型的统一定义，如类目、企业类型、注册资金货币类型、经营模式等都可以用
 * 
 * @author qizhi.tangqz
 */

@interface AMCategory : NSObject <AMObjectMappingDelegate> {
    NSString* _identifier;
    NSString * _name;
    BOOL _leaf;
  }

/**
 * 类目编号
 */
@property(nonatomic, retain) NSString * identifier;

/**
 * 类目名称
 */
@property(nonatomic, retain) NSString * name;

/**
 * 是否叶子类目
 */
@property(nonatomic) BOOL leaf;

@end
