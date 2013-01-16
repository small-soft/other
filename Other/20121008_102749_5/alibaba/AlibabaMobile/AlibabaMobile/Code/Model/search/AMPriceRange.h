

/**
 * 价格区间
 * 
 * @author qizhi.tangqz
 */

@interface AMPriceRange : NSObject {

  /**
   * 价格下限
 */
  NSNumber * _priceStart;

  /**
   * 价格上限
 */
  NSNumber * _priceEnd;
}

@property(nonatomic, retain) NSNumber * priceStart;
@property(nonatomic, retain) NSNumber * priceEnd;

- (NSString *) description;

@end
