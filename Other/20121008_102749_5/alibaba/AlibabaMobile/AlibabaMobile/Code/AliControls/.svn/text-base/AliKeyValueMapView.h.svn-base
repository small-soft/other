//
//  AliKeyValueMapView.h
//  AlibabaMobile
//
//  Created by xiejin on 12-2-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "KeyValueObject.h"

extern const int VALUE_STYLE_PLAIN;
extern const int VALUE_STYLE_MULTI_HORIZONTAL;
extern const int ITEM_STYLE_LINE_DIVIDED;
extern const int ITEM_STYLE_ONE_LABEL;
extern const int ITEM_STYLE_TITLE;
extern const int ITEM_STYLE_CUSTOME;


@interface AliKeyValueMapView : UIView
{
}



@property (nonatomic, assign) int paddingTop;
@property (nonatomic, assign) int paddingBottom;
@property (nonatomic, assign) int paddingLeft;
@property (nonatomic, assign) int paddingRight;
@property (nonatomic, assign) int horizontalSpace;
@property (nonatomic, assign) int verticalSpace;
@property (nonatomic, assign) int fontSize;
@property (nonatomic, assign) NSString * keyTextColor; 
@property (nonatomic, assign) NSString * valueTextColor;
@property (nonatomic, assign) int keyZoneWidth;
@property (nonatomic, assign) int valueZoneWidth; 
@property (nonatomic, assign) BOOL alignCenter;

- (id) init;
- (id) initWithKeyValues:(NSMutableArray *)array  maxKeyLabelString:(const NSString*) maxKeyLabelString;
- (void) setContentArray:(NSMutableArray *)contentArray   maxKeyLabelString:(const NSString*) maxKeyLabelString;

-(void) setPadding:(int)padding;

@end
