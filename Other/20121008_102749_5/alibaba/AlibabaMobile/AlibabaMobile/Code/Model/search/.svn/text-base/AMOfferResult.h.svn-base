#import "AMObjectMappingDelegate.h"
#import "AMOffer.h"

/**
 * Offer查询结果
 * 
 * @author qizhi.tangqz
 */

extern NSInteger const AMDEFAULT;
extern NSInteger const AMKEYWORDS_EXTEND;
extern NSInteger const AMKEYWORDS_REWRITE;

@interface AMOfferResult : NSObject <AMObjectMappingDelegate> {

  /**
   * Offer Model List
 */
  NSArray * _offerList;

  /**
   * 结果总数
 */
  NSNumber * _total;

  /**
   * 是否需要显示行业化属性
 */
  NSNumber * _showIndustryAttributes;

  /**
   * 行业化特有属性(通过XTool配置)
 */
  NSArray * _industryAttributes;

  /**
   * 搜索结果的重写类型（0：未重写，1：搜索关键字被扩展；2：搜索关键字被重写）
 */
  NSNumber * _rewriteType;

  /**
   * 重写后的关键字
 */
  NSString * _rewritedKeywords;
}

@property(nonatomic, retain)  NSArray * offerList;
@property(nonatomic, retain)  NSNumber * total;
@property(nonatomic, retain)  NSNumber * showIndustryAttributes;
@property(nonatomic, retain)  NSArray * industryAttributes;
@property(nonatomic, retain)  NSNumber * rewriteType;
@property(nonatomic, retain)  NSString * rewritedKeywords;

@end
