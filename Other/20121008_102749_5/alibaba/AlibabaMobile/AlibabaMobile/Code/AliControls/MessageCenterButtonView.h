//
//  MessageCenterButtonView.h
//  AlibabaMobile
//
//  Created by  on 12-2-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MessageCenterButtonView : UIControl
-(id)initWithState:(BOOL)state num:(int)number;

- (void) changeLoginState:(BOOL)state;
- (void) setMsgNum:(int)msgNum;
@property (nonatomic, retain) UIImageView * hightlightedImg;

@end
