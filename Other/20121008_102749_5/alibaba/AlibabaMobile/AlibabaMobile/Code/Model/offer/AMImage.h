#import "AMObjectMappingDelegate.h"

/**
 * 图片模型
 * 
 * @author qizhi.tangqz
 */

extern NSString * const DEFAULT_IMAGE_EXT;

@interface AMImage : NSObject <AMObjectMappingDelegate> {
  /**
   * 图片绝对路径
 */
  NSString * imageURI;
  NSNumber * bankImage;
}

@property(nonatomic, retain) NSString * imageURI;
@property(nonatomic, retain) NSNumber * bankImage;

- (NSString *) convertSearchImageURI;
- (NSString *) convertSize310x310ImageURI;
- (NSString *) convertSize220x220ImageURI;
- (NSString *) convertSize64x64ImageURI;
- (NSString *) convertSize100x100ImageURI;
- (NSString *) convertSize150x150ImageURI;
- (NSString *) convertSummImageURI;
- (NSString *) getImageName:(NSInteger)imagesizetype;
- (NSString *) getImageSize:(NSInteger)imagesizetype;

@end
