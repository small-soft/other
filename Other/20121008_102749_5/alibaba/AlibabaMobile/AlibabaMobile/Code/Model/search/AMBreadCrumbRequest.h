

/**
 * 面包屑导航查询条件
 * 
 * @author qizhi.tangqz
 */

@interface AMBreadCrumbRequest : NSObject {

  /**
   * 类目ID
 */
  NSNumber * _categoryId;
}

@property(nonatomic, retain) NSNumber * categoryId;

@end
