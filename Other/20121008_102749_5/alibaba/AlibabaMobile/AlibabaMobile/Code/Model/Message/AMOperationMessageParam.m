#import "AMOperationMessageParam.h"
#import <RestKit/RestKit.h>

@implementation AMOperationMessageParam

@synthesize logisticsId = _logisticsId;
@synthesize newsId = _newsId;
@synthesize wap_url = _wap_url;
@synthesize keyword = _keyword;
@synthesize pictureNewsId = _pictureNewsId;
@synthesize categoryId = _categoryId;
@synthesize categorydisplayName = _categorydisplayName;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [RKObjectMapping mappingForClass:[AMOperationMessageParam class]];
            [sharedObjectMapping mapKeyPath:@"logisticsId" toAttribute:@"logisticsId"];
            [sharedObjectMapping mapKeyPath:@"newsId" toAttribute:@"newsId"];
            [sharedObjectMapping mapKeyPath:@"wap_url" toAttribute:@"wap_url"];
            [sharedObjectMapping mapKeyPath:@"keyword" toAttribute:@"keyword"];
            [sharedObjectMapping mapKeyPath:@"pictureNewsId" toAttribute:@"pictureNewsId"];
            [sharedObjectMapping mapKeyPath:@"categoryId" toAttribute:@"categoryId"];
            [sharedObjectMapping mapKeyPath:@"categorydisplayName" toAttribute:@"categorydisplayName"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_logisticsId release];
    [_newsId release];
    [_wap_url release];
    [_keyword release];
    [_categoryId release];
    [_pictureNewsId release];
    [_categorydisplayName release];
    
    [super dealloc];
}

@end
