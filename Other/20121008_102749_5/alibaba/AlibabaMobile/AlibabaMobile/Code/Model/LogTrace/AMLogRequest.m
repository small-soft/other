#import "AMLogRequest.h"
#import "AMLogEntry.h"
#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation AMLogRequest

@synthesize transactionType = _transactionType;

@synthesize request = _request;
@synthesize header = _header;
@synthesize logs = _logs;

@synthesize accessToken;

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
    
    if (self.header) {
        [wrappedParams setObject: self.header forKey:@"header"];
    }
    if (self.logs) {
        [wrappedParams setObject:self.logs forKey:@"clicks"];
    }
    
    self.request = wrappedParams;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMLogRequest class]];
    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    
    [params setObject: _data_ forKey: @"_data_"];
    
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_SEND_LOGS params:params];
    
    [params release];
    NSLog(@"send logs request\n %@",signedBodyString);
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
  [_header release];
  [_logs release];
  [_request release];
  
  self.accessToken = nil;
    
  [super dealloc];
}

@end
