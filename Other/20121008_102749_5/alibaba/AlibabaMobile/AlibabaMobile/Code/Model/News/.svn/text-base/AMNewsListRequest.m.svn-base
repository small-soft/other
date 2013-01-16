#import "AMNewsListRequest.h"
#import  "AMNewsConstants.h"

#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMNewsListRequest

@synthesize page = _page;
@synthesize count = _count;
@synthesize cateId = cateId;
@synthesize tags = _tags;
@synthesize type = _type;
@synthesize newsType = _newsType;
@synthesize excludeTags = _excludeTags;
@synthesize excludeCats = _excludeCats;

@synthesize transactionType = _transactionType;

- (id) init {
  if (self = [super init]) {
      self.page = [NSNumber numberWithInt: 1];
    self.count = [NSNumber numberWithInt: 20];
    self.newsType = AMRequest_News_Type_NEWS;
  }
    
    return self;
}

// Impliment RKRequestSerializable delegate methods here

/**
 * The value of the Content-Type header for the HTTP Body representation of the serialization
 */
- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}

/**
 * An NSData representing the HTTP Body serialization of the object implementing the protocol
 */
- (NSData*)HTTPBody {
    
    NSString *signedBodyString = nil;
    NSMutableDictionary *params = nil;
    
    switch (self.transactionType) {
        case AMTRANSACTION_TYPE_HOT_NEWS:
            signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_HOTNEWS_LIST params:nil];
            break;
            
        case AMTRANSACTION_TYPE_NEWS_LIST:
            // Create NSDictionary object and setObject to it
            params = [[NSMutableDictionary alloc] init];
            
//            if (self.page) {
//                [params setObject: self.page forKey:@"page"];
//            }
//            if (self.count) {
//                [params setObject:self.count forKey:@"count"];
//            }
//            if (self.cateId) {
//                [params setObject:self.cateId forKey:@"cateId"];
//            }
//            if (self.tags) {
//                [params setObject:self.tags forKey:@"tags"];
//            }
//            if (self.newsType) {
//                [params setObject:self.newsType forKey:@"newsType"];
//            }
//            if (self.excludeTags) {
//                [params setObject:self.excludeTags forKey:@"excludeTags"];
//            }
//            if (self.excludeCats) {
//                [params setObject:self.excludeCats forKey:@"excludeCats"];
//            }
            
            RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMNewsListRequest class]];
            [requestMapping mapKeyPath:@"page" toAttribute:@"page"];
            [requestMapping mapKeyPath:@"count" toAttribute:@"count"];
            [requestMapping mapKeyPath:@"cateId" toAttribute:@"cateId"];
            [requestMapping mapKeyPath:@"tags" toAttribute:@"tags"];
            [requestMapping mapKeyPath:@"newsType" toAttribute:@"newsType"];
            [requestMapping mapKeyPath:@"excludeTags" toAttribute:@"excludeTags"];
            [requestMapping mapKeyPath:@"excludeCats" toAttribute:@"excludeCats"]; 
            
            RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
            NSError *error = nil;
            NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
            
            if (_data_) {
                 [params setObject: _data_ forKey: @"_data_"];
            }
            
            signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_NEWS_LIST params:params];
            
            [params release];
            break;

        case AMTRANSACTION_TYPE_NEWSCATEGORY_LIST:
            signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_NEWS_CATEGORIES params:nil];
            break;
            
        default:
            break;
    }
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
  [_cateId release];
  [_tags release];
  [_type release];
  [_newsType release];
  [_excludeTags release];
  [_excludeCats release];
  
  [super dealloc];
}

@end
