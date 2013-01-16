#import "AMObjectMappingDelegate.h"

@interface AMImgMagazineCategory : NSObject <AMObjectMappingDelegate> {
  NSString * _categoryId;
  NSString * _categoryName;
  NSString * _categoryTags;
  NSString * _type;

  /**
   * 返回该类目下的前5条画报信息，方便前端缓存随机读取（可能不足五条）
 */
  NSArray * _listImgMagazineItem;
}

@property(nonatomic, retain) NSString * categoryId;
@property(nonatomic, retain) NSString * categoryName;
@property(nonatomic, retain) NSString * categoryTags;
@property(nonatomic, retain) NSString * type;
@property(nonatomic, retain) NSArray * listImgMagazineItem;

@end
