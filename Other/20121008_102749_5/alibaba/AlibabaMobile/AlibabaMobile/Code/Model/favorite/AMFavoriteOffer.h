#import "AMFavoriteBaseItem.h"
#import "AMObjectMappingDelegate.h"

@class AMMoney;
@class AMFavoriteCompany;

@interface AMFavoriteOffer : AMFavoriteBaseItem {
  NSString * _offerid;

  /**
   * 标题
 */
  NSString * _title;

  /**
   * 价格
 */
  AMMoney * _price;

  /**
   * 计量单位
 */
  NSString * _unit;

  /**
   * 该offer是否有效
 */
  NSNumber * _valid;

  /**
   * 有效天数
 */
  NSString * _validDay;

  /**
   * 有效小时数
 */
  NSString * _validHour;

  /**
   * 公司信息
 */
  AMFavoriteCompany * _company;

  /**
   * offer缩略图
 */
  NSString * _firstImage;

  /**
   * 发货地址
 */
  NSString * _sendAddress;

  /**
   * 该offer所属的类目，预留用
 */
  NSArray * _categories;

  /**
   * 最小起订量
 */
  NSNumber * _quantityBegin;
}

@property(nonatomic, retain) NSString * sendAddress;
@property(nonatomic, retain) NSArray * categories;
@property(nonatomic, retain) NSString * offerid;
@property(nonatomic, retain) NSString * title;
@property(nonatomic, retain) AMMoney * price;
@property(nonatomic, retain) NSString * unit;
@property(nonatomic, retain) NSNumber * valid;
@property(nonatomic, retain) NSString * validDay;
@property(nonatomic, retain) NSString * validHour;
@property(nonatomic, retain) AMFavoriteCompany * company;
@property(nonatomic, retain) NSString * firstImage;
@property(nonatomic, retain) NSNumber * quantityBegin;


@end
