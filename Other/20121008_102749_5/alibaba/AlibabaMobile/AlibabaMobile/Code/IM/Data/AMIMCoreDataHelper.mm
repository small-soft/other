//
//  AMIMCoreDataHelper.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-21.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <WangWangNetLib/LoginDataStructDefs.h>

#import "AMIMCoreDataHelper.h"
#import "Test.h"
#import "AMIMOwnerModel.h"
#import "AMIMUserModel.h"
#import "AMIMGroupModel.h"
#import "AMIMMessageModel.h"
#import "AMLogEntry.h"
#import "InternetDataTool.h"
#import "AMIMDefaultStorageHelper.h"
#import "StringConversionUtils.h"

#define COREDATA_CURRENT_CONTEXT @"CurrentCoreDataContext"

static AMIMCoreDataHelper * _instance = nil;

@interface AMIMCoreDataHelper()

@property (nonatomic, retain) NSPersistentStoreCoordinator * persistentStoreCoordinator;

@end

@implementation AMIMCoreDataHelper

@synthesize persistentStoreCoordinator = _persistentStoreCoordinator;

+ (AMIMCoreDataHelper *) getInstance
{
    @synchronized([AMIMCoreDataHelper class]){
        if(_instance == nil){
            _instance = [[AMIMCoreDataHelper alloc] init];
        }
    }
    return _instance;
}

+ (void)destroy
{
    @synchronized([AMIMCoreDataHelper class]){
        if(_instance){
            [_instance release];
            _instance = nil;
        }
    }
}

- (id) init
{
    self = [super init];
    if(self){
        NSError *error;
        
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);  
        NSString *documentsDirectory = [paths objectAtIndex:0];  
        NSString * path = [NSString stringWithFormat:@"%@/AlibabaMobile.sqlite", documentsDirectory];
        
//        NSString * path = [NSHomeDirectory() stringByAppendingString:@"/Documents/AlibabaMobile.sqlite"];
        NSURL *url = [NSURL fileURLWithPath:path];
        
        NSManagedObjectModel * managedObjectModel = [NSManagedObjectModel mergedModelFromBundles:nil];
        
        self.persistentStoreCoordinator = [[NSPersistentStoreCoordinator alloc] initWithManagedObjectModel:managedObjectModel];
        
        NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:YES], NSMigratePersistentStoresAutomaticallyOption,
            [NSNumber numberWithBool:YES], NSInferMappingModelAutomaticallyOption,
                                 nil];
        if(![self.persistentStoreCoordinator addPersistentStoreWithType:NSSQLiteStoreType configuration:nil URL:url options:options error:&error]){
            NSLog(@"create core data context failed! %@", [error localizedDescription]);
        }
     //   [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(mergeContextChangesForNotification:) name:NSManagedObjectContextDidSaveNotification object:nil]; 
    }                                          
    return self;
}

- (void)mergeContextChangesForNotification:(NSNotification *)aNotification 
{ 
    [[self getContext] mergeChangesFromContextDidSaveNotification:aNotification];  
} 

- (void) dealloc
{
    self.persistentStoreCoordinator = nil;
    
    [super dealloc];
}

- (NSManagedObjectContext *) getContext
{
    NSManagedObjectContext * thisContext = [[[NSThread currentThread] threadDictionary] objectForKey:COREDATA_CURRENT_CONTEXT];
    if ( !thisContext ) {
        thisContext = [[[NSManagedObjectContext alloc] init] autorelease];
//        NSMergePolicy *mergePolicy = [[NSMergePolicy alloc] initWithMergeType:NSOverwriteMergePolicy];
        [thisContext setMergePolicy:NSOverwriteMergePolicy];
        [thisContext setPersistentStoreCoordinator:self.persistentStoreCoordinator]; 
        
        [[[NSThread currentThread] threadDictionary] setObject:thisContext forKey:COREDATA_CURRENT_CONTEXT];
    }
  
    return thisContext;
}


- (void) saveData
{
    NSManagedObjectContext * thisContext =  [self getContext];
    @synchronized(thisContext){
        NSError * error;

        if( ![thisContext save:&error ]){
            NSLog(@"save core data error: %@", [error localizedDescription]);
        }
        
//        if([NSThread currentThread] != [NSThread mainThread]){
//            [[NSNotificationCenter defaultCenter] postNotificationName:NSManagedObjectContextDidSaveNotification object:[self getContext]];
//        }
    }
}

