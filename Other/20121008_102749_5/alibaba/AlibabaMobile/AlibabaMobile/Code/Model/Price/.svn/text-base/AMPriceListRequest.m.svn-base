#import "AMPriceListRequest.h"


#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>


@implementation AMPriceListRequest

@synthesize request = _request;
@synthesize keywords = _keywords;

@synthesize cateId = _cateId;
@synthesize catName = _catName;
@synthesize areaId = _areaId;
@synthesize page = _page;
@synthesize count = _count;

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
      
    NSMutableDictionary *wrappedParams = [[[NSMutableDictionary alloc] init] autorelease];

    
    if (self.keywords) {
        [wrappedParams setObject: self.keywords forKey:@"keywords"];
    }
     if (self.keywords) {
          [wrappedParams setObject: self.keywords forKey:@"keyword"];
             }
   if (self.cateId) {
        [wrappedParams setObject: self.cateId forKey:@"cateId"];

    }
    if (self.catName) {
        [wrappedParams setObject: self.catName forKey:@"cateName"];
        
    }
    if (self.areaId) {
         [wrappedParams setObject: self.areaId forKey:@"areaId"];

    }
     if (self.page) {
          [wrappedParams setObject: self.page forKey:@"page"];
  
     }
     if (self.count) {
          [wrappedParams setObject: self.count forKey:@"count"];
       }
    
    self.request = wrappedParams;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMPriceListRequest class]];
    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_SEARCH_PRICE params:params];
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_keyword release];
    [_cateId release];
    [_areaId release];
    [_page release];
    [_count release];
        
    [super dealloc];
}

@end