#import "AMObjectMappingDelegate.h"

extern NSString * const FAVORITE_ADD_CONTENT_HAS_EXISTED;
extern NSString * const FAVORITE_ADD_STORAGE_HAS_FULL;

@interface AMFavoriteBaseItem : NSObject <AMObjectMappingDelegate> {

  /**
   * 收藏ID
 */
  NSString * _favoriteId;

  /**
   * 收藏人气数
 */
  NSNumber * _collectedCount;

  /**
   * 收藏夹标签model列表
 */
  NSArray * _favoriteTaglList;
}

@property(nonatomic, retain) NSNumber * collectedCount;
@property(nonatomic, retain) NSArray * favoriteTaglList;
@property(nonatomic, retain) NSString * favoriteId;

@end
