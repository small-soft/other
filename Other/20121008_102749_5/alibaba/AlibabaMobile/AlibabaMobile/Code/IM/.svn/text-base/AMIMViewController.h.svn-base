//
//  AMIMViewController.h
//  AlibabaMobile
//
//  Created by zzh on 11-12-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import <Foundation/Foundation.h>
#import "LoginResult.h"
#import "LoginRequest.h"
#import "LogoutRequest.h"
#import "AliNavigationButton.h"
#import "AliNavigationBackButton.h"
#import "AliLoadingDataView.h"



@interface AMIMViewController : UIViewController<UITableViewDataSource,UITextFieldDelegate,UITableViewDelegate,RKObjectLoaderDelegate,AliNavigationBackDelegate,AliNavigationButtonDelegate>{

    IBOutlet UITableViewCell			*nameCell,*pwdCell,*rememberPwdCell,*registerCell;
    IBOutlet UITableView				*loginTableView, *rememberPwdTableView,          
                                        *accountTableView;
    
    IBOutlet UITextField				*nameTextField, *pwdTextField;
    
    IBOutlet UIButton					*loginButton,*autoLoginButton;
    IBOutlet UIButton					*delButton;
    IBOutlet UIButton				    *delPWDButton;
    IBOutlet UISwitch                   *rememberPwdButton;
	IBOutlet UIButton					*nameButton;
    NSMutableArray						*sitePrefixList;
	NSMutableDictionary				    *accountDictionary;
	NSInteger							lastAccountRow, lastSiteRow;

    IBOutlet UIView						*loginView;
    
    BOOL                                isTimeout;
    
    NSMutableDictionary					*loginData;
    
    LoginRequest                        *_loginRequset;
    BOOL                                isLogoutRequest;
    BOOL                                isLogining;

}

@property (nonatomic, retain) UIButton *navigationBackButton;
@property (nonatomic, retain) LoginRequest *_loginRequset;
@property (nonatomic, retain) LoginResult  * _object;
@property (nonatomic,retain)  AliLoadingDataView * mLoadingView;
@property (nonatomic, assign) BOOL loginWangwang;
@property (nonatomic, assign) BOOL enterWangwang;
@property (retain,nonatomic)  LogoutRequest *logoutRequset;

//- (IBAction) registerButtonOnClick:(id)sender;
//- (IBAction) loginButtonOnClick:(id)sender;
- (IBAction) rememberPwdButtonOnClick:(id)sender;
- (IBAction) textFieldDoneEditing:(id)sender;
- (IBAction) textFieldDoneEditing:(id)sender;
- (IBAction) nameButtonOnClick:(id)sender;
- (IBAction) delButtonOnClick:(id)sender;

@end