- (void) rollback
{
    NSManagedObjectContext * thisContext =  [self getContext];
    @synchronized(thisContext){
        [thisContext rollback];
    }
}

- (void) reset
{
    NSManagedObjectContext * thisContext =  [self getContext];
    @synchronized(thisContext){
        [thisContext reset];
    }
}

- (void) testWrite
{
    Test * test = (Test *)[NSEntityDescription insertNewObjectForEntityForName:@"Test" inManagedObjectContext:[self getContext]];
    test.id = @"55912";
    test.name = @"xiejin";
    test.age = [NSNumber numberWithInt:23];
    
    [self saveData];
}

- (void) testSearch
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"Test" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"age" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    
    NSArray * results = fetchedResultsController.fetchedObjects;
    for(Test * test in results){
        NSLog(@"SearchTest id:%@ name:%@ age:%d",test.id, test.name, test.age.intValue );
    }
     
    [fetchedResultsController release];
    [fetchRequest release];
}

- (void) testDelete
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"Test" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"age" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }

    NSArray * results = fetchedResultsController.fetchedObjects;
    if(results.count <=0 ){
        NSLog(@"nothing to delete!");
    }

    for(Test * test in results){
        [[self getContext] deleteObject:test]; 
    }
#warning 修改人 孟希羲
    //[fetchRequest release];
    [fetchedResultsController release];
    [self saveData ];
}

- (void) testModify
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"Test" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"age" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    NSArray * results = fetchedResultsController.fetchedObjects;
    if(results.count <=0 ){
        NSLog(@"nothing !");
    }
    
    for(Test * test in results){
        test.age = [NSNumber numberWithInt:10];
    }
#warning 修改人 孟希羲
    //[fetchRequest release];
    [fetchedResultsController release];
    [self saveData ];
}

#pragma ww
- (void) addOwnerWithUid:(NSString *)uid paswd:(NSString *)passwd autoLogin:(BOOL)autoLogin
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMOwnerModel" inManagedObjectContext:[self getContext] ]];
    NSError * error;
    
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"uid" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];

    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"uid = %@", uid];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    
    NSArray * results = fetchedResultsController.fetchedObjects;
    if(results != nil && results.count > 0){
        
        AMIMOwnerModel * owner = [results objectAtIndex:0];
        owner.uid = uid;
        owner.passwd = passwd;
        owner.autoLogin = [NSNumber numberWithBool:autoLogin];
        
        [self saveData];
    }else{
       
        [self insertNewOwnerWithUid:uid paswd:passwd autoLogin:autoLogin];
    }
    
}

- (void) insertNewOwnerWithUid:(NSString *)uid paswd:(NSString *)passwd autoLogin:(BOOL)autoLogin
{
    AMIMOwnerModel * owner = (AMIMOwnerModel *)[NSEntityDescription insertNewObjectForEntityForName:@"AMIMOwnerModel" inManagedObjectContext:[self getContext]];
    owner.uid = uid;
    owner.passwd = passwd;
    owner.status = [NSNumber numberWithInt:1];
    owner.autoLogin = [NSNumber numberWithBool:YES];
    owner.soundNotice = [NSNumber numberWithBool:YES];
    owner.shakeNotice = [NSNumber numberWithBool:YES];
    
    [self saveData];
}

- (void) addUsesrWithUid:(NSString *)uid nickname:(NSString *)nickname groupId:(NSString *)groupId ownerId:(NSString *)ownerId;
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext] ]];
    NSError * error;
    
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"uid" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"uid = %@ and ownerId = %@", uid, ownerId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    
    NSArray * results = fetchedResultsController.fetchedObjects;
    if(results != nil && results.count > 0){
        AMIMUserModel * user = [results objectAtIndex:0];

        user.nickname = nickname;
        user.groupId = groupId;
        user.status = [NSNumber numberWithInt:0];

        [self saveData];
    }else{
        
        [self insertNewUserWithUid:uid nickname:nickname groupId:groupId ownerId:ownerId];
    }
}

- (void) insertNewUserWithUid:(NSString *)uid nickname:(NSString *)nickname groupId:(NSString *)groupId ownerId:(NSString *)ownerId
{
    AMIMUserModel * user = (AMIMUserModel *)[NSEntityDescription insertNewObjectForEntityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext]];
    user.uid = uid;
    user.status = [NSNumber numberWithInt:0];
    user.nickname = nickname;
    user.groupId = groupId;
    user.ownerId = ownerId;
    user.contactTime = [NSNumber numberWithInt:0];
    
    [self saveData];
}

