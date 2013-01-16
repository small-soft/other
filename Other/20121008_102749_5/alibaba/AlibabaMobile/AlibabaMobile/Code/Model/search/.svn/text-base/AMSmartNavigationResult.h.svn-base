
#import "AMCategory.h"
#import "AMFeature.h"
#import "AMPriceRange.h"
#import "AMObjectMappingDelegate.h"

/**
 * AMSmartNavigation查询结果，包装SN层级数据
 * 
 * @author qizhi.tangqz
 */

@interface AMSmartNavigationResult : NSObject <AMObjectMappingDelegate> {

  /**
   * 类目
 */
  NSArray * _categories;

  /**
   * 属性信息
 */
  NSArray * _features;

  /**
   * 价格区间
 */
  NSArray * _priceRanges;

  /**
   * 查询属性信息
 */
  NSArray * _requestFeatures;

  /**
   * 查询类目
 */
  AMCategory * _requestCategory;
}

@property(nonatomic, retain) NSArray * categories;
@property(nonatomic, retain) NSArray * features;
@property(nonatomic, retain) NSArray * priceRanges;
@property(nonatomic, retain) AMCategory * requestCategory;
@property(nonatomic, retain) NSArray * requestFeatures;

@end
