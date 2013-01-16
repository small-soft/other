//
//  AliSearchView.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


#import "AliTableViewMyCustomerPickerView.h"
#import "searchHistoryTable.h"
@class AliCustomerSearchView;

@protocol AliCustomerSearchViewDelegate
-(void)searchBarEditViewDidEnd:(AliCustomerSearchView*)searchView content:(NSString*)content selected:(NSUInteger)selected pickerContent:(NSString*)pickerContent; 
@optional
-(void)searchBarEditViewEditBegin:(AliCustomerSearchView*)searchView;
-(void)searchBarEditCancel:(AliCustomerSearchView*)searchBarView;

@end


@interface AliCustomerSearchView : UIView<AliTableViewMyCustomerPickerViewDelegate>
@property (nonatomic,retain) NSObject <AliCustomerSearchViewDelegate> *delegate;
@property (nonatomic, retain) IBOutlet UIView * mMyCustomerSelectionView;
@property (nonatomic, retain) NSString *pickerContent;
-(void)editBecomeFirstResponder;
-(void)keyDisappearForce;
@end
