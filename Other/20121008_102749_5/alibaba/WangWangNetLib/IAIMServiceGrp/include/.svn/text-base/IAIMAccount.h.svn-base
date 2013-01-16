#ifndef __IACCOUNT_H__
#define __IACCOUNT_H__

#include "AMTypes.h"
#include "AIMEnum.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief					Get the long ID from an Account handle.
 * @param hAccount			Account handle
 * @param pszAccountId		[in/out] return the pointer to the long ID.	
 * @more					Long ID is a const string of Account, terminated with '\0'. Do not modify or free it!
 */
	AIM_RESULT IAIMAccount_GetId( AMHandle hAccount, const AMChar **pszId);
/**
 * @brief					Get the name from an IAIMAccount handle
 * @param pszName			[in/out] return the pointer to the name.	
 * @more					Name is a const string of Account, terminated with '\0'. Do not modify or free it!
 */
	AIM_RESULT IAIMAccount_GetName( AMHandle hAccount, const AMChar **pszName);
	
/**
 * @brief					Get the account type
 * @param pType				[in/out] return the type.
 */
	AIM_RESULT IAIMAccount_GetType( AMHandle hAccount, AIM_ACCOUNT_TYPE *pType);
	
/**
* @brief					Get Default Setting.
* @param pSetting			[in/out] A pointer to AIM_ACCOUNT_SETTING.
*							the AIM_ACCOUNT_SETTING pointed by pSetting will be filled.
*/
	AIM_RESULT IAIMAccount_GetSetting( AMHandle hAccount, AIM_ACCOUNT_SETTING *pSetting );

/**
* @brief					Get Presence		
*/
	AIM_RESULT IAIMAccount_GetPresence( AMHandle hAccount, AIM_PRESENCE *pPresence);
/**
 * @brief					get savePwd Setting				
 */
	AIM_RESULT IAIMAccount_IsSavePwd( AMHandle hAccount, AMBool *pIsSave);
/**
 * @brief					get Vibrate Setting
 */
	AIM_RESULT IAIMAccount_IsVibrate( AMHandle hAccount, AMBool *pIsVibrate);
/**
 * @brief					get Mute Setting
 */
	AIM_RESULT IAIMAccount_IsMute( AMHandle hAccount, AMBool *pIsMute);	

/**
 * @brief					Whether is E-Customer
 * @param hAccount		
 */
	AIM_RESULT IAIMAccount_IsECustomer( AMHandle hAccount, AMBool *pbECustomer);	
	
/**
 * @brief					Whether E-Customer is hung up now.
 * @param hAccount			
 */
	AIM_RESULT IAIMAccount_IsHungup( AMHandle hAccount, AMBool *pbHungup);
	
/**
 * @brief					Get signature
 * @param pszName			[in/out] return the pointer to the signature.	
 * @more					signature is a const string of Account, terminated with '\0'. Do not modify or free it!
 */
	AIM_RESULT IAIMAccount_GetSignature( AMHandle hAccount, const AMChar **pszSignature);
/**
* @brief					Get Password token
* @param pszName			[in/out] return the pointer to the pwdToken.	
* @more						pwdToken is a const string of Account, terminated with '\0'. Do not modify or free it!
*/
	AIM_RESULT IAIMAccount_GetPwdToken(AMHandle hAccount, const AMChar **pszToken);
/**
* @brief					Get web token
* @param pszName			[in/out] return the pointer to the WebToken.	
* @more						webToken is a const string of Account, terminated with '\0'. Do not modify or free it!
*/
	AIM_RESULT IAIMAccount_GetWebToken(AMHandle hAccount, const AMChar **pszToken);

	
#ifdef __cplusplus
};
#endif

#endif // __IACCOUNT_H__