- (void) changeUserStatusWithUid:(NSString *)uid status:(int)status ownerId:(NSString *)ownerId
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"uid" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"uid = %@ and ownerId = %@", uid, ownerId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    //NSManagedObjectContext * thisContext =  [self getContext];
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    NSArray * results = fetchedResultsController.fetchedObjects;
    if( results == nil || results.count <=0 ){
        NSLog(@"nothing !");
        return;
    }
    
    for(AMIMUserModel * user in results){
        user.status = [NSNumber numberWithInt:status];
    }
    
    [self saveData ];
}

- (void) addGroupWithGroupId:(NSString *)groupId ownerId:(NSString *)ownerId groupName:(NSString *)groupName parentId:(NSString *)parentId
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMGroupModel" inManagedObjectContext:[self getContext] ]];
    NSError * error;
    
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"groupId" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"groupId = %@ and ownerId = %@", groupId, ownerId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    
    NSArray * results = fetchedResultsController.fetchedObjects;
    if(results != nil && results.count > 0){
        
        AMIMGroupModel * group = [results objectAtIndex:0];
        group.groupName = groupName;
        group.parentId = parentId;
        
        [self saveData];
    }else{
        
        [self insertNewGroupWithGroupId:groupId ownerId:ownerId groupName:groupName parentId:parentId];
    }

}

- (void) insertNewGroupWithGroupId:(NSString *)groupId ownerId:(NSString *)ownerId groupName:(NSString *)groupName parentId:(NSString *)parentId
{
    AMIMGroupModel * group = (AMIMGroupModel *)[NSEntityDescription insertNewObjectForEntityForName:@"AMIMGroupModel" inManagedObjectContext:[self getContext]];
    group.groupId = groupId;
    group.groupName = groupName;
    group.parentId = parentId;
    group.ownerId = ownerId;
    
    [self saveData];
}

- (void) changeUserSignatureWithUid:(NSString *)uid ownerId:(NSString *)ownerId signature:(NSString *)signature
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"uid" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"uid = %@ and ownerId = %@", uid, ownerId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    NSArray * results = fetchedResultsController.fetchedObjects;
    if(results.count <=0 ){
        NSLog(@"nothing !");
    }
    
    for(AMIMUserModel * user in results){
        user.signature = signature;
    }
    
    [self saveData ];
}

- (void) changeUserDetailWithUid:(NSString *) uid ownerId:(NSString *)ownerId data:(NSDictionary *)data
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"uid" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"uid = %@ and ownerId = %@", uid, ownerId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    NSArray * results = fetchedResultsController.fetchedObjects;
    if(results.count <=0 ){
        [self insertNewUserWithUid:uid nickname:[uid substringFromIndex:8] groupId:[NSNumber numberWithInt:-2 ].stringValue ownerId:ownerId];
        [self changeUserDetailWithUid:uid ownerId:ownerId data:data];
    }else{
    
        for(AMIMUserModel * user in results){
            user.name =  [data objectForKey:NSLocalizedString(@"Name", nil)];
            user.gender = [data objectForKey:NSLocalizedString(@"Gender", nil)];
            user.birthday = [data objectForKey:NSLocalizedString(@"Birthday", nil)];
            user.zodiac = [data objectForKey:NSLocalizedString(@"Zodiac Sign", nil)];
            user.yearof = [data objectForKey:NSLocalizedString(@"Year of", nil)] ;
            user.country = [data objectForKey:NSLocalizedString(@"Country", nil)];
            user.province = [data objectForKey:NSLocalizedString(@"State/Province", nil)];
            user.city = [data objectForKey:NSLocalizedString(@"City", nil)];
            user.cellphone = [data objectForKey:NSLocalizedString(@"Cell Phone", nil)] ;
            user.telephone = [data objectForKey:NSLocalizedString(@"Tel", nil)] ;
            user.email = [data objectForKey:NSLocalizedString(@"Email Address", nil)];
            user.occupation = [data objectForKey:NSLocalizedString(@"Occupation", nil)];
            user.school = [data objectForKey:NSLocalizedString(@"School", nil)];
            user.homepage = [data objectForKey:NSLocalizedString(@"Homepage", nil)];
        }
    
     [self saveData ];
    }
  
}

