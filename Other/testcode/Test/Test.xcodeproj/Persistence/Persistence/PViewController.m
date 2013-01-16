//
//  PViewController.m
//  Persistence
//
//  Created by 佳 刘 on 12-9-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "PViewController.h"
#import "PFourLines.h"

@interface PViewController ()

@end

@implementation PViewController
@synthesize field1;
@synthesize field2;
@synthesize field3;
@synthesize field4;

#pragma mark -
#pragma mark vc lifecycyle

- (void)viewDidLoad
{
//    NSString *filePath = [self dataFilePath];
//    if ([[NSFileManager defaultManager] fileExistsAtPath:filePath]) {
////        NSArray *array = [NSArray arrayWithContentsOfFile:filePath];
////        self.field1.text = [array objectAtIndex:0];
////        
//////        for (int i = 0; i<4; i++) {
//////            [self setValue:[array objectAtIndex:i] forKeyPath:[NSString stringWithFormat:@"field%@.text",(i+1)]];
//////        }
////
////        self.field2.text = [array objectAtIndex:1];
////        self.field3.text = [array objectAtIndex:2];
////        self.field4.text = [array objectAtIndex:3];
//
//        NSData *data = [[NSMutableData alloc]initWithContentsOfFile:filePath];
//        NSKeyedUnarchiver *unarchiver = [[[NSKeyedUnarchiver alloc]initForReadingWithData:data]autorelease];
//        PFourLines *fourLines = [unarchiver decodeObjectForKey:kDataKey];
//        [unarchiver finishDecoding];
//        
//        field1.text = fourLines.field1;
//        field2.text = fourLines.field2;
//        field3.text = fourLines.field3;
//        field4.text = fourLines.field4;
//    } else {
//        [[NSFileManager defaultManager] createFileAtPath:filePath contents:nil attributes:nil];
//    }

    // use database
    if (sqlite3_open([[self dataFilePath] UTF8String], &database) != SQLITE_OK) {
        sqlite3_close(database);
        NSAssert(0, @"failed to open database");
    }
    
    char *errorMsg;
    NSString *createSql = @"CREATE TABLE IF NOT EXISTS FIELDS (ROW INTEGER PRIMARY KEY,FIELD_DATA TEXT);";
    if (sqlite3_exec(database, [createSql UTF8String], NULL, NULL, &errorMsg)!=SQLITE_OK) {
        sqlite3_close(database);
        NSAssert1(0, @"error creating table:%s", errorMsg);
    }
    
    NSString *query = @"SELECT ROW,FIELD_DATA FROM FIELDS ORDER BY ROW";
    sqlite3_stmt *statmement;
    if (sqlite3_prepare_v2(database, [query UTF8String], -1, &statmement, nil) == SQLITE_OK) {
        while (sqlite3_step(statmement) == SQLITE_ROW) {
            int row = sqlite3_column_int(statmement, 0);
            char *rowData = (char *)sqlite3_column_text(statmement, 1);
            
            NSString *fieldName = [NSString stringWithFormat:@"field%d",row];
            NSString *fieldValue = [NSString stringWithUTF8String:rowData];
            UITextField *field = [self valueForKey:fieldName];
            field.text = fieldValue;
        }
        
        sqlite3_finalize(statmement);
    }
    
    UIApplication *app = [UIApplication sharedApplication];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationWillTerminate:) name:UIApplicationWillResignActiveNotification object:app];
    
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    self.field1 = nil;
    self.field2 = nil;
    self.field3 = nil;
    self.field4 = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}


#pragma mark -
#pragma mark action
-(NSString *)dataFilePath {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSLog(@"path is :%@",[[paths objectAtIndex:0] stringByAppendingPathComponent:kFilename]);
    
    return [[paths objectAtIndex:0] stringByAppendingPathComponent:kFilename];
}

-(void)applicationWillTerminate:(NSNotification *)notification {
//    NSMutableArray *array = [NSMutableArray arrayWithObjects:field1.text,field2.text,field3.text,field4.text, nil];

//    PFourLines *fourLines = [[[PFourLines alloc]init]autorelease];
//    fourLines.field1 = field1.text;
//    fourLines.field2 = field2.text;
//    fourLines.field3 = field3.text;
//    fourLines.field4 = field4.text;
//    
//    NSMutableData *data = [[[NSMutableData alloc]init]autorelease];
//    NSKeyedArchiver *archive = [[[NSKeyedArchiver alloc]initForWritingWithMutableData:data]autorelease];
//    [archive encodeObject:fourLines forKey:kDataKey];
//    [archive finishEncoding];
//    
//    [data writeToFile:[self dataFilePath] atomically:YES];

    // use database
    for (int i = 1; i <= 4; i++) {
        NSString *fieldName = [NSString stringWithFormat:@"field%d",i];
        UITextField *field = [self valueForKey:fieldName];
        
        char *errorMsg;
        char *update = "INSERT OR REPLACE INTO FIELDS (ROW,FIELD_DATA) VALUES (?,?);";
        
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(database, update, -1, &stmt, nil) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, i);
            sqlite3_bind_text(stmt, 2, [field.text UTF8String], -1, NULL);
        }
        
        if (sqlite3_step(stmt)!=SQLITE_DONE) {
            NSAssert1(0, @"Error updating table: %s",errorMsg);
        }
        
        sqlite3_finalize(stmt);
        
    }
    
    sqlite3_close(database);
}
@end
