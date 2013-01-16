//
//  AliUIButton.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliUIButton.h"

@implementation AliUIButton

-(void)setBackgroundImage:(UIImage *)image forState:(UIControlState)state
{  
    UIGraphicsBeginImageContextWithOptions(self.frame.size, NO, 0.0);
    [[image stretchableImageWithLeftCapWidth:image.size.width/2 topCapHeight:image.size.height/2] drawInRect:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height)];  
    
    // Generate a new image
    UIImage* newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    [super setBackgroundImage:newImage forState:state];
}
-(void)setImage:(UIImage *)image forState:(UIControlState)state
{  
    UIGraphicsBeginImageContextWithOptions(self.frame.size, NO, 0.0);
    [[image stretchableImageWithLeftCapWidth:image.size.width/2 topCapHeight:image.size.height/2] drawInRect:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height)];  
    
    // Generate a new image
    UIImage* newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    [super setImage:newImage forState:state];
}

@end
