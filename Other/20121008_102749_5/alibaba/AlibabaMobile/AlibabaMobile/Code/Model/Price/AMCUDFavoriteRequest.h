#import "AMObjectMappingDelegate.h"

@interface AMCUDFavoriteRequest : NSObject <AMObjectMappingDelegate> {
  NSString * _memberId;

  /**
   * 涓婚Id
 */
  NSString * _themeId;

  /**
   * 鍦板尯Id
 */
  NSString * _area;

  /**
   * 闃块噷浠凤紙1锛夛紝鍑哄巶浠凤紙3锛夛紝甯傚満浠凤紙4锛?
 */
  NSString * _sourceFromId;
}

@property(nonatomic, retain) NSString * memberId;
@property(nonatomic, retain) NSString * themeId;
@property(nonatomic, retain) NSString * area;
@property(nonatomic, retain) NSString * sourceFromId;

@end
