#ifndef __IAGROUP_H__
#define __IAGROUP_H__

#include "AMTypes.h"
#include "AIMEnum.h"

#ifdef __cplusplus
extern "C" {
#endif

#define	DEFAULT_GRP_ID			0
#define	BLACK_GRP_ID			-11
#define	RECENT_GRP_ID			-111
#define STRANG_GRP_ID			-1111
#define BIND_ACCOUNT_GRP_ID		-6666	//virtual group
	
/**
 * @brief					get group ID
 */
	AIM_RESULT IAIMGroup_GetID( AMHandle hGroup, AMInt64 *pi64Id);
/**
 * @brief					get group name
 * @param pszName			[in/out] return the pointer to the group name.	
 * @more					name is a const string terminated with '\0'. Do not modify or free it!
 */
	AIM_RESULT IAIMGroup_GetName( AMHandle hGroup, const AMChar **pszName);
/**
 * @brief					count the contacts in this group
 * @bRecursive				count recursively or not.
 * more						if a group is counted recursively, the count result of each child group will be added to the final result.
 */
	AIM_RESULT IAIMGroup_CountContacts( AMHandle hGroup, AMBool bRecursive, AMInt32 *piCount);
/**
 * @brief					count online contacts
 */
	AIM_RESULT IAIMGroup_CountOnlines( AMHandle hGroup, AMBool bRecursive, AMInt32 *piCount);
/**
 * @brief					count unread messages of this group
 */
	AIM_RESULT IAIMGroup_CountUnreadMsgs( AMHandle hGroup, AMBool bRecursive, AMInt32 *piCount);

/**
 * @brief					get the child contacts of this group.
 * @param pphContactArray	[in/out] return an array of contact handles, which should be released by IAIMGroup_ReleaseContacts
 * @param piSize			[in/out] return the array size
 */
	AIM_RESULT IAIMGroup_GetContacts( AMHandle hGroup, AMBool bRecursive, AMHandle **pphContactArray, AMInt32 *piSize);
/**
 * @brief					release the array returned by IAIMGroup_GetContacts
 */
	AIM_RESULT IAIMGroup_ReleaseContacts( AMHandle hGroup, AMHandle *phContactArray, AMInt32 iArraySize);

/**
 * @brief					get the child groups of this group.
 * @param pphGroupArray		[in/out] return an array of group handles, which should be released by IAIMGroup_ReleaseGroups
 * @param piSize			[in/out] return the array size
 */
	AIM_RESULT IAIMGroup_GetGroups( AMHandle hGroup, AMBool bRecursive, AMHandle **pphGroupArray, AMInt32 *piSize);

/**
 * @brief					release the array returned by IAIMGroup_GetGroups
 */
	AIM_RESULT IAIMGroup_ReleaseGroups( AMHandle hGroup, AMHandle *phGroupArray, AMInt32 iArraySize);

#ifdef __cplusplus
};
#endif

#endif // __IAGROUP_H__
