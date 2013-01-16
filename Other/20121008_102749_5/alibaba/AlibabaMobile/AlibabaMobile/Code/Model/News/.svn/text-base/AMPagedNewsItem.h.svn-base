#import "AMObjectMappingDelegate.h"

@class AMNewsItem;

@interface AMPagedNewsItem : NSObject <AMObjectMappingDelegate> {
  AMNewsItem * _newsItem;

  /**
   * 鍒嗛〉鍚庣殑鍐呭锛屾牴鎹〉鏁伴『搴忔帓鍒?
 */
  NSArray * _pagedContent;

  /**
   * 鍒嗛〉鎬绘暟
 */
  NSNumber * _pageCount;

  /**
   * 姣忛〉瀛楁暟澶у皬
 */
  NSNumber * _pageSize;
}

@property(nonatomic, retain) NSArray * pagedContent;
@property(nonatomic, retain) AMNewsItem * newsItem;
@property(nonatomic, retain) NSNumber * pageCount;
@property(nonatomic, retain) NSNumber * pageSize;

@end
