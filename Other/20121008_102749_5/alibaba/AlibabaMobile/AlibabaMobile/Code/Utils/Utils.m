//
//  Utils.m
//  AlibabaMobile
//
//  Created by  on 12-1-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Utils.h"

@implementation Utils

+ (NSString *) generateBodyString: (NSDictionary *) params {
    NSMutableString *bodyString = [[[NSMutableString alloc] initWithString:@""] autorelease];
    for (NSString *key in [params allKeys]) {
        NSString *value = [params valueForKey:key];
        if( value ){
            [bodyString appendString:@"="];
            [bodyString appendString:value];
            [bodyString appendString:@"&"];
        }
    }
    
    // remove last '&'
    NSRange range = {0, [bodyString length] - 2};

    return [bodyString substringWithRange: range] ;
}

+ (NSString *)createUUID {
    // Create universally unique identifier (object)
    CFUUIDRef uuidObject = CFUUIDCreate(kCFAllocatorDefault);
    // Get the string representation of CFUUID object.
    NSString *uuidStr = [(NSString *)CFUUIDCreateString(kCFAllocatorDefault, uuidObject) autorelease];
    // If needed, here is how to get a representation in bytes, returned as a structure
    // typedef struct {
    //   UInt8 byte0;
    //   UInt8 byte1;
    //   ...
    //   UInt8 byte15;
    // } CFUUIDBytes;
    //CFUUIDBytes bytes = CFUUIDGetUUIDBytes(uuidObject);
    CFRelease(uuidObject);
    return uuidStr;
}

+ (BOOL) isApplicationFirstLaunched {
    if (![[NSUserDefaults standardUserDefaults] boolForKey:@"everLaunched"]) {
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"everLaunched"];
//        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"firstLaunch"];
        
        return YES;
    }
    else{
//        [[NSUserDefaults standardUserDefaults] setBool:NO forKey:@"firstLaunch"];
        
        return NO;
    }
}

+ (void)launchMailApp:(NSString *) emailAddress {
    if (emailAddress == nil) {
        return ;
    }
    NSMutableString *mailUrl = [[[NSMutableString alloc]init]autorelease];   
    NSArray *toRecipients = [NSArray arrayWithObject: emailAddress];   
    [mailUrl appendFormat:@"mailto:%@", [toRecipients componentsJoinedByString:@","]];   
    NSString* email = [mailUrl stringByAddingPercentEscapesUsingEncoding: NSUTF8StringEncoding]; 
    
    NSLog(@"launching mail app...%@",email);
    
    [[UIApplication sharedApplication] openURL: [NSURL URLWithString:email]];   
}

+ (HJObjManager *)createObjManagerDefault {
    return [self createObjManagerWithLoadingBufferSize:12 memCacheSize:40 fileCountLimit:100 fileAgeLimit:60*60*24*7];
}

+ (HJObjManager *)createObjManagerWithLoadingBufferSize:(int)loadingBufferSize memCacheSize:(int)memCacheSize fileCountLimit:(long)fileCountLimit fileAgeLimit:(long)fileAgeLimit {
    HJObjManager *objMan = [[HJObjManager alloc] initWithLoadingBufferSize:loadingBufferSize memCacheSize:memCacheSize];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
    HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
    objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
    fileCache.fileCountLimit = fileCountLimit;
    fileCache.fileAgeLimit = fileAgeLimit; //1 week
    [fileCache trimCacheUsingBackgroundThread];
    
    return objMan;
}
@end
