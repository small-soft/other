#import "AMObjectMappingDelegate.h"

/**
 * @author qizhi.tangqz
 * 
 */

@interface AMNewsItemImageOffer : NSObject <AMObjectMappingDelegate> {

  /**修改时间*/
  NSNumber * _gmtModified;

  /**搜索关键字*/
  NSString * _keywords;

  /**标签*/
  NSString * _tags;

  /**创建时间*/
  NSNumber * _gmtCreate;

  /**画报url的MD5值，用于匹配画报*/
  NSString * _pageMd5;

  /**价格单位*/
  NSString * _priceUnit;
  
  NSNumber * _identifier;

  /**标题*/
  NSString * _title;

  /**对应的画报资讯id*/
  NSNumber * _newsId;

  /**价格*/
  NSString * _price;

  /**对应的offerID*/
  NSNumber * _offerId;
}

@property(nonatomic, retain) NSNumber * gmtModified;
@property(nonatomic, retain) NSString * keywords;
@property(nonatomic, retain) NSString * tags;
@property(nonatomic, retain) NSNumber * gmtCreate;
@property(nonatomic, retain) NSString * pageMd5;
@property(nonatomic, retain) NSString * priceUnit;
@property(nonatomic, retain) NSNumber * identifier;
@property(nonatomic, retain) NSString * title;
@property(nonatomic, retain) NSNumber * newsId;
@property(nonatomic, retain) NSString * price;
@property(nonatomic, retain) NSNumber * offerId;

@end
