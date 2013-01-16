//
//  AMOrderBuyedResult.m
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-8-30.
//
//
//NSNumber *_totalCount;
//NSNumber *_page;
//NSNumber *_curPageCount;
//NSNumber *_pageSize;
//NSArray *_modelList;
#import "AMOrderBuyedResult.h"
#import "AMOrderBuyed.h"

@implementation AMOrderBuyedResult
@synthesize totalCount = _totalCount;
@synthesize page = _page;
@synthesize curPageCount = _curPageCount;
@synthesize pageSize = _pageSize;
@synthesize modelList = _modelList;
-(void) dealloc
{
    [_curPageCount release];
    [_page release];
    [_totalCount release];
    [_pageSize release];
    [_modelList release];
    [super dealloc];
}

+ (RKObjectMapping *)sharedObjectMapping
{
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOrderBuyedResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"totalCount" toAttribute:@"totalCount"];
            [sharedObjectMapping mapKeyPath:@"page" toAttribute:@"page"];
            [sharedObjectMapping mapKeyPath:@"curPageCount" toAttribute:@"curPageCount"];
            [sharedObjectMapping mapKeyPath:@"pageSize" toAttribute:@"pageSize"];
			[sharedObjectMapping mapRelationship:@"modelList" withMapping:[AMOrderBuyed sharedObjectMapping]];
			
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMOrderBuyed sharedObjectMapping] forKeyPath:@"modelList"];
        }
    }
    
    return sharedObjectMapping;
}
@end
