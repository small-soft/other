
@interface AMPriceListResultV2 : NSObject {

  /**
   * 查询结果总数
 */
  NSNumber * _total;

  /**
   * 当前页包含的数据总数
 */
  NSNumber * _count;

  /**
   * 当前页数
 */
  NSNumber * _page;

  /**
   * 价格数据数组
 */
  NSArray * _priceList;
}

@property(nonatomic, retain) NSNumber * total;
@property(nonatomic, retain) NSNumber * count;
@property(nonatomic, retain) NSNumber * page;
@property(nonatomic, retain) NSArray * priceList;

@end
