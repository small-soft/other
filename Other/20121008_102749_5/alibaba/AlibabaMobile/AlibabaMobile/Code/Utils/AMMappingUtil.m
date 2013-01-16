//
//  AMMappingUtil.m
//  AlibabaMobile
//
//  Created by  on 12-9-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMMappingUtil.h"

@implementation AMMappingUtil
+(id)performMappingWithMapping:(RKObjectMappingDefinition *)configuredObjectMapping forJsonString:(NSString *)jsonString{
    RKObjectMappingProvider * mappingProvider = [RKObjectMappingProvider mappingProvider];
    NSString *rootKeyPath = configuredObjectMapping.rootKeyPath ? configuredObjectMapping.rootKeyPath : @"";
    [mappingProvider setMapping:configuredObjectMapping forKeyPath:rootKeyPath];
    NSError * error = nil;
    id<RKParser> parser = [[RKParserRegistry sharedRegistry] parserForMIMEType:RKMIMETypeJSON];
    id parsedData = [parser objectFromString:jsonString error:&error];
    if (parsedData == nil && error) {
        return nil;
    }
    RKObjectMapper * mapper = [RKObjectMapper mapperWithObject:parsedData mappingProvider:mappingProvider];
    RKObjectMappingResult * result = [mapper performMapping];
    if (result) {
        return [result asObject];
    }
    return nil;
}
@end
