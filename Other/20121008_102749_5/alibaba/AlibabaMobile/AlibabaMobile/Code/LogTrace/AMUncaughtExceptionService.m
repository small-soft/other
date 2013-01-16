//
//  AMUncaugthExceptionService.m
//  AlibabaMobile
//
//  Created by  on 12-7-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMUncaughtExceptionService.h"
#import "AMLogResult.h"
#import "ConstDef.h"
#import "AMLogUtils.h"

void UncaughtExceptionHandler(NSException *exception){
    [AMUncaughtExceptionService catchException:exception];
}

@implementation AMUncaughtExceptionService
@synthesize count = _count;
static AMUncaughtExceptionService * _instance = nil;

+ (AMUncaughtExceptionService *) instance
{
    @synchronized(self){
        if(_instance == nil){
            _instance = [[AMUncaughtExceptionService alloc] init];
            //该字段用于模拟token过期
            _instance.count = 0;
        }
    }
    return _instance;
}

+ (void)destroy
{
    @synchronized(self){
        if(_instance){
            AM_RELEASE_SAFELY(_instance);
        }
    }
}
-(NSArray *)getErrorLogs:(NSException *)exception{
    /*
     * 封装针对error的log
     * christ.yuj
     */
    NSMutableDictionary *error =[[[NSMutableDictionary alloc]init] autorelease];
    
    NSArray *detail = [exception callStackSymbols];
    NSString *reason = [exception reason];
    NSString *name = [exception name];
    NSString *cause = [NSString stringWithFormat:@"name:\n%@\nreason:\n%@\ncallStackSymbols:\n%@",name,reason,[detail componentsJoinedByString:@"\n"]];
    
    [error setObject:cause forKey:@"cause"];
    [error setObject:[NSString stringWithFormat:@"%@",[NSNumber numberWithLong:[[NSDate date] timeIntervalSince1970]]] forKey:@"logTime"];
    NSLog(@"exception cause is \n%@",cause);
    return [NSArray arrayWithObjects:error,nil];
}
-(void) sendLog:(NSException *)exception{
    if (_request == nil ) {
        _request = [[AMUncaughtExceptionRequest alloc] init];
    }
    
    NSLog(@"AMUncaughtExceptionSevice:start to send error log to server.....");
    
    _request.header = [AMLogUtils getLogHeader];
    
    _request.logs = [self getErrorLogs:exception];
    
    if ([_request.logs count] == 0) {
        NSLog(@"AMUncaughtExceptionSevice: no log needs to be sent!!!");
        return;
    }
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
    RKObjectMapping* resultMapping = [AMLogResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: resultMapping];
    
    RKObjectLoader* loader = [objectManager loaderWithResourcePath:OCEAN_API_URL_SEND_EXCEPTION_LOGS];
    loader.delegate = self;
    
    if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
        loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMLogResult class]];
    }
    
    // Change Method to POST
    loader.method = RKRequestMethodPOST;
    loader.params = _request;
    [loader sendSynchronously];

}

+ (void) catchException:(NSException *)exception{
    [[AMUncaughtExceptionService instance] sendLog:exception];
    [AMUncaughtExceptionService destroy];
}

+ (void) setDefaultHandler
{
    
    NSSetUncaughtExceptionHandler(&UncaughtExceptionHandler);
}

+ (NSUncaughtExceptionHandler*)getHandler
{
    return NSGetUncaughtExceptionHandler();
}

#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@; body encoding name=%@", [response bodyAsString], [response bodyEncodingName]);
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	NSLog(@"Loaded objects: %@", objects);    
    
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
}
@end


