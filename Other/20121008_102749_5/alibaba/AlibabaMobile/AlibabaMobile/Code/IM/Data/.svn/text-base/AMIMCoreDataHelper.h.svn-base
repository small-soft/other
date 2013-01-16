//
//  AMIMCoreDataHelper.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-21.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMIMMessageModel.h"
#import "AMIMUserModel.h"


@interface AMIMCoreDataHelper : NSObject

+ (AMIMCoreDataHelper *) getInstance;
+ (void)destroy;

- (void) saveData;
- (void) rollback;
- (void) reset;

- (void) testWrite;
- (void) testSearch;
- (void) testDelete;
- (void) testModify;

// For IM core data operations
- (void) addOwnerWithUid:(NSString *)uid paswd:(NSString *)passwd autoLogin:(BOOL)autoLogin;
- (void) addUsesrWithUid:(NSString *)uid nickname:(NSString *)nickname groupId:(NSString *)groupId ownerId:(NSString *)ownerId;
- (void) changeUserStatusWithUid:(NSString *)uid status:(int)status ownerId:(NSString *)ownerId;
- (void) addGroupWithGroupId:(NSString *)groupId ownerId:(NSString *)ownerId groupName:(NSString *)groupName parentId:(NSString *)parentId;
- (void) changeUserSignatureWithUid:(NSString *)uid ownerId:(NSString *)ownerId signature:(NSString *)signature;
- (void) changeUserDetailWithUid:(NSString *) uid ownerId:(NSString *)ownerId data:(NSDictionary *)data;
- (void) insertNewMsgWithOwnerId:(NSString *)ownerId msgFrom:(NSString *)msgFrom msgTo:(NSString *)msgTo msgType:(NSNumber *)msgType msgContent:(NSString *)content hasRead:(NSNumber *)hasRead msgTime:(NSNumber*)time msgSequence:(NSNumber *)sequence;
- (NSFetchedResultsController *) getMsgFetchControllerWithOwnerId:(NSString *)ownerId friendId:(NSString *)friendId;
- (void) modifyContactTimeWithOwner:(NSString *)owner friendId:(NSString *)friendId msgTime:(NSNumber *)time;
- (NSFetchedResultsController *) getRecentContactFetchControllerWithOwnerId:(NSString *)ownerId;
- (NSFetchedResultsController *) getSysMsgFetchControllerWithOwnerId:(NSString *)ownerId;
- (NSArray *) getFriendListWithOwnerId:(NSString *)ownerId;
- (AMIMUserModel *) getFriendWithOwnerId:(NSString *)ownerId  uid:(NSString *)uid;
- (NSArray *) getGroupListWithOwnerId:(NSString *)ownerId ;
- (void) changeMsgReadStateWithMsgObj:(AMIMMessageModel *)msgObj;
- (int) getNewMsgNumWithOwnerId:(NSString *)ownerId friendId:(NSString *)friendId;
- (void) changeMsgReadStateWithOwner:(NSString *)ownerId friendId:(NSString *)friendId;
- (void) initFriendStatusWithOwnerId:(NSString *)ownerId ;
- (void) changeGroupOpenState:(BOOL)state ownerId:(NSString *)ownerId groupId:(NSString *)groupId;
- (void) deleteGroupWithOwner:(NSString *)ownerId groupId:(NSString *)groupId;
- (void) deleteFriendWithOwner:(NSString *)ownerId uid:(NSString *)uid;
//- (void) setGroupListWithOwnerId:(NSString *)ownerId groupList:(GroupList_t&)groupList;
//- (void) setFriendListWithOwnerId:(NSString *)ownerId friendList:(ContactList_t&)contactList;


// For log trace core data operations
- (void)appendLog: (NSString *)type;
- (NSArray *)allLogsWaitingForSending;
- (NSArray *)allSentLogs;
- (void)removeAllSentLogs;

@end
