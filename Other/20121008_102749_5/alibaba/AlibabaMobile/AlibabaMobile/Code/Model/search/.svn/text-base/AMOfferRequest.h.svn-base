

/**
 * Offer查询条件
 * 
 * @author qizhi.tangqz
 */

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

extern NSString * const AM_SORT_TYPE_BOOKED;
extern NSString * const AM_SORT_TYPE_PRICE;

#define OCEAN_API_URL_SEARCH_OFFER ([@"/search.offer.listOffer/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMOfferRequest : NSObject<RKRequestSerializable> {
    
    NSInteger _transactionType;

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
   * 人气搜索标志
 */
  NSNumber * _pop;

  /**
   * 类目属性
 */
  //NSMutableDictionary * _featureMap;

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
   * 经度（比如116.3000808）
 */
  NSString * _longitude;

  /**
   * 纬度（比如39.9761502）
 */
  NSString * _latitude;

  /**
   * 周围距离（公里，比如20代表周边20公里以内）
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

  /**
   * 是否包含价格参数
 */
  NSNumber * _priceEnabled;

  /**
   * 价格下限
 */
  NSNumber * _priceStart;

  /**
   * 价格上限
 */
  NSNumber * _priceEnd;

  /**
   * 排序方式
 */
  NSString * _sortType;

  /**
   * 是否为倒叙排列（从大到小）
 */
  NSNumber * _descendOrder;
    /**
     * 用户id
     */
    NSString * _loginId;
    /**
     * 非登陆用户id
     */
    NSString * _clientId;
    /**
     * 从行业导航触发搜索时的一级类目标识名
     */
    
    NSString * _navigationCategoryId;
}
@property (nonatomic) NSInteger transactionType;

@property(nonatomic, retain) NSString * keywords;
@property(nonatomic, retain) NSString * categoryId;
@property(nonatomic, retain) NSString * categoryName;
@property(nonatomic, retain) NSNumber * pop;
//@property(nonatomic, retain) NSMutableDictionary * featureMap;
@property(nonatomic, retain) NSString * province;
@property(nonatomic, retain) NSString * bizType;
@property(nonatomic, retain) NSString * longitude;
@property(nonatomic, retain) NSString * latitude;
@property(nonatomic, retain) NSString * distance;
@property(nonatomic, retain) NSNumber * pageSize;
@property(nonatomic, retain) NSString * city;
@property(nonatomic, retain) NSNumber * beginPage;
@property(nonatomic, retain) NSNumber * priceEnabled;
@property(nonatomic, retain) NSNumber * priceStart;
@property(nonatomic, retain) NSNumber * priceEnd;
@property(nonatomic, retain) NSString * sortType;
@property(nonatomic, retain) NSNumber * descendOrder;

@property (nonatomic, copy) NSString *loginId;
@property (nonatomic, copy) NSString *clientId;
@property (nonatomic, copy) NSString *navigationCategoryId;

@property(nonatomic, retain) NSDictionary * request;

@end
