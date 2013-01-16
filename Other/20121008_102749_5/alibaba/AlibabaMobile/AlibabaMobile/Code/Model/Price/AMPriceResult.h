#import "AMObjectMappingDelegate.h"

/**
 * 浠锋牸鏁版嵁
 * @author shunhui.wu
 */



@interface AMPriceItem : NSObject <AMObjectMappingDelegate> {

  /**
   * 鎶ヤ环绫诲瀷
 */
  NSString * _sourceFromName;

  /**
   * 鎶ヤ环鏃ユ湡
 */
  NSString * _priceDate;

  /**
   * 浠锋牸
 */
  NSString * _price;

  /**
   * 鍦板煙
 */
  NSString * _areaName;

  /**
   * 鎶ヤ环绫诲瀷ID
 */
  NSString * _sourceFromId;

  /**
   * 浜у搧Id
 */
  NSString * _themeId;

  /**
   * 鎻忚堪
 */
  NSString * _description;

  /**
   * 浜у搧鍚嶇О
 */
  NSString * _themeName;

  /**
   * 鍦板煙Id
 */
  NSString * _areaId;
  NSString * _updown;

  /**
   * 灞炴?鍊硷紝閫氳繃瑙ｆ瀽鎻忚堪淇℃伅鑾峰彇
 */
  NSDictionary * _ttributes;
    
    NSNumber * _valid;
}

@property(nonatomic, retain, readonly) NSDictionary * attributes;
@property(nonatomic, retain) NSString * sourceFromName;
@property(nonatomic, retain) NSString * priceDate;
@property(nonatomic, retain) NSString * price;
@property(nonatomic, retain) NSString * areaName;
@property(nonatomic, retain) NSString * sourceFromId;
@property(nonatomic, retain) NSString * themeId;
@property(nonatomic, retain) NSString * description;
@property(nonatomic, retain) NSString * themeName;
@property(nonatomic, retain) NSString * areaId;
@property(nonatomic, retain) NSString * updown;
@property(nonatomic, retain) NSNumber * valid;


@end

@interface AMPriceResult : NSObject <AMObjectMappingDelegate> {

  /**
   * 鏌ヨ缁撴灉鎬绘暟
 */
  NSNumber * total;

  /**
   * 褰撳墠椤靛寘鍚殑鏁版嵁鎬绘暟
 */
  NSNumber * count;

  /**
   * 褰撳墠椤垫暟
 */
  NSNumber * page;

  /**
   * 浠锋牸鏁版嵁鏁扮粍
 */
  NSArray * priceList;
}

@property(nonatomic, retain) NSNumber * total;
@property(nonatomic, retain) NSNumber * count;
@property(nonatomic, retain) NSNumber * page;
@property(nonatomic, retain) NSArray * priceList;

@end
