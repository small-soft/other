//
//  AMCommonTableForOceanClientViewController.m
//  AlibabaMobile
//
//  Created by  on 12-10-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCommonTableForOceanClientViewController.h"
#import <RestKit/RestKit.h>
#import "LoginTokenHelper.h"
#import "LoginToken.h"
#import "UIHelp.h"
#import "AMUncaughtExceptionService.h"
#import "ConstDef.h"
#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
@interface AMCommonTableForOceanClientViewController ()
@property (nonatomic, retain) NSMutableArray * lastRequestArray;
@end

@implementation AMCommonTableForOceanClientViewController
@synthesize oceanClient = _oceanClient;
@synthesize lastRequestArray = _lastRequestArray;

-(NSArray *)lastRequestArray{
    if (nil ==_lastRequestArray) {
        _lastRequestArray = [[NSMutableArray alloc]init];
    }
    return _lastRequestArray;
}
-(RKOceanClient*)oceanClient{
    if (nil==_oceanClient) {
        _oceanClient = [[RKOceanClient alloc] init];
        _oceanClient.delegate = self;
    }
    return _oceanClient;
}


#pragma mark RKOceanClientDelegate methods
- (void)OceanClient:(RKOceanClient *)oceanClient Request:(RKRequest *)request didAcessTokenOutOfDate:(RKResponse *)response{
    if (![self.lastRequestArray count]) {
        NSMutableDictionary * dictionary = [[NSMutableDictionary alloc] init];
        [dictionary setObject:request forKey:@"request"];
        [dictionary setObject:@"NO" forKey:@"isSended"];
        [self.lastRequestArray addObject:dictionary];
        [dictionary release];
    }else {
        BOOL isInDic = NO;
        for (NSMutableDictionary * olddictionary in self.lastRequestArray) {
            if ([(RKRequest*)[olddictionary objectForKey:@"request"] isEqual: request]) {
                [olddictionary setObject:@"NO" forKey:@"isSended"];
                isInDic = YES;
                break;
            }
            
        }
        if (!isInDic) {
            NSMutableDictionary * dictionary = [[NSMutableDictionary alloc] init];
            [dictionary setObject:request forKey:@"request"];
            [dictionary setObject:@"NO" forKey:@"isSended"];
            [self.lastRequestArray addObject:dictionary];
            [dictionary release];
        } 
    }
    
    [[LoginTokenHelper sharedTokenHelper] updateAccessToken];
    [AMUncaughtExceptionService instance].count = 1;
    
}

- (void)OceanClient:(RKOceanClient *)oceanClient didRefreshTokenOutOfDate:(RKResponse *)response{
    //    [self.mLoadingView endLoadingView];
    //    [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"鉴权失败"] show]; 
    //    
    //    UIViewController *nextController;
    //    nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
    //    nextController.hidesBottomBarWhenPushed=YES;
    //    
    //    [self.navigationController pushViewController:nextController animated:YES];
    [AMUncaughtExceptionService instance].count = 2;
}

- (void)OceanClient:(RKOceanClient *)oceanClient didDonotLogin:(RKResponse *)response{
    //    [self.mLoadingView endLoadingView];
    //    [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"请您重新登陆"] show]; 
}

//extern NSInteger gLastDisplayErrorTimeInterval;
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"RKRequset didFailLoadWithError: %@", error);   
    
    //    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
    //    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
    //        NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
    //        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
    //        
    //        gLastDisplayErrorTimeInterval = currentTime;
    //    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
    //        NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
    //        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];    
    //        
    //        gLastDisplayErrorTimeInterval = currentTime;
    //    }
}

-(void)viewDidLoad{
    [[LoginTokenHelper sharedTokenHelper] setDelegate:self];
    [super viewDidLoad];
}
-(void)viewDidUnload{
    self.oceanClient = nil;
    //    _mLoadingView = nil;
    [super viewDidUnload];
}
- (void)dealloc
{
    AM_RELEASE_SAFELY(_oceanClient);
    //    [_mLoadingView release];
    [[LoginTokenHelper sharedTokenHelper] setDelegate:nil];
    AM_RELEASE_SAFELY(_lastRequestArray);
    [super dealloc];
}

-(void)loginTokenHelperDidUpdateAccessToken{
    for (NSMutableDictionary * dictionary in self.lastRequestArray) {
        if ([(NSString*)[dictionary objectForKey:@"isSended"] isEqualToString:@"NO"]) {
            [(RKRequest*)[dictionary objectForKey:@"request"] send];
            [dictionary setObject:@"YES" forKey:@"isSended"];
        }
    }
}


@end
