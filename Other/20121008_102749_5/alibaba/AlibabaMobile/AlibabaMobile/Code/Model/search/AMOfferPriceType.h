

/**
 * AMOfferPriceType
 * 
 * @author qizhi.tangqz
 */

@interface AMOfferPriceType : NSObject {

  /**
   * currency
 */
  NSString * _currency;

  /**
   * price
 */
  NSString * _price;

  /**
   * RMB price
 */
  NSString * _rmbPrice;

  /**
   * price ammount
 */
  NSString * _priceAmount;
  NSNumber * _quantityBegin;
  NSNumber * _lockPrice;
  NSNumber * _showEtcPrice;
  NSNumber * _showOnlineTrade;
  NSNumber * _showPrice;
}

@property(nonatomic, retain) NSString * currency;
@property(nonatomic, retain) NSString * price;
@property(nonatomic, retain) NSString * rmbPrice;
@property(nonatomic, retain) NSString * priceAmount;
@property(nonatomic, retain) NSNumber * quantityBegin;
@property(nonatomic, retain) NSNumber * lockPrice;
@property(nonatomic, retain) NSNumber * showEtcPrice;
@property(nonatomic, retain) NSNumber * showOnlineTrade;
@property(nonatomic, retain) NSNumber * showPrice;

@end
