//
//  AppController.m
//  oct
//
//  Created by 佳 刘 on 12-9-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AppController.h"

@implementation AppController

- (id)init {
    if (self=[super init]) {
        NSLog(@"init:text %@ | results %@",textField,resultField);
    }
    
    return self;
}

- (void)lowercase:(id)sender {
    NSString *original = textField.stringValue;
    
    resultField.stringValue = [original lowercaseString];
}

- (void)uppercase:(id)sender {
    NSString *original = textField.stringValue;
    
    resultField.stringValue = [original uppercaseString];
}

- (void)awakeFromNib {
    NSLog(@"awake:text %@ | results %@",textField,resultField);
    
//    textField.stringValue = @"Enter text here";
    resultField.stringValue = @"Results";
}

@end
