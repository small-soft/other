//
//  AMIMUserDefault.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-19.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <WangWangNetLib/LoginDataStructDefs.h>
#import "AMIMUserDefault.h"

@implementation AMIMUserDefault

@synthesize uid = _uid;
@synthesize passwd = _passwd;
@synthesize status = _status;
@synthesize autoLogin = _autoLogin;
@synthesize soundNotice = _soundNotice;
@synthesize shakeNotice = _shakeNotice;
@synthesize groupListUpdated = _groupListUpdated;
@synthesize friendListUpdated = _friendListUpdated;
@synthesize groupListTimestamp = _groupListTimestamp;
@synthesize friendListTimestamp = _friendListTimestamp;
@synthesize blackListUpdated = _blackListUpdated;
@synthesize blackListTimestamp = _blackListTimestamp;
@synthesize quickWords = _quickWords;
@synthesize isSpecialPassWord = _isSpecialPassWord;

- (id) initWithCoder: (NSCoder *)coder  
{  
    if (self = [super init])  
    {  
        _uid = [[coder decodeObjectForKey:@"uid"] retain];  
        _passwd = [[coder decodeObjectForKey:@"passwd"] retain];  
        _status = ((NSNumber *)[coder decodeObjectForKey:@"status"]).intValue; 
        _autoLogin = ((NSNumber *)[coder decodeObjectForKey:@"autoLogin"]).boolValue; 
        _soundNotice = ((NSNumber *)[coder decodeObjectForKey:@"soundNotice"]).boolValue; 
        _shakeNotice = ((NSNumber *)[coder decodeObjectForKey:@"shakeNotice"]).boolValue;
        _groupListUpdated = ((NSNumber *)[coder decodeObjectForKey:@"groupListUpdated"]).boolValue;
        _friendListUpdated = ((NSNumber *)[coder decodeObjectForKey:@"friendListUpdated"]).boolValue;
        _blackListUpdated = ((NSNumber *)[coder decodeObjectForKey:@"blackListUpdated"]).boolValue;
         _groupListTimestamp = ((NSNumber *)[coder decodeObjectForKey:@"groupListTimestamp"]).intValue; 
         _friendListTimestamp = ((NSNumber *)[coder decodeObjectForKey:@"friendListTimestamp"]).intValue; 
         _blackListTimestamp = ((NSNumber *)[coder decodeObjectForKey:@"blackListTimestamp"]).intValue;
        _quickWords = ((NSMutableArray *)[coder decodeObjectForKey:@"quickWords"]);
        _isSpecialPassWord = ((NSNumber *)[coder decodeObjectForKey:@"isSpecialPassWord"]).boolValue;
    }  
    return self;  
}  
- (void) encodeWithCoder: (NSCoder *)coder  
{  
    [coder encodeObject:_uid forKey:@"uid"];  
    [coder encodeObject:_passwd forKey:@"passwd"];
    [coder encodeObject:[NSNumber numberWithInt: _status ] forKey:@"status"];
    [coder encodeObject:[NSNumber numberWithBool: _autoLogin] forKey:@"autoLogin"];
    [coder encodeObject:[NSNumber numberWithBool:_soundNotice] forKey:@"soundNotice"];
    [coder encodeObject:[NSNumber numberWithBool:_shakeNotice] forKey:@"shakeNotice"];
    [coder encodeObject:[NSNumber numberWithBool:_groupListUpdated] forKey:@"groupListUpdated"];
    [coder encodeObject:[NSNumber numberWithBool:_friendListUpdated] forKey:@"friendListUpdated"];
    [coder encodeObject:[NSNumber numberWithBool:_blackListUpdated] forKey:@"blackListUpdated"];
    [coder encodeObject:[NSNumber numberWithInt: _groupListTimestamp ] forKey:@"groupListTimestamp"];
    [coder encodeObject:[NSNumber numberWithInt: _friendListTimestamp ] forKey:@"friendListTimestamp"];
    [coder encodeObject:[NSNumber numberWithInt: _blackListTimestamp ] forKey:@"blackListTimestamp"];
    [coder encodeObject:_quickWords forKey:@"quickWords"];
    [coder encodeObject:[NSNumber numberWithBool: _isSpecialPassWord] forKey:@"isSpecialPassWord"];
}  

-(void) dealloc
{
    [_uid release];
    [_passwd release];
    [_quickWords release];
    
    [super dealloc];
}

- (id) init
{
    self = [super init];
    if(self){
        _uid = nil;
        _passwd = nil;
        _status = IMPREDEFSTATUS_FREE;
        _autoLogin = NO;
        _soundNotice = NO;
        _shakeNotice = NO;
        _groupListUpdated = NO;
        _friendListUpdated = NO;
        _groupListTimestamp = 0;
        _friendListTimestamp = 0;
        _blackListUpdated = NO;
        _blackListTimestamp = 0;
        _quickWords = nil;
        _isSpecialPassWord = NO;
    }
    return self;
}



@end
