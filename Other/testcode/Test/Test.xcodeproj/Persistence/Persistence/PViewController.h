//
//  PViewController.h
//  Persistence
//
//  Created by 佳 刘 on 12-9-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "sqlite3.h"

//#define kFilename @"data.plist"
//#define kFilename @"archive"
#define kFilename @"data.sqlite3"
#define kDataKey @"Data"

@interface PViewController : UIViewController {
    UITextField *field1;
    UITextField *field2;
    UITextField *field3;
    UITextField *field4;
    
    sqlite3 *database;
}

@property (nonatomic,retain)IBOutlet UITextField *field1;
@property (nonatomic,retain)IBOutlet UITextField *field2;
@property (nonatomic,retain)IBOutlet UITextField *field3;
@property (nonatomic,retain)IBOutlet UITextField *field4;

-(NSString *)dataFilePath;
-(void)applicationWillTerminate:(NSNotification *)notification;

@end
