//
//  AliImageButton.m
//  AlibabaMobile
//
//  Created by  on 12-2-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliImageButton.h"

@implementation AliImageButton

- (id) initWithImageNormal:(NSString *)normal pressed:(NSString *)pressed
{
    self = [super init];
    if(self){
        self.highlighted = NO;
        [self setImage:[UIImage imageNamed:normal] forState:UIControlStateNormal];
        [self setImage:[UIImage imageNamed:pressed] forState:UIControlEventTouchDown];
        [self sizeToFit];
    }
    return self;
}

- (id) initWithImageNormal:(NSString *)normal
{
    self = [super init];
    if(self){
        self.highlighted = NO;
        [self setImage:[UIImage imageNamed:normal] forState:UIControlStateNormal];
        [self sizeToFit];
    }
    return self;
}

- (id) initWithImageNormal:(NSString *)normal size:(CGSize) size
{
    self = [super init];
    if(self){
        self.highlighted = NO;
        [self setContentMode:UIViewContentModeScaleAspectFill];
        [self setImage:[UIImage imageNamed:normal] forState:UIControlStateNormal];
        
        [self sizeToFit];
        
        if(size.width == 0){
            self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, size.height);
        }else if(size.height == 0){
            self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, size.width, self.frame.size.height);
        }else{
            self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, size.width, size.height);
        }
    }
    return self;
}

@end