- (void) insertNewMsgWithOwnerId:(NSString *)ownerId msgFrom:(NSString *)msgFrom msgTo:(NSString *)msgTo msgType:(NSNumber *)msgType msgContent:(NSString *)content hasRead:(NSNumber *)hasRead msgTime:(NSNumber*)time msgSequence:(NSNumber *)sequence
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMMessageModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"msgTime" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and msgFrom = %@ and msgTo = %@ and msgType = %@ and msgContent = %@ and msgTime = %@",  ownerId, msgFrom, msgTo, msgType.stringValue, content, time.stringValue];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    NSArray * results = fetchedResultsController.fetchedObjects;
    if(results != nil &&  results.count >0 ){
        NSLog(@"nothing !");
    }else{
        AMIMMessageModel * msg = (AMIMMessageModel *)[NSEntityDescription insertNewObjectForEntityForName:@"AMIMMessageModel" inManagedObjectContext:[self getContext]];
        msg.ownerId = ownerId;
        msg.msgFrom = msgFrom;
        msg.msgTo = msgTo;
        msg.msgType = msgType;
        msg.msgContent =content;
        msg.hasRead = hasRead;
        msg.msgSequence = sequence;
        msg.msgTime = time;
        
        [self saveData];

    }

}

- (void) deleteFriendWithOwner:(NSString *)ownerId uid:(NSString *)uid
{
    NSFetchRequest *request = [[NSFetchRequest alloc] init];
    [request setEntity:[NSEntityDescription entityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext]]];
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and uid = %@",ownerId, uid];
    [request setPredicate:predicate];
    NSSortDescriptor *sortDescriptor = [[NSSortDescriptor alloc] initWithKey:@"uid" ascending:NO];
    [request setSortDescriptors:[NSArray arrayWithObject:sortDescriptor]];
    [sortDescriptor release];
    NSError *error = nil;
    NSArray *result = [[self getContext] executeFetchRequest:request error:&error];
    if(result != nil && result.count >0){
        int size = result.count;
        for(int i=0; i<size; i++){
            AMIMUserModel * user = [result objectAtIndex:i];
            user.groupId = [NSNumber numberWithInt:-2 ].stringValue;
        }
        [self saveData];
       
    }
}

- (void) deleteGroupWithOwner:(NSString *)ownerId groupId:(NSString *)groupId
{
    NSFetchRequest *request = [[NSFetchRequest alloc] init];
    [request setEntity:[NSEntityDescription entityForName:@"AMIMGroupModel" inManagedObjectContext:[self getContext]]];
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and groupId = %@",ownerId, groupId];
    [request setPredicate:predicate];
    NSSortDescriptor *sortDescriptor = [[NSSortDescriptor alloc] initWithKey:@"groupId" ascending:NO];
    [request setSortDescriptors:[NSArray arrayWithObject:sortDescriptor]];
    [sortDescriptor release];
    NSError *error = nil;
    NSArray *result = [[self getContext] executeFetchRequest:request error:&error];
    if(result != nil && result.count >0){
        int size = result.count;
        for(int i=0; i<size; i++){
            AMIMGroupModel * group = [result objectAtIndex:i];
            [[self getContext] deleteObject:group];
        }
        [self saveData];
        [self deleteUserWithOwner:ownerId groupId:groupId];
    }
}

- (void) deleteUserWithOwner:(NSString *)ownerId groupId:(NSString *)groupId
{
    NSFetchRequest *request = [[NSFetchRequest alloc] init];
    [request setEntity:[NSEntityDescription entityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext]]];
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and groupId = %@",ownerId, groupId];
    [request setPredicate:predicate];
    NSSortDescriptor *sortDescriptor = [[NSSortDescriptor alloc] initWithKey:@"uid" ascending:NO];
    [request setSortDescriptors:[NSArray arrayWithObject:sortDescriptor]];
    [sortDescriptor release];
    NSError *error = nil;
    NSArray *result = [[self getContext] executeFetchRequest:request error:&error];
    if(result != nil && result.count >0){
        int size = result.count;
        for(int i=0; i<size; i++){
            AMIMUserModel * user = [result objectAtIndex:i];
            user.groupId = [NSNumber numberWithInt:0].stringValue;
        }
        [self saveData];
    }
}


