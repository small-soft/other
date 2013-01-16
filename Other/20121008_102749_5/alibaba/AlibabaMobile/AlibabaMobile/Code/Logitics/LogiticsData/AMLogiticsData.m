//
//  AMLogiticsData.m
//  AlibabaMobile
//
//  Created by zzh on 12-1-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMLogiticsData.h"


#define kLastCompanyFilename @"logitics_data.plist"
#define kHisttoryFilename @"logitics_history_data.plist"
@interface AMLogiticsData()
-(NSString*)dataFilePath:(NSString*)fileName;

@end
@implementation AMLogiticsData
@synthesize data=_data;
@synthesize historyData=_historyData;

-(void)dealloc
{
    [_data release];
    [_historyData release];
    [super dealloc];
}
-(AMCorporation*)data
{
    if (_data==nil) {
        _data = [[AMCorporation alloc]init];
    }
    NSString *filePath = [self dataFilePath:kLastCompanyFilename];
    if ([[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
        NSArray *array = [[NSArray alloc] initWithContentsOfFile:filePath];
        _data.name =  [array objectAtIndex:0];
        _data.code =  [array objectAtIndex:1];
        _data.pinyin =  [array objectAtIndex:2];
        [array release];
    }
        
     
    return _data;
}
-(void)setData:(AMCorporation *)data
{
    if (data!=nil) {
        self.data.name=data.name;
        self.data.code = data.code;
        self.data.pinyin = data.pinyin;
        NSMutableArray *array = [[NSMutableArray alloc]init];
        [array addObject:data.name];
        [array addObject:data.code];
        [array addObject:data.pinyin];
        [array writeToFile:[self dataFilePath:kLastCompanyFilename] atomically:YES];
        [array release];
    }
}
-(NSMutableArray*)historyData
{
    if (_historyData==nil) {
        NSString *filePath = [self dataFilePath:kHisttoryFilename];
        if ([[NSFileManager defaultManager] fileExistsAtPath:filePath]) {
            _historyData = [[NSMutableArray alloc] initWithContentsOfFile:filePath];
        }
        else
        {
            _historyData = [[NSMutableArray alloc]init];
        }
    }
    return _historyData;
    
}

-(void)saveHistoryData:(AMCorporation *)data orderNumber:(NSString *)number
{
    if (data!=nil&&data.name!=nil&&data.code!=nil&&data.pinyin!=nil&&number!=nil) {
        
        int num=[self.historyData count];
        
        for (int i=0; i<num; i+=4) {
            if ([data.name isEqualToString:[self.historyData objectAtIndex: i]]) {
                 if ([number isEqualToString:[self.historyData objectAtIndex: i+3]])
                 {
                     return;
                 }
            }
                
        }
                
        [self.historyData addObject:data.name];
        [self.historyData addObject:data.code];
        [self.historyData addObject:data.pinyin];
        [self.historyData addObject:number];
        
        
        [self.historyData writeToFile:[self dataFilePath:kHisttoryFilename] atomically:YES];
        
        
    }
}
-(NSString*)dataFilePath:(NSString*)fileName
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(
                                                         NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    return [documentsDirectory stringByAppendingPathComponent:fileName];
   
}


@end
