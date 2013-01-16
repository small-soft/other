#import "AMNewsItemImage.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMNewsItemImage

@synthesize url = _url;
@synthesize surl = _surl;
@synthesize picDesc = _picDesc;
@synthesize newsItemImageOffer = _newsItemImageOffer;
@synthesize image = _image;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMNewsItemImage class]] retain];
			[sharedObjectMapping mapKeyPath:@"url" toAttribute:@"url"];
			[sharedObjectMapping mapKeyPath:@"surl" toAttribute:@"surl"];
			[sharedObjectMapping mapKeyPath:@"picDesc" toAttribute:@"picDesc"];
			
			[sharedObjectMapping mapRelationship:@"newsItemImageOffer" withMapping:[AMNewsItemImageOffer sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"image" withMapping:[AMImage sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMNewsItemImageOffer sharedObjectMapping] forKeyPath:@"newsItemImageOffer"];
			[mappingProvider setMapping:[AMImage sharedObjectMapping] forKeyPath:@"image"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_url release];
  [_surl release];
  [_picDesc release];
  [_image release];
  [_newsItemImageOffer release];
  
  [super dealloc];
}

@end