- (NSFetchedResultsController *) getMsgFetchControllerWithOwnerId:(NSString *)ownerId friendId:(NSString *)friendId
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMMessageModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"msgTime" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and (msgType = %d or msgType = %d) and (msgFrom = %@ or msgTo = %@)", ownerId, TEXT_MSG_NORMAL_TEXT, TEXT_MSG_AUTO_REPLY, friendId, friendId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil] autorelease];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
        return nil;
    }
    
    return fetchedResultsController;

}

- (NSFetchedResultsController *) getSysMsgFetchControllerWithOwnerId:(NSString *)ownerId
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMMessageModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"msgTime" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and msgType = %d ", ownerId,TEXT_MSG_CONTACT];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil] autorelease];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
        return nil;
    }
    
    return fetchedResultsController;
    
}

- (NSFetchedResultsController *) getRecentContactFetchControllerWithOwnerId:(NSString *)ownerId 
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"contactTime" ascending:NO];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and contactTime>0", ownerId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil] autorelease];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
        return nil;
    }
    
    return fetchedResultsController;
    
}


- (void) modifyContactTimeWithOwner:(NSString *)owner friendId:(NSString *)friendId msgTime:(NSNumber *)time
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"uid" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"uid = %@ and ownerId = %@", friendId, owner];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    if(fetchedResultsController != nil && fetchedResultsController.fetchedObjects != nil && fetchedResultsController.fetchedObjects.count >0){
        NSArray * results = fetchedResultsController.fetchedObjects;
        for(AMIMUserModel * user in results){
            user.contactTime = time;
        }
        
        [self saveData];
    }else{
        [self addUsesrWithUid:friendId nickname:[friendId substringFromIndex:8] groupId:@"-2" ownerId:owner];
        [self modifyContactTimeWithOwner:owner friendId:friendId msgTime:time];
    }
    
}

- (NSArray *) getFriendListWithOwnerId:(NSString *)ownerId 
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"uid" ascending:NO];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and uid != %@", ownerId,ownerId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil] autorelease];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
        return nil;
    }
    
    if(fetchedResultsController!=nil && fetchedResultsController.fetchedObjects != nil){
        return fetchedResultsController.fetchedObjects;
    }
    
    return nil;
    
    
    
}

- (AMIMUserModel *) getFriendWithOwnerId:(NSString *)ownerId  uid:(NSString *)uid
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"uid" ascending:NO];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and uid = %@", ownerId,uid];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil] autorelease];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
        return nil;
    }
    
    if(fetchedResultsController!=nil && fetchedResultsController.fetchedObjects != nil && fetchedResultsController.fetchedObjects.count > 0){
        return [fetchedResultsController.fetchedObjects objectAtIndex:0];
    }
    
    return nil;
    
}

- (NSArray *) getGroupListWithOwnerId:(NSString *)ownerId 
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMGroupModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"groupId" ascending:NO];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"ownerId = %@", ownerId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil] autorelease];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
        return nil;
    }
    
    if(fetchedResultsController!=nil && fetchedResultsController.fetchedObjects != nil){
        return fetchedResultsController.fetchedObjects;
    }
    
    return nil;
}

- (void) changeMsgReadStateWithMsgObj:(AMIMMessageModel *)msgObj
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMMessageModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"msgTime" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and msgFrom = %@ and msgTo = %@ and msgType = %@ and msgTime = %@ and msgSequence = %@ and msgContent = %@", msgObj.ownerId, msgObj.msgFrom, msgObj.msgTo, msgObj.msgType, msgObj.msgTime, msgObj.msgSequence, msgObj.msgContent];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    NSArray * results = fetchedResultsController.fetchedObjects;
    if(results.count <=0 ){
        NSLog(@"nothing !");
    }
    
    for(AMIMMessageModel * msg in results){
        msg.hasRead = [NSNumber numberWithBool:YES];
    }
    
    [self saveData ];
}

- (void) changeMsgReadStateWithOwner:(NSString *)ownerId friendId:(NSString *)friendId
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMMessageModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"msgTime" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and msgFrom = %@", ownerId, friendId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    NSArray * results = fetchedResultsController.fetchedObjects;
    if(results.count <=0 ){
        NSLog(@"nothing !");
    }
    
    for(AMIMMessageModel * msg in results){
        msg.hasRead = [NSNumber numberWithBool:YES];
    }
    
    [self saveData ];
}

- (int) getNewMsgNumWithOwnerId:(NSString *)ownerId friendId:(NSString *)friendId
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMMessageModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"msgTime" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and msgFrom = %@ and hasRead = NO", ownerId, friendId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
    }
    
    NSArray * results = fetchedResultsController.fetchedObjects;
    if(results.count <=0 ){
        NSLog(@"nothing !");
        return 0;
    }
    
    
    return results.count;
}

