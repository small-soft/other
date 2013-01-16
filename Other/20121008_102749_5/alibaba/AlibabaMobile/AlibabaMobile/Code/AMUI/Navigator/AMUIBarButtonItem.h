//
//  AMUIBarButtonItem.h
//  AlibabaMobile
//
//  Created by  on 12-7-31.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum {
    AMUIBarButtonItemStyleNavCommon,    
    AMUIBarButtonItemStyleNavMain,
} AMUIBarButtonItemStyle;

@protocol AMUIBarButtonItemDelegate 

@required
- (void) buttonItemClick;

@end

@interface AMUIBarButtonItem : UIBarButtonItem
{
    AMUIBarButtonItemStyle _AMStyle;
    NSString * _text;
    NSObject <AMUIBarButtonItemDelegate> * _buttonItemClickDelegate;
}
@property (nonatomic, assign) AMUIBarButtonItemStyle AMStyle;
@property (nonatomic, retain) NSString * text;
@property (nonatomic, retain) NSObject <AMUIBarButtonItemDelegate> *buttonItemClickDelegate;

- (id) initWithTitle:(NSString *)title style:(AMUIBarButtonItemStyle)style;
@end
