

/**
 * 属性信息
 * 
 * @author qizhi.tangqz
 */

@interface AMFeature : NSObject {

  /**
   * 编号
 */
  NSString * _identifier;

  /**
   * 名称
 */
  NSString * _name;

  /**
   * 取值选项
 */
  NSArray * _values;
}

@property(nonatomic, retain) NSString * identifier;
@property(nonatomic, retain) NSString * name;
@property(nonatomic, retain) NSArray * values;
- (NSString *) description;

@end