#pragma log
-(void)appendLog: (NSString *)type {
    if ([self getContext] == nil) {
        return;
    }
    
    AMLogEntry *log = (AMLogEntry *)[NSEntityDescription insertNewObjectForEntityForName:@"AMLogEntry" inManagedObjectContext:[self getContext]];
    
    log.createAt = [NSDate date];
    log.content = type;
    log.sent = [NSNumber numberWithBool:NO];
    
    [self saveData];
}

- (NSArray *)allLogsWaitingForSending {
    if ([self getContext] == nil) {
        return nil;
    }
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMLogEntry" inManagedObjectContext:[self getContext] ]];
    
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"createAt" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];

    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"sent = %@", [NSNumber numberWithBool:NO]];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
   // NSFetchedResultsController * fetchedResultsController = [[[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil] autorelease];
    NSFetchedResultsController * fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil];
    

        if(![fetchedResultsController performFetch:&error ]){
            NSLog(@"search core data failed: %@", [error localizedDescription]);
            return nil;
        } 
    
    if(fetchedResultsController!=nil && fetchedResultsController.fetchedObjects != nil){
        NSArray *logs = fetchedResultsController.fetchedObjects;
        NSMutableArray *result = [[[NSMutableArray alloc] init] autorelease];
        for (AMLogEntry *log in logs) {
            NSMutableDictionary *md = [[[NSMutableDictionary alloc] init] autorelease];
            [md setObject:log.identifier forKey:@"id"];
            [md setObject:log.content forKey:@"content"];
            [md setObject:[NSString stringWithFormat:@"%@",[NSNumber numberWithLong:[log.createAt timeIntervalSince1970]]] forKey:@"logTime"];
            [md setObject:log.sent forKey:@"hasSend"];
            
            // Mark as sent, not commited
            log.sent = [NSNumber numberWithBool:YES];
            
            [result addObject:md];
        }
        
#warning 修改人孟希羲
        
        [descriptors release];
        //[fetchRequest release];
        [fetchedResultsController release];
        NSLog(@"descriptors : %d, fetchRequest : %d.",[descriptors retainCount],[fetchRequest retainCount]);
        return result;
    }
#warning 修改人孟希羲
    //[descriptors release];
    //[fetchRequest release];
    return nil;
}

- (NSArray *)allSentLogs {
    if ([self getContext] == nil) {
        return nil;
    }
    
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMLogEntry" inManagedObjectContext:[self getContext] ]];
    
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"createAt" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"sent = %@", [NSNumber numberWithBool:YES]];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil] autorelease];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
        return nil;
    }
    
    if(fetchedResultsController!=nil && fetchedResultsController.fetchedObjects != nil){
        return fetchedResultsController.fetchedObjects;
    }
#warning 修改人孟希羲
    //[fetchRequest release];
    return nil;
}

- (void)removeAllSentLogs {
    if ([self getContext] == nil) {
        return;
    }
    
    NSArray *logs = [self allSentLogs];
    for ( AMLogEntry *log in logs ) {
        [[self getContext] deleteObject: log];
    }
}

- (void) changeGroupOpenState:(BOOL)state ownerId:(NSString *)ownerId groupId:(NSString *)groupId
{
    if ([self getContext] == nil) {
        return;
    }
    
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMGroupModel" inManagedObjectContext:[self getContext] ]];
    
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"groupId" ascending:YES];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and groupId = %@", ownerId, groupId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil] autorelease];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
        return;
    }
    
    if(fetchedResultsController!=nil && fetchedResultsController.fetchedObjects != nil){
        int size = fetchedResultsController.fetchedObjects.count;
        for(int i=0; i<size;i++){
            AMIMGroupModel * group = [fetchedResultsController.fetchedObjects objectAtIndex:i];
            group.opened = [NSNumber numberWithBool:state];
        
        }
        [self saveData];
    }

}

