#import "AMObjectMappingDelegate.h"

@class AMNewsTitleItem;

@interface AMNewsTitle : NSObject <AMObjectMappingDelegate> {

  /**
	 * 类目项，如[商机] 重磅商品!发热垫网购火爆  中的"商机"
  */
  AMNewsTitleItem * _categoryItem;

  /**
	 * 标题项，如[商机] 重磅商品!发热垫网购火爆 中的"重磅商品!发热垫网购火爆"
  */
  AMNewsTitleItem * _newsTitleItem;
}

@property(nonatomic, retain) AMNewsTitleItem * categoryItem;
@property(nonatomic, retain) AMNewsTitleItem * newsTitleItem;

@end
