//
//  AMIMUser.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-13.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <WangWangNetLib/LoginDataStructDefs.h>
#import "AMIMUser.h"

@implementation AMIMUser

@synthesize groupId = _groupId;
@synthesize nickname = _nickname;
@synthesize uid = _uid;
@synthesize status = _status;
@synthesize signature = _signature;

@synthesize name = _name;
@synthesize gender = _gender;
@synthesize birthday = _birthday;
@synthesize zodiac = _zodiac;
@synthesize yearof = _yearof;
@synthesize country = _country;
@synthesize province = _province;
@synthesize city = _city;
@synthesize cellphone = _cellphone;
@synthesize telephone = _telephone;
@synthesize email = _email;
@synthesize occupation = _occupation;
@synthesize school = _school;
@synthesize homepage = _homepage;



- (int) getStatus
{
    return _status;
}

- (void) setStatus:(int)status
{
    _status = (int)status;
}

- (void) dealloc
{
    [_groupId release];
    [_nickname release];
    [_uid release];
    [_signature release];
    
    [_name release];
    [_gender release];
    [_birthday release];
    [_zodiac release];
    [_yearof release];
    [_country release];
    [_province release];
    [_city release];
    [_cellphone release];
    [_telephone release];
    [_email release];
    [_occupation release];
    [_school release];
    [_homepage release];
    
    [super dealloc];
}

@end