- (void) initFriendStatusWithOwnerId:(NSString *)ownerId 
{
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] init];
    [fetchRequest setEntity:[NSEntityDescription entityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext] ]];
    NSSortDescriptor * sortDescriptor= [[NSSortDescriptor alloc] initWithKey:@"uid" ascending:NO];
    NSArray * descriptors = [NSArray arrayWithObjects:sortDescriptor , nil];
    [fetchRequest setSortDescriptors:descriptors];
    [sortDescriptor release];
    
    NSPredicate * predicate;  
    predicate = [NSPredicate predicateWithFormat:@"ownerId = %@ and uid != %@", ownerId,ownerId];  
    [fetchRequest setPredicate:predicate];
    [predicate release];
    
    NSError * error;
    
    NSFetchedResultsController * fetchedResultsController = [[[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:[self getContext] sectionNameKeyPath:nil cacheName:nil] autorelease];
    
    if(![fetchedResultsController performFetch:&error ]){
        NSLog(@"search core data failed: %@", [error localizedDescription]);
        return;
    }
    
    if(fetchedResultsController!=nil && fetchedResultsController.fetchedObjects != nil){
        int size = fetchedResultsController.fetchedObjects.count;
        for(int i=0; i<size;i++){
            AMIMUserModel * user = [fetchedResultsController.fetchedObjects objectAtIndex:i];
            user.status = [NSNumber numberWithInt: 0];
        }
        [self saveData];
    }
    
    
}

- (void) setGroupListWithOwnerId:(NSString *)ownerId groupList:(GroupList_t&)groupList 
{
    //删除本地没有的分组
    NSArray * groups = [[AMIMCoreDataHelper getInstance] getGroupListWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId]];
    
    int size = groups.count;
    for(int i=0; i<size; i++){
        AMIMGroupModel * group = [groups objectAtIndex:i];
        BOOL existed = NO;
        for (GroupList_t::iterator item = groupList.begin(); item != groupList.end(); item++) {
            if([[NSNumber numberWithInt:item->m_groupId].stringValue isEqualToString:group.groupId]){
                existed = YES;
                
                group.groupName = CStr2NSStr(item->m_groupName);
                group.parentId = [NSNumber numberWithInt:item->m_parentId].stringValue;
                
                groupList.erase(item);
                
                break;
            }
            
        }
        
        if(!existed){
            [[self getContext] deleteObject:group];
        }
    }
    
    //更新分组
    for (GroupList_t::const_iterator item = groupList.begin(); item != groupList.end(); item++) {
        
        AMIMGroupModel * group = (AMIMGroupModel *)[NSEntityDescription insertNewObjectForEntityForName:@"AMIMGroupModel" inManagedObjectContext:[self getContext]];
        group.groupId = [NSNumber numberWithInt:item->m_groupId].stringValue;
        group.groupName = CStr2NSStr(item->m_groupName);
        group.parentId = [NSNumber numberWithInt:item->m_parentId].stringValue;
        group.ownerId = [AMIMDefaultStorageHelper getLastLoginedUserId];
    }
    
    [self saveData];
}

- (void) setFriendListWithOwnerId:(NSString *)ownerId friendList:(ContactList_t&)contactList 
{
    //删除本地没有的用户
    NSArray * users = [[AMIMCoreDataHelper getInstance] getFriendListWithOwnerId:[AMIMDefaultStorageHelper getLastLoginedUserId]];
    int size = users.count;
    for(int i=0; i<size; i++){
        AMIMUserModel * user = [users objectAtIndex:i];
        BOOL existed = NO;
        for (ContactList_t::iterator item = contactList.begin(); item != contactList.end(); item++) {
            if([CStr2NSStr(item->m_strUid) isEqualToString:user.uid]){
                existed = YES;
                user.nickname = CStr2NSStr(item->m_strNickName);
                user.groupId = [NSNumber numberWithLongLong:item->m_groupId].stringValue;
                contactList.erase(item);
                break;
            }
            
        }
        
        if(!existed){

            [[self getContext] deleteObject:user];
        }
    }
    
    for (ContactList_t::iterator item = contactList.begin(); item != contactList.end(); item++) {
        
        AMIMUserModel * user = (AMIMUserModel *)[NSEntityDescription insertNewObjectForEntityForName:@"AMIMUserModel" inManagedObjectContext:[self getContext]];
        user.uid = CStr2NSStr(item->m_strUid);
        user.status = [NSNumber numberWithInt:0];
        user.nickname = CStr2NSStr(item->m_strNickName);
        user.groupId = [NSNumber numberWithLongLong:item->m_groupId].stringValue;
        user.ownerId = [AMIMDefaultStorageHelper getLastLoginedUserId];
        user.contactTime = [NSNumber numberWithInt:0];
        
        
    }

    [self saveData];
}


@end
