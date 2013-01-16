#import "AMObjectMappingDelegate.h"
/**
 * Offer状态枚举
 * 
 * @author qizhi.tangqz
 */

typedef enum {
  AMMEMBER_EXPIRED,
  AMAUTO_EXPIRED,
  AMEXPIRED,
  AMMEMBER_DELETED,
  AMPUBLISHED,
  AMMODIFIED,
  AMNEW,
  AMDELETED,
  AMTBD,
  AMAPPROVED,
  AMAUDITING,
  AMUNTREAD,
  AMUNKNOWN
} _AMOfferStatus;

@interface AMOfferStatus : NSObject<AMObjectMappingDelegate> {
    NSInteger  _type;
    NSString *_name;
}

@property(nonatomic, assign) NSInteger  type;
@property(nonatomic, retain) NSString *name;

-(NSString *) description;
-(NSString *) description: (NSInteger)key;
-(NSInteger) valueOf: (NSString * )value;
-(NSInteger) valueOf;

@end
