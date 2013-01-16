//
//  AliImageButton.h
//  AlibabaMobile
//
//  Created by xiejin on 12-2-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AliImageButton : UIButton

- (id) initWithImageNormal:(NSString *)normal pressed:(NSString *)pressed;
- (id) initWithImageNormal:(NSString *)normal;
- (id) initWithImageNormal:(NSString *)normal size:(CGSize) size;

@end
