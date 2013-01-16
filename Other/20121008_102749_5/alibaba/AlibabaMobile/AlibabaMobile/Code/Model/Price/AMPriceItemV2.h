
@interface AMPriceItemV2 : NSObject {

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

  /**
   * 灞炴?鍊硷紝閫氳繃瑙ｆ瀽鎻忚堪淇℃伅鑾峰彇
 */
  NSDictionary * _attribute;
}

@property(nonatomic, retain) NSString * updown;

@property(nonatomic, retain) NSDictionary * attribute;
@property(nonatomic, retain) NSString * sourceFromName;
@property(nonatomic, retain) NSString * priceDate;
@property(nonatomic, retain) NSString * price;
@property(nonatomic, retain) NSString * areaName;
@property(nonatomic, retain) NSString * sourceFromId;
@property(nonatomic, retain) NSString * themeId;
@property(nonatomic, retain) NSString * description;
@property(nonatomic, retain) NSString * themeName;
@property(nonatomic, retain) NSString * areaId;

@end
