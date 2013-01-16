//
//  AliImageControlFactory.m
//  AlibabaMobile
//
//  Created by  on 12-2-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliImageControlFactory.h"
#import "AliImageButton.h"

static AliImageControlFactory * _imageControlFactory = nil;

//type image button
const int FAV_NAV_BTN = 0;

const int FAV_SUCCESS_BTN = 1;

const int FAV_SUCCESS_EXTEND_BTN = 10;

//type icon
const int MIXED_BUY_ICON = 201;

const int CHENG_BAO_ICON = 202;

const int ALI_PAY_ICON = 203;

const int REAL_AUTH_COMPANY_ICON = 204;

const int REAL_AUTH_PERSON_ICON = 205;

const int LINE_DIVIDED = 206;

//image
const int SUB_TITLE_BACKGROUND = 401;


@implementation AliImageControlFactory

#pragma 功能代码
- (AliImageButton *) getImageButtonWithType:(int)type
{
    if(type == FAV_SUCCESS_BTN){
        return  [[[AliImageButton alloc]initWithImageNormal:@"icon_aliww_fav_01" pressed:@"icon_aliww_fav_02"]  autorelease];
    }
    if(type == FAV_SUCCESS_EXTEND_BTN){//当收藏完成后替换五角星
        return  [[[AliImageButton alloc]initWithImageNormal:@"icon_aliww_fav_02" pressed:@"icon_aliww_fav_01"]  autorelease];
    }
    if(type == FAV_NAV_BTN){
        return  [[[AliImageButton alloc]initWithImageNormal:@"icon_aliww_fav_01" pressed:@"icon_aliww_fav_01"]  autorelease];
    }else if(type == MIXED_BUY_ICON){
        AliImageButton * img =    [[[AliImageButton alloc] initWithImageNormal:@"icon_hp"] autorelease];
        img.userInteractionEnabled = NO;
        return  img;
    }else if(type == ALI_PAY_ICON){
        AliImageButton * img =     [[[AliImageButton alloc] initWithImageNormal:@"icon_dbjy"] autorelease];
        img.userInteractionEnabled = NO;
        return img;
    }else if(type == CHENG_BAO_ICON ){
        AliImageButton * img =    [[[AliImageButton alloc] initWithImageNormal:@"icon_bzj"] autorelease];
        img.userInteractionEnabled = NO;
        return img;
    }else if(type == REAL_AUTH_COMPANY_ICON ){
        AliImageButton * img =     [[[AliImageButton alloc] initWithImageNormal:@"Icon_qyrz"] autorelease];
        img.userInteractionEnabled = NO;
        return img;
    }else if(type == REAL_AUTH_PERSON_ICON ){
        AliImageButton * img =   [[[AliImageButton alloc] initWithImageNormal:@"Icon_grrz"] autorelease];
        img.userInteractionEnabled = NO;
        return img;
    }else if(type == LINE_DIVIDED){
        AliImageButton * icon =   [[[AliImageButton alloc] initWithImageNormal:@"line_gray" size:CGSizeMake(320, 0)] autorelease];
        icon.userInteractionEnabled = NO;
        return icon;
        
    }else if(type == SUB_TITLE_BACKGROUND){
        AliImageButton * image = [[[AliImageButton alloc] initWithImageNormal:@"bg_subtitle" size:CGSizeMake(320, 25)] autorelease];
        image.userInteractionEnabled = NO;
        
        return image;
    }else{
        return nil;
    }
}

#pragma 单例模式
+ (AliImageControlFactory *) sharedInstance
{
    
    if(_imageControlFactory == nil){
        _imageControlFactory = [NSAllocateObject([self class], 0, NULL) init];
    }
    return _imageControlFactory;
}

+ (id) allocWithZone:(NSZone *)zone
{
    return [[self sharedInstance] retain];
}

- (id) copyWithZone:(NSZone*)zone
{
    return self;
}

- (id) retain
{
    return self;
}

- (NSUInteger) retainCount
{
    return NSUIntegerMax; // denotes an object that cannot be released
}

- (oneway void) release
{
    // do nothing
}

- (id) autorelease
{
    return self;
}

@end
