//
//  AMSearchResultData.m
//  AlibabaMobile
//
//  Created by zzh on 12-2-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSearchResultData.h"

#define ksearchResultFilename @"searchresult_data.plist"

@interface AMSearchResultData()
-(NSString*)dataFilePath:(NSString*)fileName;
@end
@implementation AMSearchResultData
@synthesize resultData=_resultData;

-(void)dealloc
{
    [_resultData release];
    [super dealloc];
}

-(NSString*)dataFilePath:(NSString*)fileName
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(
                                                         NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    return [documentsDirectory stringByAppendingPathComponent:fileName];
    
}

-(void)saveData:(NSString*)data
{
    NSString *filePath = [self dataFilePath:ksearchResultFilename];

    NSMutableArray *sourceData = [[NSMutableArray alloc] initWithContentsOfFile:filePath];
    
    if (sourceData) {
        for (NSString *object in sourceData) {
            if ([data isEqualToString:object]) {
                [sourceData release];
                return;
            }
        }
    }
    else {
        sourceData =[[NSMutableArray alloc] init];
    }
    
 
    [sourceData addObject:data];
    [sourceData writeToFile:[self dataFilePath:ksearchResultFilename] atomically:YES];
    [sourceData release];


}
-(NSMutableArray*)resultData
{
    if (_resultData==nil) {
        
        _resultData = [[NSMutableArray alloc]init];
       
    }
     NSString *filePath = [self dataFilePath:ksearchResultFilename];
    [_resultData removeAllObjects];
    if ([[NSFileManager defaultManager] fileExistsAtPath:filePath]) {
        
        NSArray *data = [[NSArray alloc] initWithContentsOfFile:filePath];
        [_resultData addObjectsFromArray:data];
        [data release];
    }
    return _resultData;
    
}

@end
