#import "AMNewsItem.h"
#import "AMNewsItemImage.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMNewsItem

@synthesize content = _content;
@synthesize identifier = _identifier;
@synthesize title = _title;
@synthesize gmtCreate = _gmtCreate;
@synthesize imageSecondPath = _imageSecondPath;
@synthesize publishDate = _publishDate;
@synthesize coverUrl = _coverUrl;
@synthesize type = _type;
@synthesize tags = _tags;
@synthesize agencyName = _agencyName;
@synthesize memberId = _memberId;
@synthesize newsItemImages = _newsItemImages;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMNewsItem class]] retain];
			[sharedObjectMapping mapKeyPath:@"tags" toAttribute:@"tags"];
			[sharedObjectMapping mapKeyPath:@"gmtCreate" toAttribute:@"gmtCreate"];
			[sharedObjectMapping mapKeyPath:@"coverUrl" toAttribute:@"coverUrl"];
			[sharedObjectMapping mapKeyPath:@"imageSecondPath" toAttribute:@"imageSecondPath"];
			[sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
			[sharedObjectMapping mapKeyPath:@"agencyName" toAttribute:@"agencyName"];
			[sharedObjectMapping mapKeyPath:@"content" toAttribute:@"content"];
			[sharedObjectMapping mapKeyPath:@"title" toAttribute:@"title"];
			[sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
			[sharedObjectMapping mapKeyPath:@"publishDate" toAttribute:@"publishDate"];
			
			[sharedObjectMapping mapRelationship:@"newsItemImages" withMapping:[AMNewsItemImage sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMNewsItemImage sharedObjectMapping] forKeyPath:@"newsItemImages"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_content release];
  [_identifier release];
  [_title release];
  [_gmtCreate release];
  [_imageSecondPath release];
  [_publishDate release];
  [_coverUrl release];
  [_type release];
  [_tags release];
  [_agencyName release];
  [_memberId release];
  [_newsItemImages release];
  
  [super dealloc];
}

@end
