//
//  LoginTokenHelper.m
//  AlibabaMobile
//
//  Created by lih on 12-3-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "LoginTokenHelper.h"
#import "ConstDef.h"
#import "LoginToken.h"
#import "AccessTokenRequest.h"
#import "AccessTokenResult.h"
#import "LoginToken.h"


static LoginTokenHelper *sharedTokenHelper = nil;

@implementation LoginTokenHelper

@synthesize delegate = _delegate;
@synthesize accessTokenRequest=_accessTokenRequest; 
@synthesize object=_object; 

#pragma mark Singleton Methods

+ (id)sharedTokenHelper {
    @synchronized(self) {
        if(sharedTokenHelper == nil)
            sharedTokenHelper = [[super allocWithZone:NULL] init];
    }
    
    return sharedTokenHelper;
}

+ (id)allocWithZone:(NSZone *)zone {
    return [[self sharedTokenHelper] retain];
}

- (id)copyWithZone:(NSZone *)zone {
    return self;
}

- (id)retain {
    return self;
}

- (unsigned)retainCount {
    return UINT_MAX; //denotes an object that cannot be released
}

- (oneway void)release {
    // never release
}

- (id)autorelease {
    return self;
}

- (void)loadObjectsFromRemote {
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
	objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL4OAUTH];
	
    
    RKObjectMapping* logoutMapping = [RKObjectMapping mappingForClass:[AccessTokenResult class]];
    
    [logoutMapping mapKeyPath:@"accessToken" toAttribute:@"mAccessToken"];
    [logoutMapping mapKeyPath:@"accessTokenTimeout" toAttribute:@"mAccessTokenTimeout"];
    [logoutMapping mapKeyPath:@"resourceOwnerId" toAttribute:@"mResourceOwnerId"];
    [logoutMapping mapKeyPath:@"uid" toAttribute:@"mUid"];
    
    // Register our mappings with the provider
    [objectManager.mappingProvider addObjectMapping: logoutMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_GET_ACCESSTOKEN usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AccessTokenResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = _accessTokenRequest;
    }];
}

#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
    
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    
    NSLog(@"Loaded objects: %@", objects);    
	//[_object release]; maybe cause crash  -->modify by xiaowen  
    
    _object = [objects objectAtIndex:0];
    [LoginToken updateAccessToken:_object.mAccessToken :_object.mAccessTokenTimeout];
    if ([self.delegate respondsToSelector:@selector(loginTokenHelperDidUpdateAccessToken)]) {
        [self.delegate loginTokenHelperDidUpdateAccessToken];
    }
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
    
	NSLog(@"Hit error: %@", error);
    
}

- (void) updateAccessToken {
    
	if (_accessTokenRequest==nil) {        
        _accessTokenRequest = [[AccessTokenRequest alloc] init];
    }  
    _accessTokenRequest.refreshToken=[LoginToken getRefreshToken]; 
    [self loadObjectsFromRemote];
    
}

- (void) dealloc {
    [_accessTokenRequest release];
    [_object release]; 
    [_delegate release];
    _delegate = nil;
    [super dealloc];
}

@end

