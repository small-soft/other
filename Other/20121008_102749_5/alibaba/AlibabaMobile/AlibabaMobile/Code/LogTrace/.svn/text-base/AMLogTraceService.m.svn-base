//
//  AMLogTraceService.m
//  AlibabaMobile
//
//  Created by qizhi.tangqz on 12-3-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMLogTraceService.h"
#import "AMLogRequest.h"
#import "AMLogResult.h"
#import "ConstDef.h"
#import "AMLogUtils.h"
#import "AMIMCoreDataHelper.h"
#import <Foundation/Foundation.h>

@implementation AMLogTraceService

@synthesize request = _request;

- (void) startLogService {
    // Stop service first
    [self stopLogService];
    
    // Restart service
    if ( !logRunLoop ) {
        logRunLoop = [NSRunLoop currentRunLoop];
    }

    // Send log interval is 5 minutes
    NSDate* futureDate = [NSDate dateWithTimeIntervalSinceNow:30.0];
    NSTimer* logTimer = [[NSTimer alloc] initWithFireDate: futureDate
                                                interval: 60 * 5
                                                  target: self
                                                selector: @selector(sendLog)
                                                userInfo: nil
                                                 repeats: YES];
    
    [logRunLoop addTimer: logTimer forMode: NSDefaultRunLoopMode];
    
    NSLog(@"AMLogTraceService: started!!!");
}

- (void) sendLog {
    if ( self.request == nil ) {
        self.request = [[AMLogRequest alloc] init];
    }
    
    NSLog(@"AMLogTraceService: start to send log to server.....");
    
    self.request.header = [AMLogUtils getLogHeader];
    self.request.logs = [[AMIMCoreDataHelper getInstance] allLogsWaitingForSending];
    
    if ([self.request.logs count] == 0) {
        NSLog(@"AMLogTraceService: no log needs to be sent!!!");
        return;
    }
    
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
    RKObjectMapping* resultMapping = [AMLogResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: resultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_SEND_LOGS usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMLogResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.request;
    }];
}


#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@; body encoding name=%@", [response bodyAsString], [response bodyEncodingName]);
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
	NSLog(@"Loaded objects: %@", objects);    
    
    AMLogResult * result = (AMLogResult *)[objects objectAtIndex:0];
    if (result && [result.success boolValue]) {
        [[AMIMCoreDataHelper getInstance] saveData];
        
        [[AMIMCoreDataHelper getInstance] removeAllSentLogs];
    }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
    
    // Undo change to the logs waiting for sendding
    [[AMIMCoreDataHelper getInstance] reset];
}


- (void) stopLogService {
    
}

@end
