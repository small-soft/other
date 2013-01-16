#ifndef __IACONTACT_H__
#define __IACONTACT_H__

#include "AMTypes.h"
#include "AIMEnum.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief					get contact long id
 * @param pszID				[in/out] return the pointer to the long ID.	
 * @more					Long ID is a const string of Contact, terminated with '\0'. Do not modify or free it!
 */
	AIM_RESULT IAIMContact_GetID( AMHandle hContact, const AMChar **pszID);

/**
 * @brief					get contact name.
 * @param pszName			[in/out] return the pointer to the name.	
 * @more					name is a const string terminated with '\0'. Do not modify or free it!
 */
	AIM_RESULT IAIMContact_GetName( AMHandle hContact, const AMChar **pszName);

/**
 * @brief					get the last chat-message body of this contact. may be AMNULL
 * @param pszMsg			[in/out] return the pointer to the lastMsg.	
 * @more					lastMsg is a const string terminated with '\0'. Do not modify or free it!
 */
	AIM_RESULT IAIMContact_GetLastMsg( AMHandle hContact, const AMChar **pszMsg);
/**
 * @brief					get signature of this contact. may be AMNULL
 * @param pszSignature		[in/out] return the pointer to the signature.	
 * @more					signature is a const string terminated with '\0'. Do not modify or free it!
 */
	AIM_RESULT IAIMContact_GetSignature( AMHandle hContact, const AMChar **pszSignature);
	
/**
 * @brief					get portrait file path of this contact. may be AMNULL
 * @param pszFilePath		[in/out] return the pointer to the portrait filepath.	
 * @more					filepath is a const string terminated with '\0'. Do not modify or free it!
 */
	AIM_RESULT IAIMContact_GetPortrait( AMHandle hContact, const AMChar **pszFilePath);

/**
 * @brief					get contact type.
 */
	AIM_RESULT IAIMContact_GetType( AMHandle hContact, AIM_ACCOUNT_TYPE *pType);

/**
 * @brief					get the parent group of this contact.
 */
	AIM_RESULT IAIMContact_GetParentGroup( AMHandle hContact, AMHandle *phGroup);

/**
 * @brief					get presence.
 */
	AIM_RESULT IAIMContact_GetPresence( AMHandle hContact, AIM_PRESENCE *pePresence);

/**
 * @brief					is in black group
 */
	AIM_RESULT IAIMContact_IsBlack( AMHandle hContact, AMBool *pbBlack);

/**
 * @brief					is a stranger
 */
	AIM_RESULT IAIMContact_IsStrange( AMHandle hContact, AMBool *pbStrange);

/**
 * @brief					is a recent contact
 */
	AIM_RESULT IAIMContact_IsRecent( AMHandle hContact, AMBool *pbRecent);

#ifdef __cplusplus
};
#endif
#endif // __IACONTACT_H__


