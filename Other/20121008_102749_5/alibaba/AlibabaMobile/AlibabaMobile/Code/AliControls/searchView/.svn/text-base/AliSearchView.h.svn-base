//
//  AliSearchView.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


#import "searchPickerView.h"
#import "searchHistoryTable.h"
#import "searchBarEditView.h"
#import "searchBarEditViewWithImage.h"
@class AliSearchView;

@protocol AliSearchViewDelegate
-(void)searchBarEditViewDidEnd:(AliSearchView*)searchView content:(NSString*)content selected:(NSUInteger)selected;
@optional
-(void)searchBarEditViewEditBegin:(AliSearchView*)searchView;
-(void)searchBarEditCancel:(AliSearchView*)searchBarView;

@end


@interface AliSearchView : UIView<SearchHistoryTableDelegate,searchPickerViewDelegate>
//@property (nonatomic,retain) NSObject <AliSearchViewDelegate> *delegate;

@property (nonatomic,retain)searchBarEditViewWithImage*editView;
@property (nonatomic,assign) id <AliSearchViewDelegate> delegate;
-(void)editBecomeFirstResponder;
-(void)historyBecomeFirstResponder;
@end
