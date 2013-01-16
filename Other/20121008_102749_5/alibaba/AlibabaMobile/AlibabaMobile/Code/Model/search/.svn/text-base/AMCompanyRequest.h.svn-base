#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

/**
 * AMCompany查询条件
 * 
 * @author qizhi.tangqz
 */

#define OCEAN_API_URL_SEARCH_COMPANY ([@"/search.company.listCompany/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMCompanyRequest : NSObject <RKRequestSerializable> {

    /**
     * 请求参数容器
     */
    NSDictionary * _request;
    
    /**
   * 搜索关键字
 */
  NSString * _keywords;

  /**
   * 类目Id
 */
  NSString * _categoryId;

  /**
   * 类目名称
 */
  NSString * _categoryName;

  /**
   * 省份名称
 */
  NSString * _province;

  /**
   * 城市名称
 */
  NSString * _city;

  /**
   * 经营模式
 */
  NSString * _bizType;

  /**
   * 经度
 */
  NSString * _longitude;

  /**
   * 纬度
 */
  NSString * _latitude;

  /**
   * 周围距离范围
 */
  NSString * _distance;

  /**
   * 每页条数
 */
  NSNumber * _pageSize;

  /**
   * 第几页，从1开始
 */
  NSNumber * _beginPage;
}

@property(nonatomic, retain) NSString * keywords;
@property(nonatomic, retain) NSString * categoryId;
@property(nonatomic, retain) NSString * categoryName;
@property(nonatomic, retain) NSString * province;
@property(nonatomic, retain) NSString * bizType;
@property(nonatomic, retain) NSString * longitude;
@property(nonatomic, retain) NSString * latitude;
@property(nonatomic, retain) NSString * distance;
@property(nonatomic, retain) NSNumber * pageSize;
@property(nonatomic, retain) NSString * city;
@property(nonatomic, retain) NSNumber * beginPage;

@property(nonatomic, retain) NSDictionary * request;

@end


