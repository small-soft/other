
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_NAVIGATION ([@"/search.smartNavigation.listSmartNavigation/" stringByAppendingString:AMCONST_APP_KEY])

/**
 * AMSmartNavigation查询条件
 * 
 * @author qizhi.tangqz
 */

@interface AMSmartNavigationRequest : NSObject <RKRequestSerializable>{

  /**
   * 关键词
 */
  NSString * _keywords;

  /**
   * 类目Id
 */
  NSString * _categoryId;

  /**
   * 类目属性
 */
  NSDictionary * featureMap;
}

@property(nonatomic, retain) NSString * keywords;
@property(nonatomic, retain) NSString * categoryId;
@property(nonatomic, retain) NSDictionary * featureMap;
@property(nonatomic, retain) NSDictionary * request;

@end
