//
//  AppController.h
//  oct
//
//  Created by 佳 刘 on 12-9-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AppController : NSObject {
    IBOutlet NSTextField *textField;
    IBOutlet NSTextField *resultField;
}

- (IBAction)uppercase:(id)sender;
- (IBAction)lowercase:(id)sender;

@end // AppController
