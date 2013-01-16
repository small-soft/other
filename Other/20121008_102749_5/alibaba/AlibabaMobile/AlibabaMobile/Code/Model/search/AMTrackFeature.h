

/**
 * iprofile引擎的track域，保存用户浏览历史信息
 * 
 * @author qizhi.tangqz
 */

@interface AMTrackFeature : NSObject {

  /**
   * 最近搜索记录
 */
  NSArray * _recentSearchs;

  /**
   * 最近浏览offer
 */
  NSString * _offerIds;

  /**
   * 最近浏览公司
 */
  NSString * _companyIds;
}

@property(nonatomic, retain) NSArray * recentSearchs;
@property(nonatomic, retain) NSString * offerIds;
@property(nonatomic, retain) NSString * companyIds;

@end
