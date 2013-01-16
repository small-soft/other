//
//  main.m
//  StopCallTest
//
//  Created by 刘 佳 on 12-12-6.
//  Copyright (c) 2012年 刘 佳. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "SSQUAppDelegate.h"

#import <CoreTelephony/CDStructures.h>

#include <notify.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
typedef struct __CTSMSMessage CTSMSMessage;
NSString *CTSMSMessageCopyAddress(void *, CTSMSMessage *);
NSString *CTSMSMessageCopyText(void *, CTSMSMessage *);
id CTTelephonyCenterGetDefault(void);
void CTTelephonyCenterAddObserver(id,id,CFNotificationCallback,NSString*,void*,int);
void dolog(id formatstring,...)
{
    va_list arglist;
    if (formatstring)
    {
        va_start(arglist, formatstring);
        id outstring = [[NSString alloc] initWithFormat:formatstring arguments:arglist];
        printf("%s\n", [outstring UTF8String]);
        va_end(arglist);
    }
}
static void callback(CFNotificationCenterRef center,
                     void *observer, CFStringRef name,
                     const void *object, CFDictionaryRef userInfo)
{
    
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    // printf("NOTIFICATION: %s\n", [name UTF8String]);
    if (!userInfo) return;
    
    NSDictionary *info = (NSDictionary*)userInfo;
    int dcount = CFDictionaryGetCount(userInfo);
    id keys = [(NSDictionary*)userInfo allKeys];
    int i;
    for (i = 0; i < dcount; i++)
    {
        id key = [keys objectAtIndex:i];
        dolog(@"  %@: %@", key, [info objectForKey:key]);
    }
    
    
    if ([[(NSDictionary *)userInfo allKeys]
         containsObject:@"kCTSMSMessage"]) // SMS Message
    {
        CTSMSMessage *message = (CTSMSMessage *)
        [(NSDictionary *)userInfo objectForKey:@"kCTSMSMessage"];
        NSString *address = CTSMSMessageCopyAddress(NULL, message);
        NSString *text = CTSMSMessageCopyText(NULL, message);
        NSArray *lines = [text componentsSeparatedByString:@"\n"];
        
        printf("  %s %d\n", [address UTF8String], [lines count]);
        printf("  %s\n", [text UTF8String]);
        fflush(stdout);
    }
    
    [pool release];
    
    return ;
}
static void signalHandler(int sigraised)
{
    printf("\nInterrupted.\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    @autoreleasepool {
        // Initialize listener by adding CT Center observer implicit
        id ct = CTTelephonyCenterGetDefault();
        CTTelephonyCenterAddObserver( ct, NULL, callback,NULL,NULL,
                                     CFNotificationSuspensionBehaviorHold);
        
        // Handle Interrupts
        sig_t oldHandler = signal(SIGINT, signalHandler);
        if (oldHandler == SIG_ERR)
        {
            printf("Could not establish new signal handler");
            exit(1);
        }
        
        // Run loop lets me catch notifications
        printf("Starting run loop and watching for notification.\n");
        CFRunLoopRun();
        
        // Shouldn't ever get here. Bzzzt
        printf("Unexpectedly back from CFRunLoopRun()!\n");
        
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([SSQUAppDelegate class]));
    }
    
}
