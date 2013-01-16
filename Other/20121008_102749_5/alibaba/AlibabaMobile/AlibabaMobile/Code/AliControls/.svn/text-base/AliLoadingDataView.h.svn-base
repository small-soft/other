//
//  AliLoadingDataView.h
//  AlibabaMobile
//
//  Created by zzh on 12-2-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RestKit.h>
//@protocol AliLoadingDataViewDelegate
//@optional
//-(void)reloadLoadingData;
//@end
@interface AliLoadingDataView : UIView

@property (retain, nonatomic) IBOutlet UIView *noDataView;
@property (retain, nonatomic) IBOutlet UIView *loadingView;
@property (retain, nonatomic) IBOutlet UILabel *noDataMessageLabel;
@property (retain, nonatomic) IBOutlet UIView * loadFailedView;
@property (retain, nonatomic) IBOutlet UIButton * reloadButton;
//@property (assign, nonatomic) id<AliLoadingDataViewDelegate> delegate;
-(void)showLoadingView;
-(void)endLoadingView;
-(void)showNodataMessage;
//-(void)showLoadFailedMessage;
-(void)showLoadFailedMessageForRequest:(RKRequest*)request;
-(void)clearFailedRequest;
@end
